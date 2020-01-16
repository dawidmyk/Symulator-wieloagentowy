#include "general.hpp"
#include <vector>
#include <cmath>
#include <random>
#include <mutex>
#include <ctime>

#ifndef ELEMENTS
#define ELEMENTS

class Edge;
/** @brief Klasa opakowująca generator z biblioteki standardowe
 * 
 * Przygotowuje go na dostęp wielowątkowy */
class Rander { //klasa losująca
	/* trzeba losować następną krawędź którą agent wybierze gdy dojdzie do wierzchołka
	 * (jeśli jest wybór)
	 * bo agent się nie będzie cofał */
	//Tu coś trzeba napisać
	std::unique_ptr<std::mt19937> generator; //taki specjalny generator
	/* w unique_ptr bo obiekt Rander jest jego właścicielem ale nie może
	 * go utworzyć od razu, bo musi zasiać mu ziarno w jego konstruktorze */
	///@brief Realizacja sekcji krytycznej w dostępie do generatora
	std::mutex rand_mutex; 
	/* tylko jeden wątek może mieć dostęp jednocześnie
	 * do maszyny losującej */
	public:
	///@brief Tak jak większość generatorów (pseudolosowych) musi być zasiany
	void makeSeed();
	///@brief Użycie generatora
	///@param size Co może zostać zwrócone? 0 <-> size-1
	int generate(int size);
};

///@brief Abstrakcyjny punkt w przestrzeni (miasto)
class Point {
	
	///@name Współrzędne w przestrzeni
	///@{
	double x;
	double y;
	///@}
	
	protected:
	Rander & rander;
	
	/**@brief Jeśli punkty są od siebie bliżej niż ta wartość
	 * to znaczy że są jednym punktem */
	static double close;
	
	///@brief Używane w heurystyce
	/** Ostatni człon heurystyki jest robiony poza jakąkolwiek
	 * krawędzią więc nie ma jakiej pojemności wykorzystać */
	static double defaultCapacity;
	
	///@brief Liczba krawędziowych stopni heurystyki
	static int levels;
	
	public:
	
	Point(double x, double y, Rander & rander);
	
	///@brief Wybór następnej krawędzi
	/** gdy się zaczyna lub gdy się kończy poprzednią.
	 * Obecna wersja używa heurystyki */
	virtual std::pair<general_ptr<Edge>, char> chooseExcept
	(const general_ptr<Edge> & exception, const general_ptr<Point> & aim) = 0;
	/* każdy późniejszy obór nowej krawędzi
	 * trzeba podać tą, którą się doszłą i ona nie będzie mogła zostać wybrana */
	
	///@brief Heurystyczna ocena opłacalności wzięcia tego punktu jako następnego
	/** Metoda rekurencyjna */
	///@param exception Krawędź którą dochodzimy więc nie możemy nią wyjść w następnym kroku
	///@param aim Cel agenta, który pośrednio wywołuje tą metodę w swoim wątku (Agent::end) - niezmiennik rekursji
	///@param level Liczba poziomów rekursji jakie jeszcze można 
	///@return Szacowany czas dojazdu
	virtual double countExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level) = 0; 
	
	///@brief Dodanie krawędzi (enksapsulacja - też nie wiadomo jak krawędzie są trzymane)
	virtual void addEdge(const general_ptr<Edge> & edge) = 0; 
	/* punkt ma zbiór krawędzi
	 * (o odpowiedniej formie w każdej z klas pochodnych Pointa) */
	
	///@brief Metoda ta miała służyć do graficznej interakcji
	/** a dokładnie do rysowania grafu przez użytkownika */
	bool spotted(double x, double y); 
	/* czy podane x i y są wystarczająco blisko
	 * x i y tego punktu, by można powiedzieć, że "strzał był udany"
	 * przydaje się przy nakładaniu krawędzi na punkty */
	
	///@brief Liczy długość i nachylenie krawędzi, która będzie rozpięta przez te punkty
	static std::pair<double, double> countDimensions(const general_ptr<Point> & one, const general_ptr<Point> & second);
	
	///@brief Getter, który zwraca współrzędne punktu
	std::pair<double, double> locate();
	
	///@brief Na potrzeby heurystyki oblicza odległość (czasową) do podanego punktu
	/** Czasową gdyż wykorzystuje przemnożnik Point::defaultCapacity */
	double countInterval(const general_ptr<Point> & aim);
	
	///@brief Ustala wartość Point::close 
	static void setClose(double close);
	
	///@brief Ustala wartość Point::defaultCapacity
	static void setDefaultCapacity(double cap);
	
	///@brief Ustala wartość Point::levels
	static void setLevels(int levels);
};

///@brief Klasa nie użyta w tej wersji
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

///@brief Połączenie między punktami - fragment drogi
class Edge {
public:
	///@name Punkty rozpinające
	///@{
	general_ptr<Point> begin;
	general_ptr<Point> end;
	///@}
	/* ma początek i koniec ! jest ukierunkowana
	 * tu może być coś takiego jak std::list
     * długość tego vectora musi być równa properties_num
	 * properties_num jest osobną zmienną żeby było szybciej
	 * bo wiadomo że vector można odpytać o rozmiar */
	 
	///@brief Długość krawędzi
	double length;
	/* liczenie długości za każdym razem by naprawdę spowolniło
	 * bo się ją liczy za pomocą pitagorasa
	 * ale się raczej używa powyższej długości FRAGMENTu,
	 * w metodzie runFunction agenta */
	
	///@brief Nachylenie krawędzi
	double angle; 
	/* to również jest używane przez agenta
	 * w tej metodzie i liczony z tego cos i sin */
	
	///@brief Pojemność krawędzi (jej przemnożnik prędkości) 
	double capacity;
	/* dodane do tej klasy jako że EdgeProperty już nie ma */
	
	Edge(const general_ptr<Point> & begin, const general_ptr<Point> & end, double cap = 1);
	
	///@brief Nadaje krawędzi zarówno długość jak i nachylenie
	void countDimensions();
	
	///@brief Nadaje krawędzi tylko długość, nieużyta
	void countLength();

	///@brief W obecnej wersji jest po prostu getterem pojemności
	double velocityAt();
	
	///@brief Zwraca przeciwny kraniec od podanego
	general_ptr<Point> otherSide(const general_ptr<Point> & point);
	
	///@brief Podaje z której strony jest dany punkt
	/** Czy jest początkiem czy końcem? */
	char side(const general_ptr<Point> & point);
	
	///@brief Getter nachylenia Edge::angle
	double getAngle();
	
	///@brief Getter długości Edge::length
	double getLength();
	
	///@brief Ile (w przyszłości) zajmie podróż tą krawędzią?
	/** Używane w heurystyce */
	double countDelay();
	
};
	
///@brief Punkt który może być węzłem sieci drogowej
class SpecialPoint : public Point {
	//one miałyby chyba reprezentować miasta
	//i tylko one być końcowe/początkowe
	//choć narazie wszystkie mogą być
	public:
	
	SpecialPoint(double x, double y, Rander & rander);
	
	///@brief Kontener na tyle krawędzi ile chcemy
	std::vector<general_ptr<Edge>> edges; 
	/* on ma dowolną liczbę krawędzi więc trzyma je w wektorze
	 * choć mógłby w std::list */
	
	std::pair<general_ptr<Edge>, char> chooseExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim);
	double countExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level);
	void addEdge(const general_ptr<Edge> & edge);
	//Tych wirtualnych narazie nie doxygenuję
};

///@brief Punkt który może być tylko przystankiem na drodze
/** dzięki niemu połączenia nie muszą być liniami prostymi */
class UsualPoint : public Point {
	public:
	
	UsualPoint(double x, double y, Rander & rander);
	
	///@brief Kontener na tylko 2 krawędzie
	/** mniej mogłoby by być po tam są wskaźniki,
	 * ale nie chielibyśmy dopuścić do takiej sytuacji */
	std::pair<general_ptr<Edge>, general_ptr<Edge>> myEdges;
	std::pair<general_ptr<Edge>, char> chooseExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim);
	double countExcept(const general_ptr<Edge> & exception, const general_ptr<Point> & aim, int level);
	void addEdge(const general_ptr<Edge> & edge);
};

#include "inline_elements.cpp"
#endif
