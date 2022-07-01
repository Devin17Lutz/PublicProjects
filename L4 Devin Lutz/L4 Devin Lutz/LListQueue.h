/************************************************************************
* Class: ArrayQueue
*
* Purpose: This class creates the queue by using the the class array that
*				we previously created.
*
* Manager functions:
*	LListQueue()
*	LListQueue(const LListQueue &copy)
*	LListQueue & operator=(const LListQueue &rhs)
*	~LListQueue()
*
* Methods:
*	void Enqueue(const T & data)					-Adds data to the end of the array
*	T Dequeue()										-Removes data from the front of the
*														array.
*	T & Front()										-Returns data from the front of the
*														array.
*	int Size()										-Returns the size of the array
*	bool isEmpty()									-Returns true if array is empty false
*														if array is filled.
*
* Data Members:
*	LinkedList<T> m_queue
*	int m_first
*	int m_rear
*
*************************************************************************/
#pragma once
#include <iostream>
#include "LinkedList.h"
using std::cout;
using std::endl;

#ifndef LLISTQUEUE_H
#define LLISTQUEUE_H

template <typename T>
class LListQueue
{
public:
	LListQueue();
	LListQueue(const LListQueue & copy);
	LListQueue & operator=(const LListQueue &rhs);

	void Enqueue(const T & data);
	T Dequeue();
	T & Front();
	int Size();
	bool isEmpty();

	~LListQueue();
private:
	LinkedList<T> m_queue;								//Holds the linked list to store the data
	int m_size;											//Holds the size or how many nodes are in the linked list
};

template<typename T>
inline LListQueue<T>::LListQueue()
	: m_size(0)
{
	//cout << "In LinkedList Queue c'tor" << endl;
}

template<typename T>
inline LListQueue<T>::LListQueue(const LListQueue & copy)
	: m_queue(copy.m_queue), m_size(copy.m_size)
{
	//cout << "In LinkedList Queue Copy c'tor" << endl;
}

template<typename T>
inline LListQueue<T> & LListQueue<T>::operator=(const LListQueue & rhs)
{
	//cout << "In LinkedList Queue Op =" << endl;
	if (this != &rhs)
	{
		m_queue = rhs.m_queue;
		m_size = rhs.m_size;
	}
	return *this;
}

template<typename T>
inline void LListQueue<T>::Enqueue(const T & data)
{
	m_queue.Append(data);
	m_size++;
}

template<typename T>
inline T LListQueue<T>::Dequeue()
{
	if (isEmpty())
	{
		throw Exception("LinkedList Queue is empty");
	}
	T data = m_queue.First();							//Holds the data that will be dequeue
	m_queue.Extract(data);
	m_size--;

	return data;
}

template<typename T>
inline T & LListQueue<T>::Front()
{
	return m_queue.First();
}

template<typename T>
inline int LListQueue<T>::Size()
{
	return m_size;
}

template<typename T>
inline bool LListQueue<T>::isEmpty()
{
	return m_queue.isEmpty();
}

template<typename T>
inline LListQueue<T>::~LListQueue()
{
	//cout << "In LinkedList Queue d'tor" << endl;
	m_size = 0;
}
#endif
