#include "headers.hpp"
//Te których nie ogarniasz mogą pozostać puste

void actualize(const general_ptr<Agent> & agent, double x, double y, int i) {
	//odrysowanie
}
		
void prenoteCrash() {
}
		
void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j) {
	//spotkanie
}
		
void endRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & end, int i, bool success) {
	//dojście do celu
}
		
void changeRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & now,
			const general_ptr<Edge> & previousOne,  const general_ptr<Edge> & newOne, int nume) {
				//przejście przez punkt (także początek i koniec)
			}

void endInform() {
	//koniec symulacji
}
		
void lockAchive(int i) {
}
