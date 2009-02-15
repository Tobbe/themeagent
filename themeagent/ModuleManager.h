#ifndef MODULE_MANAGER_H_
#define MODULE_MANAGER_H_

#include "ModuleList.h"
#include <string>
#include <vector>
#include <windows.h>

class ModuleManager
{
private:
	std::string modulesDir;
	std::vector<std::string> downloadSites;
	ModuleList modules;
	void findModulesInModulesDir();
	bool isDll(const WIN32_FIND_DATA &wfd) const;
	bool isDir(const WIN32_FIND_DATA &wfd) const;

public:
	ModuleManager(std::string modulesDir, std::vector<std::string> downloadSites);
	ModuleList getModuleList() const;
	bool installModule(std::string moduleName);
};

#endif