#ifndef OUTPUT
#define OUTPUT

class Output 
{
	public:
	virtual void actualize(const general_ptr<Agent> & agent, double x, double y, int i) = 0; //i to numer agenta
		
	virtual void prenoteCrash() = 0;
		
	virtual void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j) = 0;
		//i oraz j to numery obydwu agentów
		
	virtual void endRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & end, int i, bool success) = 0;
		
	virtual void changeRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & now,
			const general_ptr<Edge> & previousOne,  const general_ptr<Edge> & newOne, int nume) = 0;

	virtual void endInform() = 0;
		
	virtual void lockAchive(int i) = 0;

};

#endif
