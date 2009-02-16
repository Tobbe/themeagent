#ifndef MODULE_MANAGER_H_
#define MODULE_MANAGER_H_

#include "ModuleList.h"
#include "FileDownloader.h"
#include <string>
#include <vector>
#include <windows.h>

class ModuleManager
{
private:
	std::string modulesDir;
	std::vector<std::string> downloadSites;
	ModuleList modules;
	FileDownloader fileDownloader;
	void findModulesInModulesDir();
	bool isDll(const WIN32_FIND_DATA &wfd) const;
	bool isDir(const WIN32_FIND_DATA &wfd) const;
	bool fileExists(const std::string &path) const;
	bool downloadModule(const std::string &moduleName);

public:
	ModuleManager(std::string modulesDir, std::vector<std::string> downloadSites);
	ModuleList getModuleList() const;
	bool installModule(const std::string &moduleName);
};

#endif