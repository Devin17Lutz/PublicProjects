/*************************************************************
* Author: Devin Lutz
* Filename: Exception.cpp
* Date Created: 4/2/18
* Modifications:
**************************************************************/
#include <iostream>
#include "Exception.h"
using std::cout;
using std::endl;

Exception::Exception()
	: m_msg(nullptr)
{
	//cout << "In Exception c'tor" << endl;

	m_msg = new char[1];
	m_msg[0] = { '\0' };
}

Exception::Exception(const char * msg)
	: m_msg(nullptr)
{
	//cout << "In Exception 1 arg c'tor" << endl;

	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

Exception::Exception(const Exception & copy)
	: m_msg(nullptr)
{
	//cout << "In Exception copy c'tor" << endl;

	if (strlen(copy.m_msg) == 0)
	{
		m_msg = new char[1];
		m_msg[0] = { '\0' };
	}
	else
	{
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
}

Exception & Exception::operator=(const Exception & rhs)
{
	//cout << "In Exception op=" << endl;

	if (this != &rhs)
	{
		delete[] m_msg;

		if (strlen(rhs.m_msg) == 0)
		{
			m_msg = new char[1];
			m_msg[0] = { '\0' };
		}
		else
		{
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
	}
	return *this;
}

void Exception::setMessage(const char * msg)
{
	delete[] m_msg;
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

const char * Exception::getMessage() const
{
	return m_msg;
}

Exception::~Exception()
{
	//cout << "In Exception d'tor" << endl;
	delete[] m_msg;
	m_msg = nullptr;
}

ostream & operator<<(ostream & stream, const Exception & except)
{
	//cout << "In Exception <<" << endl;

	return 	stream << except.m_msg;
}