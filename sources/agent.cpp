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
	std::shared_ptr<Point> previousOne = generatePosition();
	std::pair<std::shared_ptr<Edge>, char> situation = previousOne->choose(); //virtual method
	std::shared_ptr<Edge> actual = situation.first;
	char dir = situation.second;
	std::shared_ptr<Point> nextOne;
	
	while(true) { //because there is no defined limit
		nextOne = otherSide(previousOne, actualEdge);
		int n = getFragmentNum();
		
		for(int in = 0; in != n; n++) {
			if (dir) fragment = in;
			else fragment = n - in;
			edgeThreadFunction();
		}
		
		previousOne = nextOne;
		situation = previousOne->chooseExcept(actual);
		actual = situation.first;
		dir = situation.second;
	}
}