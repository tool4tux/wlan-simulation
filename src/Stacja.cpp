#include "Stacja.h"

Stacja :: Stacja(long long int seed)
{
	generator = Generator(seed);
	reset();
}

bool Stacja ::aktywacja()
{
	if(bufor.size() == 1)
	{
		return true;
	}
	return false;
}

bool Stacja :: bufor_test()
{
	if(bufor.size() >= BN)
	{
		return false; // brak miejsca na nowe zgloszenie
	}
	return true; // jest miejse na nowy pakiet
}

void Stacja :: dodaj_pakiet(Pakiet* x)
{
	bufor.push(x); // dodanie pakietu do buforu oczekujacego
}

void Stacja :: execute()
{
	bool active = true;
	while(active)
	{
		switch(phase)
		{
		case 0: // inicjacja dzialania stacji (wykonywane tylko raz)
			{
				//(new Pakiet(this))->activate(generator.losuj_wykladniczy());
				Pakiet *pt = new Pakiet(this);
				pt->activate(generator.losuj_wykladniczy());

				phase = 1;
				active = false;
				break;
			}
		case 1: 
			{
				if(bufor.size()) // sprawdzenie czy jest pakiet do wyslania
				{
					if(RT > RTmax) // test licznika RT
					{
						Dane->zwieksz_tracone();
						bufor.pop();
						reset();
					}
					else // mozna aktywowac do nadawania
					{
						licznik = generator.losuj_przedzial();
						phase = 2;
					}
				}
				else
				{
					active = false;
				}
				break;
			}
		case 2: // testowanie zajetosci kanalu
			{
				if(kanal->test_zajetosci()) // oczekiwanie na wolny kanal
				{
					active = false;
					kanal->dodaj_oczekujaca(this);
				}
				else // kanal jest wolny
				{
					if(licznik == 0) 
					{
						phase = 3; // rozpoczecie transmisji
					}
					else // dalsze zmiejszanie licznika
					{
						active = false;
						activate(test_kanalu);
						licznik--;
					}					
				}
				break;
			}
		case 3: // transmisja pakietu droga radiowa
			{
				kanal->zajmij_kanal(bufor.front());
				phase = 4;
				if(RT > 0)
				{
					Dane->zwieksz_retransmisje();
				}
				active = false;
				break;
			}
		case 4: //czyszczenie buforu i przygotowanie do przeslania kolejnej wiadomosci
			{
				bufor.pop();
				reset();
				phase = 1;
			}
		}
	}
}

void Stacja :: kolizja()
{
	retransmisja();
	KL++;
}

void Stacja :: przeslano()
{
	reset();
	phase = 1;
}

void Stacja :: reset()
{
	RT = 0;
	KL = 0;
}

void Stacja :: retransmisja()
{
	phase = 1;
	RT++;
}

Stacja::~Stacja()
{
    Pakiet* pt;
    while(!bufor.empty())
    {
        pt = bufor.front();
        bufor.pop();
        delete(pt);
    }
    pt = 0;
}
