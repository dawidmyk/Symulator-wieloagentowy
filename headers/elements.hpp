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
	void makeSeed();
	int generate(int size);
};
class Point {
	
	double x;
	double y;
	
	protected:
	Rander & rander;
	
	static double close;
	
	public:
	
	Point(double x, double y, Rander & rander);
	
	virtual std::pair<general_ptr<Edge>, char> choose() = 0;
	//metoda która wybiera krawędź na początku życia agenta, w jego punkcie startowym
	//tam żadna krawędź nie jest wyłączona z wyboru, bo żadną nie doszedł do tego punktu
	
	virtual std::pair<general_ptr<Edge>, char> chooseExcept(const general_ptr<Edge> & exception) = 0;
	//każdy późniejszy obór nowej krawędzi
	//trzeba podać tą, którą się doszłą i ona nie będzie mogła zostać wybrana
	
	virtual void addEdge(const general_ptr<Edge> & edge) = 0; //punkt ma zbiór krawędzi
	//(o odpowiedniej formie w każdej z klas pochodnych Pointa)
	
	bool spotted(double x, double y); //czy podane x i y są wystarczająco blisko
	//x i y tego punktu, by można powiedzieć, że "strzał był udany"
	//przydaje się przy nakładaniu krawędzi na punkty
	
	static std::pair<double, double> countDimensions(const general_ptr<Point> & one, const general_ptr<Point> & second);
	
	std::pair<double, double> locate();
	
	static void setClose(double close);
	
};

class EdgeProperty {
	//tutaj są zdefiniowane pewne cechy przypisane
	//do FRAGMENTU krawędzi
	//narazie tylko capacity przekładające
	//się bezpośrednio na prędkość
	//którą będą mieli agenci (ze swoim przelicznikiem)
	//na tej krawędzi
public:
	EdgeProperty(double c);
	double capacity;
};

class Edge {
public:
	general_ptr<Point> begin;
	general_ptr<Point> end;
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

	Edge(const general_ptr<Point> & begin, const general_ptr<Point> & end, double capacity = 1);
	
	
	void countDimensions();
	
	void countLength();

		
	double velocityAt(int fragment);
	
	general_ptr<Point> otherSide(const general_ptr<Point> & point);
	
	char side(const general_ptr<Point> & point);
	//sprawdza czy dany punkt jest końcem czy początkiem
	//czy ani jednym ani drugim
	
	int getFragmentNum();
	
	double getAngle();
	
	double getFragmentLength();
	
	void setProperties(const std::vector<EdgeProperty> & properties);
	//za jednym zamachem można ustawić wszystkie propertiesy
	
	void addProperty(const EdgeProperty & property);
	//albo można je dodawać sukcesywnie
	
};
	
class SpecialPoint : public Point {
	//one miałyby chyba reprezentować miasta
	//i tylko one być końcowe/początkowe
	//choć narazie wszystkie mogą być
	public:
	
	SpecialPoint(double x, double y, Rander & rander);
	
	std::vector<general_ptr<Edge>> edges; //on ma dowolną liczbę krawędzi więc trzyma je w vektorze
	//choć mógłby w std::list
	
	std::pair<general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<general_ptr<Edge>, char> chooseExcept(const general_ptr<Edge> & exception);
	void addEdge(const general_ptr<Edge> & edge);
	//metodą wektora do dodawania obiektów
};

class UsualPoint : public Point {
	public:
	
	UsualPoint(double x, double y, Rander & rander);
	
	std::pair<general_ptr<Edge>, general_ptr<Edge>> myEdges;
	std::pair<general_ptr<Edge>, char> choose(); //both virtual in base class
	std::pair<general_ptr<Edge>, char> chooseExcept(const general_ptr<Edge> & exception);
	void addEdge(const general_ptr<Edge> & edge);
};

#include "elements.cpp"
#endif
