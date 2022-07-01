/************************************************************************
* Class: Alchemy
*
* Purpose: This class serves as the Alchemy game. you'll start and finish
*	here. It will hold your score and discard pile and create the board.
*
* Manager functions:
*	Alchemy()
*	Alchemy(const Alchemy &copy)
*	Alchemy & operator=(const Alchemy &rhs)
*	~Alchemy()
*
* Methods:
*	Tile GenerateTile()				-Creates a Tile and returns the Tile
*	void Menu()						-Main menu for the game
*	void Play()						-if option one in menu is chosen then you
*										play the game
*	void PrintRules()				-prints the rules of the game
*	string GenerateSymbol(int numb) -generates teh symbol using the int numb
*
* Data Members:
*	Board *m_board
*	int m_level
*	int m_score
*	int m_discard
*
*************************************************************************/
#pragma once
#include "Board.h"
#ifndef ALCHEMY_H
#define ALCHEMY_H

class Alchemy
{
public:
	Alchemy();
	Alchemy(const Alchemy &copy);
	Alchemy & operator=(const Alchemy &rhs);
	void Menu();
	~Alchemy();
private:
	Tile GenerateTile();
	void Play();
	void PrintRules();
	string GenerateSymbol(int numb);

	Board *m_board;								// Used for creating the board
	int m_level;								// holds the level your on
	int m_score;								// holds the score during your game
	int m_discard;								// holds the displace pile
};
#endif
