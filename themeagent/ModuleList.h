#ifndef _MODULE_LIST_H_
#define _MODULE_LIST_H_

#include "Module.h"
#include <set>

class ModuleList {
private:
	std::set<Module> list;
public:
	bool add(Module module);
	bool contains(Module module) const;
	Module operator[](int index) const;
	int size() const;
};

#endif