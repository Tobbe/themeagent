#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <vector>

class Observable
{
private:
	std::vector<class Observer*> observers;
public:
	void addObserver(class Observer *o);
	void notifyObservers(const Observable *o);
};

#endif