#ifndef _MODULE_LIST_H_
#define _MODULE_LIST_H_

class ModuleList {
	void add(Module module);
	bool contains(Module module);
	Module operator[](int index);
	int size();
};

#endif