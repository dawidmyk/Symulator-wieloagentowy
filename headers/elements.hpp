#include "general.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <mutex>
#include <ctime>

#ifndef ELEMENTS
#define ELEMENTS

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
	
	double x;
	double y;
	
	protected:
	Rander & rander;
	
	static double close;
	
	public:
	
	Point(double x, double y, Rander & rander): x(x), y(y), rander(rander) {}
	
	virtual std::pair<std::general_ptr<Edge>, char> choose() = 0;
	virtual std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception) = 0;
	virtual void addEdge(const std::general_ptr<Edge> & edge) = 0;
	
	bool spotted(double x, double y);
	
	static std::pair<double, double> countDimensions(const std::general_ptr<Point> & one, const std::general_ptr<Point> & second);
	
	std::pair<double, double> locate() {
		return std::pair(x, y);
	}
	
	static void setClose(double close) {
		Point::close = close;
	}
	
};

class EdgeProperty {
	//here are defined some Edge features
	//like capacity
public:
	EdgeProperty(double c) : capacity(c) {}
	double capacity;
};

class Edge {
public:
	std::general_ptr<Point> begin;
	std::general_ptr<Point> end;
	//these could be other types of pointer
	std::vector<EdgeProperty> properties;
	//and other type of collection used
	int properties_num;
	double length;
	double piece_length;
	double angle;

	Edge(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end, double capacity = 1) :
		begin(begin),
		end(end),
		properties_num(0)
	{
		begin->addEdge(std::general_ptr(this));
		end->addEdge(std::general_ptr(this));
		EdgeProperty property = EdgeProperty(capacity);
		addProperty(property);
		countLength();
	}
	
	
	void countDimensions();
	
	void countLength();

		
	double velocityAt(int fragment) {
		return properties.at(fragment).capacity;
	}
	std::general_ptr<Point> otherSide(const std::general_ptr<Point> & point) {
		if(begin == point) return end;
		else if(end == point) return begin;
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
	
	double getAngle() {
		return angle;
	}
	
	double getFragmentLength() {
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
	
	SpecialPoint(double x, double y, Rander & rander): Point(x, y, rander) {}
	
	std::vector<std::general_ptr<Edge>> edges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
	void addEdge(const std::general_ptr<Edge> & edge) {
		edges.push_back(edge);
	}
};

class UsualPoint : public Point {
	public:
	
	UsualPoint(double x, double y, Rander & rander): Point(x, y, rander) {}
	
	std::pair<std::general_ptr<Edge>, std::general_ptr<Edge>> myEdges;
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
	void addEdge(const std::general_ptr<Edge> & edge) {
		if(myEdges.first.isEmpty()) myEdges.first = edge;
		else if(myEdges.second.isEmpty()) myEdges.second = edge;
	}
};

#endif
