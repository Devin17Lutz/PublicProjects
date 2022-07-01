/*************************************************************
* Author: Devin Lutz
* Filename: main.cpp
* Date Created: 5/19/18
* Modifications:
**************************************************************/
/*************************************************************
*
* Lab/Assignment: Lab4
*
* Overview:
* This program will loop through all the test functions and
* return a boolean type if its true it passed and false it
* failed.
*
* Input:
* There is no input for this program
*
* Output:
* The output of this program will be if the function passed
* or failed or Print the list in InOrder, PreOrder, PostOrder,
* Breadth First.
*
************************************************************/
typedef bool(*Funcptr)();
#include <iostream>
#include <string>
#include "AVLTree.h"
using std::cout;
using std::endl;
using std::string;

bool TestCopyCtors();
bool TestOp();
bool TestInsert();
bool TestDelete();
bool TestHeight();
bool TestPurge();
void TestPrints();

Funcptr test[] = { TestCopyCtors, TestOp, TestInsert, TestDelete, TestHeight, TestPurge };

void Display(const int & data);
void Display(const string & data);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for (Funcptr func : test)
	{
		if (func())
		{
			cout << "passed" << endl;
		}
		else
		{
			cout << "****FAILED****" << endl;
		}
	}
	cout << endl;
	TestPrints();
	return 0;
}

/**********************************************************************
* Purpose: This function Displays the data within the binary search
*		tree if the data is an int.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      no postconditions
*
************************************************************************/
void Display(const int & data)
{
	cout << data << " ";
}

/**********************************************************************
* Purpose: This function Displays the data within the binary search
*		tree if the data is a string.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      no postconditions
*
************************************************************************/
void Display(const string & data)
{
	cout << data << endl;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree Copy c'tor
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestCopyCtors()
{
	bool passed = true;
	AVLTree<int> tree;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(8);
	tree.Insert(7);
	tree.Delete(10);
	tree.Insert(12);
	tree.Insert(11);

	AVLTree<int> tree2(tree);

	if (tree.Height() != tree2.Height())
	{
		passed = false;
	}
	cout << "Testing AVLTree Copy C'tor:\t\t";
	return passed;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree Op =
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestOp()
{
	bool passed = true;
	AVLTree<int> tree, tree2;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(8);
	tree.Insert(7);
	tree.Delete(10);
	tree.Insert(12);
	tree.Insert(11);

	tree2 = tree;

	if (tree.Height() != tree2.Height())
	{
		passed = false;
	}
	cout << "Testing AVLTree Op=:\t\t\t";
	return passed;
}

/**********************************************************************
* Purpose: This function Test the Insert for the Avl tree. test LL, LR,
*		RR, and RL rotations.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestInsert()
{
	bool passed = true;
	AVLTree<int> tree;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(7);
	tree.Insert(4);
	cout << "\nTesting LL Rotation\n"
		 << "before Inserting 0: ";
	tree.BreadthFirst(Display);
	tree.Insert(0);
	cout << "\nAfter Inserting 0: ";
	tree.BreadthFirst(Display);
	cout << "\nTesting LR Rotation\n"
		<< "before Inserting 8: ";
	tree.BreadthFirst(Display);
	tree.Insert(8);
	cout << "\nAfter Inserting 8: ";
	tree.BreadthFirst(Display);
	tree.Insert(20);
	cout << "\nTesting RR Rotation\n"
		<< "before Inserting 40: ";
	tree.BreadthFirst(Display);
	tree.Insert(40);
	cout << "\nAfter Inserting 40: ";
	tree.BreadthFirst(Display);
	tree.Insert(5);
	tree.Insert(3);
	cout << "\nTesting RL Rotation\n"
		<< "before Inserting 2: ";
	tree.BreadthFirst(Display);
	tree.Insert(2);
	cout << "\nAfter Inserting 2: ";
	tree.BreadthFirst(Display);

	cout << "\nTesting AVLTree Insert:\t\t\t";
	return true;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree Delete
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestDelete()
{
	bool passed = false;
	AVLTree<int> tree, tree2;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(7);
	tree.Insert(4);
	tree.Delete(4);

	try
	{
		tree.Delete(4);
	}
	catch (Exception &c)
	{
		passed = true;
	}
	cout << "\nTesting AVLTree Delete:\t\t\t";
	return passed;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree height
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestHeight()
{
	bool passed = true;
	const int one = 1;
	AVLTree<int> tree;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(7);

	if (tree.Height() != one)
	{
		passed = false;
	}
	cout << "Testing AVLTree Height:\t\t\t";
	return passed;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree Purge
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
bool TestPurge()
{
	bool passed = true;
	AVLTree<int> tree;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(7);

	tree.Purge();
	
	if (tree.Height() >= 0)
	{
		passed = false;
	}
	cout << "Testing AVLTree Purge:\t\t\t";
	return passed;
}

/**********************************************************************
* Purpose: This function Test the AVL Tree Prints that are InOrder, 
*	PreOrder, PostOrder, Breadth First.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      Returns pass if it passed returns true, false if it failed
*
************************************************************************/
void TestPrints()
{
	AVLTree<int> tree;
	tree.Insert(9);
	tree.Insert(10);
	tree.Insert(8);
	tree.Insert(7);
	tree.Insert(12);
	tree.Insert(11);

	cout << "InOrder: ";
	tree.InOrder(Display);
	cout << "\nPreOrder: ";
	tree.PreOrder(Display);
	cout << "\nPostOrder: ";
	tree.PostOrder(Display);
	cout << "\nBreadthFirst: ";
	tree.BreadthFirst(Display);
	cout << "\t";
}
