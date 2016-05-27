#include "Monitor.h"

Monitor :: Monitor(int ilosc_stacji, double czas, bool wr) { 
	write = wr;
	liczba_stacji = ilosc_stacji;
	delta = 10000;
	activate(delta);
	czas_symulacji = czas;
	reset();
	Generator gen = Generator(int(time(NULL)));
	kanal = new Medium();
	Stacja* st;
	for(int i = 0; i < liczba_stacji; i++) {
		st = new Stacja(gen.hash());
		stacje.push(st);
		st->activate(0);
	}
	st = NULL;
	if(write) {
		delay = fopen("delay.txt","w");
	}
}

void Monitor :: execute() {
	reset();
	opoznienia.clear();
}

void Monitor :: opoznienie(double czas) {
	if(write) {
		fprintf(delay, "%.6f %.6f\n", zegar, czas);
	}
	opoznienia.push_back(czas);
	dostarczone++;
}

void Monitor :: reset() {
	opoznienia.clear();
	dostarczone = 0;
	oferowane = 0;
	tracone = 0;
	retransmisje = 0;
	kolizje = 0;
}

void Monitor :: zwieksz_kolizje() {
	kolizje++;
}

void Monitor :: zwieksz_oferowane() {
	oferowane++;
}

void Monitor :: zwieksz_retransmisje() {
	retransmisje++;
}

void Monitor :: zwieksz_tracone() {
	tracone++;
}

Monitor :: ~Monitor() {
	double suma = 0;
	for(unsigned int i = 0; i < opoznienia.size(); i++) {
		suma += opoznienia[i];
	}
	double srednia = suma/dostarczone;

	suma = 0;
	for(unsigned int i = 0; i < opoznienia.size(); i++) {
		suma += pow((srednia - opoznienia[i]),2);
	}
	double wariancja = suma/dostarczone;

	if(dostarczone == 0) {
		srednia = 0;
		wariancja = 0;
	}

	printf(" ::: WYNIKI SYMULACJI CYFROWEJ ::: \n");
	printf(" --------------------------------- \n");
	printf("   stacje   : %7i\n", liczba_stacji);
	printf("    czas    : %7i [ms]\n", (int)czas_symulacji); 
	printf(" --------------------------------- \n");
	printf("max predkosc:  %.4f MBps\n", 15*(dostarczone*0.1)/(czas_symulacji-delta));
	printf("   srednia  :  %.4f [ms]\n", srednia);
	printf("  wariancja :  %.4f \n", wariancja);
	printf("  oferowane : %7i \n", oferowane);
	printf(" dostarczone: %7i \n", dostarczone);
	printf("   tracone  : %7i (%.4f)\n", tracone, (double)tracone/oferowane);
	printf("   kolizje  :  %.4f \n", (double)kolizje/(czas_symulacji-delta));
	printf("retransmisje:  %.4f \n", (double)retransmisje/(czas_symulacji-delta));

	if(write) {	
		FILE* fpredkosc = fopen("predkosc.txt","a");
		FILE* fsrednia = fopen("srednia.txt","a");
		FILE* fwariancja = fopen("wariancja.txt","a");
		FILE* ftracone = fopen("tracone.txt","a");
		FILE* fkolizje = fopen("kolizje.txt","a");
		FILE* fretransmisje = fopen("retransmisje.txt","a");
		FILE* wyniki = fopen("wyniki.txt","a");

		fprintf(wyniki, " ::: WYNIKI SYMULACJI CYFROWEJ ::: \n");
		fprintf(wyniki, " --------------------------------- \n");
		fprintf(wyniki, "   stacje   : %7i\n", liczba_stacji);
		fprintf(wyniki, "    czas    : %7i [ms]\n", (int)czas_symulacji); 
		fprintf(wyniki, " --------------------------------- \n");
		fprintf(wyniki, "max predkosc:  %2.4f MBps\n", 15*(dostarczone*0.1)/(czas_symulacji-delta));
		fprintf(wyniki, "   srednia  :  %2.4f [ms]\n", srednia);
		fprintf(wyniki, "  wariancja :  %2.4f \n", wariancja);
		fprintf(wyniki, "  oferowane : %7i \n", oferowane);
		fprintf(wyniki, " dostarczone: %7i \n", dostarczone);
		fprintf(wyniki, "   tracone  : %7i (%.4f)\n", tracone, (double)tracone/oferowane);
		fprintf(wyniki, "   kolizje  :  %2.4f \n", (double)kolizje/(czas_symulacji-delta));
		fprintf(wyniki, "retransmisje:  %2.4f \n\n", (double)retransmisje/(czas_symulacji-delta));

		fprintf(fpredkosc,"%.4f\n", 15*(dostarczone*0.1)/(czas_symulacji-delta));
		fprintf(fsrednia,"%.4f \n", srednia);
		fprintf(fwariancja,"%.4f \n", wariancja);
		fprintf(ftracone,"%.4f\n", (double)tracone/oferowane);
		fprintf(fkolizje,"%.4f \n", (double)kolizje/(czas_symulacji-delta));
		fprintf(fretransmisje,"%.4f \n", (double)retransmisje/(czas_symulacji-delta));

		fclose(wyniki);
		fclose(fpredkosc);
		fclose(fsrednia);
		fclose(fwariancja);
		fclose(ftracone);
		fclose(fkolizje);
		fclose(fretransmisje);
		fclose(delay);
	}
    //delete kanal;
    Stacja* st;
    while(!stacje.empty()) {
        st = stacje.front();
        stacje.pop();
        delete(st);
    }
    st = NULL;
}
