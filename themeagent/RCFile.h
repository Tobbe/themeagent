#ifndef _RC_FILE_H_
#define _RC_FILE_H_

#include <map>
#include <string>

class RCFile
{
private:
	std::multimap<std::string, std::string> rc;
	int lineCount;
	std::string trim(std::string str) const;
	std::string getSetting(const std::string &line) const;
	std::string getValue(const std::string &line) const;
public:
	RCFile(const std::string &path);
	std::string get(const std::string &key) const;
	int lines() const;
};

#endif