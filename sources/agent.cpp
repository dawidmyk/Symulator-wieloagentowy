#include <chrono>
#include "../headers/agent.hpp"
//this include should be changed when we have Makefile/Sconsfile

Agent::Agent(const std::general_ptr<Point> & begin, const std::general_ptr<Point> & end): dir(0), active(false), begin(begin),
	end(end), fragment(-1) {
		auto pointPositions = begin->locate();
		x = pointPositions.first;
		y = pointPositions.second;	
}
	
bool Agent::twoClose(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		std::lock_guard lock1(one->posits);
		std::lock_guard lock2(second->posits);
		float xdiff = one->x - second->x;
		float ydiff = one->y - second->y;
		return (sqrt(xdiff*xdiff + ydiff*ydiff) <= close);
}

bool Agent::crash(const std::general_ptr<Agent> & one, const std::general_ptr<Agent> & second) {
		if(!one->checkActive()||!second->checkActive()) return false;
		bool ifClose = twoClose(one, second);
		if(!ifClose) return false;
		{
			std::lock_guard lock1(one->dir_read);
			std::lock_guard lock2(second->dir_read);
			//it is to correct because there might occur a deadlock
			if(one->actual == second->actual && one->dir == -second->dir) return true;
			return false;
		}
}


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
	setActive(true);
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
	
	while(previousOne != end) { //because there is no defined limit

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
	setActive(false);
}
