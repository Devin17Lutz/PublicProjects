/************************************************************************
* Class: Array
*
* Purpose: This class creates the array that will hold a specified data
*	type
*
* Manager functions:
*	Array()
*	Array(int length, int start_index = 0)
*	Array(const Array & rhs)
*	Array & operator=(const Array & rhs)
*	~Array()
*
* Methods:
*	T & operator[](int index)					-Returns the Tile
*	void SetStartIndex(int start_index)			-Sets the start index
*	void SetLength(int length)					-Sets the length of the array
*	int GetStartIndex()							-Returns the start index
*	int GetLength()								-Returns the Length of the arrat
*
* Data Members:
*	T * m_array
*	int m_length
*	int m_start_index
*
*************************************************************************/
#pragma once
#include <iostream>
#include <string.h>
#include "Exception.h"
using std::cout;
using std::endl;

#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
class Array
{
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array & rhs);
	Array & operator=(const Array & rhs);
	T & operator[](int index);
	const T & operator[](int index) const;

	//Setters
	void SetStartIndex(int start_index);
	void SetLength(int length);

	//Getters
	int GetStartIndex() const;
	int GetLength() const;

	~Array();
private:
	T* m_array;								//m_array will hold whatever T is into an array
	int m_length;							//how many elements the array will have
	int m_start_index;						//is where the array will start
};

template<typename T>
inline Array<T>::Array()
	: m_array(nullptr), m_length(0), m_start_index(0)
{
	//cout << "In Array c'tor" << endl;
}

template<typename T>
inline Array<T>::Array(int length, int start_index)
	: m_array(nullptr), m_length(length), m_start_index(start_index)
{
	//cout << "In Array two arg c'tor" << endl;
	m_array = new T[length];
}

template<typename T>
inline Array<T>::Array(const Array<T> & rhs)
	: m_array(nullptr), m_length(rhs.m_length), m_start_index(rhs.m_start_index)
{
	//cout << "In Array copy c'tor" << endl;
	m_array = new T[m_length];
	for (int i = 0; i < m_length; i++)
	{
		m_array[i] = rhs.m_array[i];
	}
}

template<typename T>
inline Array<T> & Array<T>::operator=(const Array<T> & rhs)
{
	//cout << "In Array op=" << endl;
	if (this != &rhs)
	{
		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;

		delete[]m_array;
		m_array = new T[m_length];

		for (int i = 0; i < m_length; i++)
		{
			m_array[i] = rhs.m_array[i];
		}
	}
	return *this;
}

template<typename T>
inline T & Array<T>::operator[](int index)
{
	if (index < m_start_index || index > (m_start_index + m_length))
	{
		throw Exception("Index is out of bounds");
	}
	return m_array[index - m_start_index];
}

template<typename T>
inline const T & Array<T>::operator[](int index) const
{
	cout << "In Array const []" << endl;
	if (index < m_start_index || index > (m_start_index + m_length))
	{
		throw Exception("Index is out of bounds");
	}
	return m_array[index - m_start_index];
}

template<typename T>
inline void Array<T>::SetStartIndex(int start_index)
{
	m_start_index = start_index;
}

template<typename T>
inline void Array<T>::SetLength(int length)
{
	if (length < 0)
	{
		throw Exception("Length is less than zero");
	}

	int smallest = m_length < length ? m_length : length;				//small will hold the smallest length

	T *temp = new T[length];
	for (int i = 0; i < smallest; i++)
	{
		temp[i] = m_array[i];
	}

	delete[] m_array;
	m_array = temp;
	m_length = length;
}

template<typename T>
inline int Array<T>::GetStartIndex() const
{
	return m_start_index;
}

template<typename T>
inline int Array<T>::GetLength() const
{
	return m_length;
}

template<typename T>
inline Array<T>::~Array()
{
	//cout << "In Array d'tor" << endl;
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}
#endif

