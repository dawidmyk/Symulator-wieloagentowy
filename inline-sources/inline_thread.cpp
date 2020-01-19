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
