#include "Theme.h"

using namespace std;

Theme::Theme(string path, RCFile rc)
{
	this->path = path;
	this->name = parseName(rc);
	this->author = parseAuthor(rc);
	this->version = parseVersion(rc);
}

string Theme::parseName(RCFile rc) const
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

string Theme::parseAuthor(RCFile rc) const
{
	return rc.get("ThemeAuthor");
}

string Theme::parseVersion(RCFile rc) const
{
	return rc.get("ThemeVersion");
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