#include <UnitTest++.h>
#include "Observable.h"
#include "Observer.h"

class ConcreteObservable : public Observable
{
private:
	int msg;
public:
	void doSomething(int data)
	{
		msg = data;
		notifyObservers(this);
	}

	int getMsg() const
	{
		return msg;
	}
};

class ConcreteObserver : public Observer
{
private:
	int msg;

public:
	ConcreteObserver()
	{
		msg = 0;
	}

	int getMsg()
	{
		return msg;
	}

	virtual void update(const Observable *o)
	{
		msg = reinterpret_cast<const ConcreteObservable*>(o)->getMsg();
	}
};

SUITE(Observer)
{
	TEST(NotifyObservers)
	{
		ConcreteObserver observer1;
		ConcreteObserver observer2;
		ConcreteObserver observer3;
		ConcreteObservable observable;

		CHECK(observer1.getMsg() == 0);

		observable.doSomething(7);

		CHECK(observer1.getMsg() == 0);

		observable.addObserver(&observer1);

		observable.doSomething(7);

		CHECK(observer1.getMsg() == 7);

		observable.addObserver(&observer2);
		observable.addObserver(&observer3);

		CHECK(observer2.getMsg() == 0);
		CHECK(observer3.getMsg() == 0);

		observable.doSomething(8);

		CHECK(observer1.getMsg() == 8);
		CHECK(observer2.getMsg() == 8);
		CHECK(observer3.getMsg() == 8);
	}
}
