/*************************************************************
* Author: Devin Lutz
* Filename: CommandHandler.cpp
* Date Created: 6/1/18
* Modifications:
**************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "CommandHandler.h"
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

CommandHandler::CommandHandler()
{
	//cout << "In CommandHandler ctor" << endl;
}

CommandHandler::CommandHandler(const CommandHandler & copy)
	: m_graph(copy.m_graph)
{
	//cout << "In CommandHandler copy c'tor" << endl;
}

CommandHandler & CommandHandler::operator=(const CommandHandler & rhs)
{
	if (this != &rhs)
	{
		m_graph = rhs.m_graph;
	}
	return *this;
}

void CommandHandler::ReadCommands()
{
	string vertex1,														//Holds the starting vertex for an edge
		   vertex2,														//Holds the end vertex for an edge
		   edgeData,													//Holds the edge data
		   weightString,												//Holds the weight as a string	
		   start,														//Holds the start vertex
		   end;															//Holds the end vertex
	char again = 'y',													//Holds the value if you want to see another route
		 display = '\0';												//Holds if you want to display the vertex's
	int weight = 0;														//Holds the weight as an integer value
	ifstream fin;														//Used to open the file
	bool found = true;                                                  //If true do dijkstra algorithm if false do not

	fin.open("Lab05.txt");
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			getline(fin, vertex1, ',');
			getline(fin, vertex2, ',');
			getline(fin, edgeData, ',');
			getline(fin, weightString, '\n');
			size_t size = weightString.size();
			weight = atoi(weightString.c_str());
			try
			{
				m_graph.InsertVertex(vertex1);
			}
			catch (Exception &c) {}

			try
			{
				m_graph.InsertVertex(vertex2);
			}
			catch (Exception &c) {}

			m_graph.InsertArc(vertex1, vertex2, edgeData, weight);
		}

		while (again == 'y')
		{
			cout << "Do you want to Display the vertices (y/n): ";
			cin >> display;
			if (display == 'y' || display == 'Y')
			{
				m_graph.DisplayVertex();
			}
			
			cout << "\nNote: You MUST enter the vertex's exactly the way they're in the list. Capitalization is IMPORTANT, also no EXTRA spaces!!!!"
				 << "\n\nEnter Starting Point: ";
			cin.ignore();
			getline(cin, start);
			cout << "Enter Ending Point: ";
			getline(cin, end);

			try
			{
				m_graph.Check(start);
				m_graph.Check(end);
			}
			catch (Exception &c)
			{
				cout << c << endl;
				found = false;
			}
			if (found == true)
			{
				cout << "\nShortest path from " << start << " to " << end << " is" << endl;
				m_graph.Dijkstra(start, end);
			}
			cout << "\nDo you want to see another route (y/n): ";
			cin >> again;
		}
		fin.close();
	}
	else
	{
		cout << "File couldn't open" << endl;
	}
}

CommandHandler::~CommandHandler()
{
	//cout << "In CommandHandler dtor" << endl;
}
