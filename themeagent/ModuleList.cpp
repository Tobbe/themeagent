#include "ModuleList.h"

using namespace std;

bool ModuleList::add(Module m)
{
	if (contains(m) || m.getName() == "")
	{
		// Return false if the module already is in the list
		// or if it doesn't have a name.
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

ModuleList::const_iterator ModuleList::begin() const
{
	return list.begin();
}

ModuleList::const_iterator ModuleList::end() const
{
	return list.end();
}