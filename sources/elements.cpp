#include "elements.hpp"
#include <random>
//In future we will use random here
//and later something even more wise - heuristics

double Point::close;

double Point::defaultCapacity;

int Point::levels;

//W funkcjach choose zwraca się parę: (krawędź, kierunek na krawędzi)


std::pair<general_ptr<Edge>, char> SpecialPoint::chooseExcept
(const general_ptr<Edge> & exception, const general_ptr<Point> & aim) {
	//exception może być nullptr i wtedy to nigdy nie będzie prawdą
	auto it = edges.begin();
	auto end = edges.end();
	if(it == end) return std::pair(general_ptr<Edge>(), 0);
	//powyżej powinno być rzucenie wyjątkiem
	if(*it == exception) {
		it++;
		if(it == end) return std::pair(general_ptr<Edge>(), 0);
	}
	//powyżej powinno być rzucenie wyjątkiem
	
	general_ptr<Edge> best = *it;
	double count = best->otherSide(this)->countExcept(best, aim, levels) + best->countDelay();
	//tu jeszcze level trzeba dopisać
	it++;
	while (it != end) {
		double temp = (*it)->otherSide(this)->countExcept(*it, aim, levels) + (*it)->countDelay();
		//poniżej znak może się zmienić 
		if(temp < count) {
			count = temp;
			best = *it;
		}
		it++;
		if(it != end && *it == exception) it++;
	}
	//a kiedy są równe to czy nie losujmy?
	return std::pair(best, best->side(general_ptr<Point>(this)));
}

double SpecialPoint::countExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level) {
	//prawie to samo co wyżej
	//exception może być nullptr i wtedy to nigdy nie będzie prawdą
	if(exception.isEmpty()) return 0; //wyjątkiem rzuć
	if(level == 0) return countInterval(aim);
	//pytanie jak my powyższe przekształcamy
	auto it = edges.begin();
	auto end = edges.end();
	if(it == end) return 0;
	//powyżej powinno być rzucenie wyjątkiem
	if(*it == exception) {
		it++;
		if(it == end) return 0;
	}
	//powyżej powinno być rzucenie wyjątkiem
	double count = (*it)->otherSide(this)->countExcept(*it, aim, level - 1)
		+ (*it)->countDelay();
	it++;
	while (it != end) {
		double temp = (*it)->otherSide(this)->countExcept(*it, aim, level - 1)
		+ (*it)->countDelay();
		//poniżej znak może się zmienić 
		if(temp < count)
			count = temp;
		it++;
		if(it != end && *it == exception) it++;
	}
	//a kiedy są równe to czy nie losujmy?
	return count;
}

std::pair<general_ptr<Edge>, char> UsualPoint::chooseExcept
(const general_ptr<Edge> & exception, const general_ptr<Point> & aim) {
	if(exception.isEmpty()) {
		double count1 = myEdges.first->otherSide(this)->countExcept(myEdges.first, aim, levels);
		double count2 = myEdges.second->otherSide(this)->countExcept(myEdges.second, aim, levels);
		general_ptr<Edge> best = count1<count2?myEdges.first:myEdges.second;
		return std::pair(best, best->side(general_ptr<Point>(this)));
	}
	if (myEdges.first != exception) return std::pair(myEdges.first, myEdges.first->side(general_ptr<Point>(this)));
	return std::pair(myEdges.second, myEdges.second->side(general_ptr<Point>(this)));
}

double UsualPoint::countExcept
(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level) {
	if(exception.isEmpty()) return 0; //rzuć wyjątkiem
	if(level == 0) return countInterval(aim);
	if(myEdges.first != exception) return myEdges.first->otherSide(this)->countExcept(myEdges.first, aim, level - 1);
	return myEdges.second->otherSide(this)->countExcept(myEdges.second, aim, level - 1);
}
//uwaga! trzeba coś dodać

std::pair<double, double> Point::countDimensions(const general_ptr<Point> & one, const general_ptr<Point> & second) {
		double xdiff = one->x - second->x;
		double ydiff = one->y - second->y;
		double distance = sqrt(xdiff*xdiff + ydiff*ydiff);
		double angle = atan2(-ydiff, -xdiff);
		return std::pair(distance, angle);
} //liczy ważne parametry dla krawędzi na podstawie położeń jej punktów krańcowych

void Edge::countDimensions() {
		auto dimensions = Point::countDimensions(begin, end);
		length = dimensions.first;
		angle = dimensions.second;
} //tu wykorzystano wcześniejszą funkcję i widać przypisania do parametrów krawędzi

bool Point::spotted(double x, double y) {
		double xdiff = x - this->x;
		double ydiff = y - this->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close); //pitagoras <= ...
}

void Edge::countLength() { //nieużyta narazie
		auto beginPos = begin->locate();
		auto endPos = end->locate();
		double xdiff = beginPos.first - endPos.first;
		double ydiff = beginPos.second - endPos.second;
		length = sqrt(xdiff*xdiff - ydiff*ydiff);
}
