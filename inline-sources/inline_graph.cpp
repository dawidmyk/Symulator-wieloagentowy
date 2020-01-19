

inline void Graph::addUsualPoint(double x, double y) {
	points.push_back(std::unique_ptr<Point>(new UsualPoint(x, y, rander)));
	//musimy dodać do wektora obiekt typu unique_ptr
	//unique_ptr to z jakiś powodów wyjątek od możliwości domyślenia
	//sie parametru szablonu w konstruktorze (c++17)
	//ale tu nie chcemy by się domyślał bo unique_ptr ma typ Point
	//a konstruktor ma typ UsualPoint
	//w konstruktorach unique_ptr się woła "new" i najlepiej nigdzie indziej 
}

inline void Graph::addSpecialPoint(double x, double y) {
	points.push_back(std::unique_ptr<Point>(new SpecialPoint(x, y, rander)));
}

inline void Graph::addEdge(double x1, double y1, double x2, double y2) {
	//tu jeszcze nie założone że może być błąd
	//tzn. może się nie wstrzelić i wtedy spotPoint zwraca nulle
	edges.push_back(std::unique_ptr<Edge>(new Edge(spotPoint(x1, y1), spotPoint(x2, y2))));
	//spotPoint zwraca general_ptr
	//najpierw dobrze jest potworzyć punkty i potem niech Edge się w nie wstrzeliwują
}

inline void Graph::addEdgeNum(int begin, int end) {
	edges.push_back(std::unique_ptr<Edge>(new Edge(general_ptr(points.at(begin)),
	general_ptr(points.at(end)))));
	//rozpinamy krawędź na punktach zajmujących określone pozycje w wektorze punktów
	//(dodane w określonej kolejności)
	//wtedy nie musimy się wstrzelać
	//a general_ptr bo nie można przenosić unique_ptr, trzeba zamienić
}

inline void Graph::addAgent(double x1, double y1, double x2, double y2) {
	agents.push_back(std::unique_ptr<Agent>(new Agent(spotPoint(x1, y1), spotPoint(x2, y2), agents.size())));
} //agent też może się wstrzelić w odpowiednie punkty

inline void Graph::addAgentNum(int begin, int end) {
	agents.push_back(std::unique_ptr<Agent>(new Agent(general_ptr(points.at(begin)),
	general_ptr(points.at(end)), agents.size())));
} //



inline void Graph::spawnAgents(Output & out) {
	for(auto & ptr : agents) {
		ptr->spawn(out); //uruchamia dla każdego agenta jego wątek
	}
}

inline void Graph::joinAgents() {
	for(auto & ptr : agents) ptr->join();
}


inline void Graph::makeSeed() {
	rander.makeSeed(); //zasadzenie ziarna dla maszyny losującej
}

inline void Graph::edgesAdjust() { //wszystkie parametry dla każdej krawędzi muszą być gdzieś
	//w końcu policzone
	for (auto & ptr : edges) ptr->countDimensions();
}

