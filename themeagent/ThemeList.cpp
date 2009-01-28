#include "ThemeList.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

size_t ThemeList::size() const
{
	return themeList.size();
}

size_t ThemeList::addTheme(Theme t)
{
	vector<Theme>::iterator pos = themeList.insert(themeList.end(), t);

	return pos - themeList.begin();
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
