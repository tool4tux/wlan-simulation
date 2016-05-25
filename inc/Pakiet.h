#ifndef PAKIET_H
#define PAKIET_H

class Stacja;
#include "Stacja.h"

extern const double Pz;

class Pakiet: public Process
{
	Stacja* nadajnik;
	double czas_nadania;
public:
	Pakiet(Stacja* nadajnik);
	void execute();
	~Pakiet();
};

#endif