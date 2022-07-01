/************************************************************************
* Class: Tile
*
* Purpose: This class serves as each tile that will be placed on the
*	board. It will have a symbol, color and background color.
*
* Manager functions:
*	Tile()
*	Tile(string symbol, int color, int backgrndColor)
*	Tile(const Tile &copy)
*	Tile & operator=(const Tile &rhs)
*	~Tile()
*
* Methods:
*	void SetSymbol(string symbol)						-Sets the symbol
*	void SetColor(int color)							-Sets the color
*	void SetBackGround(int backgrndColor)				-Sets the background color
*
*	string GetSymbol()const								-Returns symbol
*	int GetColor()const									-Returns color
*	int GetBackGround()const							-Returns background color
*
* Data Members:
*	Symbol m_symbol
*	int m_backgrndColor
*
*************************************************************************/
#pragma once
#include <iostream>
#include <string>
#include "Symbol.h"
using std::cout;
using std::string;

#ifndef TILE_H
#define TILE_H

class Tile
{
public:
	Tile();
	Tile(string symbol, int color, int backgrndColor);
	Tile(const Tile &copy);
	Tile & operator=(const Tile &rhs);

	//Setters
	void SetSymbol(string symbol);
	void SetColor(int color);
	void SetBackGround(int backgrndColor);

	//Getters
	string GetSymbol()const;
	int GetColor()const;
	int GetBackGround()const;

	~Tile();
private:
	Symbol m_symbol;								// holds the symbol for the type of symbol and color
	int m_backgrndColor;							// holds the integer value for background color
};
#endif
