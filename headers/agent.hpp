#include "elements.hpp"
#include <thread>
class Agent {
	public:
	static float close;
	float x;
	float y;
	float roadAngle;
	std::mutex posits;
	//std::thread edgeThread;
	std::thread pointThread;
	
	std::general_ptr<Point> begin, end;
	std::general_ptr<Edge> actualEdge;
	int fragment; //used for checking velocity
	
	Agent(std::general_ptr<Point> begin, std::general_ptr<Point> end): begin(begin), end(end) {}
	
	void runFunction();
	void threadFunction();
	
	double getVelocity() {
		return actualEdge->velocityAt(fragment);
	}
	double getFragmentLength() {
		return actualEdge->piece_length;
	}
	
	std::pair<float, float> locate() {
		std::lock_guard(posits);
		return std::pair<float, float>(x, y);
	}
	
};
