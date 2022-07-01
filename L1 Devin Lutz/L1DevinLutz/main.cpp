/*************************************************************
* Author:		Devin Luts
* Filename:		main.cpp
* Date Created:	4/8/18
* Modifications:
*
* Lab/Assignment: Lab 1 – Alchemy
*
* Overview:
*	This program will play the game Alchemy. Need to fill all
*	the tiles in the array to gold. If you have three discards
*	you lose the game. For you to place a tile you need to have
*	a tile near it have the same color or same symbol or even a 
*	wild card.
*
* Input:
*	The input is if you want to play alchemy, see the rules, or
*	exit. Next the input is row and column to place the tile on the 
*	board. Lastly input y or n to discard a tile if it comes up.
*
* Output:
*	The output of this program is to ouput the board after ever
*	tile that is inserted or discarded.
*
************************************************************/
#include <windows.h>
#include <iostream>
#include <string>
#include "Alchemy.h"

int main()
{
	Alchemy game;
	game.Menu();

	return 0;
}