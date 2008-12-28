#include "ModuleList.h"

bool ModuleList::add(Module m)
{
	if (contains(m))
	{
		// Return false if the module already is in the list
		return false;
	}

	list.insert(m);

	return true;
}

int ModuleList::size() const
{
	return list.size();
}

bool ModuleList::contains(const Module &module) const
{
	return list.find(module) != list.end();
}