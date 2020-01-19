#ifndef DISTANCE
#define DISTANCE


struct Distance {
	double value;
	bool transparent;
	bool exception;
	bool initial;
	
	Distance();
	Distance(double value, bool transparent);
	bool operator < (const Distance & another) const;
	bool operator > (const Distance & another) const;
	void operator += (double addition);
	Distance operator + (double addition);
	void hide();
};

#endif
