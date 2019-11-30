#include "elements.hpp"
#include <thread>
#include <mutex>
class Agent {
	public:
	static float close;
	float x;
	float y;
	float roadAngle;
	char dir;
	std::mutex posits;
	std::mutex dir_read;
	std::mutex edgeLock;
	//std::thread edgeThread;
	std::thread pointThread;
	
	std::general_ptr<Point> begin, end;
	std::general_ptr<Edge> actual;
	int fragment; //used for checking velocity
	
	Agent(std::general_ptr<Point> begin, std::general_ptr<Point> end): begin(begin), end(end) {}
	
	void runFunction();
	void threadFunction();
	
	double getVelocity() {
		return actual->velocityAt(fragment);
	}
	double getFragmentLength() {
		return actual->piece_length;
	}
	
	std::pair<float, float> locate() {
		std::lock_guard<std::mutex> lock(posits);
		return std::pair<float, float>(x, y);
	}
	
	static bool twoClose(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		std::lock_guard<std::mutex> lock1(one->posits);
		std::lock_guard<std::mutex> lock2(second->posits);
		float xdiff = one->x - second->x;
		float ydiff = one->y - second->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
	}

	
	static bool crash(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
			bool ifClose = twoClose(one, second);
			if(!ifClose) return false;
			{
				std::lock_guard<std::mutex> lock1(one->dir_read);
				std::lock_guard<std::mutex> lock2(second->dir_read);
				//it is to correct because there might occur a deadlock
				if(one->actual == second->actual && one->dir == -second->dir) return true;
				return false;
			}
	}

};

