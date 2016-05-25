#ifndef STACJA_H
#define STACJA_H

class Monitor;
class Medium;

#include "Generator.h"
#include "Simula.h"
#include "Pakiet.h"
#include "Monitor.h"
#include "Medium.h"

extern unsigned const int BN;
extern unsigned const int RTmax;
extern Monitor* Dane;
extern Medium* kanal;
extern const double test_kanalu;

class Stacja: public Process
{
	std::queue <Pakiet *> bufor;	// bufor nadawczy przechowujacy pakiety
	unsigned int KL, RT;	// licznik retransmisji, kolizji
	int licznik;			// licznik D
public:
	Generator generator;	// generator liczb pseudolosowych
	Stacja(long long int seed);
	bool aktywacja();
	bool bufor_test();
	void dodaj_pakiet(Pakiet* x);
	void execute();
	void kolizja();
	void przeslano();
	void reset();
	void retransmisja();
	~Stacja();
};

#endif
