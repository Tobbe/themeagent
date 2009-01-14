#include "Theme.h"

using namespace std;

Theme::Theme(string path, RCFile rc)
{
	this->path = path;
	this->name = parseName(rc);
}

string Theme::parseName(RCFile rc) const
{
	string name = rc.get("ThemeName");
	if (name == "")
	{
		//parse name from path
	}

	return name;
}

string Theme::getName() const
{
	return name;
}