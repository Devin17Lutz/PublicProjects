/************************************************************************
* Class: Symbol
*
* Purpose: This class serves as the symbol for every tile. It will have
*	a color and type of symbol
*
* Manager functions:
*	Symbol()
*	Symbol(string symbol, int color)
*	Symbol(const Symbol & copy)
*	Symbol & operator=(const Symbol &rhs)
*	~Symbol()
*
* Methods:
*	void SetSymbol(string symbol)				-Sets the symbol
*	void SetColor(int color)					-Sets the color
*   string GetSymbol()const						-Returns the symbol
*	int GetColor()const							-Returns the color
*
* Data Members:
*	string m_symbol
*	int m_color
*
*************************************************************************/
#pragma once
#include <iostream>
#include <string>

using namespace std;

#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol
{
public:
	Symbol();
	Symbol(string symbol, int color);
	Symbol(const Symbol & copy);
	Symbol & operator=(const Symbol &rhs);

	//Setters
	void SetSymbol(string symbol);
	void SetColor(int color);
	//Getters
    string GetSymbol()const;
	int GetColor()const;

	~Symbol();
private:
	string m_symbol;								// holds the type of symbol
	int m_color;									// holds the integer value for the color
};
#endif

