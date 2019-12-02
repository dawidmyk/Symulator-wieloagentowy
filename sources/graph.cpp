#include "../headers/console.hpp"
	void Graph::agentDrawThread(Console & cons, ThreadInterruptible & thread) {
		while (thread.getCondition()) {
			int i = 0;
			for(auto & ptr : agents) {
				std::pair posit = ptr->locate();
				cons.actualize(ptr, posit.first, posit.second, i);
				i++;
			}
		}
	}
	
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
	}
	
