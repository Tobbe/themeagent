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

	std::string parseName(RCFile rc) const;
	std::string parseAuthor(RCFile rc) const;
	std::string parseVersion(RCFile rc) const;
	std::string lookForPreview(std::string path) const;
	ModuleList parseNeededModules(RCFile rc) const;

public:
	Theme(std::string path, RCFile rc);
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