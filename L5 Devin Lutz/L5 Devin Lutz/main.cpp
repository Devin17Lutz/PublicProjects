/*************************************************************
* Author:		Devin Luts
* Filename:		main.cpp
* Date Created:	5/28/18
* Modifications:
*
* Lab/Assignment: Lab 5
*
* Overview:
*	This program will read a file formatted as start vertex,
*	end vertex, E data, and the weight. If the vertex hasnt
*	been inserted insert it and create the edge. Next well input
*	if we want to see the list of vertices in the graph for the 
*	start and end input. Once the start and end input vertexs are
*	inputed it will display the shortest path, the miles traveled,
*	and how long it will take to reach that location.
*
* Input:
*	The input for this program is to see if you want to display the
*	vertices in the graph. Next you will input the start vertex and
*	the end vertex. The last thing you'll input if you want to insert
*	another route.
*
* Output:
*	The output of this program is the path that will be taken between
*	vertices, the miles that will be travelled and how long it will 
*	take to reach your destination
*
************************************************************/
#include <iostream>
#include <string>
#include <list>
#include "Graph.h"
#include "CommandHandler.h"
using std::cout;
using std::cin;
using std::string;


void Display(int data);
void Display(string data);

int main()
{
	CommandHandler command;
	command.ReadCommands();

	return 0;
}

/**********************************************************************
* Purpose: This function Displays the data within the graph
*		if the data is an int.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      no postconditions
*
************************************************************************/
void Display(int data)
{
	cout << data << " ";
}

/**********************************************************************
* Purpose: This function Displays the data within the graph
*		if the data is a string.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      no postconditions
*
************************************************************************/
void Display(string data)
{
	cout << data << " ";
}