
#include <random>
#include "headers.hpp"
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
	general_ptr<Edge> best;
	if(it == end) return std::pair(best, 0);
	//to znaczy że punkt nie ma żadnych krawędzi
	Distance dist(countInterval(aim), false);
	while (it != end) {
		Distance new_dist = (*it)->otherSide(this)->countExcept(*it, aim, levels) + (*it)->countDelay();
		new_dist.exception = ((*it) == exception);
			//poniżej znak może się zmienić 
		if(new_dist < dist) {
			dist = new_dist;
			best = *it;
		}
		it++;
	}
	if(best.isEmpty()) 
		return std::pair(best, 0);
		//agent będzie musiał rozważyć że nie wybrano żadnej krawędzi
	//tu jest możliwość wysunięcia nullptr!
	return std::pair(best, best->side(general_ptr<Point>(this)));
}

Distance SpecialPoint::countExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level) {
	//prawie to samo co wyżej
	//exception może być nullptr i wtedy to nigdy nie będzie prawdą
	if(exception.isEmpty()) throw GeneralException(std::string(__FILE__), __LINE__);
	if(aim.get() == this)
		return Distance(0, true);
	if(level == 0) return Distance(countInterval(aim), true);
	//pytanie jak my powyższe przekształcamy
	auto it = edges.begin();
	auto end = edges.end();
	if(it == end) throw GeneralException(std::string(__FILE__), __LINE__);
	//powyżej powinno być rzucenie wyjątkiem
	//powyżej powinno być rzucenie wyjątkiem
	Distance dist(countInterval(aim), false);
	while (it != end) {
		Distance new_dist = (*it)->otherSide(this)->countExcept(*it, aim, level - 1) + (*it)->countDelay();
		new_dist.exception = ((*it) == exception);
			//poniżej znak może się zmienić 
		if(new_dist < dist) {
			dist = new_dist;
		}
		it++;
	}
	dist.hide();
	return dist;
}

std::pair<general_ptr<Edge>, char> UsualPoint::chooseExcept
(const general_ptr<Edge> & exception, const general_ptr<Point> & aim) {
	general_ptr<Edge> best;
	if(myEdges.first.isEmpty() && myEdges.second.isEmpty()) return std::pair(best, 0);
	if(myEdges.first.isEmpty()) best = myEdges.second;
	if(myEdges.second.isEmpty()) best = myEdges.first;
	if(exception.isEmpty()) {
		Distance count1 = myEdges.first->otherSide(this)->countExcept(myEdges.first, aim, levels) + myEdges.first->countDelay();
		Distance count2 = myEdges.second->otherSide(this)->countExcept(myEdges.second, aim, levels) + myEdges.second->countDelay();
		best = count1<count2?myEdges.first:myEdges.second;
	}
	if (myEdges.first != exception) 
		best = myEdges.second;
	else 
		best = myEdges.first;
	return std::pair(best, best->side(general_ptr<Point>(this)));
}


Distance UsualPoint::countExcept
(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level) {
	if(exception.isEmpty()) throw GeneralException(std::string(__FILE__), __LINE__);
	if(level == 0) return Distance(countInterval(aim), true);
	if(myEdges.first.isEmpty() && myEdges.second.isEmpty()) 
		throw GeneralException(std::string(__FILE__), __LINE__);

	if(myEdges.first.isEmpty() || myEdges.second.isEmpty())
		return Distance(countInterval(aim), false);
		
		//to sugeruje że nieprzezroczysty jest lepszy od cofającego
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
