void Agent::edgeThreadFunction() {
	double pos = 0;
	double fragmentLength = getFragmentLength();
	std::chrono::time_point<std::chrono::high_resolution_clock> first, second;
	first = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff;
	while(pos < fragmentLength) {
		second = std::chrono::high_resolution_clock::now();
		diff = second - first;
		first = second;
		pos += diff.count()*getVelocity();
		//here little change with sin and cos
	}
}

void Agent::pointThreadFunction() {
	std::general_ptr<Point> previousOne = generatePosition();
	std::pair<std::general_ptr<Edge>, char> situation = previousOne->choose(); //virtual method
	std::general_ptr<Edge> actual = situation.first;
	char dir = situation.second;
	std::general_ptr<Point> nextOne;
	
	while(true) { //because there is no defined limit
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
		actual = situation.first;
		dir = situation.second;
	}
}
