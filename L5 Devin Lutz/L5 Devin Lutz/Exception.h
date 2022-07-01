/************************************************************************
* Class: Exception
*
* Purpose: This class will handle any exception that has occured.
*
* Manager functions:
*	Exception();
*	Exception(char *msg);
*	Exception(const Exception & copy);
*	Exception & operator=(const Exception & rhs);
*	~Exception();
*
* Methods:
*	friend ostream & operator<<(ostream & stream, const Exception & except);
*	void setMessage(char *msg);
*	char *getMessage();
*
* Data Members:
*	char *m_msg;
*
*************************************************************************/
#pragma once
#include <iostream>
#include <fstream>
using std::ostream;

#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{
public:
	Exception();
	Exception(const char *msg);
	Exception(const Exception & copy);
	Exception & operator=(const Exception & rhs);
	friend ostream & operator<<(ostream & stream, const Exception & except);

	//Setter
	void setMessage(char *msg);

	//Getter
	const char *getMessage() const;

	~Exception();
private:
	char *m_msg;					//will hold the message if an exception has occured.
};
#endif