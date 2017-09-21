#ifndef MISTAKE_GM
#define MISTAKE_GM

#include <iostream>
#include <string>
#include <sstream>

template<typename T>
inline std::string toStr(const T& elem){
	std::stringstream vss;
	vss << elem;
	return vss.str();
}

inline void print_mistake(const std::string& funcName, int line, const std::string& filename, const std::string& message){
	std::cerr << "ERROR in " << funcName << ", line " << line << ", file " << filename << std::endl;
	std::cerr << '\t' << message << std::endl;
	throw;
}

inline void print_mistake_lite(const std::string& funcName, int line, const std::string& filename, const std::string& message){
	std::cerr << "WARNING in " << funcName << ", line " << line << ", file " << filename << std::endl;
	std::cerr << '\t' << message << std::endl;
}

#endif /* MISTAKE_GM */
