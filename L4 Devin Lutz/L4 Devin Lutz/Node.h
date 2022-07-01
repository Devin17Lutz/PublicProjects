/************************************************************************
* Class: Node
*
* Purpose: This class will handle the data and to see whats next and previous
*			of the node.
*
* Manager functions:
*	Node()
*	Node(const Node &copy)
*	Node & operator=(const Node &rhs)
*	~Node()
*
* Methods:
*	void SetData(T data)						-Sets the data
*	void SetNext(Node *next)					-Sets the next pointer
*	void SetPrev(Node *prev)					-Sets the prev pointer
*	T GetData()const							-Returns the data
*	Node *GetNext()const						-Returns the next pointer
*	Node *GetPrev()const						-Returns the prev pointer
*
* Data Members:
*	T m_data									-Holds the data
*	Node *m_next								-Holds the next pointer
*	Node *m_prev								-Holds the prev pointer
*
*************************************************************************/
#pragma once
#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	Node();
	Node(const Node &copy);
	Node & operator=(const Node &rhs);

	//Setters
	void SetData(T data);
	void SetPrev(Node *prev);
	void SetNext(Node *next);
	//Getters
	T & GetData();
	Node * GetPrev() const;
	Node * GetNext() const;

	~Node();
private:
	T m_data;
	Node *m_next;
	Node *m_prev;
};

template<typename T>
inline Node<T>::Node()
	: m_next(nullptr), m_prev(nullptr)
{
	//cout << "In Node c'tor" << endl;
}

template<typename T>
inline Node<T>::Node(const Node & copy)
	: m_data(copy.m_data), m_next(copy.m_next), m_prev(copy.m_prev)
{
	//cout << "In Node copy c'tor" << endl;
}

template<typename T>
inline Node<T> & Node<T>::operator=(const Node & rhs)
{
	//cout << "In Node op=" << endl;
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
	}
	return *this;
}

template<typename T>
inline void Node<T>::SetData(T data)
{
	m_data = data;
}

template<typename T>
inline void Node<T>::SetPrev(Node * prev)
{
	m_prev = prev;
}

template<typename T>
inline void Node<T>::SetNext(Node * next)
{
	m_next = next;
}

template<typename T>
inline T & Node<T>::GetData()
{
	return m_data;
}

template<typename T>
inline Node<T> * Node<T>::GetNext() const
{
	return m_next;
}

template<typename T>
inline Node<T> * Node<T>::GetPrev() const
{
	return m_prev;
}

template<typename T>
inline Node<T>::~Node()
{
	//cout << "In Node d'tor" << endl;
	m_next = nullptr;
	m_prev = nullptr;
}
#endif
