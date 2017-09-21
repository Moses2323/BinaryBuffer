/*
 * binarybuffer.cpp
 *
 *  Created on: 21 сент. 2017 г.
 *      Author: Gasparyan Moses
 */
#include <cstring>
#include <string>

template<typename T>
inline BinaryBuffer& BinaryBuffer::operator<< ( const T& t){
    ostr_.write(reinterpret_cast<const char*>(&t), sizeof(T));
    std::cout << "element " << t << " has been written" << std::endl;
    return *this;
}

template<>
inline BinaryBuffer& BinaryBuffer::operator<<( const std::string& s ){
	if ( !s.empty() )
		ostr_.write( s.c_str(), s.size() );		// + 1 ?
	std::cout << "std::string \"" << s << "\" has been written" << std::endl;
	return *this;
}

inline BinaryBuffer& BinaryBuffer::operator<<( const char* t ){
    ostr_.write(t, std::strlen(t));		// + 1 ?
    std::cout << "c string \"" << t << "\" has been written" << std::endl;
    return *this;
}

template<typename T>
inline BinaryBuffer& BinaryBuffer::operator<<(const std::vector<T>& vec){
	if ( vec.size() > 0 )
		ostr_.write( reinterpret_cast<const char*>(vec.data()), vec.size()*sizeof(T) );
	std::cout << "vector [";
	for(size_t i=0; i < vec.size(); ++i){
		std::cout << " " << vec[i];
	}
	std::cout << "] has been written" << std::endl;
	return *this;
}

template<typename T>
inline BinaryBuffer& BinaryBuffer::operator<<(const std::valarray<T>& val){
	if ( val.size() > 0 )
		ostr_.write( reinterpret_cast<const char*>(&val[0]), val.size()*sizeof(T) );
	std::cout << "valarray [";
	for(size_t i=0; i < val.size(); ++i){
		std::cout << " " << val[i];
	}
	std::cout << "] has been written" << std::endl;
	return *this;
}
