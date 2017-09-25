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

#define DEBUG 0

/*! \~russian
 * \brief Бинарный буфер.
 *
 * Данный класс создан, чтобы с помощью
 * обычного оператора вывода можно было
 * выводить данные в бинарном формате.
 *
 * Поток, в который должен осуществляться вывод,
 * должен быть создан заранее.
 *
 * Схема использования:
 * \code
 *
 * std::string filename = "myBinFile";
 * std::ofstream fout;
 * fout.open(filename, std::ios::out | std::ios::binary);
 *
 * BinaryBuffer binbuf(fout);
 *
 * int vi = 34353;
 * double vd = 3434.343434;
 * std::string vs = "Hello!";
 *
 * binbuf << vi << vd << vs;
 *
 * binbuf.flushIt();	// not necessary
 *
 * fout.close();
 *
 * \endcode
 *
 */
class BinaryBufferOutS {
    //! \~russian \brief Поток, в который происходит вывод.
    std::ostream & ostr_;

public:

    /*! \~russian
     * \brief Конструктор.
     * \param ostr ссылка на поток, в который будет происходить вывод.
     */
    explicit BinaryBufferOutS( std::ostream & ostr) : ostr_(ostr) {}

    /*! \~russian
     * \brief Оператор вывода, который выводит элемент в виде бинарной информации.
     * \param t произвольный элемент (не си-строка, не строка, не vector и не valarray).
     * \return ссылку на текущий объект.
     */
    template<typename T>
    BinaryBufferOutS& operator<< ( const T& t);

    /*! \~russian
     * \brief Оператор вывода. Перегруженная версия для си-строк.
     * \details Выводит посимвольно всю строку. Не выводит символ конца строки.
     * \param t строка в си-стиле.
     * \return ссылку на текущий объект.
     */
    BinaryBufferOutS& operator<< ( const char* t );

    /*! \~russian
     * \brief Оператор вывода. Перегруженная версия для массива (vector).
     * \details Выводит вектор целым блоком в поток вывода.
     * \param vec константная ссылка на вектор.
     * \return ссылку на текущий объект.
     */
    template<typename T>
    BinaryBufferOutS& operator<< ( const std::vector<T>& vec );

    /*! \~russian
     * \brief Оператор вывода. Перегруженная версия для массива (valarray).
     * \details Выводит массив целым блоком в поток вывода.
     * \param val константная ссылка на массив.
     * \return ссылку на текущий объект.
     */
    template<typename T>
    BinaryBufferOutS& operator<< ( const std::valarray<T>& val );

    /*! \~russian
     * \brief Функция для сброса буфера.
     * \details Т.к. данный класс не является наследником basic_ostream,
     * то std::endl, std::flush нельзя просто так использовать с ним.
     * Поэтому используется данный метод, чтобы произвести сброс буфера.
     */
    void flushIt() { ostr_ << std::flush; }
};

/*! \~russian
 * \brief
 */
class BinaryBufferInS{
	//!
	std::istream& bf_;
public:
	//!
	explicit BinaryBufferInS(std::istream& bf) : bf_(bf) {}

	template<typename T>
	BinaryBufferInS& operator>> (T& elem);

	template<typename T>
	BinaryBufferInS& operator>> (std::vector<T>& vec);

	template<typename T>
	BinaryBufferInS& operator>> (std::valarray<T>& val);

	BinaryBufferInS& operator>> (char* s);
};

#include "binarybuffer.tcc"

#endif /* BINARYBUFFER_GASPARYANMOSES_21092017 */
