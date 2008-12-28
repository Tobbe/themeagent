#ifndef _MODULE_H_
#define _MODULE_H_

#include <string>

class Module {
private:
	std::string name;
public:
	Module(const std::string path);
	std::string getName() const;
	bool operator==(const Module &rhs) const;
};

#endif