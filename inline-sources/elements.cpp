


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
	


inline EdgeProperty::EdgeProperty(double c) : capacity(c) {}


inline Edge::Edge(const general_ptr<Point> & begin, const general_ptr<Point> & end, double capacity) :
	begin(begin),
	end(end),
	properties_num(0)
{
	begin->addEdge(general_ptr(this)); //ktoś musi dodać do krańców tą krawędź
	end->addEdge(general_ptr(this));
	EdgeProperty property = EdgeProperty(capacity);
	addProperty(property); //tutaj zakładamy w szkielecie że każda krawędź ma po prostu jedną
	//Property o prędkości 1
}

	
inline double Edge::velocityAt(int fragment) { //taki getter
	//agent pyta o prędkość osiągalną na fragmencie o pewnym numerze
	return properties.at(fragment).capacity;
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

inline int Edge::getFragmentNum() { //taki getter
	return properties_num;
}

inline double Edge::getAngle() { //taki getter
	return angle;
}

inline double Edge::getFragmentLength() { //taki getter
	return piece_length;
}

inline void Edge::setProperties(const std::vector<EdgeProperty> & properties) {
	this->properties = properties;
	properties_num = properties.size();
} //za jednym zamachem można ustawić wszystkie propertiesy

inline void Edge::addProperty(const EdgeProperty & property) {
	properties.push_back(property);
	properties_num++;
} //albo można je dodawać sukcesywnie




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


