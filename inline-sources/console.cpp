/*
Class used for communication with user to get simulation parameters
Author: Mateusz Szewczyk
*/


inline ThreadInterruptible::ThreadInterruptible(): condition(true) {}
inline void ThreadInterruptible::setThread(std::unique_ptr<std::thread> thread) { //i tu podamy funkcję na jakiej wątek
	//ma działać
	threadInstance = std::move(thread); //unique_ptr trzeba dotykać za pomocą
	//move, bo nie są kopiowalne
}
inline void ThreadInterruptible::setCondition(bool condition) { //ustawimy condition na false
	//gdy będziemy chcieli żeby wątek się skończył
	std::lock_guard lock(locker); //założenie blokady
	this->condition = condition;
} //zwolnienie blokady
inline bool ThreadInterruptible::getCondition() { //wątek za pomocej tej metody będzie sprawdzał
	//condition, czyli czy ma dalej trwać
	std::lock_guard lock(locker); //założenie blokady
	return condition;
} //zwolnienie blokady
inline void ThreadInterruptible::join() { //najpierw sprawdzamy czy przypadkiem już się nie
	//skończył, potem "delikatnie" sugerujemy mu by się zakończył
	//ustawiając condition, a potem czekamy aż się zakończy
	if(!threadInstance->joinable()) return;
	setCondition(false);
	threadInstance->join();
}
	
inline void Console::setAgentDraw() {
	agentDraw.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentDrawThread,
	&g, std::ref(*this), std::ref(agentDraw))));
	//std::ref oznacza przekazanie odpowiedniej referencji (bo funkcja jako argumenty przyjmuje
	//2 referencje), patrz sygnatura funkcji agentDrawThread w graf
	//z kolei obiekt którego metoda ma być wykonana (Graph g) musi być chyba przekazany przez adres
	//stąd &g
}

inline void Console::setAgentCrash() {
	agentCrash.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentCrashThread,
	&g, std::ref(*this), std::ref(agentCrash))));
	//patrz komentarz wyżej
}

inline void Console::getchWait() {
	getchar(); //nie potrafię w przenośny sposób zrobić by można było przerwać tą funkcję
	Simulation::endSimulation();
}

inline void Console::setWait() {
	getchThread.reset(new std::thread(&Console::getchWait, this));
}

inline void Console::joinWait() {
	if(getchThread->joinable()) getchThread->join();
}

inline Console::Console(Graph & graph): g(graph), n(0) {}

inline void Console::setTime(double time_reg) {
	Console::time_reg = time_reg;
}
