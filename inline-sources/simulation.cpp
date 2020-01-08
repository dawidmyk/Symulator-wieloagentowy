/*
Class stores parameters of simulation
Author: Mateusz Szewczyk
*/


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
