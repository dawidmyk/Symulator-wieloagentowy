#include "../headers/console.hpp"
#include "../headers/graph.hpp"
#include <iostream>
#include <string>

void Console::run() {
	g.makeSeed();
	g.spawnAgents();
	setAgentDraw();
	setAgentCrash();
	g.joinAgents();
	agentDraw.join();
	agentCrash.join();
}

void Console::actualize(const std::general_ptr<Agent> & agent, float x, float y, int i) {
	//ta metoda komunikuje się z widokiem
	std::stringstream agentInformation;
	agentInformation << "Agent nr " << i;
	agentInformation << ", Skladowa X " << x;
	agentInformation << ", Skladowa Y " << y;
	agentInformation << ", Predkosc " << agent->getVelocity() << std::endl << std::endl;
	std::lock_guard lock(consoleLock);
	std::cout << agentInformation.str();
}

void Console::noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2, int i, int j) {
	std::stringstream crashInformation;
	crashInformation << "Agent nr " << i;
	crashInformation << "<->";
	crashInformation << "Agent nr " << j << std::endl;
	crashInformation << "Spotkali się" << std::endl << std::endl;
	std::lock_guard lock(consoleLock);
	std::cout << crashInformation.str();
}

