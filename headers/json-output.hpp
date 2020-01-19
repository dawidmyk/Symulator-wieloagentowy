#ifndef JSON_OUTPUT
#define JSON_OUTPUT

class JsonOutput : public Output
{
	public:
	void actualize(const general_ptr<Agent> & agent, double x, double y, int i); //i to numer agenta
		
	void prenoteCrash();
		
	void noteCrash(const general_ptr<Agent> & ptr1, const general_ptr<Agent> & ptr2, int i, int j);
		//i oraz j to numery obydwu agentów
		
	void endRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & end, int i, bool success);
		
	void changeRoute(const general_ptr<Agent> & ptr, const general_ptr<Point> & now,
			const general_ptr<Edge> & previousOne,  const general_ptr<Edge> & newOne, int nume);

	void endInform();
		
	void lockAchive(int i);

};

#endif
