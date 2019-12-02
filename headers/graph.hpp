#include <vector>
#include "agent.hpp"
#include <sstream>
#include <random>
#ifndef GRAPH
#define GRAPH



class Graph {
	
	//here pointers in containers
	//are to be owners of the objects
	public:
	static double close;
	
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	std::unique_ptr<std::thread> agentCrash;
	std::unique_ptr<std::thread> agentDraw;
	
	Rander rander;
	
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
	
	std::string actualize() {
		//ta metoda komunikuje się z widokiem
		std::stringstream agentInformation;
		for (int i = 0; i < agents.size(); i++) {
			agentInformation << "Agent nr " << i;
			agentInformation << ", Skladowa X " << agents[i]->x;
			agentInformation << ", Skladowa Y " << agents[i]->y;
			agentInformation << ", Predkosc " << agents[i]->getVelocity() << "\n";
			return agentInformation.str();
		}

	}
		
	
	std::general_ptr<Point> spotPoint(float x, float y) {
		std::general_ptr<Point> ret;
		char found = 0;
		for(auto & ptr : points) {
			if(ptr->spotted(x, y)) {
				ret = ptr;
				found++;
			}
			if (found == 2) return std::general_ptr<Point>(); //nullptr
		}
		if(found == 1) return ret;
		if(found == 0) return std::general_ptr<Point>(); //nullptr
	}
	
	void agentDrawThread() {
		while (true) { //tam jest tak naprawde jakaś zmienna graphu
			for(auto & ptr : agents) {
				std::pair posit = ptr->locate();
				//actualize(ptr, posit.first, posit.second);
				actualize();
			}
		}
	}
	void agentCrashThread() {
		while(true)
			for(auto & ptr1 : agents)
				for(auto & ptr2 : agents)
					if(Agent::crash(ptr1, ptr2))
						noteCrash(ptr1, ptr2);
	}
	
	void spawnAgentDrawThread() {
		agentDraw.reset(new std::thread(&Graph::agentDrawThread, this));
	}
	
	void spawnAgentCrashThread() {
		agentCrash.reset(new std::thread(&Graph::agentCrashThread, this));
	}
	
	void spawnAgents() {
		for(auto & ptr : agents) {
			ptr->spawn();
		}
	}
	
	
	
	void makeSeed() {
		rander.makeSeed();
	}
		

	void noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2);
	//ta metoda komunikuje się z widokiem
			
};

#endif