#include <iostream>
#include "simulation.hpp"


int main()
{
	Simulation sim;
	sim.testSimulation();
	
	std::cout << "Koniec symulacji";
	getchar();
	//wyłapie dopiero jak skończy się wszystko
	return 0;
}
