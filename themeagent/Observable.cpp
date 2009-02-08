#include "Observable.h"
#include "Observer.h"

void Observable::addObserver(Observer *o)
{
	observers.push_back(o);
}

void Observable::notifyObservers(const Observable *o)
{
	for (size_t i = 0; i < observers.size(); ++i)
	{
		observers[i]->update(o);
	}
}
