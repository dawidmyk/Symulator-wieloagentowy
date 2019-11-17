class Agent {
	public:
	float x;
	float y;
	float roadAngle;
	//std::thread edgeThread;
	std::thread pointThread;
	
	std::shared_ptr<Edge> actualEdge;
	int fragment; //used for checking velocity
	
	void edgeThreadFunction();
	void pointThreadFunction();
	
	double getVelocity() {
		return actualEdge.velocityAt(fragment);
	}
	double getFragmentLength() {
		return actualEdge.piece_length;
	}
	
};
