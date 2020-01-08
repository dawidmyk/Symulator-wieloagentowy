
	
inline double Agent::getVelocity() {
	if(actual.isEmpty()) return 0; //wątek sprawdzania pozycji może
	//próbować odczytać tą prędkość zanim zostanie ustalona na początku
	//wątku agenta
	
	return actual->velocityAt(fragment); //aktualnie to po prostu capacity
	//fragmentu
}

inline std::pair<double, double> Agent::locate() { //zwraca pozycję agenta
	// składającej się z pary liczb rzeczywistych
	std::lock_guard lock(posits); //trzeba do tego zasadzić blokadę bo odczyt ten bywa w innym wątku
	//niż poruszanie się (i wogóle są 2 wątki które odczytują)
	return std::pair(x, y);
} //blokada jest zdejmowana


inline void Agent::spawn() {
	pointThread.reset(new std::thread(&Agent::threadFunction, this)); //pierwszy argument to adres metody
	
} //uruchamianie nowego wątku
//odpowiada wywołaniu funkcji [this->][Agent::]threadFunction()

inline void Agent::setActive(bool active) {
	std::lock_guard lock(activeLock); //zakładamy blokadę
	this->active = active;
} //zwalniamy blokadę

inline bool Agent::checkActive() {
	std::lock_guard lock(activeLock); //zakładamy blokadę
	
	//przydałoby się zorganizować mechanizm mutexów
	//trochę inaczej żeby możliwe było wielu czytelników i jeden pisarz
	//ale to mogłoby pozwolić na zagłodzenia pisarza
	return active;
} //zwalniamy blokadę

inline void Agent::join() {
	if(pointThread->joinable()) //jeśli już wcześniej się zakończył
	//to join dałoby wyjątek, więc sprawdzamy czy się przypadkiem już
	//nie zakończył
	
	pointThread->join();
}

inline void Agent::setClose(double close) {
	Agent::close = close;
}

inline void Agent::setVelocity(double velo) {
	defaultVelocity = velo;
}
