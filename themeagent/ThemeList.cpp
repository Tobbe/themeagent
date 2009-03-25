#include "ThemeList.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

ThemeList::ThemeList(string themesDir)
{
	string searchDir = themesDir + "\\*";
	string searchFile;

	WIN32_FIND_DATA wfd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	HANDLE hFindFile = INVALID_HANDLE_VALUE;

	hFind = FindFirstFile(searchDir.c_str(), &wfd);

	if (hFind != INVALID_HANDLE_VALUE) {
		//Loop through all subfolders to the themes dir
		while (FindNextFile(hFind, &wfd) != 0) {
			if (isDir(wfd)) {
				string fullThemePath = themesDir + "\\" + wfd.cFileName;

				//Check if the folder contains a theme.rc
				if (fileExists(fullThemePath + "\\theme.rc")) {
					//This is most likely a themes dir

					RCFile rc(fullThemePath + "\\theme.rc");
					themeList.push_back(Theme(fullThemePath, rc));
				}
			}
		}
	}
}

bool ThemeList::isDir(const WIN32_FIND_DATA &wfd) const
{
	return wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
		strcmp(wfd.cFileName, ".") != 0 &&
		strcmp(wfd.cFileName, "..") != 0;
}

bool ThemeList::fileExists(const string &path) const
{
	return (GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES);
}

size_t ThemeList::size() const
{
	return themeList.size();
}

size_t ThemeList::addTheme(Theme t)
{
	vector<Theme>::iterator pos = themeList.insert(themeList.end(), t);

	notifyObservers(this);

	return pos - themeList.begin();
}

bool ThemeList::removeTheme(const Theme &t)
{
	struct comp : public binary_function<Theme, Theme, bool>
	{
		bool operator() (const Theme &lhs, const Theme &rhs) const
		{
			return lhs.getName() == rhs.getName();
		}
	};

	vector<Theme>::iterator pos = find_if(themeList.begin(), themeList.end(), bind1st(comp(), t));

	if (pos != themeList.end())
	{
		themeList.erase(pos);
		notifyObservers(this);
		return true;
	}

	return false;
}

Theme &ThemeList::operator[](size_t index)
{
	if (index >= 0 && index < themeList.size())
	{
		return themeList[index];
	}
	else
	{
		return nullTheme;
	}
}

const Theme &ThemeList::operator[](size_t index) const
{
	if (index >= 0 && index < themeList.size())
	{
		return themeList[index];
	}
	else
	{
		return nullTheme;
	}
}

void ThemeList::writeToFile(std::string path) const
{
	ofstream outfile(path.c_str(), ios_base::out | ios_base::trunc);
	if (outfile.is_open())
	{
		for (size_t i = 0; i < themeList.size(); ++i)
		{
			if (themeList[i].getEnabled())
			{
				outfile << "*Popup \"" << themeList[i].getName() << 
					"\" !execute " << "[\"$LiteStepDir$utilities\\SLI-" \
					"ThemeManager.exe\" /switch \"" << themeList[i].getName()
					<< "\"]" << endl;
				outfile.flush();
			}
		}
		outfile.close();
	}
}
