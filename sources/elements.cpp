#include "elements.hpp"
#include <random>
//In future we will use random here
//and later something even more wise - heuristics

double Point::close;

std::pair<std::general_ptr<Edge>, char> SpecialPoint::choose() {
	int n = edges.size();
	std::uniform_int_distribution dist(0, n - 1);
	auto edge = edges.at(rander.generate(edges.size()));
	return std::pair(edge, edge->side(std::general_ptr<Point>(this)));
}

std::pair<std::general_ptr<Edge>, char> SpecialPoint::chooseExcept(const std::general_ptr<Edge> & exception) {
	int now = 0;
	while(edges.at(now) != exception) now++;
	int n = edges.size();
	int randed = rander.generate(n);
	if(randed == now) randed = n - 1;
	auto edge = edges.at(randed);
	return std::pair(edge, edge->side(std::general_ptr<Point>(this)));
}

std::pair<std::general_ptr<Edge>, char> UsualPoint::choose() {
	std::uniform_int_distribution dist(0, 1);
	int i = rander.generate(2);
	std::general_ptr<Edge> edge;
	if(i == 0) edge = myEdges.first;
	else edge = myEdges.second;
	return std::pair(myEdges.first, myEdges.first->side(std::general_ptr<Point>(this)));
}

std::pair<std::general_ptr<Edge>, char> UsualPoint::chooseExcept(const std::general_ptr<Edge> & exception) {
	if (myEdges.first != exception) return std::pair(myEdges.first, myEdges.first->side(std::general_ptr<Point>(this)));
	return std::pair(myEdges.second, myEdges.second->side(std::general_ptr<Point>(this)));
}

std::pair<double, double> Point::countDimensions(const std::general_ptr<Point> & one, const std::general_ptr<Point> & second) {
		double xdiff = one->x - second->x;
		double ydiff = one->y - second->y;
		double distance = sqrt(xdiff*xdiff + ydiff*ydiff);
		double angle = atan2(ydiff, xdiff);
		return std::pair(distance, angle);
}

void Edge::countDimensions() {
		auto dimensions = Point::countDimensions(begin, end);
		length = dimensions.first;
		piece_length = length/properties_num;
		angle = dimensions.second;
}

bool Point::spotted(double x, double y) {
		double xdiff = x - this->x;
		double ydiff = y - this->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
}

void Edge::countLength() {
		auto beginPos = begin->locate();
		auto endPos = end->locate();
		double xdiff = beginPos.first - endPos.first;
		double ydiff = beginPos.second - endPos.second;
		length = sqrt(xdiff*xdiff - ydiff*ydiff);
	}
