//In future we will use random here
//and later something even more wise
std::shared_ptr<Edge> SpecialPoint::choose() {
	return edges.at(0);
}

std::shared_ptr<Edge> SpecialPoint::chooseExcept(std::shared_ptr<Edge> exception) {
	int now = 0;
	while(true) {
		if(edges.at(now) != exception) return edges.at(now);
		now++;
	}
}

std::shared_ptr<Edge> UsualPoint::choose() {
	return myEdges.first;
}
std::shared_ptr<Edge> UsualPoint::chooseExcept(std::shared_ptr<Edge> exception) {
	if (myEdges.first != exception) return myEdges.first;
	return myEdges.second;
}
