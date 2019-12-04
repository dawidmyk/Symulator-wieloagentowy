#include "simulation.hpp"
#include "graph.hpp"
#include "agent.hpp"
#include "console.hpp"

void Simulation::testSimulation() {
	Graph graph;
	
	//ustalenie stałych własności symulacji
	//(statycznych w różnych klasach)
	Agent::setClose(0.05); //jak blisko muszą być od siebie
	//agenci by się spotkać
	
	Point::setClose(0.01); //jak blisko musi być punkt początku
	//krawędzi żeby się do niego dopasowała
	
	Agent::setVelocity(0.01); //wspólny przemnożnik prędkości
	//wszystkich agentów
	
	Console::setTime(500); //co ile wypisanie kolejnej pozycji
	//agentów
	//ustalenie stałych własności symulacji
	
	Console cons(graph); //przekazanie referencji
	//jest tylko jeden graf
	
	graph.addUsualPoint(0, 0);
	graph.addSpecialPoint(0, 3);
	graph.addUsualPoint(2, 0);
	graph.addSpecialPoint(5, 2);
	graph.addSpecialPoint(7, 3);
	graph.addEdge(0, 0, 0, 3);
	graph.addEdge(0, 0, 2, 0);
	graph.addEdge(0, 3, 5, 2);
	graph.addEdge(2, 0, 5, 2);
	graph.addEdge(0, 3, 7, 3);
	graph.addEdge(5, 2, 7, 3);
	graph.addAgent(0, 0, 7, 3);
	graph.addAgent(2, 0, 7, 3);
	graph.addAgent(5, 2, 0, 0);
	cons.run();

}
