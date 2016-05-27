#ifndef MONITOR_H
#define MONITOR_H
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <queue>	// kolejka FIFO
#include <deque>	// kolejka dwukierunkowa
#include "Simula.h"
#include "Stacja.h"

class Monitor: public Process {
	double time_test, czas_symulacji, delta;
	int liczba_stacji, dostarczone, tracone, oferowane;
	int retransmisje, kolizje;
	std::deque <double> opoznienia;
	FILE* delay;
	bool write;
	std::queue <Stacja *> stacje;
public:
	Monitor(int ilosc_stacji, double czas, bool wr);
	void execute();
	void opoznienie(double czas);
	void reset();
	void zwieksz_kolizje();
	void zwieksz_oferowane();
	void zwieksz_retransmisje();
	void zwieksz_tracone();
	~Monitor();
};

#endif
