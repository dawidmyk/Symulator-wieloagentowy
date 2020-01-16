/*
Class used for communication with user to get simulation parameters
Author: Mateusz Szewczyk
*/
#ifndef CONSOLE
#define CONSOLE
#include "graph.hpp"
#include "simulation.hpp"
#include <iostream>

class ThreadInterruptible {
	/* klasa obudowująca wątek
	 * stworzona by można było w sposób przyzwoity
	 * zakończyć wątek z zewnątrz
	 * dobrze się nadająca do wątków których główna funkcja
	 * jest jakąś pętlą */
	
	std::unique_ptr<std::thread> threadInstance; //obudowany wątek
	//unique_ptr z tego samego powodu co przy Agent
	
	bool condition; //zatrzymanie wątku ma się odbyć przez ustawienie tej zmiennej na false
	
	std::mutex locker; //blokada związana z powyższą zmienną
	public:
	ThreadInterruptible();
	void setThread(std::unique_ptr<std::thread> thread) ;
	void setCondition(bool condition);
	bool getCondition();
	void join();
	
	
	
};

class Console {
	
	Graph & g; //referencja na Graph & g, ten obiekt Console nie jest jego właścicielem
	//czyli taki jakby wskaźnik ale obsługiwany jak obiekt w zwykłej zmiennej
	ThreadInterruptible agentDraw;
	ThreadInterruptible agentCrash;
	std::unique_ptr<std::thread> getchThread;
	//Dwa wątki bo dwie funkcje odpytywania agentów - o pozycje i o zderzenia (spotkania)
	//Trzeci - czekanie na wciśnięcie klawisza
	std::mutex consoleLock; //dostęp do konsoli musi być wyłączny w danym momencie
	int n; //który raz wypisywana jest pozycja jakiegoś agenta
	static double time_reg; //co ile sprawdzana jest pozycja jakiegoś agenta
	void setAgentDraw();
	void setAgentCrash();
	
	void getchWait();
	
	void setWait();
	
	void joinWait();
	
	public:
	Console(Graph & graph);
	void run();
	
	void actualize(const general_ptr<Agent> & agent, double x, double y, int i); //i to numer agenta
	
	void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j);
	//i oraz j to numery obydwu agentów

	static void setTime(double time_reg);
		

};

#include "inline_console.cpp"
#endif
