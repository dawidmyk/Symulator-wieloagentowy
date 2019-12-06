#include "console.hpp"
#include "simulation.hpp"
	void Graph::agentDrawThread(Console & cons, ThreadInterruptible & thread) {
		while (thread.getCondition()) {
			int i = 0;
			for(auto & ptr : agents) {
				std::pair posit = ptr->locate();
				cons.actualize(ptr, posit.first, posit.second, i);
				i++;
			}
		}
	} //funkcja pozycjonowania agentów (na mapie, w konsoli)
	
	void Graph::agentCrashThread(Console & cons, ThreadInterruptible & thread) {
		while(thread.getCondition()) {
			int i, j;
			i = 0;
			for(auto & ptr1 : agents) {
				j = 0;
				for(auto & ptr2 : agents) {
					if(Agent::crash(ptr1, ptr2))
						cons.noteCrash(ptr1, ptr2, i, j);
					j++;
				}
				i++;
			}
		}
	} //funkcja wykrywająca (nie koniecznie wszystkie) zderzenia agentów
	// a jak nic nie jest w stanie wykryć to po prostu się kręci
	
	std::general_ptr<Point> Graph::spotPoint(double x, double y) {
		//zwraca punkt w który wstrzelają się określone współrzędne
		//a jeśli takiego punktu nie ma albo jest więcej niż
		//1, trzeba zwrócić nulla
		std::general_ptr<Point> ret;
		char found = 0;
		for(auto & ptr : points) { 
			//tu auto rozwija się na std::unique_ptr<Point>
			if(ptr->spotted(x, y)) {
				ret = ptr; //przypisanie general_ptr = unique_ptr
				found++;
			}
			if (found == 2) return std::general_ptr<Point>(); //nullptr
		}
		if(found == 1) return ret;
		if(found == 0) return std::general_ptr<Point>(); //nullptr
	}
	
