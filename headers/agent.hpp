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
	
	int fragment; //używane by sprawdzić prędkość i inne ewentualne parametry
	//miejsca w którym się znajduje
	//znajduje się na fragmencie krawędzi o określonym numerze
	
	public:
	Agent(const general_ptr<Point> & begin, const general_ptr<Point> & end);
	//punkt na którym zaczyna symulacje i na którym ma skończyć - do którego zmierza
	
	bool runFunction(); //metoda wywoływana tylko z tej następnej
	//w niej jest wykonywany cały ruch na FRAGMENCIE krawędzi
	void threadFunction(); //metoda na której jest zakładany wątek agenta
	//w niej przejdzie całą drogą od swojego punktu początkowego do
	//końcowego
	
	double getVelocity();
	
	std::pair<double, double> locate(); //blokada jest zdejmowana
	
	static bool twoClose(const general_ptr<Agent> & one, const general_ptr<Agent> & second);
	//czy 2 agenty są blisko tak że można powiedzieć że się spotkały
	
	static bool crash(const general_ptr<Agent> & one, const general_ptr<Agent> & second);
	//czy 2 agenty mogą się w tej chwili spotkać (bo nie tylko liczy się odległość)
	void spawn(); //uruchamianie nowego wątku
	//odpowiada wywołaniu funkcji [this->][Agent::]threadFunction()
	
	void setActive(bool active);
	
	bool checkActive();
	
	void join();
	
	static void setClose(double close);
	
	static void setVelocity(double velo);
	
};

#include "agent.cpp"
#endif
