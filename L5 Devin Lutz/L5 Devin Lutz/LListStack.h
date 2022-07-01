/************************************************************************
* Class: LListStack
*
* Purpose: This class serves as the stack for linked list
*
* Manager functions:
*	LListStack()
*	LListStack(const LListStack &copy)
*	LListStack & operator=(const LListStack &rhs)
*	~LListStack()
*
* Methods:
*	void Push(const T & data)				-Push will input data into array
*	T Pop()									-Pop will extract the top element
*	T Peek()								-Returns whats on top of the stack
*	bool isEmpty()							-Returns true if empty false if not
*	bool isFull()							-Returns true if full false if not
*	int Size()								-Returns the size of the stack
*
* Data Members:
*	LinkedList<T> m_stack
*	int m_size
*
*************************************************************************/
#pragma once
#include <iostream>
#include "LinkedList.h"
using std::cout;

#ifndef LLISTSTACK_H
#define LLISTSTACK_H

template <typename T>
class LListStack
{
public:
	LListStack();
	LListStack(const LListStack &copy);
	LListStack & operator=(const LListStack &rhs);

	void Push(const T & data);
	T Pop();
	T Peek();
	bool isEmpty();
	int Size() const;

	void MOVE();
	~LListStack();

private:
	LinkedList<T> m_stack;						// Will hold the data for the stack
	int m_size;									// Holds the size how many elements are in the linked list stack
};

template<typename T>
inline LListStack<T>::LListStack()
	: m_size(0)
{
	//cout << "In LinkedList Stack c'tor" << endl;
}

template<typename T>
inline LListStack<T>::LListStack(const LListStack & copy)
	: m_stack(copy.m_stack), m_size(copy.m_size)
{
	//cout << "In LinkedList Stack c'tor" << endl;
}

template<typename T>
inline LListStack<T> & LListStack<T>::operator=(const LListStack & rhs)
{
	//cout << "In LinkedList Stack op=" << endl;
	if (this != &rhs)
	{
		m_stack = rhs.m_stack;
		m_size = rhs.m_size;
	}
	return *this;
}

template<typename T>
inline void LListStack<T>::Push(const T & data)
{
	m_stack.Prepend(data);
	m_size++;
}

template<typename T>
inline T LListStack<T>::Pop()
{
	T data;
	if (isEmpty())
	{
		throw Exception("LinkedList Stack is empty");
	}
	data = (m_stack.First());
	m_stack.Extract(data);
	m_size--;

	return data;
}

template<typename T>
inline T LListStack<T>::Peek()
{
	if (isEmpty())
	{
		throw Exception("LinkedList Stack is empty");
	}
	return m_stack.First();
}

template<typename T>
inline bool LListStack<T>::isEmpty()
{
	return m_stack.isEmpty();
}

template<typename T>
inline int LListStack<T>::Size() const
{
	return m_size;
}

template<typename T>
inline void LListStack<T>::MOVE()
{
	m_stack.Move();
}

template<typename T>
inline LListStack<T>::~LListStack()
{
	//cout << "In LinkedList Stack d'tor" << endl;
	m_size = 0;
}
#endif