/*
Class used for communication with user to get simulation parameters
Author: Mateusz Szewczyk
*/
#ifndef CONSOLE
#define CONSOLE
#include "graph.hpp"
#include <iostream>

class ThreadInterruptible {
	std::unique_ptr<std::thread> threadInstance;
	bool condition;
	std::mutex locker;
	public:
	ThreadInterruptible(): condition(false) {}
	void setThread(std::unique_ptr<std::thread> thread) {
		threadInstance = std::move(thread);
	}
	void setCondition(bool condition) {
		std::lock_guard lock(locker);
		this->condition = condition;
	}
	bool getCondition() {
		std::lock_guard lock(locker);
		return condition;
	}
	void join() {
		setCondition(false);
		threadInstance->join();
	}
	
	
};

class Console {
	
	Graph & g;
	ThreadInterruptible agentDraw;
	ThreadInterruptible agentCrash;
	std::mutex consoleLock;
	void setAgentDraw() {
		agentDraw.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentDrawThread,
		&g, std::ref(*this), std::ref(agentDraw))));
	}
	void setAgentCrash() {
		agentCrash.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentCrashThread,
		&g, std::ref(*this), std::ref(agentCrash))));
	}
	
public:
	Console(Graph & graph): g(graph) {}
	void run() {
		//Tu hardkodujemy graf
		//g.add(...);
		g.makeSeed();
		g.spawnAgents();
		setAgentDraw();
		setAgentCrash();
		g.joinAgents();
		agentDraw.join();
		agentCrash.join();
	}
	
	void actualize(const std::general_ptr<Agent> & agent, float x, float y, int i) {
		//ta metoda komunikuje się z widokiem
		std::stringstream agentInformation;
		agentInformation << "Agent nr " << i;
		agentInformation << ", Skladowa X " << x;
		agentInformation << ", Skladowa Y " << y;
		agentInformation << ", Predkosc " << agent->getVelocity() << std::endl << std::endl;
		std::lock_guard lock(consoleLock);
		std::cout << agentInformation.str();

	}
	
	void noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2, int i, int j) {
		std::stringstream crashInformation;
		crashInformation << "Agent nr " << i;
		crashInformation << "<->";
		crashInformation << "Agent nr " << j << std::endl;
		crashInformation << "Spotkali się" << std::endl << std::endl;
		std::lock_guard lock(consoleLock);
		std::cout << crashInformation.str();
	}
		
		

};


#endif
