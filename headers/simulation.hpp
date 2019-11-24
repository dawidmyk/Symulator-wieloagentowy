class Point {
	public:
	float x;
	float y;
	virtual std::shared_ptr<Edge> choose() = 0;
	virtual std::shared_ptr<Edge> chooseExcept(std::shared_ptr<Edge> exception) = 0;
};

class EdgeProperty {
	//here are defined some Edge features
	//like capacity
	public:
	float capacity;
};

class Edge {
	public:
	std::shared_ptr<Point> begin;
	std::shared_ptr<Point> end;
	//these could be other types of pointer
	std::vector<EdgeProperty> properties;
	//and other type of collection used
	int properties_num;
	float length;
	float piece_length;
	
	double velocityAt(int fragment) {
		return properties.at(fragment);
	}
};

class SpecialPoint : public Point {
	//.. they will can be start and end points
	//and represent cities
	public:
	std::vector<std::shared_ptr<Edge>> edges;
	std::shared_ptr<Edge> choose(); //both virtual in base class
	std::shared_ptr<Edge> chooseExcept(std::shared_ptr<Edge> exception);
	
};

class UsualPoint : public Point {
	public:
	std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>> myEdges;
	std::shared_ptr<Edge> choose(); //both virtual in base class
	std::shared_ptr<Edge> chooseExcept(std::shared_ptr<Edge> exception);
};

class Graph {
	//here pointers in containers
	//are to be owners of the objects
	public:
	std::vector<std::shared_ptr<Point>> points;
	std::vector<std::shared_ptr<Edge>> edges;
	std::vector<std::shared_ptr<Agent>> agents;
};

