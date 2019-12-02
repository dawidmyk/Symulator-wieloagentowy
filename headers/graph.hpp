#include <vector>
#include "agent.hpp"
#include <random>

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

class Graph {
	
	//here pointers in containers
	//are to be owners of the objects
	
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	ThreadInterruptible agentDraw;
	ThreadInterruptible agentCrash;
	
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
	
	void actualize(const std::general_ptr<Agent> & agent, float x, float y);
	//ta metoda komunikuje się z widokiem
		
	
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
		while (agentDraw.getCondition()) { //tam jest tak naprawde jakaś zmienna graphu
			for(auto & ptr : agents) {
				std::pair posit = ptr->locate();
				actualize(ptr, posit.first, posit.second);
			}
		}
	}
	void agentCrashThread() {
		while(agentCrash.getCondition())
			for(auto & ptr1 : agents)
				for(auto & ptr2 : agents)
					if(Agent::crash(ptr1, ptr2))
						noteCrash(ptr1, ptr2);
	}
	
	void spawnAgentDrawThread() {
		agentDraw.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentDrawThread, this)));
	}
	
	void spawnAgentCrashThread() {
		agentCrash.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentCrashThread, this)));
	}
	
	void spawnAgents() {
		for(auto & ptr : agents) {
			ptr->spawn();
		}
	}
	
	void joinAgents() {
		for(auto & ptr : agents) ptr->join();
	}
	
	void joinDraw() {
		agentDraw.join();
	}
	
	void joinCrash() {
		agentCrash.join();
	}	
	
	
	void makeSeed() {
		rander.makeSeed();
	}
		

	void noteCrash(const std::general_ptr<Agent> & ptr1, const std::general_ptr<Agent> & ptr2);
	//ta metoda komunikuje się z widokiem
	
			
};

