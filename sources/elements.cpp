#include "elements.hpp"
#include <random>
//In future we will use random here
//and later something even more wise - heuristics

double Point::close;

//W funkcjach choose zwraca się parę: (krawędź, kierunek na krawędzi)
std::pair<general_ptr<Edge>, char> SpecialPoint::choose() {
	auto edge = edges.at(rander.generate(edges.size()));
	return std::pair(edge, edge->side(general_ptr<Point>(this)));
}

std::pair<general_ptr<Edge>, char> SpecialPoint::chooseExcept(const general_ptr<Edge> & exception) {
	int now = 0;
	while(edges.at(now) != exception) now++;
	//musimy odnaleźć numer podanej krawędzi 
	int n = edges.size();
	int randed = rander.generate(n - 1); //nie może wylosować przedostatniej
	if(randed == now) randed = n - 1; //jeśli wylosował tą wyłączoną, to zamieni ją na przedostatnią
	auto edge = edges.at(randed);
	return std::pair(edge, edge->side(general_ptr<Point>(this)));
}

std::pair<general_ptr<Edge>, char> UsualPoint::choose() {
	int i = rander.generate(2); //są 2 możliwości w UsualPoincie który to może mieć
	//tylko 2 rozejścia
	general_ptr<Edge> edge;
	if(i == 0) edge = myEdges.first;
	else edge = myEdges.second;
	return std::pair(edge, edge->side(general_ptr<Point>(this)));
}

std::pair<general_ptr<Edge>, char> UsualPoint::chooseExcept(const general_ptr<Edge> & exception) {
	if (myEdges.first != exception) return std::pair(myEdges.first, myEdges.first->side(general_ptr<Point>(this)));
	return std::pair(myEdges.second, myEdges.second->side(general_ptr<Point>(this)));
} //tu nie ma losowania - sytuacja jest deterministyczna - idziemy tam, skąd nie przyszliśmy

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
		piece_length = length/properties_num;
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
