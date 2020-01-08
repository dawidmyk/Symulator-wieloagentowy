#include <vector>
#include "agent.hpp"
#include <random>
#include <sstream>
#ifndef GRAPH
#define GRAPH

class Console;
class ThreadInterruptible;
class Graph {
	
	//tutaj wskażniki muszą trzymać własność do tych obiektów, żeby
	//je usunąć na końcu
	//żeby nie było wycieków pamięci
	//dlatego są unique_ptr
	
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	
	
	Rander rander;
	
	public:
	//rózne funkcje rozbudowujące graf
	//i one są wołane w Simulation::test
	void addUsualPoint(double x, double y);
	void addSpecialPoint(double x, double y);
	
	void addEdge(double x1, double y1, double x2, double y2);
	
	void addEdgeNum(int begin, int end);
	
	void addAgent(double x1, double y1, double x2, double y2);
	//agent też może się wstrzelić w odpowiednie punkty
	
	void addAgentNum(int begin, int end);
	
	void setEdgeProperties(int nume, const std::vector<EdgeProperty> & properties);
	
	void addEdgeProperty(int nume, const EdgeProperty & property);
	

		
	
	general_ptr<Point> spotPoint(double x, double y);
	
	void agentDrawThread(Console & cons, ThreadInterruptible & thread);
	void agentCrashThread(Console & cons, ThreadInterruptible & thread);
	//te funkcje uruchamiane są w dwóch osobnych wątkach
	
	void spawnAgents();
	
	void joinAgents();
	
	
	void makeSeed();
	
	void edgesAdjust();

	
	
			
};

#include "graph.cpp"
#endif
