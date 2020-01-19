/*
Class used for communication with user to get simulation parameters
Author: Mateusz Szewczyk
*/
#ifndef CONSOLE
#define CONSOLE
#include <iostream>



class Console {
	
	std::unique_ptr<std::thread> getchThread;
	//Dwa wątki bo dwie funkcje odpytywania agentów - o pozycje i o zderzenia (spotkania)
	//Trzeci - czekanie na wciśnięcie klawisza
	std::mutex consoleLock; //dostęp do konsoli musi być wyłączny w danym momencie
	int n; //który raz wypisywana jest pozycja jakiegoś agenta
	public:
	void getchWait();
	
	void setWait();
	
	void joinWait();
	
	
	Console();
	
	void actualize(const general_ptr<Agent> & agent, double x, double y, int i); //i to numer agenta
	
	void prenoteCrash();
	
	void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j);
	//i oraz j to numery obydwu agentów
	
	void endRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & end, int i, bool success);
	
	void changeRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & now,
		const general_ptr<Edge> & previousOne,  const general_ptr<Edge> & newOne, int nume);

	void endInform();
	
	void lockAchive(int i);
};

#endif
