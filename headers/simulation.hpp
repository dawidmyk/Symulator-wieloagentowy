/*
Class stores parameters of simulation
Author: Mateusz Szewczyk
*/

#ifndef SIMULATION
#define SIMULATION
#include "graph.hpp"
#include "agent.hpp"

class Simulation {
	
	static std::mutex end_lock;
	static bool end_var;
public:
	void testSimulation();
	static void startSimulation() {
		std::lock_guard lock(end_lock);
		end_var = true;
	}
	static void endSimulation() {
		std::lock_guard lock(end_lock);
		end_var = false;
	}
	static bool last() {
		std::lock_guard lock(end_lock);
		return end_var;
	}
private:

	
	
	//Graph graph;
	int cargoCount;
	int vehicleCount; // vehicle count == agents count
	int vehicleCapacity;
	int maxWorkTime; //maximum time of agents work without break
	int mishapProbability; 
	int edgeCapacity;

};
#endif
