#include "simulation.hpp"
#include "graph.hpp"
#include "agent.hpp"
#include "console.hpp"

void Simulation::testSimulation() {
	Graph graph;
	Console cons(graph);
	graph.addSpecialPoint(0, 0);
	graph.addUsualPoint(0, 3);
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
