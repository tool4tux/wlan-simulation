#ifndef MEDIUM_H
#define MEDIUM_H

class Stacja;
class Pakiet;

#include "Simula.h"
#include "Stacja.h"
#include "Pakiet.h"

extern const double czas_transmisji;

class Medium: public Process
{
	std::queue <Stacja *> kolejka;
	std::queue <Pakiet *> transmitowane;
	bool kolizja, zajety;
public:
	Medium();
	void dodaj_oczekujaca(Stacja* x);
	void execute();
	bool test_kolizji();
	bool test_zajetosci();
	void zajmij_kanal(Pakiet* x);
	void zwolnij_kanal();
	~Medium();
};

#endif
