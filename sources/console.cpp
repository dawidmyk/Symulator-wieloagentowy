#include <iostream>
#include <string>
#include "headers.hpp"


void Console::actualize(const general_ptr<Agent> & agent, double x, double y, int i) {
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
	std::this_thread::sleep_for(std::chrono::milliseconds((int)Simulation::getTime())); 
	//zeby wypisywać co jakiś czas, a nie ciągle
} //zdjęcie blokady

void Console::noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j) {
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

void Console::endRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & end, int j, bool success) {
	std::stringstream agentEndInformation;
	agentEndInformation << "Dojście do końca" << std::endl;
	agentEndInformation << "Agent nr " << j;
	agentEndInformation << ", zakończył ";
	if(success) agentEndInformation << "sukcesem";
	else agentEndInformation << "porażką";
	agentEndInformation << " w punkcie:" << std::endl;
	auto posits = end->locate();
	agentEndInformation << "{ " << posits.first << " , " << posits.second << " }" << std::endl << std::endl;
	std::lock_guard lock(consoleLock); 
	std::cout << agentEndInformation.str();
}

void Console::changeRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & now,
	const general_ptr<Edge> & previousOne,  const general_ptr<Edge> & newOne, int j) {
	std::stringstream agentChangeInformation;
	agentChangeInformation << "Przejście przez punkt" << std::endl;
	agentChangeInformation << "Agent nr " << j;
	agentChangeInformation << " , przechodzi przez punkt:" << std::endl;
	auto posits = now->locate(); 
	agentChangeInformation << "{ " << posits.first << " , " << posits.second << " }" << std::endl;
	agentChangeInformation << "pomiędzy krawędziami:" << std::endl;
	std::pair<general_ptr<Point>, general_ptr<Point>> ends;
	if(previousOne.isEmpty()) {
		agentChangeInformation << "początek";
	}
	else {
		ends = previousOne->locate();
		posits = ends.first->locate();
		agentChangeInformation << "{ " << posits.first << " , " << posits.second << " } ";
		agentChangeInformation << "<-> ";
		posits = ends.second->locate();
		agentChangeInformation << "{ " << posits.first << " , " << posits.second << " }";
	}
	agentChangeInformation << " : : ";
	if(newOne.isEmpty()) {
		agentChangeInformation << "koniec" << std::endl << std::endl;
	}
	else {
		ends = newOne->locate();
		posits = ends.first->locate();
		agentChangeInformation << "{ " << posits.first << " , " << posits.second << " } ";
		agentChangeInformation << "<-> ";
		posits = ends.second->locate();
		agentChangeInformation << "{ " << posits.first << " , " << posits.second << " }" << std::endl << std::endl;
	}
	std::lock_guard lock(consoleLock); 
	std::cout << agentChangeInformation.str();
}

void Console::endInform() {
	std::lock_guard lock(consoleLock);
	std::cout << "Symulacja dobiegła końca." << std::endl;
	std::cout << "Wprowadź dowolny znak by zakończyć." << std::endl;
}
