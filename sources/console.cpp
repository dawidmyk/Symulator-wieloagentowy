#include "console.hpp"
#include "graph.hpp"
#include <iostream>
#include <string>
double Console::time_reg;

void Console::run() {
	Simulation::startSimulation();
	setWait();
	g.edgesAdjust(); //przelicz parametry w krawędziach
	g.makeSeed(); //zasiej losowość
	g.spawnAgents(); //wystartuj agentów
	setAgentDraw(); //zacznij wypisywanie pozycji agentów
	//setAgentCrash(); //zacznij wypisywanie informacji o spotkaniach
	//jego dezaktywowałem bo on się zakleszcza
	//nie wiem dlaczego
	//(w obecnej konfiguracji spotkania raczej nie występują)
	g.joinAgents(); //czekaj aż agenci się zakończą (dojdą tam gdzie mają dojść)
	agentDraw.join(); //delikatnie wymuś zatrzymanie wątku wypisującego pozycje
	//agentCrash.join(); //delikatnie wymuś zatrzymanie wątku wypisującego spotkania
	joinWait();
}

void Console::actualize(const std::general_ptr<Agent> & agent, double x, double y, int i) {
	//ta metoda komunikuje się z widokiem
	std::stringstream agentInformation;
	agentInformation << n << ". " << std::endl; //numer kolejnego wypisania
	//daje to pewność że wypisania idą naprzód (nie ma zakleszczenia)
	n++;
	agentInformation << "Agent nr " << i;
	agentInformation << ", Skladowa X " << x;
	agentInformation << ", Skladowa Y " << y;
	agentInformation << ", Predkosc " << agent->getVelocity() << std::endl << std::endl;
	std::lock_guard lock(consoleLock); //założenie blokady
	std::cout << agentInformation.str();
	std::this_thread::sleep_for(std::chrono::milliseconds((int)time_reg)); 
	//zeby wypisywać co jakiś czas, a nie ciągle
} //zdjęcie blokady

void Console::noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2, int i, int j) {
	std::stringstream crashInformation;
	crashInformation << "Agent nr " << i;
	crashInformation << "<->";
	crashInformation << "Agent nr " << j << std::endl;
	crashInformation << "Spotkali się" << std::endl << std::endl;
	std::lock_guard lock(consoleLock); //założenie blokady
	std::cout << crashInformation.str();
	//tak rzadko się dzieje, że można nie czekać
	//bo w praktyce on będzie aktywnie oczekiwał w pętli gdzie cały czas będzie otrzymywał nieprawdę
} //zdjęcie blokady

