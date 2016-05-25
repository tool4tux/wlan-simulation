#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <queue>	// kolejka FIFO
#include <deque>	// kolejka dwukierunkowa

#include "wlan.h"

const unsigned int BN = 10;
const unsigned int RTmax = 5;
const int D = 16;
const double Pz = 0.001;
const double czas_transmisji = 0.1; // [ms]
const int rozmiar_pakietu = 1500;	// [bajtow]
const double MI = 15;
const double test_kanalu = 0.001;

double zegar = 0.0;		// [ms]
std::priority_queue <Event> agenda;
Monitor* Dane;
Medium* kanal;

int main(int argc, char *argv[])
{	
	double simulation_time = atof(*++argv);
	int stacje = atoi(*++argv);
	bool write = (bool)atoi(*++argv);
	Dane = new Monitor(stacje, simulation_time, write);
	Process* current = Dane;
	time_t start = time(NULL);

	while(simulation_time > zegar)
	{
		zegar = agenda.top().event_time;
		current = agenda.top().proc;
		agenda.pop();
		current->execute();
		if(current->terminated)
		{
			delete current;
		}
	}
	
	delete Dane;
	printf("\nczas symulacji: %i [s]\n", (int)(time(NULL) - start));

    while(false)
    {
        current = agenda.top().proc;
        agenda.pop();
        delete(current);
    }
    if(write == 0) 
	{
		getchar();
	}
	return 0;
}
