/*************************************************************
* Author: Devin Lutz
* Filename: Alchemy.cpp
* Date Created: 4/12/18
* Modifications:
**************************************************************/

/******************************************************************
NOTE:	The wild card and skull and bones tiles will only appear 
		if your discarded pile is greater than zero. I did that so
		it will show these tiles less than the symbols
*******************************************************************/
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "Alchemy.h"
using std::cout;
using std::cin;

#define LONECOLORS 5									// Level one color for color generator
#define LTWOCOLORS 6									// level two color for color generator
#define LONESYMBOLS 7									// level one symbols for symbols generator
#define LTWOSYMBOLS 8									// level two symbols for symbols generator
#define GOLD 96											// decimal number for gold
#define WHITE 7											// decimal number for white

Alchemy::Alchemy()
	: m_board(nullptr), m_level(1), m_score(0)
{
	//cout << "In Alchemy c'tor" << endl;
}

Alchemy::Alchemy(const Alchemy & copy)
	: m_board(copy.m_board), m_level(copy.m_level), m_score(copy.m_score)
{
	//cout << "In Alchemy copy c'tor" << endl;
}

Alchemy & Alchemy::operator=(const Alchemy & rhs)
{
	//cout << "In Alchemy op=" << endl;
	if (this != &rhs)
	{
		delete m_board;
		m_board = rhs.m_board;
		m_level = rhs.m_level;
		m_score = rhs.m_score;
	}
	return *this;
}

void Alchemy::Menu()
{
	int num = 0;											// chooses which path to take in the main menu											
	bool end = true;										// if end game is chosen then exit the game

	while (end)
	{
		cout << "\t\tAlchemy Game\n\n"
			 << "1.) Play Alchemy\n"
			 << "2.) Read Rules\n"
			 << "3.) End Game\n"
			 << "Please Enter a number: ";
		cin >> num;

		switch (num)
		{
			case 1:
				Play();
				break;
			case 2:
				PrintRules();
				break;
			case 3:
				end = false;
				cout << "Have a nice day" << endl;
				break;
			default:
				cout << "Error retry input must be between 1 and 3" << endl;
		}
	}
}

void Alchemy::Play()
{
	bool exit = false,										// exit is used to see if the tile was placed or discarded
		 tileSpace = true,									// tileSpace checks to see the space is taken or not
		 end = false;										// end is used to see if the game has been beaten
	string discardAns;										// if y dicsard the tile if no keep guesing row and column
	int row = 0, col = 0;									// row and col are uesed to test and insert the tile in the 2DArray
	HANDLE hStdout = 0;
	COORD cursor;
	
	cout << "place Wild Card (row and column): ";
	cin >> row >> col;

	m_board = new Board();									// creates the board
	Tile one("W", 0, GOLD);									// Wild Card that has Grey color and gold background

	m_board->Insert(one, row, col);
	m_board->PrintBoard();

	while (m_discard != 3 && end != true)
	{
		try
		{
			one = GenerateTile();

			cout << "Symbol is: ";
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdout, one.GetColor() | FOREGROUND_INTENSITY & FOREGROUND_INTENSITY);
			cout << one.GetSymbol() << endl;
			SetConsoleTextAttribute(hStdout, WHITE);

			while (exit != true)
			{
				try
				{
					cout << "\nYou have " << m_discard << " in your discard pile." << endl;
					cout << "Please enter Row and Column: ";
					cin >> row >> col;

					if ((row < 0 || row > 9) || (col < 0 || col > 9))							// if row or column is out of bounds throw exception
					{
						throw Exception("Out of bounds");
					}

					if (one.GetSymbol() != "X")
					{
						tileSpace = m_board->CheckSpace(row, col);								// Checks to see if the tile space is empty or not
					}

					if (tileSpace)
					{
						if (one.GetSymbol() == "X")
						{
							exit = m_board->InsertSpecial(one, row, col);						// inserts skull and crossbones tile
						}
						else
						{
							exit = m_board->Insert(one, row, col);								// inserts normal tile or wild card
						}

						if (exit != true)														// if insertion failed
						{
							cout << "Tile doesnt go there" << endl;
							cout << "Do you want to discard this Tile (y or n): ";
							cin >> discardAns;

							exit = (discardAns == "y") ? true : false;
							if (exit == true)
							{
								m_discard++;													// Increment m_dicard if user wants to discard the tile
							}
						}
						else
						{
							if (m_discard > 0)
							{
								m_discard--;
							}
							m_board->CheckRowCol(row, col);										// checks to see if any rows or columns are completely filled
						}
						m_board->PrintBoard();
					}
					else
					{
						cout << "Can't place a Tile where theres already a Tile." << endl;
						exit = false;
					}
				}
				catch (Exception &c)
				{
					cout << c << endl;
				}
			}
			exit = false;
		}
		catch (Exception &c)
		{
			cout << c << endl;
		}

		end = m_board->CheckWinner();																// checks to see if the board is full of gold tiles
		
		if (end == true)
		{
			m_score = m_board->GetScore();
			cout << "Score was " << m_score << endl << endl;
			if (m_level < 2)
			{
				m_level++;
				delete m_board;																		// delete or in other words reseting the board

				m_board = new Board();
				m_score = 0;																		// resets the score
				m_discard = 0;																		// resets discard pile
				cout << "\n\nplace Wild Card (row and column): ";
				cin >> row >> col;

				one.SetSymbol("W");
				one.SetColor(0);
				one.SetBackGround(GOLD);

				m_board->Insert(one, row, col);
				m_board->PrintBoard();
				end = false;
			}
		}
	}
}

void Alchemy::PrintRules()
{
	cout << "***For a better experience please use font 36 when you run the game right\n"
		 << " click on the windows display hit properties then font and select 36 and\n"
		 << "hit ok***\n" << endl;

	cout << "Object of the game is to fill the whole board with tiles of gold background\n"
		 << "To fill the board you will have tiles with a symbol and a color. For you to\n"
		 << "place a symbol it either needs to be the same color as the tile next to it\n"
		 << "or the same color. Or if there is a Wild card. You lose if you can't place a\n"
		 << "tile more than three times. Your discard pile will decrease by one if your \n"
		 << "able to place a tile down. There are two levels level two will add a color\n"
		 << "and a symbol" << endl;

	cout << "------------GOOD LUCK------------\n" << endl;
}

Tile Alchemy::GenerateTile()
{
	string symbol;																// string that will hold the symbol
	int color = 0,																// holds the number for the color
		num = 0,																// num holds the number for symbol generator
		min = 1;																// holds the min value for the generator

	int max = (m_level == 1) ? LONECOLORS : LTWOCOLORS;
	color = rand() % max + min;
	srand(time(NULL));

	if (color == 5)
	{
		if (max == LONECOLORS)
		{
			color++;
		}
		else
		{
			color += 2;
		}
	}

	max = (m_level == 1) ? LONESYMBOLS : LTWOSYMBOLS;
	num = rand() % max + min;

	if (num == 6 && m_discard == 0)
	{
		num -= 2;
	}
	else if (num == 7 && m_discard == 0)
	{
		num -= 6;
	}

	srand(time(NULL));
	symbol = GenerateSymbol(num);
	
	if (symbol == "X" || symbol == "W")
	{
		color = 0;
	}
	return Tile(symbol, color, GOLD);											// returns the Tile
}

string Alchemy::GenerateSymbol(int numb)
{
	string symbol;																// holds the symbol
	switch (numb)
	{
		case 1:
			symbol = "#";
			break;
		case 2:
			symbol = "?";
			break;
		case 3:
			symbol = "$";
			break;
		case 4:
			symbol = "&";
			break;
		case 5:
			symbol = "!";
			break;
		case 6:
			symbol = "X";
			break;
		case 7:
			symbol = "W";
			break;
		case 8:
			symbol = "<";
			break;
		default:
			throw Exception("Symbol Generation error");
	}
	return symbol;
}

Alchemy::~Alchemy()
{
	//cout << "In Alchemy d'tor" << endl;
	delete m_board;
	m_board = nullptr;
	m_level = 1;
	m_score = 0;
}
