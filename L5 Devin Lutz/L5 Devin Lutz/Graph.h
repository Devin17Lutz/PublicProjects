/************************************************************************
* Class: Graph
*
* Purpose: This class serves as the graph data structure that will hold
*	a list of vertices and the count.
*
* Manager functions:
*	Graph()
*	Graph(const Graph &copy)
*	Graph & operator=(const Graph &rhs)
*	~Graph()
*
* Methods:
*	void InsertVertex(V data)									-Insert the vertex into the graphs vertice list
*	void DeleteVertex(V data)									-Deletes the vertex from the graphs vertice list
*	void InsertArc(V from, V to, E edge, int weight)			-Inserts an edge between two vertex's
*	void DeleteArc(V from, V to, E edge)						-Deletes an edge between two vertex's
*	void DepthFirst(void(*visit)(V data))						-Does a depth first traversal
*	void BreadthFirst(void(*visit)(V data))						-Does a Breadth first traversal
*	bool isEmpty()												-checks to see if there are any vertice's in the list
*	void InsertEdge(int &pos, Edge<V, E> &newEdge)				-Gets called from InsertArc to insert the edge into the
*																	vertex list
*	void DeleteEdge(int &pos, E &edge)							-Gets called from DeleteArc to delete the edge from the
*																	vertex list
*	void Dijkstra(V start, V end)								-Performs the dijkstras algorithm
*	void Check(V data)											-checks to see if the data is in the vertex list
*	bool GetGraphProcess()										-Checks to see if the graph has been completely processed
*	void DisplayPath(Array<int> &predecessor, Array<int> &distance, V start, V end)		-Displays the path taken and how long it will take
*
* Data Members:
*	list<Vertex<V,E>> m_vertices
*	int m_count
*
*************************************************************************/
#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <iomanip>
#include <math.h> 
#include <list>
#include <iterator>
#include "Vertex.h"
#include "LListStack.h"
#include "LListQueue.h"
#include "Array.h"
using std::cout;
using std::endl;
using std::string;
using std::list;
using std::setprecision;
using std::fixed;
using std::noshowpoint;

template <typename V, typename E>
class Graph
{
public:
	Graph();
	Graph(const Graph &copy);
	Graph & operator=(const Graph &rhs);

	void InsertVertex(V data);
	void DeleteVertex(V data);
	void InsertArc(V from, V to, E edge, int weight);
	void DeleteArc(V from, V to, E edge);
	void DepthFirst(void(*visit)(V data));
	void BreadthFirst(void(*visit)(V data));
	void DisplayVertex();
	bool isEmpty();
	void Dijkstra(V start, V end);
	void Check(V data);

	~Graph();
private:
	void InsertEdge(int &pos, Edge<V, E> &newEdge);
	void DeleteEdge(int &pos, E &edge);
	bool GetGraphProcess();
	void DisplayPath(Array<int> &predecessor, Array<int> &distance, V start, V end);

	list<Vertex<V,E>> m_vertices;								//Holds a list of vertex's
	int m_count;												//Holds the number of vertex's in the graph
};

template<typename V, typename E>
inline Graph<V, E>::Graph()
	: m_count(0)
{
	//cout << "In Graph c'tor" << endl;
}

template<typename V, typename E>
inline Graph<V, E>::Graph(const Graph & copy)
	: m_vertices(copy.m_vertices), m_count(copy.m_count)
{
	//cout << "In Graph Copy c'tor" << endl;
}

template<typename V, typename E>
inline Graph<V, E> & Graph<V, E>::operator=(const Graph & rhs)
{
	if (this != &rhs)
	{
		m_vertices = rhs.m_vertices;
		m_count = rhs.m_count;
	}
	return *this;
}

template<typename V, typename E>
inline void Graph<V, E>::InsertVertex(V data)
{
	Vertex<V,E> newVertex(data);								//Creates a new Vertex
	list<Vertex<V, E>>::template iterator i;

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if ((*i).GetData() == data)
		{
			throw Exception("Can't input a vertex thats already in the graph");
		}
	}

	m_vertices.push_back(newVertex);
	m_count++;
}

template<typename V, typename E>
inline void Graph<V, E>::DeleteVertex(V data)
{
	list<Vertex<V, E>>::template iterator i;								//Used to iterate through the list
	int location = -1,											//Used to know the location of the vertex
		count = 0;												//Holds the count for the location of the vertex

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if ((*i).GetData() == data)
		{
			location = count;
		}
		else
		{
			(*i).DeleteVertexEdges(data);
		}
		count++;
	}

	if (location == -1)
	{
		throw Exception("Vertex doesnt exist");
	}

	i = m_vertices.begin();

	while (location != 0)
	{
		location--;
		i++;
	}
	m_vertices.erase(i);
	m_count--;
}

template<typename V, typename E>
inline void Graph<V, E>::InsertArc(V from, V to, E edge, int weight)
{
	list<Vertex<V, E>>::template iterator i, j;							//Used to traverse the list of the vertex's
	Edge<V, E> newEdge(edge, weight),							//Holds the edge from vertex from to vertex to
			   newEdge2(edge, weight);							//Holds the edge from vertex to to vertex from
	bool foundFrom = false,										//Holds the bool value if vertex from is found
		 foundTo = false;										//Holds the bool value if vertex to is found
	int count = 0,												//Holds the count for the posFrom and posTo
		posFrom = 0,											//Holds the index position for newEdge
		posTo = 0;												//Holds the index position fro newEdge2

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if ((*i).GetData() == from)
		{
			foundFrom = true;
			posFrom = count;
			newEdge2.SetDestination(&(*i));
		}
		if ((*i).GetData() == to)
		{
			foundTo = true;
			posTo = count;
			newEdge.SetDestination(&(*i));
		}
		count++;
	}
	if (foundFrom != true || foundTo != true)
	{
		throw Exception("One vertex is not in the graph");
	}

	InsertEdge(posFrom, newEdge);
	InsertEdge(posTo, newEdge2);
}

template<typename V, typename E>
inline void Graph<V, E>::DeleteArc(V from, V to, E edge)
{
	list<Vertex<V, E>>::template iterator i, j;							//Used to traverse the list of the vertex's
	bool foundFrom = false,										//Holds the bool value if vertex from is found
		foundTo = false;										//Holds the bool value if vertex to is found
	int count = 0,												//Holds the count for the posFrom and posTo
		posFrom = 0,											//Holds the index position for newEdge
		posTo = 0;												//Holds the index position fro newEdge2

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if ((*i).GetData() == from)
		{
			foundFrom = true;
			posFrom = count;
		}
		if ((*i).GetData() == to)
		{
			foundTo = true;
			posTo = count;
		}
		count++;
	}
	if (foundFrom != true || foundTo != true)
	{
		throw Exception("One vertex is not in the graph");
	}

	DeleteEdge(posFrom, edge);
	DeleteEdge(posTo, edge);
}

template<typename V, typename E>
inline void Graph<V, E>::DepthFirst(void(*visit)(V data))
{
	list<Vertex<V, E>>::template iterator i = m_vertices.begin();							//Used to traverse the list of the vertex's
	LListStack<Vertex<V, E>> stack;													//The stack that will holds the all the vertex's
	Vertex<V, E> temp;																//Holds the the popped value from the stack
	stack.Push((*i));

	while (!stack.isEmpty())
	{
		temp = stack.Pop();
		if (!stack.isEmpty())
		{
			if (temp == stack.Peek())
			{
				stack.Pop();
			}
		}
		for (i = m_vertices.begin(); i != m_vertices.end(); i++)
		{
			(*i).SetProcessed(temp.GetData());
		}

		temp.InsertToStack(stack);

		visit(temp.GetData());
	}
	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		(*i).ResetProcessed();
	}
}

template<typename V, typename E>
inline void Graph<V, E>::BreadthFirst(void(*visit)(V data))
{
	list<Vertex<V, E>>::template iterator i = m_vertices.begin();							//Used to traverse the list of the vertex's						
	LListQueue<Vertex<V, E>> queue;													//Queue that will hold the vertex's
	Vertex<V, E> temp;																//Holds the vertex that the queue dequeues
	queue.Enqueue((*i));

	while (!queue.isEmpty())
	{
		temp = queue.Dequeue();
		if (!queue.isEmpty())
		{
			if (queue.Front() == temp)
			{
				queue.Dequeue();
			}
		}
		for (i = m_vertices.begin(); i != m_vertices.end(); i++)
		{
			(*i).SetProcessed(temp.GetData());
		}

		temp.InsertToQueue(queue);

		visit(temp.GetData());
	}
	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		(*i).ResetProcessed();
	}
}

template<typename V, typename E>
inline void Graph<V, E>::DisplayVertex()
{
	list<Vertex<V, E>>::template iterator i;													//Used to traverse the list of the vertex's

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		cout << (*i).GetData() << endl;
	}
}

template<typename V, typename E>
inline bool Graph<V, E>::isEmpty()
{
	return m_count == 0 ? true : false;
}

template<typename V, typename E>
inline void Graph<V, E>::Dijkstra(V start, V end)
{
	list<Vertex<V, E>>::template iterator i = m_vertices.begin(),							//Used to traverse the list of the vertex's
								 j;													//Used to traverse the list of the vertex's
	Array<int> distance(m_count);													//Used as the distance between the starting point and other vertexes
	Array<int> predecessor(m_count);												//Used to display the path
	bool found = false;																//Used to find the location of the vertex
	int count = 0,																	//Used as a count to get the iterator value to the correct vertex
		smallIndex = 0;																//Used to find the next vertex with the smallest weight

	for (int i = 0; i < m_count; i++)
	{
		distance[i] = -1;
		predecessor[i] = -1;
	}

	for (i = m_vertices.begin(); i != m_vertices.end() && !found; i++)
	{
		if ((*i).GetData() == start)
		{
			found = true;
		}
		else
		{
			count++;
		}
	}
	distance[count] = 0;
	i--;

	while (!GetGraphProcess())
	{
		smallIndex = (*i).GetWeight(m_vertices, distance, predecessor, count);

		i = m_vertices.begin();
		count = 0;

		while (smallIndex != 0)
		{
			smallIndex--;
			i++;
			count++;
		}
	}

	DisplayPath(predecessor, distance, start, end);
}

template<typename V, typename E>
inline void Graph<V, E>::Check(V data)
{
	list<Vertex<V, E>>::template iterator i;
	bool found = false;

	for (i = m_vertices.begin(); i != m_vertices.end() && !found; i++)
	{
		if ((*i).GetData() == data)
		{
			found = true;
		}
	}

	if (!found)
	{
		throw Exception("\nVertex is not in the graph");
	}
}

template<typename V, typename E>
inline Graph<V, E>::~Graph()
{
	//cout << "In Graph d'tor" << endl;
	m_count = 0;
}
template<typename V, typename E>
inline void Graph<V, E>::InsertEdge(int & pos, Edge<V, E>& newEdge)
{
	list<Vertex<V, E>>::template iterator i, j;							//Used to traverse the list of the vertex's

	if (pos == 0)
	{
		i = m_vertices.begin();
		(*i).InsertEdge(newEdge);
	}
	else
	{
		j = m_vertices.begin();

		while (pos != 0)
		{
			j++;
			pos--;
		}
		(*j).InsertEdge(newEdge);

	}
}
template<typename V, typename E>
inline void Graph<V, E>::DeleteEdge(int &pos, E &edge)
{
	list<Vertex<V, E>>::template iterator i, j;							//Used to traverse the list of the vertex's

	if (pos == 0)
	{
		i = m_vertices.begin();
		(*i).DeleteEdge(edge);
	}
	else
	{
		j = m_vertices.begin();

		while (pos != 0)
		{
			j++;
			pos--;
		}
		(*j).DeleteEdge(edge);

	}
}
template<typename V, typename E>
inline bool Graph<V, E>::GetGraphProcess()
{
	list<Vertex<V, E>>::template iterator i;							//Used to traverse the list of the vertex's
	int count = 0;											//Used to see if all but one are processed

	for (i = m_vertices.begin(); i != m_vertices.end() && count < 2; i++)
	{
		if ((*i).GetProcessed() == false)
		{
			count++;
		}
	}
	return count > 1 ? false : true;
}
template<typename V, typename E>
inline void Graph<V, E>::DisplayPath(Array<int> &predecessor, Array<int>& distanceArray, V start, V end)
{
	list<Vertex<V, E>>::template iterator i, j;							//Used to traverse the list of the vertex's
	LListStack<int> stack;										//stack is used to help display the path in correct order
	Edge<V, E> edge;											//Returns an edge to find the speed of that edge
	bool found = false;											//Used for finding the right vertex
	int count = 0,												//Used as to move the iterator value to the correct vertex
		count2 = 0,												//Used as to move the iterator value to the correct vertex
		miles = 0;												//Used to hold how many miles are from vertex a to b
	float time = 0,												//Used to hold the time it takes to get to a vertex
		  speed = 0,											//Used to hold the speed on a particular edge. if on I-5 its 65 else its 55
		  distance = 0,											//Holds the weight of the edge
		  fraction = 0;											//Holds the fraction of the time or the minutes

	for (i = m_vertices.begin(); i != m_vertices.end() && !found; i++)
	{
		if ((*i).GetData() == end)
		{
			found = true;
		}
		else
		{
			count++;
		}
	}
	stack.Push(count);
	miles = distanceArray[count];

	while (predecessor[count] != -1)
	{
		stack.Push(predecessor[count]);
		count = predecessor[count];
	}

	while (!stack.isEmpty())
	{
		count = stack.Pop();
		if (!stack.isEmpty())
		{
			count2 = stack.Peek();
		}
		i = m_vertices.begin();
		j = m_vertices.begin();

		while (count != 0)
		{
			i++;
			count--;
		}

		while (count2 != 0)
		{
			j++;
			count2--;
		}

		if (!stack.isEmpty())
		{
			edge = (*i).GetEdge((*j).GetData());
			speed = edge.GetData() == "I-5" ? 65 : 55;
			distance = edge.GetWeight();

			time += (distance / speed);
		}
		if ((*i).GetData() != end)
		{
			cout << (*i).GetData() << " -> ";
		}
		else
		{
			cout << (*i).GetData() << endl;
		}
	}
	fraction = modf(time, &time);
	fraction *= 60;
	modf(fraction, &fraction);

	cout << "\nThe route is " << miles << " miles long and the estimated time of arrival is: " << setprecision(3) << noshowpoint << time << " hours and " 
		 << setprecision(1) << fixed << noshowpoint << fraction << " minutes." << endl;

	for (i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		(*i).ResetProcessed();

	}
}
#endif