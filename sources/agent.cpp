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
	auto nextOne;
	
	while(true) { //because there is no defined limit
		{
			std::lock_guard<std::mutex> lock(dir_read);
			this->dir = dir;
		}
		nextOne = actualEdge->otherSide(previousOne);
		int n = getFragmentNum();
		int in, fin;
		if(dir == 1) {
			fragment = 0;
			fin = n;
		else if(dir == -1) {
			fragment = n - 1;
			fin = -1;
		}
		
		for(; fragment != fin; fragment += dir) {
			edgeThreadFunction();
		}
		
		previousOne = nextOne;
		situation = previousOne->chooseExcept(actual);
		{
			std::lock_guard<std::mutex> lock(dir_read)
			actual = situation.first;
			dir = situation.second;
		}
	}
}
