#include "Pakiet.h"

Pakiet :: Pakiet(Stacja* ptr): nadajnik(ptr), czas_nadania(0) {}

void Pakiet :: execute() {
	bool active = true;
	while(active) {
		switch(phase) {
		case 0: {// zainicjowanie powstania nowego pakietu
				czas_nadania = zegar;
				(new Pakiet(nadajnik))->activate(nadajnik->generator.losuj_wykladniczy());
				//this->activate(nadajnik->generator.losuj_wykladniczy());

				Dane->zwieksz_oferowane(); // ustalenie ciaglosci transmisji wiadomosci
				if(nadajnik->bufor_test()) {// test przepelnienia
					phase = 1; // pakiet beddzie ozcekiwal na wyslanie w buforze stacji
					nadajnik->dodaj_pakiet(this);  
					if(nadajnik->aktywacja()) {
						nadajnik->activate(0);
					}
				}
				else {// pakiet zostaje porzucony
					Dane->zwieksz_tracone();
					terminated = true; 
				}
				active = false;
				break;
			}
		case 1: {// analiza transmisji
				if(kanal->test_kolizji()) {// zdarzyla sie kolizja
					nadajnik->kolizja();
					nadajnik->activate(0);
				}
				else {// przeslano poprawnie
					if(nadajnik->generator.losuj() < Pz) {// blad w transmisji
						nadajnik->retransmisja();
						nadajnik->activate(0);
					}
					else {// poprawna transmisja
						terminated = true;
						nadajnik->activate(0);
						Dane->opoznienie(zegar - czas_nadania);
					}
				}
				active = false;
				break;
			}
		}
	}
}

Pakiet :: ~Pakiet() {
    //delete nadajnik; 
}
