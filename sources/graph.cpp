#include "console.hpp"
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
	
	std::general_ptr<Point> Graph::spotPoint(float x, float y) {
		std::general_ptr<Point> ret;
		char found = 0;
		for(auto & ptr : points) {
			if(ptr->spotted(x, y)) {
				ret = ptr;
				found++;
			}
			if (found == 2) return std::general_ptr<Point>(); //nullptr
		}
		if(found == 1) return ret;
		if(found == 0) return std::general_ptr<Point>(); //nullptr
	}
	
