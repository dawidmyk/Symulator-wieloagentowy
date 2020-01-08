/*
Class used for communication with user to get simulation parameters
Author: Mateusz Szewczyk
*/
#ifndef CONSOLE
#define CONSOLE
#include "graph.hpp"
#include "simulation.hpp"
#include <iostream>

class ThreadInterruptible { //klasa obudowująca wątek
	//stworzona by można było w sposób przyzwoity
	//zakończyć wątek z zewnątrz
	//dobrze się nadająca do wątków których główna funkcja
	//jest jakąś pętlą
	
	std::unique_ptr<std::thread> threadInstance; //obudowany wątek
	//unique_ptr z tego samego powodu co przy Agent
	
	bool condition; //zatrzymanie wątku ma się odbyć przez ustawienie tej zmiennej na false
	
	std::mutex locker; //blokada związana z powyższą zmienną
	public:
	ThreadInterruptible(): condition(true) {}
	void setThread(std::unique_ptr<std::thread> thread) { //i tu podamy funkcję na jakiej wątek
		//ma działać
		threadInstance = std::move(thread); //unique_ptr trzeba dotykać za pomocą
		//move, bo nie są kopiowalne
	}
	void setCondition(bool condition) { //ustawimy condition na false
		//gdy będziemy chcieli żeby wątek się skończył
		std::lock_guard lock(locker); //założenie blokady
		this->condition = condition;
	} //zwolnienie blokady
	bool getCondition() { //wątek za pomocej tej metody będzie sprawdzał
		//condition, czyli czy ma dalej trwać
		std::lock_guard lock(locker); //założenie blokady
		return condition;
	} //zwolnienie blokady
	void join() { //najpierw sprawdzamy czy przypadkiem już się nie
		//skończył, potem "delikatnie" sugerujemy mu by się zakończył
		//ustawiając condition, a potem czekamy aż się zakończy
		if(!threadInstance->joinable()) return;
		setCondition(false);
		threadInstance->join();
	}
	
	
	
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
	void setAgentDraw() {
		agentDraw.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentDrawThread,
		&g, std::ref(*this), std::ref(agentDraw))));
		//std::ref oznacza przekazanie odpowiedniej referencji (bo funkcja jako argumenty przyjmuje
		//2 referencje), patrz sygnatura funkcji agentDrawThread w graf
		//z kolei obiekt którego metoda ma być wykonana (Graph g) musi być chyba przekazany przez adres
		//stąd &g
	}
	void setAgentCrash() {
		agentCrash.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentCrashThread,
		&g, std::ref(*this), std::ref(agentCrash))));
		//patrz komentarz wyżej
	}
	
	void getchWait() {
		getchar(); //nie potrafię w przenośny sposób zrobić by można było przerwać tą funkcję
		Simulation::endSimulation();
	}
	
	void setWait() {
		getchThread.reset(new std::thread(&Console::getchWait, this));
	}
	
	void joinWait() {
		if(getchThread->joinable()) getchThread->join();
	}
	
	public:
	Console(Graph & graph): g(graph), n(0) {}
	void run();
	
	void actualize(const general_ptr<Agent> & agent, double x, double y, int i); //i to numer agenta
	
	void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j);
	//i oraz j to numery obydwu agentów

	static void setTime(double time_reg) {
		Console::time_reg = time_reg;
	}
		

};


#endif
