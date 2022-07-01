/************************************************************************
* Class: Vertex
*
* Purpose: This class serves as a vertex in the Vertex. It will have a list
*	of edges, the vertex data, and if the vertex has been processed.
*
* Manager functions:
*	Vertex()
*	Vertex(const Vertex &copy)
*	Vertex & operator=(const Vertex &rhs)
*	bool operator!=(const Vertex &rhs)
*	bool operator==(const Vertex &rhs)
*	~Vertex()
*
* Methods:
*	void InsertEdge(const Edge<V,E> &edge)							-Inserts the edge into the edge list
*	void DeleteEdge(E data)											-Deletes the edge from teh edge list
*	void DeleteVertexEdges(V data)									-Deletes the edges from a vertex
*	void InsertToStack(LListStack<Vertex<V,E>> &stack)				-Inserts the vertex's into the stack
*	void InsertToQueue(LListQueue<Vertex<V,E>> &queue)				-Inserts the vertex's into the queue
*	void ResetProcessed(V data)										-Resets all the m_processes in every vertex
*	void SetProcessed(V data)										-Sets the vertex as processed by using the pointer
*	V GetData()const												-Returns the V data.
*	bool GetProcessed()const										-Returns boolean value m_processed
*	void SetProcessed(bool processed)								-Sets the boolean value m_processed
*
* Data Members:
*	V m_data
*	list<Edge<V,E>> m_edges
*	bool m_processed
*
*************************************************************************/
#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <string>
#include <list>
#include "Edge.h"
#include "LListStack.h"
#include "LListQueue.h"
#include "Array.h"
using std::cout;
using std::endl;
using std::string;
using std::list;

template <typename V, typename E>
class Vertex
{
	//typedef typename list<Edge<V, E>>::iterator;
public:
	Vertex();
	Vertex(V data);
	Vertex(const Vertex &copy);
	Vertex & operator=(const Vertex &rhs);
	bool operator!=(const Vertex &rhs);
	bool operator==(const Vertex &rhs);

	void InsertEdge(const Edge<V,E> &edge);
	void DeleteEdge(E data);
	void DeleteVertexEdges(V data);
	void InsertToStack(LListStack<Vertex<V,E>> &stack);
	void InsertToQueue(LListQueue<Vertex<V,E>> &queue);
	void ResetProcessed();
	void SetProcessed(V data);
	V GetData()const;
	Edge<V,E> GetEdge(V data);
	bool GetProcessed()const;
	int GetWeight(list<Vertex<V, E>> &m_vertices, Array<int> &distance, Array<int> &predecessor, int count);
	~Vertex();
private:
	void SetProcessed(bool processed);

	V m_data;													//Holds the vertex data
	list<Edge<V,E>> m_edges;									//Holds the lsit of edges with the pointer value
	bool m_processed;											//Holds the value if the vertex has been processed
};

template<typename V, typename E>
inline Vertex<V, E>::Vertex()
	: m_processed(false)
{
	//cout << "In Vertex d'tor" << endl;
}

template<typename V, typename E>
inline Vertex<V, E>::Vertex(V data)
	: m_data(data), m_processed(false)
{
	//cout << "In Vertex 1 arg c'tor" << endl;
}

template<typename V, typename E>
inline Vertex<V, E>::Vertex(const Vertex & copy)
	: m_data(copy.m_data), m_edges(copy.m_edges), m_processed(copy.m_processed)
{
	//cout << "In Vertex in copy c'tor" << endl;
}

template<typename V, typename E>
inline Vertex<V, E> & Vertex<V, E>::operator=(const Vertex & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_edges = rhs.m_edges;
		m_processed = rhs.m_processed;
	}
	return *this;
}

template<typename V, typename E>
inline bool Vertex<V, E>::operator!=(const Vertex<V,E> & rhs)
{
	return m_data != rhs.m_data ? true : false;
}

template<typename V, typename E>
inline bool Vertex<V, E>::operator==(const Vertex & rhs)
{
	return m_data == rhs.m_data ? true : false;
}

template<typename V, typename E>
inline void Vertex<V, E>::InsertEdge(const Edge<V,E> &edge)
{
	m_edges.push_back(edge);
}

template<typename V, typename E>
inline void Vertex<V, E>::DeleteEdge(E data)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges
	bool found = false;													//Holds if the edge data has been found

	for (i = m_edges.begin(); i != m_edges.end() && !found; i++)
	{
		if ((*i).GetData() == data)
		{
			found = true;
		}
	}

	if (m_edges.size() == 1)
	{
		m_edges.clear();
	}
	else
	{
		m_edges.erase(--i);
	}
}

template<typename V, typename E>
inline void Vertex<V, E>::DeleteVertexEdges(V data)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges
	bool found = false;													//Holds if the vertex data has been found

	for (i = m_edges.begin(); i != m_edges.end() && !found; i++)
	{
		if ((*i).GetDestination()->GetData() == data)
		{
			found = true;
		}
	}

	if (found == true)
	{
		i--;
		m_edges.erase(i);
	}
}

template<typename V, typename E>
inline void Vertex<V, E>::InsertToStack(LListStack<Vertex<V, E>> &stack)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges

	for (i = m_edges.begin(); i != m_edges.end(); i++)
	{
		if ((*i).GetDestination()->GetProcessed() != true)
		{
			stack.Push(*(*i).GetDestination());
		}
	}
	m_processed = true;
}

template<typename V, typename E>
inline void Vertex<V, E>::InsertToQueue(LListQueue<Vertex<V, E>> &queue)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges

	for (i = m_edges.begin(); i != m_edges.end(); i++)
	{
		if ((*i).GetDestination()->GetProcessed() != true)
		{
			queue.Enqueue(*(*i).GetDestination());
		}
	}
	m_processed = true;
}

template<typename V, typename E>
inline void Vertex<V, E>::ResetProcessed()
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges

	for (i = m_edges.begin(); i != m_edges.end(); i++)
	{
		(*i).GetDestination()->SetProcessed(false);
	}
	m_processed = false;
}

template<typename V, typename E>
inline void Vertex<V, E>::SetProcessed(V data)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges

	for (i = m_edges.begin(); i != m_edges.end(); i++)
	{
		if ((*i).GetDestination()->GetData() == data)
		{
			(*i).GetDestination()->SetProcessed(true);
		}
	}
}

template<typename V, typename E>
inline V Vertex<V, E>::GetData() const
{
	return m_data;
}

template<typename V, typename E>
inline Edge<V,E> Vertex<V, E>::GetEdge(V data)
{
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges
	bool found = false;

	for (i = m_edges.begin(); i != m_edges.end() && !found; i++)
	{
		if ((*i).GetDestination()->GetData() == data)
		{
			found = true;
		}
	}
	--i;
	return (*i);
}

template<typename V, typename E>
inline bool Vertex<V, E>::GetProcessed() const
{
	return m_processed;
}

template<typename V, typename E>
inline int Vertex<V, E>::GetWeight(list<Vertex<V, E>> &m_vertices, Array<int> &distance, Array<int> &predecessor, int count)
{
	int smallest = -1;
	list<Edge<V, E>>::template iterator i;										//Used to iterate through the list of edges
	list<Vertex<V, E>>::template iterator j, k;
	int verCount = 0,
		l,
		iCount = count;
	bool found = false;

	for (i = m_edges.begin(); i != m_edges.end(); i++)
	{
		if (!(*i).GetDestination()->GetProcessed())
		{
			for (j = m_vertices.begin(); j != m_vertices.end() && !found; j++)
			{
				if ((*j).GetData() == (*i).GetDestination()->GetData())
				{
					found = true;
				}
				else
				{
					verCount++;
				}
			}
			if (distance[verCount] == -1 || (*i).GetWeight() + distance[count] < distance[verCount])
			{
				//cout << "total weight: " << (*i).GetWeight() + distance[count] << endl;
				distance[verCount] = (*i).GetWeight() + distance[count];
				predecessor[verCount] = count;
			}
			found = false;
			verCount = 0;
		}
	}
	k = m_vertices.begin();

	while (iCount != 0)
	{
		iCount--;
		k++;
	}
	for (j = m_vertices.begin(); j != m_vertices.end(); j++)
	{
		(*j).SetProcessed((*k).GetData());
	}

	j = m_vertices.begin();

	for (int i = 0; i < distance.GetLength(); i++)
	{
		if (distance[i] != -1 && !(*j).GetProcessed())
		{
			if (smallest > distance[i] || smallest == -1)
			{
				smallest = distance[i];
			}
		}
		j++;
	}

	j = m_vertices.begin();
	for (l = 0; l < distance.GetLength() && !found; l++)
	{
		if (smallest == distance[l] && !(*j).GetProcessed())
		{
			found = true;
		}
		j++;
	}
	return --l;
}

template<typename V, typename E>
inline Vertex<V, E>::~Vertex()
{
	//cout << "In Vertex d'tor" << endl;
	m_processed = false;
}
template<typename V, typename E>
inline void Vertex<V, E>::SetProcessed(bool processed)
{
	m_processed = processed;
}
#endif