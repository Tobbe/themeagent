#ifndef THEME_LIST_H_
#define THEME_LIST_H_

#include "Theme.h"
#include "NullTheme.h"
#include <vector>
#include <string>
#include <windows.h>

class ThemeList
{
private:
	std::vector<Theme> themeList;
	NullTheme nullTheme;

	bool isDir(const WIN32_FIND_DATA &wfd) const;
	bool fileExists(const std::string &path) const;
public:
	ThemeList(std::string themesDir);
	size_t addTheme(Theme t);
	void writeToFile(std::string path) const;
	size_t size() const;
	const Theme &operator[](size_t index) const;
	Theme &operator[](size_t index);
};

#endif
