#include "Generator.h"

Generator :: Generator(long long int ziarno_poczatkowe) {
	ziarno = ziarno_poczatkowe;
	mnoznik = 16807;
	modulnik = 2147483647;
	mi = MI;
	mnoznik2 = 630360016;
}

Generator :: Generator() {
	Generator(1);
}

long long int Generator :: hash() {
	ziarno = (mnoznik2 * ziarno) % modulnik;
	return ziarno;
}

double Generator :: losuj() {
	ziarno = (mnoznik * ziarno) % modulnik;
	return double(ziarno) / modulnik;
}

int Generator :: losuj_przedzial() {
	ziarno = (mnoznik * ziarno) % modulnik;
	return ziarno % D + 1;
}

double Generator :: losuj_wykladniczy() {
	return -mi * log(losuj());
}

