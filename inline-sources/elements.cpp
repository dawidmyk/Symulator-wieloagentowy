
inline void Rander::makeSeed() {
	generator.reset(new std::mt19937(std::time(0)));
	//ziarno to aktualny czas
	//z dokładnością bodajże do sekund
	//co jest typowe dla aplikacji losujących
}
inline int Rander::generate(int size) {
	std::lock_guard lock(rand_mutex); //zajęcie blokady
	std::uniform_int_distribution dist(0, size - 1); //definiujemy funktor
	//którym jest jakiś konkretny rozkład - tu równomierny dyskretny
	//0 to minimalna możliwa wylosowana liczba
	//size-1 to maksymalna możliwa liczba
	return dist(*generator); //funktor jako argument pobiera generator
	//którego ma użyć do generacji
} //zwolnienie blokady

	
inline Point::Point(double x, double y, Rander & rander): x(x), y(y), rander(rander) {}

inline std::pair<double, double> Point::locate() { //zwraca współrzędne w postaci pary
	//potem się do nich trzeba odwoływać jako first i second
	return std::pair(x, y);
}

inline void Point::setClose(double close) {
	Point::close = close;
}

inline void Point::setDefaultCapacity(double cap) {
	Point::defaultCapacity = cap;
}

inline void Point::setLevels(int levels) {
	Point::levels = levels;
	//trzeba skontrolować czy złego levels
	//nie będzie podane
}
	
inline double Point::countInterval(const general_ptr<Point> & aim) {
	double xdiff = aim->x - x;
	double ydiff = aim->y - y;
	return defaultCapacity * sqrt(xdiff*xdiff + ydiff*ydiff);
}

inline double Edge::countDelay() {
	return capacity * length;
	//tu jest prosto bo to jest wersja bez EdgeProperty
}



inline Edge::Edge(const general_ptr<Point> & begin, const general_ptr<Point> & end, double cap) :
	begin(begin),
	end(end),
	capacity(cap)
{
	begin->addEdge(general_ptr(this)); //ktoś musi dodać do krańców tą krawędź
	end->addEdge(general_ptr(this));
}


	
inline double Edge::velocityAt() { //taki getter
	//agent pyta o prędkość osiągalną na fragmencie o pewnym numerze
	return capacity;
}
inline general_ptr<Point> Edge::otherSide(const general_ptr<Point> & point) {
	if(begin == point) return end;
	else if(end == point) return begin;
	return general_ptr<Point>(); //inaczej return nullptr
	//znajduje punkt znajdujący się po przeciwnej stronie krawędzi niż
	//podany
}

inline char Edge::side(const general_ptr<Point> & point) {
	if(begin == point) return 1;
	else if(end == point) return -1;
	return 0;
} //sprawdza czy dany punkt jest końcem czy początkiem
//czy ani jednym ani drugim

inline double Edge::getAngle() { //taki getter
	return angle;
}

inline double Edge::getLength() { //taki getter
	return length;
}


inline SpecialPoint::SpecialPoint(double x, double y, Rander & rander): Point(x, y, rander) {}


inline void SpecialPoint::addEdge(const general_ptr<Edge> & edge) {
	edges.push_back(edge); //tutaj już wiadomo jak dodać kolejną krawędź
} //metodą wektora do dodawania obiektów



inline UsualPoint::UsualPoint(double x, double y, Rander & rander): Point(x, y, rander) {}


inline void UsualPoint::addEdge(const general_ptr<Edge> & edge) {
	if(myEdges.first.isEmpty()) myEdges.first = edge;
	else if(myEdges.second.isEmpty()) myEdges.second = edge;
	//pierwsza dodawana wchodzi na pierwszą pozycję pary
	//druga na drugą
	//można dodawać kolejne ale nie będą już obsłużone
}
