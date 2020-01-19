#include "headers.hpp"
	void Graph::agentDrawThread(Console & out, ThreadInterruptible & thread) {
		while (thread.getCondition()) {
			int i = 0;
			for(auto & ptr : agents) {
				std::pair posit = ptr->locate();
				out.actualize(ptr, posit.first, posit.second, ptr->getNume());
				i++;
			}
		}
	} //funkcja pozycjonowania agentów (na mapie, w konsoli)
	
	void Graph::agentCrashThread(Console & out, ThreadInterruptible & thread) {
		while(thread.getCondition()) {
			for(auto & ptr1 : agents) {
				for(auto & ptr2 : agents) {
					if(ptr1 == ptr2) continue;
					out.prenoteCrash();
					if(Agent::crash(ptr1, ptr2, out))
						out.noteCrash(ptr1, ptr2, ptr1->getNume(), ptr2->getNume());
				}
			}
		}
	} //funkcja wykrywająca (nie koniecznie wszystkie) zderzenia agentów
	// a jak nic nie jest w stanie wykryć to po prostu się kręci
	
	general_ptr<Point> Graph::spotPoint(double x, double y) {
		//zwraca punkt w który wstrzelają się określone współrzędne
		//a jeśli takiego punktu nie ma albo jest więcej niż
		//1, trzeba zwrócić nulla
		general_ptr<Point> ret;
		char found = 0;
		for(auto & ptr : points) { 
			//tu auto rozwija się na std::unique_ptr<Point>
			if(ptr->spotted(x, y)) {
				ret = ptr; //przypisanie general_ptr = unique_ptr
				found++;
			}
			if (found == 2) return general_ptr<Point>(); //nullptr
		}
		if(found == 1) return ret;
		if(found == 0) return general_ptr<Point>(); //nullptr
	}
	
