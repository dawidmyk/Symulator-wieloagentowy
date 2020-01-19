inline void Simulation::setAgentDraw() {
	agentDraw.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentDrawThread,
	g, std::ref(*out), std::ref(agentDraw))));
	//std::ref oznacza przekazanie odpowiedniej referencji (bo funkcja jako argumenty przyjmuje
	//2 referencje), patrz sygnatura funkcji agentDrawThread w graf
	//z kolei obiekt którego metoda ma być wykonana (Graph g) musi być chyba przekazany przez adres
	//stąd &g
}
inline void Simulation::setAgentCrash() {
	agentCrash.setThread(std::unique_ptr<std::thread>(new std::thread(&Graph::agentCrashThread,
	g, std::ref(*out), std::ref(agentCrash))));
	//patrz komentarz wyżej
}

inline void Simulation::startSimulation() {
	std::lock_guard lock(end_lock);
	end_var = true;
}

inline void Simulation::endSimulation() {
	std::lock_guard lock(end_lock);
	end_var = false;
}

inline bool Simulation::last() {
	std::lock_guard lock(end_lock);
	return end_var;
}

inline double Simulation::getTime() {
	return time_reg;
}

inline void Simulation::setTime(double time_reg) {
	Simulation::time_reg = time_reg;
}
