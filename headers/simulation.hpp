/*
Class stores parameters of simulation
Author: Mateusz Szewczyk
*/

#ifndef SIMULATION
#define SIMULATION

class Simulation {
	
	general_ptr<Graph> g;
	general_ptr<Console> out;
	//potem będzie output generalny
	static std::mutex end_lock;
	static bool end_var;
	static double time_reg; //co ile sprawdzana jest pozycja jakiegoś agenta
	
	ThreadInterruptible agentDraw;
	ThreadInterruptible agentCrash;

	
public:
	void testSimulation();
	void run();
	void setAgentDraw();
	void setAgentCrash();
	static void startSimulation();
	static void endSimulation();
	static bool last();
	static void setTime(double time_reg);
	static double getTime();

private:

	
	
	//Graph graph;
	int cargoCount;
	int vehicleCount; // vehicle count == agents count
	int vehicleCapacity;
	int maxWorkTime; //maximum time of agents work without break
	int mishapProbability; 
	int edgeCapacity;

};

#endif
