#ifndef THREAD
#define THREAD
#include <memory>
#include <thread>
#include <mutex>

class ThreadInterruptible {
	/* klasa obudowująca wątek
	 * stworzona by można było w sposób przyzwoity
	 * zakończyć wątek z zewnątrz
	 * dobrze się nadająca do wątków których główna funkcja
	 * jest jakąś pętlą */
	
	std::unique_ptr<std::thread> threadInstance; //obudowany wątek
	//unique_ptr z tego samego powodu co przy Agent
	
	bool condition; //zatrzymanie wątku ma się odbyć przez ustawienie tej zmiennej na false
	
	std::mutex locker; //blokada związana z powyższą zmienną
	public:
	ThreadInterruptible();
	void setThread(std::unique_ptr<std::thread> thread) ;
	void setCondition(bool condition);
	bool getCondition();
	void join();
	
	
	
};

#endif
