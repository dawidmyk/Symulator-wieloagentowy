#include <chrono>
#include "../headers/agent.hpp"
//this include should be changed when we have Makefile/Sconsfile
void Agent::runFunction() {
	float pos = 0;
	float fragmentLength = actual->getFragmentLength();
	float angle = actual->getAngle();
	float sinus = sin(angle);
	float cosinus = cos(angle);
	float general_move;
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	first = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> diff;
	while(pos < fragmentLength) {
		second = std::chrono::high_resolution_clock::now();
		diff = second - first;
		first = second;
		general_move = diff.count()*getVelocity();
		pos += general_move;
		std::lock_guard lock(posits);
		x += general_move * cosinus;
		y += general_move * sinus;
	}
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
