#include "elements.hpp"
#include <thread>
#include <mutex>
class Agent {
	public:
	static float close;
	float x;
	float y;
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
	
	Agent(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end): dir(0), active(false), begin(begin),
	end(end), fragment(-1) {
		auto pointPositions = begin->locate();
		x = pointPositions.first;
		y = pointPositions.second;	
	}
	
	void runFunction();
	void threadFunction();
	
	double getVelocity() {
		return actual->velocityAt(fragment);
	}
	
	std::pair<float, float> locate() {
		std::lock_guard lock(posits);
		return std::pair(x, y);
	}
	
	static bool twoClose(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		std::lock_guard lock1(one->posits);
		std::lock_guard lock2(second->posits);
		float xdiff = one->x - second->x;
		float ydiff = one->y - second->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
	}

	
	static bool crash(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		if(!one->checkActive()||!second->checkActive()) return false;
		bool ifClose = twoClose(one, second);
		if(!ifClose) return false;
		{
			std::lock_guard lock1(one->dir_read);
			std::lock_guard lock2(second->dir_read);
			//it is to correct because there might occur a deadlock
			if(one->actual == second->actual && one->dir == -second->dir) return true;
			return false;
		}
	}
	
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
		pointThread->join();
	}
};

