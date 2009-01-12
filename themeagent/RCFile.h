#ifndef RC_FILE_H_
#define RC_FILE_H_

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
	std::multimap<std::string, std::string>::const_iterator lastValue;

public:
	RCFile(const std::string &path);
	std::string get(const std::string &key) const;
	bool isSet(const std::string &key) const;
	int lines() const;
	std::string getMultiple(const std::string &key);
	bool isTrue(const std::string &key) const;
};

#endif