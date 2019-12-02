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
	void run();
	
	void actualize(const std::general_ptr<Agent> & agent, float x, float y, int i);
	
	void noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2, int i, int j);

		
		

};


#endif
