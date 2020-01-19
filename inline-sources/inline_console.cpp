

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

inline Console::Console(): n(0) {}



