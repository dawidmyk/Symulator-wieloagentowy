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
	static void startSimulation();
	static void endSimulation();
	static bool last();
private:

	
	
	//Graph graph;
	int cargoCount;
	int vehicleCount; // vehicle count == agents count
	int vehicleCapacity;
	int maxWorkTime; //maximum time of agents work without break
	int mishapProbability; 
	int edgeCapacity;

};

#include "simulation.cpp"
#endif
