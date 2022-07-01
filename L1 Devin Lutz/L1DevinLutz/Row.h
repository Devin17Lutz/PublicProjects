/************************************************************************
* Class: Row
*
* Purpose: This class will serve as finding the data in the specified row
*	and call the select method from Array2D to retrieve the data.
*
* Manager functions:
*	Row(Array2D<T>& arr, int row)
*
* Methods:
*	T & operator[](int index)
*	const T & operator[](int index) const
*
* Data Members:
*	Array2D<T>& m_arr
*	int m_row
*
*************************************************************************/
#pragma once
#include <iostream>
#include <string.h>
#include "Tile.h"
using std::cout;

#ifndef ROW_H
#define ROW_H

template<typename T>
class Array2D;

template <typename T>
class Row
{
public:
	Row(Array2D<T>& arr, int row);
	T & operator[](int index);
	const T & operator[](int index) const;
private:
	Array2D<T>& m_arr;							// holds the reference for Array2D
	int m_row;									// holds the row
};

template<typename T>
inline Row<T>::Row(Array2D<T> & arr, int row)
	: m_arr(arr), m_row(row)
{
	//cout << "In Row c'tor" << endl;
}

template<typename T>
inline T & Row<T>::operator[](int index)
{
	if (index > (m_arr.GetColumn() - 1) || index < 0)
	{
		throw Exception("Index out of bounds");
	}
	return m_arr.Select(m_row, index);
}

template<typename T>
inline const T & Row<T>::operator[](int index) const
{
	cout << "In Row const []" << endl;
	if (index < 0 || index >(m_row + index))
	{
		throw Exception("Index is out of bounds");
	}
	return m_arr.Select(m_row, index);
}
#endif
