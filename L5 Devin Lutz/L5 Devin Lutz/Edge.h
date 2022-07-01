/************************************************************************
* Class: Edge
*
* Purpose: This class serves as a edge between two vertex's. It will hold
*	the destination vertex pointer, the Edge data and the weight. 
*
* Manager functions:
*	Edge()
*	Edge(const Edge &copy)
*	Edge & operator=(const Edge &rhs)
*	bool operator!=(const Edge &rhs)
*	bool operator==(const Edge &rhs)
*	~Edge()
*
* Methods:
*	void SetDestination(Vertex<V, E>* destination)					-Sets the Vertex Destination pointer
*	Vertex<V,E> * GetDestination()const								-Returns the Vertex Destination
*																		pointer
*	E GetData()const												-Returns the E data
*
* Data Members:
*	V m_data
*	list<Edge<V,E>> m_edges
*	bool m_processed
*
*************************************************************************/
#pragma once
#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <string>
#include <list>
using std::cout;
using std::endl;
using std::string;
using std::list;

template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge
{
public:
	Edge();
	Edge(E data, int weight);
	Edge(const Edge &copy);
	Edge & operator=(const Edge &rhs);
	
	void SetDestination(Vertex<V, E>* destination);
	Vertex<V,E> * GetDestination()const;
	E GetData()const;
	int GetWeight()const;
	~Edge();
private:
	Vertex<V, E> * m_destination;								//Holds the Vertex destination of the Vertex
	int m_weight;												//Holds the weight of the edge
	E m_data;													//Holds the E data
};

template<typename V, typename E>
inline Edge<V, E>::Edge()
	: m_destination(nullptr), m_weight(0)
{
	//cout << "In Edge c'tor" << endl;
}

template<typename V, typename E>
inline Edge<V, E>::Edge(E data, int weight)
	: m_destination(nullptr), m_weight(weight), m_data(data)
{
	//cout << "In Edge 3 arg c'tor" << endl;
}

template<typename V, typename E>
inline Edge<V, E>::Edge(const Edge & copy)
	: m_destination(copy.m_destination), m_weight(copy.m_weight), m_data(copy.m_data)
{
	//cout << "In Edge copy c'tor" << endl;
}

template<typename V, typename E>
inline Edge<V, E> & Edge<V, E>::operator=(const Edge & rhs)
{
	if (this != &rhs)
	{
		m_destination = rhs.m_destination;
		m_weight = rhs.m_weight;
		m_data = rhs.m_data;
	}
	return *this;
}

template<typename V, typename E>
inline void Edge<V, E>::SetDestination(Vertex<V, E>* destination)
{
	m_destination = destination;
}

template<typename V, typename E>
inline Vertex<V, E> * Edge<V, E>::GetDestination()const
{
	return m_destination;
}

template<typename V, typename E>
inline E Edge<V, E>::GetData() const
{
	return m_data;
}

template<typename V, typename E>
inline int Edge<V, E>::GetWeight() const
{
	return m_weight;
}

template<typename V, typename E>
inline Edge<V, E>::~Edge()
{
	//cout << "In Edge d'tor" << endl;
	m_destination = nullptr;
	m_weight = 0;
}
#endif
