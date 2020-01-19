#include "exception.hpp"

inline Distance::Distance():
	value(0),
	transparent(true),
	exception(false),
	initial(false)
	{
	}

inline Distance::Distance(double value, bool transparent):
	value(value),
	transparent(transparent),
	exception(false),
	initial(false)
	{
	}
	


inline bool Distance::operator > (const Distance & another) const {
	return !operator > (another);
}

inline void Distance::operator += (double addition) {
	value += addition;
}

inline Distance Distance::operator + (double addition) {
	Distance ret = *this;
	ret.value = value + addition;
	return ret;
}

inline void Distance::hide() {
	if(exception) transparent = false;
}
