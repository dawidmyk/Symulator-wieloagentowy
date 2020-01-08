#include "elements.hpp"
#include <thread>
#include <mutex>
#ifndef AGENT
#define AGENT

class Agent {
	
	static double close;
	static double defaultVelocity;
	double x; //pozycja
	double y; //pozycja
	char dir; //krawędź jest jak wektor ukierunkowana
	//i agent może się poruszać zgodnie lub wbrew temu kierunkowi
	//1 - zgodnie
	//-1 - wbrew
	
	bool active;
	std::mutex posits; //blokada przy odczytywaniu
	//i zapisywaniu pozycji
	
	std::mutex dir_read; //blokada przy odczytywaniu
	//krawędzi po której się porusza i kierunku
	//na tej krawędzi
	
	std::mutex edgeLock;
	std::mutex activeLock; //blokada przy ustalaniu
	//czy agent jest aktywny czy nie

	
	std::unique_ptr<std::thread> pointThread;
	//agent jest właścicielem swojego wątku
	//ale nie można go ustalić w konstruktorze
	//agenta i dlatego tu wskaźnik
	
	general_ptr<Point> begin, end;
	general_ptr<Edge> actual; //krawędź na której się znajduje
	//na samym początku null
	
	
	public:
	Agent(const general_ptr<Point> & begin, const general_ptr<Point> & end);
	//punkt na którym zaczyna symulacje i na którym ma skończyć - do którego zmierza
	
	bool runFunction(); //metoda wywoływana tylko z tej następnej
	//w niej jest wykonywany cały ruch na FRAGMENCIE krawędzi
	void threadFunction(); //metoda na której jest zakładany wątek agenta
	//w niej przejdzie całą drogą od swojego punktu początkowego do
	//końcowego
	
	double getVelocity() {
		if(actual.isEmpty()) return 0; //wątek sprawdzania pozycji może
		//próbować odczytać tą prędkość zanim zostanie ustalona na początku
		//wątku agenta
		
		return actual->velocityAt(); //aktualnie to po prostu capacity
		//fragmentu
	}
	
	std::pair<double, double> locate() { //zwraca pozycję agenta
		// składającej się z pary liczb rzeczywistych
		std::lock_guard lock(posits); //trzeba do tego zasadzić blokadę bo odczyt ten bywa w innym wątku
		//niż poruszanie się (i wogóle są 2 wątki które odczytują)
		return std::pair(x, y);
	} //blokada jest zdejmowana
	
	static bool twoClose(const general_ptr<Agent> & one, const general_ptr<Agent> & second);
	//czy 2 agenty są blisko tak że można powiedzieć że się spotkały
	
	static bool crash(const general_ptr<Agent> & one, const general_ptr<Agent> & second);
	//czy 2 agenty mogą się w tej chwili spotkać (bo nie tylko liczy się odległość)
	void spawn() {
		pointThread.reset(new std::thread(&Agent::threadFunction, this)); //pierwszy argument to adres metody
		
	} //uruchamianie nowego wątku
	//odpowiada wywołaniu funkcji [this->][Agent::]threadFunction()
	
	void setActive(bool active) {
		std::lock_guard lock(activeLock); //zakładamy blokadę
		this->active = active;
	} //zwalniamy blokadę
	
	bool checkActive() {
		std::lock_guard lock(activeLock); //zakładamy blokadę
		
		//przydałoby się zorganizować mechanizm mutexów
		//trochę inaczej żeby możliwe było wielu czytelników i jeden pisarz
		//ale to mogłoby pozwolić na zagłodzenia pisarza
		return active;
	} //zwalniamy blokadę
	
	void join() {
		if(pointThread->joinable()) //jeśli już wcześniej się zakończył
		//to join dałoby wyjątek, więc sprawdzamy czy się przypadkiem już
		//nie zakończył
		
		pointThread->join();
	}
	
	static void setClose(double close) {
		Agent::close = close;
	}
	
	static void setVelocity(double velo) {
		defaultVelocity = velo;
	}
	
};

#endif
