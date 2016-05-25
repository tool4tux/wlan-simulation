#include "Medium.h"

Medium :: Medium()
{
	kolizja = false;
	zajety = false;
}

void Medium ::dodaj_oczekujaca(Stacja* x)
{
	kolejka.push(x); // dodaj stacje oczekujaca na wolny kanal
}

void Medium :: execute() 
{
	bool active = true;
	while(active)
	{
		switch(phase)
		{
		case 0: // procedura blokowania kanalu
			{
				zajety = true;
				activate(czas_transmisji);
				phase = 1;
				active = false;
				break;
			}
		case 1: // odblokowywanie kanalu
			{
				if(transmitowane.size() > 1) // kolizja
				{
					kolizja = true;
					while(transmitowane.size() > 0)
					{
						Dane->zwieksz_kolizje();
						transmitowane.front()->execute();
						transmitowane.pop();
					}
				}
				else // odbior bez kolizji
				{
					transmitowane.front()->execute();
					transmitowane.pop();
				}
				while(kolejka.size() > 0) // aktywacja oczekujacych stacji
				{
					kolejka.front()->activate(0);
					kolejka.pop();
				}
				phase = 0;
				kolizja = false;
				zajety = false;
				active = false;
				break;
			}
		}
	}
}

bool Medium :: test_kolizji()
{
	return kolizja;
}

bool Medium :: test_zajetosci()
{
	return zajety;
}

void Medium :: zajmij_kanal(Pakiet* x)
{
	transmitowane.push(x);
	if(transmitowane.size() == 1)
	{
		activate(1e-6);
	}
	else
	{
		kolizja = true;
	}
}

void Medium :: zwolnij_kanal()
{
	zajety = false;
}

Medium :: ~Medium()
{
    Stacja* st;
    Pakiet* pt;
    while(!kolejka.empty())
    {
        st = kolejka.front();
        kolejka.pop();
        delete(st);
    }
    while(!transmitowane.empty())
    {
        pt = transmitowane.front();
        transmitowane.pop();
        delete(pt);
    }
    pt = NULL;
    st = NULL;
}