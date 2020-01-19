
#ifndef GRAPH
#define GRAPH
#include <vector>
#include <random>
#include <sstream>

class Output;

///@brief Klasa reprezentująca sieć drogową i będąca kontenerem dla większości obiektów
class Graph {
	
	/* tutaj wskażniki muszą trzymać własność do tych obiektów, żeby
	 * je usunąć na końcu
	 * żeby nie było wycieków pamięci
	 * dlatego są unique_ptr */
	
	///@brief Kontener punktów
	std::vector<std::unique_ptr<Point>> points;
	
	///@brief Kontener krawędzi
	std::vector<std::unique_ptr<Edge>> edges;
	
	///@brief Kontener agentów
	std::vector<std::unique_ptr<Agent>> agents;
	
	
	
	Rander rander;
	
	public:
	//rózne funkcje rozbudowujące graf
	//i one są wołane w Simulation::test
	
	///@name Metody rozbudowujące graf
	/** Wszystkie wołają konstruktory odpowiednich klas */
	///@{
	///@brief Dodaje punkt UsualPoint o podanych współrzędnych
	void addUsualPoint(double x, double y);
	
	///@brief Dodaje punkt SpecialPoint o podanych współrzędnych
	void addSpecialPoint(double x, double y);
	
	///@brief Dodaje krawędź dopasowując obydwa zestawy współrzędnych
	/** do współrzędnych istniejących punktów */
	void addEdge(double x1, double y1, double x2, double y2);
	
	/**@brief Dodaje krawędź do punktów o odpowiednich numerkach
	 * w kontenerze */
	void addEdgeNum(int begin, int end);
	
	///@brief Dodaje agneta dopasuwając obydwa zestawy współrzędnych
	/** do współrzędnych istniejących punktów 
	 * 
	 * Te punkty będą początkiem i końcem jego trasy */
	void addAgent(double x1, double y1, double x2, double y2);
	
	/**@brief Dodaje agenta do punktów o odpowiednich numerkach
	 * w kontenerze
	 * 
	 * Te punkty będą początkiem i końcem jego trasy */
	void addAgentNum(int begin, int end);
	///@}
	

		
	/**@brief Próbuje dopasować podane współrzędne
	 * do któregoś z punktów w kontenerze */
	general_ptr<Point> spotPoint(double x, double y);
	
	///@brief Główna funkcja wątku rysującego
	void agentDrawThread(Output & cons, ThreadInterruptible & thread);
	
	///@brief Główna funkcja wątku spotkań
	void agentCrashThread(Output & cons, ThreadInterruptible & thread);
	//te funkcje uruchamiane są w dwóch osobnych wątkach
	
	/**@brief Tworzy wątki dla wszystkich agentów już utworzonych
	 * i trzymanych w odpowiednim kontenerze */
	void spawnAgents(Output & out);
	
	///@brief Czeka na zakończenie wątków wszystkich agentów
	void joinAgents();
	
	///@brief Zasiewa ziarno w generatorze pseudolosowym
	void makeSeed();
	
	//Co to robiło?
	void edgesAdjust();

	
	
			
};

#endif
