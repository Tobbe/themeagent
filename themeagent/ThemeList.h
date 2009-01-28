#ifndef THEME_LIST_H_
#define THEME_LIST_H_

#include "Theme.h"
#include <vector>
#include <string>

class ThemeList
{
private:
	std::vector<Theme> themeList;
public:
	size_t addTheme(Theme t);
	void writeToFile(std::string path) const;
	size_t size() const;
	Theme operator[](size_t index) const;
};

#endif
