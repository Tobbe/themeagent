#include "Theme.h"
#include <windows.h>

using namespace std;

Theme::Theme()
{
	enabled = false;
}

Theme::Theme(const string &path, const RCFile &rc)
{
	enabled = false;

	this->path = cleanUpPath(path);
	this->name = parseName(rc);
	this->author = parseAuthor(rc);
	this->version = parseVersion(rc);
	this->preview = lookForPreview();
	this->otsVersion = parseOTSVersion(rc);
	this->neededModules = parseNeededModules(rc);
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

string Theme::parseOTSVersion(const RCFile &rc) const
{
	string majorVersion = rc.get("OtsMajorVersion");
	string minorVersion = rc.get("OtsMinorVersion");

	if (majorVersion == "")
	{
		return "";
	}
	else if (minorVersion == "")
	{
		return majorVersion;
	}

	return majorVersion + "." + minorVersion;
}

ModuleList Theme::parseNeededModules(RCFile rc) const
{
	string module;
	ModuleList mList;

	do
	{
		module = rc.getMultiple("*NetLoadModule");
		mList.add(Module(module));
	}
	while (module != "");

	return mList;
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

string Theme::getPath() const
{
	return path;
}

string Theme::getOTSVersion() const
{
	return otsVersion;
}

ModuleList Theme::getNeededModules() const
{
	return neededModules;
}

bool Theme::getEnabled() const
{
	return enabled;
}

void Theme::setEnabled(bool enabled)
{
	this->enabled = enabled;
}
