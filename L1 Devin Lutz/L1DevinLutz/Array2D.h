/************************************************************************
* Class: Array2D
*
* Purpose: This class creates the sets the rows and columns of the array
*	and retrieves the data in the element.
*
* Manager functions:
*	Array2D()
*	Array2D(int row, int col)
*	Array2D(const Array2D &copy)
*	Array2D & operator=(const Array2D & rhs)
*	Array2D()
*
* Methods:
*	void SetRow(int row)						-Sets the Row
*	void SetColumn(int col)						-Sets the Column
*	int GetRow() const							-Returns the Row
*	int GetColumn() const						-Returns the Column
*	T & Select(int row, int col)				- Returns the tile at position row
*													column
*
* Data Members:
*	int m_row
*	int m_col
*	Array<T> m_array
*
*************************************************************************/
#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Array.h"
#include "Tile.h"
#include "Exception.h"
#include "Row.h"

#ifndef ARRAY2D_H
#define ARRAY2D_H

template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int row, int col);
	Array2D(const Array2D &copy);
	Array2D & operator=(const Array2D & rhs);
	Row<T> operator[](int index);
	const Row<T> operator[](int index) const;

	//Setters
	void SetRow(int row);
	void SetColumn(int col);

	//Getters
	int GetRow() const;
	int GetColumn() const;

	T & Select(int row, int col);
	~Array2D();

private:
	int m_row;											// holds the row
	int m_col;											// holds the column
	Array<T> m_array;									// holds the tiles
};

template<typename T>
inline Array2D<T>::Array2D()
	: m_row(0), m_col(0)
{
	//cout << "In Array2D c'tor" << endl;
}

template<typename T>
inline Array2D<T>::Array2D(int row, int col)
	: m_row(row), m_col(col)
{
	//cout << "In Array2D 2 arg c'tor" << endl;
	if (m_row < 0)
	{
		throw Exception("m_row is negative");
	}
	else if (m_col < 0)
	{
		throw Exception("m_col is negative");
	}
	m_array.SetLength(row * col);
}

template<typename T>
inline Array2D<T>::Array2D(const Array2D & copy)
	: m_row(copy.m_row), m_col(copy.m_col), m_array(copy.m_array)
{
	//cout << "In Array2D copy c'tor" << endl;
}

template<typename T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D & rhs)
{
	//cout << "In Array2D op=" << endl;
	if (this != &rhs)
	{
		m_row = rhs.m_row;
		m_col = rhs.m_col;
		m_array = rhs.m_array;
	}
	return *this;
}
template<typename T>
inline Row<T> Array2D<T>::operator[](int index)
{
	//cout << "In Array2D []" << endl;
	if (index < 0 || index > (m_row - 1))
	{
		throw Exception("Index is out of bounds");
	}
	return Row<T>(*this, (m_col * index));
}

template<typename T>
inline const Row<T> Array2D<T>::operator[](int index) const
{
	cout << "In Array2D const []" << endl;
	if (index < 0 || index > m_row)
	{
		throw Exception("Index is out of bounds");
	}
	return Row<T>(*(const_cast<Array2D *>(this)), (m_col * index));
}

template<typename T>
inline void Array2D<T>::SetRow(int row)
{
	if (row < 0)
	{
		throw Exception("Can't have negative number");
	}
	m_row = row;
	m_array.SetLength(m_col * m_row);
}

template<typename T>
inline void Array2D<T>::SetColumn(int col)
{
	int i = 0,						//i will hold the number for the array elements
		j = 0,						//j will hold the number for temp elements
		total = 0;					//total will hold the the number of elements within a row resets to zero after finishing a row

	if (col < 0)
	{
		throw Exception("Can't have negative number");
	}
	Array<T> temp(col * m_row);		//create a temporary array to hold the bigger or smaller array based on the new column

	while (i < (m_row * m_col))
	{
		if (total < col)
		{
			if (total < m_col)
			{
				temp[j] = m_array[i];
				i++;
			}
			j++;
			total++;
		}
		else
		{
			if (col < m_col)
			{
				i += (abs(col - m_col));
			}
			total = 0;
		}
	}
	m_array = temp;
	m_col = col;
}

template<typename T>
inline int Array2D<T>::GetRow() const
{
	return m_row;
}

template<typename T>
inline int Array2D<T>::GetColumn() const
{
	return m_col;
}

template<typename T>
inline T & Array2D<T>::Select(int row, int col)
{
	if (row < 0 || col < 0)
	{
		throw Exception("Can't have negative column or row");
	}
	return m_array[row + col];
}

template<typename T>
inline Array2D<T>::~Array2D()
{
	//cout << "In Array2D d'tor" << endl;
	m_row = 0;
	m_col = 0;
} 
#endif
