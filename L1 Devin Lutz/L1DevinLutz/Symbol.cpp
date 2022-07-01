/*************************************************************
* Author: Devin Lutz
* Filename: Symbol.cpp
* Date Created: 4/14/18
* Modifications:
**************************************************************/
#include "Symbol.h"

Symbol::Symbol()
{
	//cout << "In Symbol c'tor" << endl;
}


Symbol::Symbol(string symbol, int color)
	: m_symbol(symbol), m_color(color)
{
	//cout << "In Symbol 2 arg c'tor" << endl;
}


Symbol::Symbol(const Symbol & copy)
	: m_symbol(copy.m_symbol), m_color(copy.m_color)
{
	//cout << "In Symbol copy c'tor" << endl;
}

Symbol & Symbol::operator=(const Symbol & rhs)
{
	if (this != &rhs)
	{
		m_symbol = rhs.m_symbol;
		m_color = rhs.m_color;
	}
	return *this;
}

void Symbol::SetSymbol(string symbol)
{
	m_symbol = symbol;
}


void Symbol::SetColor(int color)
{
	m_color = color;
}

string Symbol::GetSymbol() const
{
	return m_symbol;
}

int Symbol::GetColor() const
{
	return m_color;
}

Symbol::~Symbol()
{
	//cout << "In Symbol d'tor" << endl;
}
