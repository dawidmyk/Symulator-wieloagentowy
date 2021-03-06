#include "general.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <mutex>
#include <ctime>

#ifndef ELEMENTS
#define ELEMENTS

class Edge;
class Rander { //klasa losująca
	//trzeba losować następną krawędź którą agent wybierze gdy dojdzie do wierzchołka
	//(jeśli jest wybór)
	//bo agent się nie będzie cofał
	std::unique_ptr<std::mt19937> generator; //taki specjalny generator
	//w unique_ptr bo obiekt Rander jest jego właścicielem ale nie może
	//go utworzyć od razu, bo musi zasiać mu ziarno w jego konstruktorze
	std::mutex rand_mutex; //tylko jeden wątek może mieć dostęp jednocześnie
	//do maszyny losującej
	public:
	void makeSeed() {
		generator.reset(new std::mt19937(std::time(0)));
		//ziarno to aktualny czas
		//z dokładnością bodajże do sekund
		//co jest typowe dla aplikacji losujących
	}
	int generate(int size) {
		std::lock_guard lock(rand_mutex); //zajęcie blokady
		std::uniform_int_distribution dist(0, size - 1); //definiujemy funktor
		//którym jest jakiś konkretny rozkład - tu równomierny dyskretny
		//0 to minimalna możliwa wylosowana liczba
		//size-1 to maksymalna możliwa liczba
		return dist(*generator); //funktor jako argument pobiera generator
		//którego ma użyć do generacji
	} //zwolnienie blokady
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
	//metoda która wybiera krawędź na początku życia agenta, w jego punkcie startowym
	//tam żadna krawędź nie jest wyłączona z wyboru, bo żadną nie doszedł do tego punktu
	
	virtual std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception) = 0;
	//każdy późniejszy obór nowej krawędzi
	//trzeba podać tą, którą się doszłą i ona nie będzie mogła zostać wybrana
	
	virtual void addEdge(const std::general_ptr<Edge> & edge) = 0; //punkt ma zbiór krawędzi
	//(o odpowiedniej formie w każdej z klas pochodnych Pointa)
	
	bool spotted(double x, double y); //czy podane x i y są wystarczająco blisko
	//x i y tego punktu, by można powiedzieć, że "strzał był udany"
	//przydaje się przy nakładaniu krawędzi na punkty
	
	static std::pair<double, double> countDimensions(const std::general_ptr<Point> & one, const std::general_ptr<Point> & second);
	
	std::pair<double, double> locate() { //zwraca współrzędne w postaci pary
		//potem się do nich trzeba odwoływać jako first i second
		return std::pair(x, y);
	}
	
	static void setClose(double close) {
		Point::close = close;
	}
	
};

class EdgeProperty {
	//tutaj są zdefiniowane pewne cechy przypisane
	//do FRAGMENTU krawędzi
	//narazie tylko capacity przekładające
	//się bezpośrednio na prędkość
	//którą będą mieli agenci (ze swoim przelicznikiem)
	//na tej krawędzi
public:
	EdgeProperty(double c) : capacity(c) {}
	double capacity;
};

class Edge {
public:
	std::general_ptr<Point> begin;
	std::general_ptr<Point> end;
	//ma początek i koniec ! jest ukierunkowana
	std::vector<EdgeProperty> properties;
	//tu może być coś takiego jak std::list
	//długość tego vectora musi być równa properties_num
	//properties_num jest osobną zmienną żeby było szybciej
	//bo wiadomo że vector można odpytać o rozmiar
	int properties_num;
	double length;
	//liczenie długości za każdym razem by naprawdę spowolniło
	//bo się ją liczy za pomocą pitagorasa
	double piece_length;
	//ale się raczej używa powyższej długości FRAGMENTu,
	//w metodzie runFunction agenta
	double angle; //to również jest używane przez agenta
	//w tej metodzie i liczony z tego cos i sin

	Edge(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end, double capacity = 1) :
		begin(begin),
		end(end),
		properties_num(0)
	{
		begin->addEdge(std::general_ptr(this)); //ktoś musi dodać do krańców tą krawędź
		end->addEdge(std::general_ptr(this));
		EdgeProperty property = EdgeProperty(capacity);
		addProperty(property); //tutaj zakładamy w szkielecie że każda krawędź ma po prostu jedną
		//Property o prędkości 1
	}
	
	
	void countDimensions();
	
	void countLength();

		
	double velocityAt(int fragment) { //taki getter
		//agent pyta o prędkość osiągalną na fragmencie o pewnym numerze
		return properties.at(fragment).capacity;
	}
	std::general_ptr<Point> otherSide(const std::general_ptr<Point> & point) {
		if(begin == point) return end;
		else if(end == point) return begin;
		return std::general_ptr<Point>(); //inaczej return nullptr
		//znajduje punkt znajdujący się po przeciwnej stronie krawędzi niż
		//podany
	}
	
	char side(const std::general_ptr<Point> & point) {
		if(begin == point) return 1;
		else if(end == point) return -1;
		return 0;
	} //sprawdza czy dany punkt jest końcem czy początkiem
	//czy ani jednym ani drugim
	
	int getFragmentNum() { //taki getter
		return properties_num;
	}
	
	double getAngle() { //taki getter
		return angle;
	}
	
	double getFragmentLength() { //taki getter
		return piece_length;
	}
	
	void setProperties(const std::vector<EdgeProperty> & properties) {
		this->properties = properties;
		properties_num = properties.size();
	} //za jednym zamachem można ustawić wszystkie propertiesy
	
	void addProperty(const EdgeProperty & property) {
		properties.push_back(property);
		properties_num++;
	} //albo można je dodawać sukcesywnie
	
};
	
class SpecialPoint : public Point {
	//one miałyby chyba reprezentować miasta
	//i tylko one być końcowe/początkowe
	//choć narazie wszystkie mogą być
	public:
	
	SpecialPoint(double x, double y, Rander & rander): Point(x, y, rander) {}
	
	std::vector<std::general_ptr<Edge>> edges; //on ma dowolną liczbę krawędzi więc trzyma je w vektorze
	//choć mógłby w std::list
	
	std::pair<std::general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<std::general_ptr<Edge>, char> chooseExcept(const std::general_ptr<Edge> & exception);
	void addEdge(const std::general_ptr<Edge> & edge) {
		edges.push_back(edge); //tutaj już wiadomo jak dodać kolejną krawędź
	} //metodą wektora do dodawania obiektów
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
		//pierwsza dodawana wchodzi na pierwszą pozycję pary
		//druga na drugą
		//można dodawać kolejne ale nie będą już obsłużone
	}
};

#endif
