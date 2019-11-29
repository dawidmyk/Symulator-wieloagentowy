#include "general.hpp"
class Point {
	public:
	float x;
	float y;
	virtual std::pair<std::general_ptr<Edge>, char> choose() = 0;
	virtual std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception) = 0;
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
	
	double velocityAt(int fragment) {
		return properties.at(fragment);
	}
	std::general_ptr<Point> otherSide(std::general_ptr<Point> & point) {
		if(begin == point) return end;
		else if(begin == end) return begin;
		return std::general_ptr<Point>();
	}
	
	char side(std::general_ptr<Point> & point) {
		if(begin == point) return 1;
		else if(end == point) return -1;
		return 0;
	}
	
};

class SpecialPoint : public Point {
	//.. they will can be start and end points
	//and represent cities
	public:
	std::vector<std::general_ptr<Edge>> edges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(std::shared_ptr<Edge> exception);
	
};

class UsualPoint : public Point {
	public:
	std::pair<std::general_ptr<Edge>, std::general_ptr<Edge>> myEdges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(std::general_ptr<Edge> exception);
};

class Graph {
	//here pointers in containers
	//are to be owners of the objects
	public:
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	void addUsualPoint(float x, float y) {
		points.push_back(std::unique_ptr<Point>(new UsualPoint(x, y)));
	}
	
	void addSpecialPoint(float x, float y) {
		points.push_back(std::unique_ptr<Point>(new SpecialPoint(x, y)));
	}
	
	std::general_ptr<Point> spotPoint(float x, float y) {
		std::general_ptr<Point> ret;
		char found = 0;
		for(auto & ptr : points) {
			if(ptr.spotted(x, y)) {
				ret = ptr;
				found++;
			}
			if (found == 2) return std::general_ptr();
		}
		if(found == 1) return ret;
		if(found == 0) return std::general_ptr();
	}
	
	void addEdge(float x1, float x2, float y1, float y2)
	}

};

