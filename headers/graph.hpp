#include <vector>
#include "agent.hpp"
#include <random>
#include <sstream>
#ifndef GRAPH
#define GRAPH

class Console;
class ThreadInterruptible;
class Graph {
	
	//here pointers in containers
	//are to be owners of the objects
	
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	
	
	Rander rander;
	
	public:
	
	void addUsualPoint(float x, float y) {
		points.push_back(std::unique_ptr<Point>(new UsualPoint(x, y, rander)));
	}
	
	void addSpecialPoint(float x, float y) {
		points.push_back(std::unique_ptr<Point>(new SpecialPoint(x, y, rander)));
	}
	
	void addEdge(float x1, float y1, float x2, float y2, int fragments = 0) {
		//std::general_ptr<Point> begin = spotPoint(x1, y1);
		//std::general_ptr<Point> end = spotPoint(x2, y2);
		//tu jeszcze nie założone że może być błąd
		edges.push_back(std::unique_ptr<Edge>(new Edge(spotPoint(x1, y1), spotPoint(x2, y2), fragments)));
	}
	
	void addEdgeNum(int begin, int end, int fragments = 0) {
		edges.push_back(std::unique_ptr<Edge>(new Edge(std::general_ptr(points.at(begin)),
		std::general_ptr(points.at(end)), fragments)));
	}
	
	void addAgent(float x1, float y1, float x2, float y2) {
		agents.push_back(std::unique_ptr<Agent>(new Agent(spotPoint(x1, y1), spotPoint(x2, y2))));
	}
	
	void addAgentNum(int begin, int end) {
		agents.push_back(std::unique_ptr<Agent>(new Agent(std::general_ptr(points.at(begin)),
		std::general_ptr(points.at(end)))));
	}
	
	void setEdgeProperties(int nume, const std::vector<EdgeProperty> & properties) {
		edges.at(nume)->setProperties(properties);
	}
	
	void addEdgeProperty(int nume, const EdgeProperty & property) {
		edges.at(nume)->addProperty(property);
	}
	

		
	
	std::general_ptr<Point> spotPoint(float x, float y);
	
	void agentDrawThread(Console & cons, ThreadInterruptible & thread);
	void agentCrashThread(Console & cons, ThreadInterruptible & thread);
	
	
	void spawnAgents() {
		for(auto & ptr : agents) {
			ptr->spawn();
		}
	}
	
	void joinAgents() {
		for(auto & ptr : agents) ptr->join();
	}
	
	
	void makeSeed() {
		rander.makeSeed();
	}
		

	
	
			
};

#endif
