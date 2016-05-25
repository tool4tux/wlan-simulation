#ifndef GENERATOR_H
#define GENERATOR_H

#include <cmath>

extern const double MI;
extern const int D;

class Generator
{
	int modulnik;
	int mnoznik;
	int mnoznik2;
	double mi;
	unsigned long long int ziarno;
public:
	Generator(long long int ziarno_poczatkowe);
	Generator();
	long long int hash();
	double losuj();
	int losuj_przedzial();
	double losuj_wykladniczy();
};

#endif
