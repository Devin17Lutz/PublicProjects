/*************************************************************
* Author: Devin Lutz
* Filename: Board.cpp
* Date Created: 4/12/18
* Modifications:
**************************************************************/
#include "Board.h"
#define WHITE 7							// used for the color white
#define GOLD 96							// used for the background color Gold
#define MAXROW 9						// Max # of rows
#define MAXCOLUMN 9						// Max # of columns

Board::Board()
	: emptyCount(0), m_score(0)
{
	//cout << "In Board c'tor" << endl;
	m_array.SetColumn(9);
	m_array.SetRow(9);
}

Board::Board(const Board & copy)
	: m_array(copy.m_array), emptyCount(copy.emptyCount), m_score(copy.m_score)
{
	//cout << "In Board copy c'tor" << endl;
}

Board & Board::operator=(const Board & rhs)
{
	//cout << "In Board op=" << endl;
	if (this != &rhs)
	{
		m_array = rhs.m_array;
		emptyCount = rhs.emptyCount;
		m_score = rhs.m_score;
	}
	return *this;
}

bool Board::Insert(Tile & tile, int row, int col)
{
	bool pass[4],											// array of bools for the test of upper lower left and right
		 last = true;										// last bool to see if the tile gets inserted
	int i = 0;												// i is the number of test 
	int new_row = row - 1;									// new_row will act for the test upper lower left and right
	int new_col = col;										// new_col will act for the test upper lower left and right
	int tempScore = m_score;								// temp will hold the old score. If last is false then score is restored to what it was

	if (tile.GetSymbol() == "W")
	{
		m_array[row][col] = tile;
	}
	else
	{
		while (i < 4)
		{
			try
			{
				pass[i] = Check(m_array[new_row][new_col], tile);
			}
			catch (Exception &c)
			{
				pass[i] = true;
				emptyCount++;										// used to see if any pieces around the tile position if its empty
			}
			i++;

			new_row = (i == 1) ? (row + 1) : row;

			if (i > 1)
			{
				new_col = (i == 2) ? (col - 1) : (col + 1);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (pass[i] == false)
			{
				last = false;
				m_score = tempScore;
			}
		}
		if (emptyCount == 4)										// if all 4 spaces around the tile position are empty cant place tile there
		{
			last = false;
		}
	}
	if (last == true)
	{			
		m_array[row][col] = tile;
	}
	emptyCount = 0;													// resets the empty count
	return last;
}

bool Board::InsertSpecial(Tile & tile, int row, int col)
{
	bool pass = false;												// used for the skull and crossbones test

	if (m_array[row][col].GetSymbol() != "")
	{
		m_array[row][col].SetSymbol("");
		pass = true;
	}
	return pass;
}

void Board::PrintBoard()
{
	HANDLE hStdout = 0;
	COORD cursor;

	cout << " 0  1  2  3  4  5  6  7  8" << endl;
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOLUMN; j++)
		{
			if (m_array[i][j].GetSymbol() == "")
			{
				hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

				if (m_array[i][j].GetBackGround() != GOLD)
				{
					SetConsoleTextAttribute(hStdout, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
				}
				else
				{
					SetConsoleTextAttribute(hStdout, m_array[i][j].GetBackGround() | FOREGROUND_INTENSITY & FOREGROUND_INTENSITY | GOLD);
				}
					cout << "[ ]";
				if (j == 8)
				{
					SetConsoleTextAttribute(hStdout, WHITE);
					cout << i;
				}
			}
			else
			{
				hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hStdout, m_array[i][j].GetColor() | FOREGROUND_INTENSITY & FOREGROUND_INTENSITY | GOLD);
				cout << "[" <<m_array[i][j].GetSymbol() << "]";
				if (j == 8)
				{
					SetConsoleTextAttribute(hStdout, WHITE);
					cout << i;
				}
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hStdout, WHITE);
}

bool Board::Check(Tile & placed, Tile & tile)
{
	bool pass = false;																// used for the one of the test of upper left right or lower
	if (placed.GetSymbol() == "")
	{
		pass = true;
		emptyCount++;
	}
	else if (placed.GetColor() == tile.GetColor())
	{
		pass = true;
		m_score += 5;																// add +5 if a tile is touching another
	}
	else if (placed.GetSymbol() == tile.GetSymbol() || placed.GetSymbol() == "W")
	{
		pass = true;																
		m_score += 5;																// add +5 if a tile is touching another
	}
	return pass;
}

void Board::CheckRowCol(int row, int col)
{
	bool test = true;																// uesed to test to see if any rows or columns are full

	for (int i = 0; i < MAXCOLUMN; i++) 
	{
		if (m_array[row][i].GetSymbol() == "")
		{
			test = false;
		}
	}
	if (test == true)
	{
		for (int i = 0; i < MAXCOLUMN; i++)
		{
			m_array[row][i].SetSymbol("");
		}
	}

	test = true;

	for (int i = 0; i < MAXROW; i++)
	{
		if (m_array[i][col].GetSymbol() == "")
		{
			test = false;
		}
	}
	if (test == true)
	{
		for (int i = 0; i < MAXROW; i++)
		{
			m_array[i][col].SetSymbol("");
		}
	}
}

bool Board::CheckSpace(int row, int col)
{
	bool pass = true;															// used to check to see if space is available
	
	if (m_array[row][col].GetSymbol() != "")
	{
		pass = false;
	}
	return pass;
}

bool Board::CheckWinner()
{
	bool end = true;															// used to check if the board is full of gold tiles

	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXCOLUMN; j++)
		{
			if (m_array[i][j].GetBackGround() != GOLD)
			{
				end = false;
			}
		}
	}
	return end;
}

int Board::GetScore() const
{
	return m_score;
}

Board::~Board()
{
	//cout << "In Board d'tor" << endl;
	emptyCount = 0;
	m_score = 0;
}
