/************************************************************************
* Class: CommandHandler
*
* Purpose: This class as the command handler for dijkstra's algorithm
*
* Manager functions:
*	CommandHandler()
*	CommandHandler(const Graph &copy)
*	CommandHandler & operator=(const Graph &rhs)
*	~CommandHandler()
*
* Methods:
*	void ReadCommands()								-Reads the file and insert vertexs to see the shortest
*														path between the two
*
* Data Members:
*	Graph<string, string> m_graph					-Used as a graph
*
*************************************************************************/
#pragma once
#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "Graph.h"

class CommandHandler
{
public:
	CommandHandler();
	CommandHandler(const CommandHandler &copy);
	CommandHandler & operator=(const CommandHandler &rhs);
	void ReadCommands();
	~CommandHandler();
private:
	Graph<string, string> m_graph;
};
#endif
