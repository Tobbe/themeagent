#include "Theme.h"
#include <windows.h>

using namespace std;

Theme::Theme(const string &path, const RCFile &rc)
{
	this->path = cleanUpPath(path);
	this->name = parseName(rc);
	this->author = parseAuthor(rc);
	this->version = parseVersion(rc);
	this->preview = lookForPreview();
}

string Theme::cleanUpPath(string path) const
{
	TCHAR buffer[MAX_PATH];
	TCHAR **lpPart = NULL;
	GetFullPathName(path.c_str(), MAX_PATH, buffer, lpPart);
	path = buffer;
	if (path[path.length() - 1] == '\\')
	{
		path = path.substr(0, path.length() - 1);
	}

	return path;
}

string Theme::parseName(const RCFile &rc) const
{
	string name = rc.get("ThemeName");
	if (name == "")
	{
		//parse name from path
		size_t index = path.find_last_of("\\/");
		if (index == path.length() - 1)
		{
			index = path.find_last_of("\\/", path.length() - 2);
			name = path.substr(index + 1, path.length() - 2 - index);
		}
		else
		{
			name = path.substr(index + 1);
		}
	}

	return name;
}

string Theme::parseAuthor(const RCFile &rc) const
{
	return rc.get("ThemeAuthor");
}

string Theme::parseVersion(const RCFile &rc) const
{
	return rc.get("ThemeVersion");
}

string Theme::lookForPreview() const
{
	string preview("");
	string pngPath(path + "\\preview.png");
	string bmpPath(path + "\\preview.bmp");

	if (GetFileAttributes(pngPath.c_str()) != INVALID_FILE_ATTRIBUTES)
	{
		preview = "preview.png";
	}
	else if (GetFileAttributes(bmpPath.c_str()) != INVALID_FILE_ATTRIBUTES)
	{
		preview = "preview.bmp";
	}

	return preview;
}

string Theme::getName() const
{
	return name;
}

string Theme::getAuthor() const
{
	return author;
}

string Theme::getVersion() const
{
	return version;
}

string Theme::getPreview() const
{
	return preview;
}
