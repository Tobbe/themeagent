#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer
{
public:
	virtual void update(const class Observable *o) = 0;
};

#endif