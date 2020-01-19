#include "headers.hpp"
bool Distance::operator < (const Distance & another) const {
	//Tą metodę trzeba wyciągnąć do source'ów
	if((exception && another.exception) || (initial && another.initial))
		throw GeneralException(std::string(__FILE__), __LINE__);
	if(initial != another.initial) {
		return !initial;
	}
	if(exception != another.exception) {
		return !exception;
	}
	if(transparent != another.transparent)
		return transparent;
	
	
	
	return value < another.value;
}
