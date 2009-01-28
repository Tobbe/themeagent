#include "ThemeList.h"
#include <string>

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

Theme ThemeList::operator [](size_t index) const
{
	if (index >= 0 && index < themeList.size())
	{
		return themeList[index];
	}
	else
	{
		return Theme();
	}
}
