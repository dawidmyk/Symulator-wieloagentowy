#include "elements.hpp"
#include <thread>
#include <mutex>
#ifndef AGENT
#define AGENT

class Agent {
	
	static double close;
	static double defaultVelocity;
	double x;
	double y;
	char dir;
	bool active;
	std::mutex posits;
	std::mutex dir_read;
	std::mutex edgeLock;
	std::mutex activeLock;
	
	std::unique_ptr<std::thread> pointThread;
	
	std::general_ptr<Point> begin, end;
	std::general_ptr<Edge> actual;
	
	int fragment; //used for checking velocity
	
	public:
	Agent(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end);
	
	void runFunction();
	void threadFunction();
	
	double getVelocity() {
		if(actual.isEmpty()) return 0;
		return actual->velocityAt(fragment);
	}
	
	std::pair<double, double> locate() {
		std::lock_guard lock(posits);
		return std::pair(x, y);
	}
	
	static bool twoClose(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second);

	
	static bool crash(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second);
	
	void spawn() {
		pointThread.reset(new std::thread(&Agent::threadFunction, this));
	}
	
	void setActive(bool active) {
		std::lock_guard lock(activeLock);
		this->active = active;
	}
	bool checkActive() {
		std::lock_guard lock(activeLock);
		//przydałoby się zorganizować mechanizm mutexów
		//trochę inaczej żeby możliwe było wielu czytelników i jeden pisarz
		return active;
	}
	
	void join() {
		if(pointThread->joinable())
		pointThread->join();
	}
	
	static void setClose(double close) {
		Agent::close = close;
	}
	
	static void setVelocity(double velo) {
		defaultVelocity = velo;
	}
	
};

#endif
