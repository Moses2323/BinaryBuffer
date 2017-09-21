/*
 * binarybuffer.h
 *
 *  Created on: 21 ����. 2017 �.
 *      Author: Gasparyan Moses
 */
#ifndef BINARYBUFFER_GASPARYANMOSES_21092017
#define BINARYBUFFER_GASPARYANMOSES_21092017

#include <iostream>
#include <vector>
#include <valarray>

class BinaryBuffer {
    //! \~russian \brief ������ �� �����, ���� ���������� �����.
    std::ostream & ostr_;

public:

    /*! \~russian
     * \brief �����������.
     * \param ostr ������ �� �����, ���� ���������� �����.
     */
    explicit BinaryBuffer( std::ostream & ostr) : ostr_(ostr) {}

    /*! \~russian
     * \brief �������� ������.
     * \param t �������, ������� ����� ������� � �����.
     * \return ������ �� ������� ������.
     */
    template<typename T>
    BinaryBuffer& operator<< ( const T& t);

    BinaryBuffer& operator<< ( const char* t );

    template<typename T>
    BinaryBuffer& operator<< ( const std::vector<T>& vec );
    template<typename T>
    BinaryBuffer& operator<< ( const std::valarray<T>& val );

    void flushIt() { ostr_ << std::flush; }
};

#include "binarybuffer.tcc"

#endif /* BINARYBUFFER_GASPARYANMOSES_21092017 */
