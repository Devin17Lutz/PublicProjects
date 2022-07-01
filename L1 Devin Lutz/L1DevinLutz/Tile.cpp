/*************************************************************
* Author: Devin Lutz
* Filename: Tile.cpp
* Date Created: 4/14/18
* Modifications:
**************************************************************/
#include "Tile.h"

Tile::Tile()
	: m_backgrndColor(0)
{
	m_symbol.SetSymbol("");
	m_symbol.SetColor(0);
}

Tile::Tile(string symbol, int color, int backgrndColor)
	: m_backgrndColor(backgrndColor)
{
	//cout << "In Tile 3 arg c'tor" << endl;
	m_symbol.SetSymbol(symbol);
	m_symbol.SetColor(color);
}

Tile::Tile(const Tile & copy)
	: m_symbol(copy.m_symbol), m_backgrndColor(copy.m_backgrndColor)
{
	//cout << "In Tile copy c'tor" << endl;
}

Tile & Tile::operator=(const Tile & rhs)
{
	if (this != &rhs)
	{
		m_symbol = rhs.m_symbol;
		m_backgrndColor = rhs.m_backgrndColor;
	}
	return *this;
}

void Tile::SetSymbol(string symbol)
{
	m_symbol.SetSymbol(symbol);

}


void Tile::SetColor(int color)
{
	m_symbol.SetColor(color);
}

void Tile::SetBackGround(int backgrndColor)
{
	m_backgrndColor = backgrndColor;
}

string Tile::GetSymbol() const
{
	return m_symbol.GetSymbol();
}

int Tile::GetColor() const
{
	return m_symbol.GetColor();
}

int Tile::GetBackGround() const
{
	return m_backgrndColor;
}

Tile::~Tile()
{
	//cout << "In Tile d'tor" << endl;
	m_backgrndColor = 0;
}
