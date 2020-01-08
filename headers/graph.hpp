#include <vector>
#include "agent.hpp"
#include <random>
#include <sstream>
#ifndef GRAPH
#define GRAPH

class Console;
class ThreadInterruptible;
class Graph {
	
	//tutaj wskażniki muszą trzymać własność do tych obiektów, żeby
	//je usunąć na końcu
	//żeby nie było wycieków pamięci
	//dlatego są unique_ptr
	
	std::vector<std::unique_ptr<Point>> points;
	std::vector<std::unique_ptr<Edge>> edges;
	std::vector<std::unique_ptr<Agent>> agents;
	
	
	
	Rander rander;
	
	public:
	//rózne funkcje rozbudowujące graf
	//i one są wołane w Simulation::test
	void addUsualPoint(double x, double y) {
		points.push_back(std::unique_ptr<Point>(new UsualPoint(x, y, rander)));
		//musimy dodać do wektora obiekt typu unique_ptr
		//unique_ptr to z jakiś powodów wyjątek od możliwości domyślenia
		//sie parametru szablonu w konstruktorze (c++17)
		//ale tu nie chcemy by się domyślał bo unique_ptr ma typ Point
		//a konstruktor ma typ UsualPoint
		//w konstruktorach unique_ptr się woła "new" i najlepiej nigdzie indziej 
	}
	
	void addSpecialPoint(double x, double y) {
		points.push_back(std::unique_ptr<Point>(new SpecialPoint(x, y, rander)));
	}
	
	void addEdge(double x1, double y1, double x2, double y2) {
		//tu jeszcze nie założone że może być błąd
		//tzn. może się nie wstrzelić i wtedy spotPoint zwraca nulle
		edges.push_back(std::unique_ptr<Edge>(new Edge(spotPoint(x1, y1), spotPoint(x2, y2))));
		//spotPoint zwraca general_ptr
		//najpierw dobrze jest potworzyć punkty i potem niech Edge się w nie wstrzeliwują
	}
	
	void addEdgeNum(int begin, int end) {
		edges.push_back(std::unique_ptr<Edge>(new Edge(std::general_ptr(points.at(begin)),
		std::general_ptr(points.at(end)))));
		//rozpinamy krawędź na punktach zajmujących określone pozycje w wektorze punktów
		//(dodane w określonej kolejności)
		//wtedy nie musimy się wstrzelać
		//a general_ptr bo nie można przenosić unique_ptr, trzeba zamienić
	}
	
	void addAgent(double x1, double y1, double x2, double y2) {
		agents.push_back(std::unique_ptr<Agent>(new Agent(spotPoint(x1, y1), spotPoint(x2, y2))));
	} //agent też może się wstrzelić w odpowiednie punkty
	
	void addAgentNum(int begin, int end) {
		agents.push_back(std::unique_ptr<Agent>(new Agent(std::general_ptr(points.at(begin)),
		std::general_ptr(points.at(end)))));
	} //
	
	

		
	
	std::general_ptr<Point> spotPoint(double x, double y);
	
	void agentDrawThread(Console & cons, ThreadInterruptible & thread);
	void agentCrashThread(Console & cons, ThreadInterruptible & thread);
	//te funkcje uruchamiane są w dwóch osobnych wątkach
	
	void spawnAgents() {
		for(auto & ptr : agents) {
			ptr->spawn(); //uruchamia dla każdego agenta jego wątek
		}
	}
	
	void joinAgents() {
		for(auto & ptr : agents) ptr->join();
	}
	
	
	void makeSeed() {
		rander.makeSeed(); //zasadzenie ziarna dla maszyny losującej
	}
	
	void edgesAdjust() { //wszystkie parametry dla każdej krawędzi muszą być gdzieś
		//w końcu policzone
		for (auto & ptr : edges) ptr->countDimensions();
	}

	
	
			
};

#endif
