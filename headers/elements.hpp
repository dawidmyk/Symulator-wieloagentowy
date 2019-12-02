#include "general.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <mutex>
class Edge;
class Rander {
	std::unique_ptr<std::mt19937> generator;
	std::mutex rand_mutex;
	public:
	void makeSeed() {
		generator.reset(new std::mt19937(std::time(0)));
	}
	int generate(int size) {
		std::lock_guard lock(rand_mutex);
		std::uniform_int_distribution dist(0, size - 1);
		return dist(*generator);
	}
};
class Point {
	
	float x;
	float y;
	
	protected:
	Rander & rander;
	
	public:
	static float close;
	
	Point(float x, float y, Rander & rander): x(x), y(y), rander(rander) {}
	
	virtual std::pair<std::general_ptr<Edge>, char> choose() = 0;
	virtual std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception) = 0;

	bool spotted(float x, float y) {
		float xdiff = x - this->x;
		float ydiff = y - this->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
	}
	
	static std::pair<float, float> countDimensions(const std::general_ptr<Point> & one, const std::general_ptr<Point> & second) {
		float xdiff = one->x - second->x;
		float ydiff = one->y - second->y;
		float distance = sqrt(xdiff*xdiff + ydiff*ydiff);
		float angle = atan2(ydiff, xdiff);
		return std::pair(distance, angle);
	}
	
	std::pair<float, float> locate() {
		return std::pair(x, y);
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
	float angle;
	
	Edge(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end, int fragments):
		begin(begin),
		end(end),
		properties_num(fragments)
		{	
		}
	
	
	void countDimensions() {
		auto dimensions = Point::countDimensions(begin, end);
		length = dimensions.first;
		piece_length = length/properties_num;
		angle = dimensions.second;
	}
		
	double velocityAt(int fragment) {
		return properties.at(fragment).capacity;
	}
	std::general_ptr<Point> otherSide(const std::general_ptr<Point> & point) {
		if(begin == point) return end;
		else if(begin == end) return begin;
		return std::general_ptr<Point>();
	}
	
	char side(const std::general_ptr<Point> & point) {
		if(begin == point) return 1;
		else if(end == point) return -1;
		return 0;
	}
	
	int getFragmentNum() {
		return properties_num;
	}
	
	float getAngle() {
		return angle;
	}
	
	float getFragmentLength() {
		return piece_length;
	}
	
	void setProperties(const std::vector<EdgeProperty> & properties) {
		this->properties = properties;
		properties_num = properties.size();
	}
	
	void addProperty(const EdgeProperty & property) {
		properties.push_back(property);
		properties_num++;
	}
	
};
	
class SpecialPoint : public Point {
	//.. they will can be start and end points
	//and represent cities
	public:
	
	SpecialPoint(float x, float y, Rander & rander): Point(x, y, rander) {}
	
	std::vector<std::general_ptr<Edge>> edges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
	
};

class UsualPoint : public Point {
	public:
	
	UsualPoint(float x, float y, Rander & rander): Point(x, y, rander) {}
	
	std::pair<std::general_ptr<Edge>, std::general_ptr<Edge>> myEdges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
};
