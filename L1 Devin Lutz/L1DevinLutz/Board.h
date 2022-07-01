/************************************************************************
* Class: Board
*
* Purpose: This class serves as the board for Alchemy. This where the
*	the inserting the tiles printing the board and checking happens.
*
* Manager functions:
*	Board()
*	Board(const Board &copy)
*	Board & operator=(const Board &rhs)
*	~Board()
*
* Methods:
*	bool Insert(Tile &tile, int row, int col)				-Insert the tile at position row col
*	bool InsertSpecial(Tile &tile, int row, int col)		-Inserts The skull and crossbones
*	void PrintBoard()										-Prints the board
*	bool Check(Tile & placed, Tile &tile)					-checks to see if the tile can be placed
*																there
*	void CheckRowCol(int row, int col)						-Checks int row to see if it has all gold
*																tiles same with columns
*	bool CheckSpace(int row, int col)						-Checks to see if the tile space is empty
*	bool CheckWinner()										-Checks all rows and columns to see if you
*																have all the tiles filled
*	int GetScore() const									-Returns the score
*
* Data Members:
*	Array2D<Tile> m_array
*	int emptyCount
*	int m_score
*
*************************************************************************/
#pragma once
#include <windows.h>
#include "Array2D.h"

#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
	Board();
	Board(const Board &copy);
	Board & operator=(const Board &rhs);
	bool Insert(Tile &tile, int row, int col);
	bool InsertSpecial(Tile &tile, int row, int col);
	void PrintBoard();
	bool Check(Tile & placed, Tile &tile);
	void CheckRowCol(int row, int col);
	bool CheckSpace(int row, int col);
	bool CheckWinner();

	//Getter
	int GetScore() const;

	~Board();
private:
	Array2D<Tile> m_array;										// Array2D that will hold the tiles
	int emptyCount;												// holds empty count if 4 cant place tile there
	int m_score;												// holds the score
};
#endif BOARD_H