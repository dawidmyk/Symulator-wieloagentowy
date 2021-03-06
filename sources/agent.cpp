#include <chrono>
#include "agent.hpp"
#include "simulation.hpp"

double Agent::close;
double Agent::defaultVelocity;

//statyczne zmienne muszą być deklarowane oddzielnie poza samą klasą

Agent::Agent(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end): dir(0), active(false), begin(begin),
	end(end), fragment(-1) {
		//dopóki nie wystartuje to nie jest aktywny
		//nie ma kierunku, bo nie jedzie po żadnej krawędzi
		//a dir identyfikuje kierunek po określonej krawędzi
		//i nie jest na fragmencie o jakimkolwiek sprawnym numerze (>=0)
		auto pointPositions = begin->locate(); //pozycję agenta trzeba nastawić na pozycję punktu startowego
		x = pointPositions.first;
		y = pointPositions.second;	//i rozbieramy parę
}
	
bool Agent::twoClose(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		std::scoped_lock lock(one->posits, second->posits); //blokada założona jednocześnie na dwóch mutexach
		//nie da rady zrobić na 2 lock_guardy bo będzie mogło wystąpić zakleszczenie
		//a i tak jest jakieś zakleszczenie, tylko nie zakleszcza innych wątków
		double xdiff = one->x - second->x;
		double ydiff = one->y - second->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close); //pitagoras mniej niż...
} //blokada zdjęta

bool Agent::crash(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		if(!one->checkActive()||!second->checkActive()) return false;
		//nie mogą się spotkać (zderzyć) jeśli już nie jadą
		bool ifClose = twoClose(one, second);
		if(!ifClose) return false;
		{
			std::scoped_lock lock(one->dir_read, second->dir_read);
			//blokada podobnie jak wyżej
			if(one->actual == second->actual && one->dir == -second->dir) return true;
			//muszą być na tej samej krawędzi ale jechać w przeciwnym kierunku
			return false;
		} //blokada zdjęta
}


bool Agent::runFunction() {
	double pos = 0;
	double fragmentLength = actual->getFragmentLength();
	double angle = actual->getAngle();
	double sinus = sin(angle)*dir;
	double cosinus = cos(angle)*dir;
	double general_move;
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	first = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff;
	while(pos < fragmentLength) {
		if(!Simulation::last()) return false;
		second = std::chrono::high_resolution_clock::now();
		diff = second - first;
		first = second;
		general_move = diff.count()*defaultVelocity*getVelocity();
		pos += general_move;
		std::lock_guard lock(posits); //założenie blokady
		x += general_move * cosinus;
		y += general_move * sinus;
		//zdjęcie blokady
	}
	return true;
	//ta funkcja próbuje emulować ciągłe przemieszczenie w 'x' i 'y'
}

void Agent::threadFunction() {
	//W tej funkcji jest cała podróż jednego agenta
	setActive(true);
	//na początku tej podróży trzeba go aktywować
	int ndebug = 0; //debug
	//dzięki temu można monitorować ile krawędzi przebył
	auto previousOne = begin;
	//auto żeby nie pisać długich nazw typów (z szablonami)
	auto situation = previousOne->choose();
	//pierwsza krawędź podróży została wybrana (jakimś algorytmem
	//losowym bądź heurystyką)
	auto actual = situation.first;
	char dir = situation.second;
	{
			std::lock_guard lock(dir_read); //założenie blokady
			//przed tym przypisaniem this->actual jest nullem
			this->actual = actual;
			this->dir = dir;
	} //zdjęcie blokady
	std::general_ptr<Point> nextOne;
	
	while(previousOne != end) { //niech dojdzie aż do swojego postanowionego końca

		nextOne = actual->otherSide(previousOne); //przeciwległy kraniec krawędzi
		int n = actual->getFragmentNum();
		int fin;
		if(dir == 1) {
			fragment = 0;
			fin = n;
		}
		else if(dir == -1) {
			fragment = n - 1;
			fin = -1;
		}
		//bo on może iść zgodnie z kierunkiem krawędzi albo wbrew mu
		for(; fragment != fin; fragment += dir) {
			if(!runFunction()) return; //przechodzi przez fragment
			//wyjście jeśli zwróciła fałsz bo symulacja została przerwana
		}
		
		previousOne = nextOne;
		situation = previousOne->chooseExcept(actual);
		//następna krawędź zostaje wybrana, ale to nie może być ta
		//która dopiero co była
		actual = situation.first;
		dir = situation.second;
		{
			std::lock_guard lock(dir_read); //założenie blokady
			this->actual = actual;
			this->dir = dir;
		} //zdjęcie blokady
	ndebug++;
	}
	//na końcu podróży trzeba go dezaktywować
	setActive(false);
}
