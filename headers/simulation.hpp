/*
Class stores parameters of simulation
Author: Mateusz Szewczyk
*/
#include "graph.hpp"
#include "agent.hpp"

class Simulation {
public:
	void testSimulation();

private:
	Graph graph;
	int cargoCount;
	int vehicleCount; // vehicle count == agents count
	int vehicleCapacity;
	int maxWorkTime; //maximum time of agents work without break
	int mishapProbability; 
	int edgeCapacity;

};