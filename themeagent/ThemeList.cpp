#include "ThemeList.h"
#include <string>

using namespace std;

size_t ThemeList::size() const
{
	return themeList.size();
}

void ThemeList::addTheme(Theme t)
{
	themeList.push_back(t);
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
