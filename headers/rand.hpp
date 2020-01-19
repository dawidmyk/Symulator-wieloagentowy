#ifndef RAND
#define RAND

#include <random>
#include <mutex>

/** @brief Klasa opakowująca generator z biblioteki standardowe
 * 
 * Przygotowuje go na dostęp wielowątkowy */
class Rander { //klasa losująca
	/* trzeba losować następną krawędź którą agent wybierze gdy dojdzie do wierzchołka
	 * (jeśli jest wybór)
	 * bo agent się nie będzie cofał */
	//Tu coś trzeba napisać
	std::unique_ptr<std::mt19937> generator; //taki specjalny generator
	/* w unique_ptr bo obiekt Rander jest jego właścicielem ale nie może
	 * go utworzyć od razu, bo musi zasiać mu ziarno w jego konstruktorze */
	///@brief Realizacja sekcji krytycznej w dostępie do generatora
	std::mutex rand_mutex; 
	/* tylko jeden wątek może mieć dostęp jednocześnie
	 * do maszyny losującej */
	public:
	///@brief Tak jak większość generatorów (pseudolosowych) musi być zasiany
	void makeSeed();
	///@brief Użycie generatora
	///@param size Co może zostać zwrócone? 0 <-> size-1
	int generate(int size);
};

#endif
