
#include <sstream>
#include "headers.hpp"
GeneralException::GeneralException(const std::string & filename, int line_num):
	filename(filename), line_num(line_num) {
			std::stringstream message;
			message << "Błąd w: ";
			message << filename << ':';
			message << line_num << std::endl;
			eventual = message.str();
}
		
const char * GeneralException::what() {
	return eventual.c_str();
}
