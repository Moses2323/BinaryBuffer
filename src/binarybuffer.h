/*
 * binarybuffer.h
 *
 *  Created on: 21 сент. 2017 г.
 *      Author: Gasparyan Moses
 */
#ifndef BINARYBUFFER_GASPARYANMOSES_21092017
#define BINARYBUFFER_GASPARYANMOSES_21092017

#include <iostream>
#include <vector>
#include <valarray>

class BinaryBuffer {
    //! \~russian \brief Ссылка на поток, куда происходит вывод.
    std::ostream & ostr_;

public:

    /*! \~russian
     * \brief Конструктор.
     * \param ostr ссылка на поток, куда происходит вывод.
     */
    explicit BinaryBuffer( std::ostream & ostr) : ostr_(ostr) {}

    /*! \~russian
     * \brief Оператор вывода.
     * \param t элемент, который будет выведен в поток.
     * \return ссылку на текущий объект.
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
