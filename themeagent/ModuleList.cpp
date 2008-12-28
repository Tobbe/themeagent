#include "ModuleList.h"

bool ModuleList::add(Module m)
{
	if (list.find(m) != list.end())
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