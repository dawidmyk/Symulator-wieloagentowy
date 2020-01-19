inline void Rander::makeSeed() {
	generator.reset(new std::mt19937(std::time(0)));
	//ziarno to aktualny czas
	//z dokładnością bodajże do sekund
	//co jest typowe dla aplikacji losujących
}

inline int Rander::generate(int size) {
	std::lock_guard lock(rand_mutex); //zajęcie blokady
	std::uniform_int_distribution dist(0, size - 1); //definiujemy funktor
	//którym jest jakiś konkretny rozkład - tu równomierny dyskretny
	//0 to minimalna możliwa wylosowana liczba
	//size-1 to maksymalna możliwa liczba
	return dist(*generator); //funktor jako argument pobiera generator
	//którego ma użyć do generacji
} //zwolnienie blokady
