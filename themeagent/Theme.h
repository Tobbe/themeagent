#ifndef THEME_H_
#define THEME_H_

#include <string>
#include "RCFile.h"
#include "ModuleList.h"

class Theme
{
private:
	std::string name;
	std::string author;
	std::string version;
	std::string preview;
	std::string path;
	std::string otsVersion;
	bool enabled;

	std::string cleanUpPath(std::string path) const;
	std::string parseName(const RCFile &rc) const;
	std::string parseAuthor(const RCFile &rc) const;
	std::string parseVersion(const RCFile &rc) const;
	std::string lookForPreview() const;
	ModuleList parseNeededModules(const RCFile &rc) const;

public:
	Theme(const std::string &path, const RCFile &rc);
	std::string getName() const;
	std::string getAuthor() const;
	std::string getVersion() const;
	std::string getPreview() const;
	std::string getPath() const;
	std::string getOTSVersion() const;
	ModuleList getNeededModules() const;
	void setEnabled(bool enabled);
};

#endif