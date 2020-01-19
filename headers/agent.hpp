///@file 

#ifndef AGENT
#define AGENT
#include <thread>
#include <mutex>

///@brief Klasa reprentująca agenta (pojazd)
/** Jest on skojarzony ze swoim własnym wątkiem */
class Output;
class Agent {
	
	///@brief Taka odległość między agentami że można uznać że są blisko.
	/** Potrzebna przy określaniu spotkań (ewentualnym).
	 *  Użyta w Agent::twoClose (dla Graph::agentCrashThread). */
	static double close;
	
	///@brief Wspólny dla wszystkich agentów przemnożnik prędkości
	/** Ustawiając go na dużą wartość można wymusić, że symulacja skończy
	 * się natychmiast, a na małą, że będzie trwała tak długo że można
	 * będzie obserwować symulację na bieżąco.
	 * Użyty w Agent::runFunction. */
	static double defaultVelocity;
	
	///@name Współrzędne lokalizujące agenta
	///@{
	double x; //pozycja
	double y; //pozycja
	///@}
	
	///@brief Kierunek na krawędzi.
	/** Każda krawędź ma koniec i początek
	 * (graf jest skierowany) - można się poruszać w obie
	 * strony, ale agent musi wiedzieć w którą z tych stron
	 * się porusza. Zmienna przyjmuje wartości 1 i -1
	 * (ewentualnie 0). */
	 /* krawędź jest jak wektor ukierunkowana
	  * i agent może się poruszać zgodnie lub wbrew temu kierunkowi
	  * 1 - zgodnie
	  * -1 - wbrew */
	char dir; 
	
	///@brief Jest prawdą gdy agent już wystartował i jeszcze nie skończył
	/** Zanim agent nie wystartuje jego Agent::actual
	 * jest puste, a pewne inne funkcje mogą go użyć
	 * (mogłyby sprawdzać pusty wskaźnik)
	 * obecnie używane głównie dla spotkań,
	 * także by agentów którzy już zakończyli zostawić w spokoju */
	bool active;
	///@brief Blokada przy odczytywaniu i zapisywaniu pozycji
	std::mutex posits; 
	
	/**@brief Blokada przy odczytywaniu
	 * krawędzi po której się porusza i kierunku
	 * na tej krawędzi. */
	std::mutex dir_read; 
	
	//Sprawdzić co to jest i czy wogóle jest potrzebne!
	std::mutex edgeLock;
	///@brief Blokada przy ustalaniu czy agent jest aktywny czy nie.
	std::mutex activeLock; 

	///@brief Wątek realizujący ruch danego agenta.
	/** Powiązany głównie z metodami Agent::runFunction i 
	 * Agent::threadFunction */
	std::unique_ptr<std::thread> pointThread;
	/* agent jest właścicielem swojego wątku
	 * ale nie można go ustalić w konstruktorze
	 * agenta i dlatego tu wskaźnik */
	
	///@brief Punkt w którym agent zaczął.
	/** Utrzymywanie go przez całe życie agenta
	 * może nie jest konieczne. */
	general_ptr<Point> begin;
	
	///@brief Punkt do którego agent zmierza.
	/** Jest on wykorzystywany za każdym razem gdy
	 * przeliczana jest heurystyka */
	general_ptr<Point> end;
	
	///@brief Krawędź na której znajduje się agent
	/** Trudno zaprzeczyć że większość swojego życia
	 * agent spędza na krawędziach a nie w punktach.
	 * Krawędź określa warunki poruszania się agenta.
	 * Zmieniana jest tylko w Agent::threadFunction.*/
	 //na samym początku null
	general_ptr<Edge> actual;
	int nume;
	
	public:
	Agent(const general_ptr<Point> & begin, const general_ptr<Point> & end, int nume);
	//punkt na którym zaczyna symulacje i na którym ma skończyć - do którego zmierza
	
	/** @brief Metoda w której są wykonywane przeliczenia matematyczne
	 * definiujące ruch i związane z czasem */
	/* metoda wywoływana tylko z tej następnej
	 * w niej jest wykonywany cały ruch na FRAGMENCIE krawędzi */
	bool runFunction(); 
	
	/** @brief Metoda która określa i zmienia aktualne położenie w kontekście
	 * grafu */
	/* metoda na której jest zakładany wątek agenta
	 * w niej przejdzie całą drogą od swojego punktu początkowego do
	 * końcowego */
	void threadFunction(Output & out); 
	
	///@brief Zwraca przemnożnik prędkości zależny od krawędzi.
	double getVelocity();
	
	///@brief Getter pozycji przestrzennej agenta.
	std::pair<double, double> locate();
	
	///@brief Stwierdza bliskość na potrzeby analizy spotkań
	//czy 2 agenty są blisko tak że można powiedzieć że się spotkały
	static bool twoClose(const general_ptr<Agent> & one, const general_ptr<Agent> & second, Output & out);
	
	///@brief Stwiedza czy mogą się spotkać ze względu na różne czynniki
	//czy 2 agenty mogą się w tej chwili spotkać (bo nie tylko liczy się odległość)
	static bool crash(const general_ptr<Agent> & one, const general_ptr<Agent> & second, Output & out);
	
	///@brief Rozpoczyna wątek agenta
	void spawn(Output & out);
	
	///@brief Zmienia stan aktywności agenta stosując sekcję krytyczną
	void setActive(bool active);
	
	///@brief Sprawdza stan aktywności agenta stosując sekcję krytyczną
	bool checkActive();
	
	///@brief Kończy wątek agenta
	void join();
	
	int getNume();
	
	///@brief Ustala wartość Agent::close, bo mogą być różne dobre wartości.
	static void setClose(double close);
	
	///@brief Ustala domyślną prędkość.
	static void setVelocity(double velo);
	
};

#endif
