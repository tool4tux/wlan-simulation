#ifndef SIMULA_H
#define SIMULA_H

#include <queue>
#include <deque>

class Process;
class Event;

extern double zegar;
extern std::priority_queue <Event> agenda;

class Process
{
	Event* my_event;
public:
	int phase;
	bool terminated;
	Process();
	void activate(double time);
	void virtual execute() {};
	~Process();
};

class Event
{
public:
	double event_time;
	Process* proc;
	Event(Process* ptr): event_time(-1.0), proc(ptr) {}
	bool operator < (const Event &other) const;
};

#endif
