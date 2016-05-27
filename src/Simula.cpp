#include "Simula.h"

Process::Process() {
	phase = 0; 
	terminated = false;
	my_event = new Event(this);
}

void Process::activate(double time) {
	my_event->event_time = zegar + time;
	agenda.push(my_event);
}

Process::~Process() {
	delete my_event;
}

bool Event::operator < (const Event &other) const {
	return event_time < other.event_time;
}

bool Event::operator <= (const Event &other) const {
	return event_time <= other.event_time;
}

