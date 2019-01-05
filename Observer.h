#ifndef OBSERVER_H
#define OBSERVER_H

class Observer  // classe basica de View
{
public:
	virtual void update() { }	// default: no-op
};

#endif  // OBSERVER_H