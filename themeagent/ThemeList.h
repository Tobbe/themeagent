#ifndef THEME_LIST_H_
#define THEME_LIST_H_

#include "Theme.h"
#include "NullTheme.h"
#include <vector>
#include <string>

class ThemeList
{
private:
	std::vector<Theme> themeList;
	NullTheme nullTheme;
public:
	size_t addTheme(Theme t);
	void writeToFile(std::string path) const;
	size_t size() const;
	const Theme &operator[](size_t index) const;
	Theme &operator[](size_t index);
};

#endif
