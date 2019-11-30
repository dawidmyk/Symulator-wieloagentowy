#include <chrono>
#include "../headers/agent.hpp"
//this include should be changed when we have Makefile/Sconsfile
void Agent::runFunction() {
	double pos = 0;
	double fragmentLength = getFragmentLength();
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	first = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff;
	while(pos < fragmentLength) {
		std::lock_guard lock(posits);
		second = std::chrono::high_resolution_clock::now();
		diff = second - first;
		first = second;
		pos += diff.count()*getVelocity();
		//here little change with sin and cos
	} //nie jest dopracowana
}

void Agent::threadFunction() {
	auto previousOne = begin;
	auto situation = previousOne->choose(); //virtual method
	auto actual = situation.first;
	char dir = situation.second; //this variable may be reached form other 
	{
			std::lock_guard lock(dir_read);
			this->actual = actual;
			this->dir = dir;
	}
	std::general_ptr<Point> nextOne;
	
	while(true) { //because there is no defined limit

		nextOne = actual->otherSide(previousOne);
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
		
		for(; fragment != fin; fragment += dir) {
			runFunction();
		}
		
		previousOne = nextOne;
		situation = previousOne->chooseExcept(actual);
		actual = situation.first;
		dir = situation.second;
		{
			std::lock_guard lock(dir_read);
			this->actual = actual;
			this->dir = dir;
		}
	}
}
