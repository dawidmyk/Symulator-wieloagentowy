#include "general.hpp"
#include <vector>
#include <cmath>

class Edge;

class Point {
	
	float x;
	float y;
	
	public:
	static float close;
	
	Point(float x, float y): x(x), y(y) {}
	
	virtual std::pair<std::general_ptr<Edge>, char> choose() = 0;
	virtual std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception) = 0;

	bool spotted(float x, float y) {
		float xdiff = x - this->x;
		float ydiff = y - this->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
	}
	
};

class EdgeProperty {
	//here are defined some Edge features
	//like capacity
	public:
	float capacity;
};

class Edge {
	public:
	std::general_ptr<Point> begin;
	std::general_ptr<Point> end;
	//these could be other types of pointer
	std::vector<EdgeProperty> properties;
	//and other type of collection used
	int properties_num;
	float length;
	float piece_length;
	
	Edge(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end, int fragments):
		begin(begin),
		end(end),
		properties_num(fragments)
		{}
	double velocityAt(int fragment) {
		return properties.at(fragment).capacity;
	}
	std::general_ptr<Point> otherSide(const std::general_ptr<Point> & point) {
		if(begin == point) return end;
		else if(begin == end) return begin;
		return std::general_ptr<Point>();
	}
	
	char side(std::general_ptr<Point> & point) {
		if(begin == point) return 1;
		else if(end == point) return -1;
		return 0;
	}
	
	int getFragmentNum() {
		return properties_num;
	}
	
};
	
class SpecialPoint : public Point {
	//.. they will can be start and end points
	//and represent cities
	public:
	
	SpecialPoint(float x, float y): Point(x, y) {}
	
	std::vector<std::general_ptr<Edge>> edges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
	
};

class UsualPoint : public Point {
	public:
	
	UsualPoint(float x, float y): Point(x, y) {}
	
	std::pair<std::general_ptr<Edge>, std::general_ptr<Edge>> myEdges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
};
