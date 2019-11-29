//In future we will use random here
//and later something even more wise
std::pair<std::general_ptr<Edge>, char> SpecialPoint::choose() {
	std::general_ptr<Edge> edge = edges.at(0);
	return std::pair<std::general_ptr<Edge>, char>(edge, edge.side(std::general_ptr<Point>(this)));
}

std::pair<std::general_ptr<Edge>, char> SpecialPoint::chooseExcept(const std::general_ptr<Edge> & exception) {
	int now = 0;
	while(true) {
		if(edges.at(now) != exception) {
			std::general_ptr<Edge> edge = edges.at(0);
			return std::pair<std::general_ptr<Edge>, char>(edge, edge.side(std::general_ptr<Point>(this)));
		}
		now++;
	}
}

std::pair<std::general_ptr<Edge>, char> UsualPoint::choose() {
	return std::pair<std::general_ptr<Edge>, char>(myEdges.first, myEdges.first.side(std::general_ptr<Point>(this)));
}

std::pair<std::general_ptr<Edge>, char> UsualPoint::chooseExcept(const std::general_ptr<Edge> & exception) {
	if (myEdges.first != exception) return std::pair<std::general_ptr<Edge>, char>(myEdges.first, myEdges.first.side(std::general_ptr<Point>(this)));
	return std::pair<std::general_ptr<Edge>, char>(myEdges.second, myEdges.second.side(std::general_ptr<Point>(this)));
}
