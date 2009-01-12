#ifndef MODULE_LIST_H_
#define MODULE_LIST_H_

#include "Module.h"
#include <set>
#include <iterator>

class ModuleList {
private:
	std::set<Module> list;
public:
	typedef std::set<Module>::const_iterator const_iterator;

	bool add(Module module);
	bool contains(const Module &module) const;
	int size() const;
	const_iterator begin() const;
	const_iterator end() const;
};

#endif