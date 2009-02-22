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
	std::string nlmIni;
	std::vector<std::string> downloadSites;
	ModuleList modules;
	FileDownloader fileDownloader;
	void findModulesInModulesDir();
	bool isDll(const WIN32_FIND_DATA &wfd) const;
	bool isDir(const WIN32_FIND_DATA &wfd) const;
	bool fileExists(const std::string &path) const;
	bool downloadModule(const std::string &moduleName);
	bool unzipModule(const std::string &moduleName) const;
	void fillUnzipVectors(const std::string &moduleName,
		const std::string &path,
		std::vector<std::pair<int, std::string>> &dllFiles,
		std::vector<std::pair<int, std::string>> &docsFiles) const;
	bool extractDlls(const std::string &moduleName, const std::string &path,
		const std::vector<std::pair<int, std::string>> &dllFiles) const;
	void extractDocs(const std::string &moduleName, const std::string &path,
		const std::vector<std::pair<int, std::string>> &docsFiles) const;
	bool updateNLMList(const std::string &moduleName) const;

public:
	ModuleManager(const std::string &modulesDir, const std::string &nlmIni,
		const std::vector<std::string> &downloadSites);
	ModuleList getModuleList() const;
	bool installModule(const std::string &moduleName);
};

#endif