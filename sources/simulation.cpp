#include "headers.hpp"

std::mutex Simulation::end_lock;
bool Simulation::end_var;

double Simulation::time_reg;

void Simulation::run() {
	Simulation::startSimulation();
	out->setWait();
	g->edgesAdjust(); //przelicz parametry w krawędziach
	g->makeSeed(); //zasiej losowość
	g->spawnAgents(*out); //wystartuj agentów
	setAgentDraw(); //zacznij wypisywanie pozycji agentów
	setAgentCrash(); //zacznij wypisywanie informacji o spotkaniach
	//jego dezaktywowałem bo on się zakleszcza
	//nie wiem dlaczego
	//(w obecnej konfiguracji spotkania raczej nie występują)
	g->joinAgents(); //czekaj aż agenci się zakończą (dojdą tam gdzie mają dojść)
	agentDraw.join(); //delikatnie wymuś zatrzymanie wątku wypisującego pozycje
	agentCrash.join(); //delikatnie wymuś zatrzymanie wątku wypisującego spotkania
	out->endInform();
	out->joinWait();
}

void Simulation::testSimulation() {
	Graph graph;
	Console cons;
	g.set(&graph);
	out.set(&cons);
	
	//ustalenie stałych własności symulacji
	//(statycznych w różnych klasach)
	Agent::setClose(0.3); //jak blisko muszą być od siebie
	//agenci by się spotkać
	
	Point::setClose(0.01); //jak blisko musi być punkt początku
	//krawędzi żeby się do niego dopasowała
	
	Agent::setVelocity(0.5); //wspólny przemnożnik prędkości
	//wszystkich agentów
	
	Point::setLevels(4);
	
	Point::setDefaultCapacity(0.5);
	
	Simulation::setTime(500); //co ile wypisanie kolejnej pozycji
	//agentów
	//ustalenie stałych własności symulacji
	
	graph.addSpecialPoint(0, 0);
	graph.addSpecialPoint(1, 2);
	graph.addSpecialPoint(2, 3);
	graph.addSpecialPoint(4, 2);
	graph.addSpecialPoint(1, 5);
	graph.addSpecialPoint(6, 3);
	graph.addSpecialPoint(4, 5);
	graph.addEdge(0, 0, 1, 2);
	graph.addEdge(0, 0, 2, 3);
	graph.addEdge(1, 2, 2, 3);
	graph.addEdge(1, 2, 4, 2);
	graph.addEdge(4, 2, 2, 3);
	graph.addEdge(4, 2, 6, 3);
	graph.addEdge(1, 5, 2, 3);
	graph.addEdge(1, 5, 1, 2);
	graph.addEdge(1, 5, 4, 5);
	graph.addEdge(2, 3, 4, 5);
	graph.addEdge(6, 3, 4, 5);

	graph.addAgent(1, 2, 0, 0);
	graph.addAgent(0, 0, 1, 2);

	graph.addAgent(1, 2, 2, 3);
	graph.addAgent(6, 3, 1, 2);
	graph.addAgent(4, 5, 0, 0);
	graph.addAgent(1, 5, 6, 3);
	run();

}
