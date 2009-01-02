#ifndef MODULE_H_
#define MODULE_H_

#include <string>

class Module {
private:
	std::string name;
public:
	Module(const std::string path);
	std::string getName() const;
	bool operator==(const Module &rhs) const;
	bool operator<(const Module &rhs) const;
};

#endif