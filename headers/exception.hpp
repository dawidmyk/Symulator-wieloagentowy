#ifndef EXCEPTION
#define EXCEPTION

#include <string>
class GeneralException : std::exception {
	std::string eventual;
	std::string filename;
	int line_num;
	public:
	GeneralException(const std::string & filename, int line_num);
	const char * what();
};

#endif
