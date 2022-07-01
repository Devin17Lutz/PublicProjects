/************************************************************************
* Class: AVLTree
*
* Purpose: This class will act as the AVL tree that will insert
*	delete, purge, height and print the data InOrder, PreOrder, PostOrder,
*	Breadth First. If the tree is unbalanced when inserting or deleting a
*	node it will perform a LL, LR, RR, RL rotation to balance the tree. theres
*	also a balance method to check the balance of that node.
*
* Manager functions:
*	AVLTree()
*	AvLTree(const BSTree &copy)
*	AVLTree & operator=(const BSTree &rhs)
*	~AVLTree()
*
* Methods:
*	void Insert(T data)													//Calls the Private Insert
*	void Delete(T data)													//Calls the Private Delete
*	void Purge()														//Calls the Private Purge
*	int Height()														//Calls the Private height
*	void InOrder(void(*visit)(const T & data))							//Calls the Private InOrder
*	void PreOrder(void(*visit)(const T & data))							//Calls the Private PreOrder
*	void PostOrder(void(*visit)(const T & data))						//Calls the Private PostOrder
*	void BreadthFirst(void(*visit)(const T & data))						//Calls the Private BreadthFirst
*
*	void Insert(BSTNode<T> *&root, T data)								//Inserts the data
*	void Delete(BSTNode<T> *&BSTNode, T data)							//finds the node and deletes it
*	void InOrder(void(*visit)(const T & data), BSTNode<T> *root)		//Prints the BSTree InOrder
*	void PreOrder(void(*visit)(const T & data), BSTNode<T> *root)		//Prints the BSTree PreOrder
*	void PostOrder(void(*visit)(const T & data), BSTNode<T> *root)		//Prints the BSTree PostOrder
*	void BreadthFirst(void(*visit)(const T & data), BSTNode<T> *root)	//Prints the BSTree BreadthFirst
*	void Purge(BSTNode<T> *&root)										//Deletes all the nodes in the tree
*	int Height(BSTNode<T> *&root)										//Returns the height of the tree
*	BSTNode<T> *findMin(BSTNode<T> *node)								//finds the min node to switch with
*																				deleted node
*	void LeftBalance(BSTNode<T> *&root, bool &taller)					//Left Left or Left Right Rotation
*	void RightBalance(BSTNode<T> *&root, bool &taller)					//Right Right or Right Left Rotation
*
* Data Members:
*	BSTNode<T> *m_root
*
*************************************************************************/
#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H
#include "BSTNode.h"
#include "LListQueue.h"

enum CASES { LH = -1, EH, RH };

template <typename T>
class AVLTree
{
public:
	AVLTree();
	AVLTree(const AVLTree &copy);
	AVLTree & operator=(const AVLTree &rhs);

	void Insert(T data);
	void Delete(T data);
	void InOrder(void(*visit)(const T & data));
	void PreOrder(void(*visit)(const T & data));
	void PostOrder(void(*visit)(const T & data));
	void BreadthFirst(void(*visit)(const T & data));
	int Height();
	void Purge();

	~AVLTree();
private:
	void InOrder(void(*visit)(const T & data), BSTNode<T> *root);
	void PreOrder(void(*visit)(const T & data), BSTNode<T> *root);
	void PostOrder(void(*visit)(const T & data), BSTNode<T> *root);
	void BreadthFirst(void(*visit)(const T & data), BSTNode<T> *root);
	void Insert(BSTNode<T> *&root, T data, bool &taller);
	void Delete(BSTNode<T> *&BSTNode, T data);
	BSTNode<T> *findMin(BSTNode<T> *node);
	void LeftBalance(BSTNode<T> *&root, bool &taller);
	void RightBalance(BSTNode<T> *&root, bool &taller);
	int Height(BSTNode<T> *root);
	void Purge(BSTNode<T> *&m_root);

	BSTNode<T> *m_root;														//Holds the root of the tree
};

template<typename T>
inline AVLTree<T>::AVLTree()
	: m_root(nullptr)
{
	//cout << "In AVLTree c'tor" << endl;
}

template<typename T>
inline AVLTree<T>::AVLTree(const AVLTree & copy)
	: m_root(nullptr)
{
	//cout << "In AVLTree copy c'tor" << endl;
	BSTNode<T> *curr = copy.m_root;									//Used for traversing for the copy

	Purge();

	LListQueue<BSTNode<T> *> queue;									//Used to hold the data to be inserted correctly
	queue.Enqueue(curr);

	while (!queue.isEmpty())
	{
		curr = queue.Dequeue();

		if (curr->GetLeft() != nullptr)
		{
			queue.Enqueue(curr->GetLeft());
		}
		if (curr->GetRight() != nullptr)
		{
			queue.Enqueue(curr->GetRight());
		}

		Insert(curr->GetData());
	}
}

template<typename T>
inline AVLTree<T> & AVLTree<T>::operator=(const AVLTree & rhs)
{
	//cout << "In AVLTree Op=" << endl;
	if (this != &rhs)
	{
		BSTNode<T> *curr = rhs.m_root;									//Used for traversing for the copy

		Purge();

		LListQueue<BSTNode<T> *> queue;									//Used to hold the data to be inserted correctly
		queue.Enqueue(curr);

		while (!queue.isEmpty())
		{
			curr = queue.Dequeue();

			if (curr->GetLeft() != nullptr)
			{
				queue.Enqueue(curr->GetLeft());
			}
			if (curr->GetRight() != nullptr)
			{
				queue.Enqueue(curr->GetRight());
			}

			Insert(curr->GetData());
		}
	}
	return *this;
}

template<typename T>
inline void AVLTree<T>::Insert(T data)
{
	bool taller = false;												//Holds if the tree grew
	Insert(m_root, data, taller);
}

template<typename T>
inline void AVLTree<T>::Delete(T data)
{
	Delete(m_root, data);
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	//cout << "In AVLTree d'tor" << endl;
	Purge();
	m_root = nullptr;
}

template<typename T>
inline void AVLTree<T>::Insert(BSTNode<T> *&root, T data, bool &taller)
{
	if (root == nullptr)
	{
		root = new BSTNode<T>();										//Creates a new Node
		root->SetData(data);
		taller = true;
	}
	else if (data < root->GetData())
	{
		Insert(root->m_left, data, taller);

		if (taller)
		{
			switch (root->GetBalance())
			{
				case LH:
					LeftBalance(root, taller);
					break;
				case EH:
					root->SetBalance(LH);
					break;
				case RH:
					root->SetBalance(EH);
					taller = false;
					break;
			}
		}
	}
	else
	{
		Insert(root->m_right, data, taller);

		if (taller)
		{
			switch (root->GetBalance())
			{
			case LH:
				root->SetBalance(EH);
				taller = false;
				break;
			case EH:
				root->SetBalance(RH);
				break;
			case RH:
				RightBalance(root, taller);
				break;
			}
		}
	}
}

template<typename T>
inline void AVLTree<T>::Delete(BSTNode<T>* &node, T data)
{
	BSTNode<T> *temp = nullptr;											//Will hold the node that needs to be deleted
	bool taller = false;												//Holds if the tree grew

	if (node == nullptr)
	{
		throw Exception("Data not in the AVL tree");
	}
	else if (data > node->GetData())
	{
		Delete(node->m_right, data);
	}
	else if (data < node->GetData())
	{
		Delete(node->m_left, data);
	}
	else if (node->GetLeft() != nullptr && node->GetRight() != nullptr)
	{
		temp = findMin(node->GetRight());
		node->SetData(temp->GetData());
		Delete(node->m_right, node->GetData());
	}
	else
	{
		temp = node;
		if (node->GetLeft() == nullptr)
		{
			node = node->GetRight();
		}
		else if (node->GetRight() == nullptr)
		{
			node = node->GetLeft();
		}
		delete temp;
		temp = nullptr;
	}
	if (node != nullptr)
	{
		if (node->GetRight() == nullptr && ((Height(node->GetLeft()) + 1) > 1 || (Height(node->GetLeft()) + 1) < -1))
		{
			LeftBalance(node, taller);
		}
		else if (node->GetLeft() == nullptr && ((Height(node->GetRight()) + 1) > 1 || (Height(node->GetRight()) + 1) < -1))
		{
			RightBalance(node, taller);
		}
		else if ((Height(node->GetLeft()) + 1) - (Height(node->GetRight()) + 1) == 2)
		{
			if ((Height(node->GetLeft()->GetLeft()) + 1) - (Height(node->GetRight()->GetRight()) + 1) == 1)
			{
				LeftBalance(node, taller);
			}
			else
			{
				taller = true;
				LeftBalance(node, taller);
			}
		}
		else if ((Height(node->GetRight()) + 1) - (Height(node->GetLeft()) + 1) == 2)
		{
			if ((Height(node->GetRight()->GetRight()) + 1) - (Height(node->GetLeft()->GetLeft()) + 1) == 1)
			{
				RightBalance(node, taller);
			}
			else
			{
				taller = true;
				RightBalance(node, taller);
			}
		}
	}
}

template<typename T>
inline BSTNode<T> * AVLTree<T>::findMin(BSTNode<T>* node)
{
	BSTNode<T> *temp = nullptr;													//Will Hold the minimun Node if a parent node is deleted

	if (node->GetLeft() == nullptr)
	{
		temp = node;
	}
	else
	{
		temp = findMin(node->GetLeft());
	}
	return temp;
}

template<typename T>
inline void AVLTree<T>::LeftBalance(BSTNode<T>*& root, bool & taller)
{
	BSTNode<T> *newChild = root;
	BSTNode<T> *T2 = nullptr;

	if (root->GetLeft()->GetBalance() == RH && taller == true)
	{
		taller = false;
		RightBalance(root->m_left, taller);
	}

	T2 = root->GetLeft()->GetRight();
	root = root->GetLeft();
	root->SetRight(newChild);
	newChild->SetLeft(T2);

	if ((Height(root->GetRight()->GetLeft()) + 1) > (Height(root->GetRight()->GetRight()) + 1))
	{
		root->GetRight()->SetBalance(LH);
	}
	else if ((Height(root->GetRight()->GetLeft()) + 1) < (Height(root->GetRight()->GetRight()) + 1))
	{
		root->GetRight()->SetBalance(RH);
	}
	else
	{
		root->GetRight()->SetBalance(EH);
	}

	if ((Height(root->GetLeft()) + 1) > (Height(root->GetRight()) + 1))
	{
		root->SetBalance(LH);
	}
	else if ((Height(root->GetLeft()) + 1) < (Height(root->GetRight()) + 1))
	{
		root->SetBalance(RH);
	}
	else
	{
		root->SetBalance(EH);
	}
	taller = false;
}

template<typename T>
inline void AVLTree<T>::RightBalance(BSTNode<T>*& root, bool & taller)
{
	BSTNode<T> *newChild = root;												//Holds the new Child
	BSTNode<T> *T2 = nullptr;													//Holds the what the old child points to

	if (root->GetRight()->GetBalance() == LH && taller == true)
	{
		taller = false;
		LeftBalance(root->m_right, taller);
	}

	T2 = root->GetRight()->GetLeft();
	root = root->GetRight();
	root->SetLeft(newChild);
	newChild->SetRight(T2);

	if ((Height(root->GetLeft()->GetLeft()) + 1) > (Height(root->GetLeft()->GetRight()) + 1))
	{
		root->GetLeft()->SetBalance(LH);
	}
	else if ((Height(root->GetLeft()->GetLeft()) + 1) < (Height(root->GetLeft()->GetRight()) + 1))
	{
		root->GetLeft()->SetBalance(RH);
	}
	else
	{
		root->GetLeft()->SetBalance(EH);
	}

	if ((Height(root->GetLeft()) + 1) > (Height(root->GetRight()) + 1))
	{
		root->SetBalance(LH);
	}
	else if ((Height(root->GetLeft()) + 1) < (Height(root->GetRight()) + 1))
	{
		root->SetBalance(RH);
	}
	else
	{
		root->SetBalance(EH);
	}
	taller = false;
}

template<typename T>
inline int AVLTree<T>::Height(BSTNode<T>* root)
{
	int height = 0,																//Holds the height of the tree
		leftDepth = 0,															//Holds the Left depth of the sub tree
		rightDepth = 0;															//Holds the Right depth of the sub trees

	if (root == nullptr)
	{
		height = 0;
	}
	else
	{
		leftDepth = Height(root->m_left);
		rightDepth = Height(root->m_right);
		height = leftDepth > rightDepth ? (leftDepth + 1) : (rightDepth + 1);
	}

	return height;
}

template<typename T>
inline void AVLTree<T>::Purge(BSTNode<T>*& m_root)
{
	if (m_root != nullptr)
	{
		Purge(m_root->m_left);
		Purge(m_root->m_right);

		delete m_root;
		m_root = nullptr;
	}
}

template<typename T>
inline void AVLTree<T>::Purge()
{
	Purge(m_root);
}

template<typename T>
inline void AVLTree<T>::InOrder(void(*visit)(const T & data))
{
	InOrder(visit, m_root);
}

template<typename T>
inline void AVLTree<T>::PreOrder(void(*visit)(const T &data))
{
	PreOrder(visit, m_root);
}

template<typename T>
inline void AVLTree<T>::PostOrder(void(*visit)(const T &data))
{
	PostOrder(visit, m_root);
}

template<typename T>
inline void AVLTree<T>::BreadthFirst(void(*visit)(const T &data))
{
	BreadthFirst(visit, m_root);
}

template<typename T>
inline int AVLTree<T>::Height()
{
	return (Height(m_root) - 1);
}

template<typename T>
inline void AVLTree<T>::InOrder(void(*visit)(const T & data), BSTNode<T> *root)
{
	if (root != nullptr)
	{
		InOrder(visit, root->GetLeft());
		visit(root->GetData());
		InOrder(visit, root->GetRight());
	}
}

template<typename T>
inline void AVLTree<T>::PreOrder(void(*visit)(const T & data), BSTNode<T>* root)
{
	if (root != nullptr)
	{
		visit(root->GetData());
		PreOrder(visit, root->GetLeft());
		PreOrder(visit, root->GetRight());
	}
}

template<typename T>
inline void AVLTree<T>::PostOrder(void(*visit)(const T & data), BSTNode<T>* root)
{
	if (root != nullptr)
	{
		PostOrder(visit, root->GetLeft());
		PostOrder(visit, root->GetRight());
		visit(root->GetData());
	}
}

template<typename T>
inline void AVLTree<T>::BreadthFirst(void(*visit)(const T & data), BSTNode<T>* root)
{
	BSTNode<T> *curr = root;									//Used for traversing for the tree
	LListQueue<BSTNode<T> *> queue;								//Used to hold the data to be inserted correctly
	queue.Enqueue(curr);

	while (!queue.isEmpty())
	{
		curr = queue.Dequeue();

		if (curr->GetLeft() != nullptr)
		{
			queue.Enqueue(curr->GetLeft());
		}
		if (curr->GetRight() != nullptr)
		{
			queue.Enqueue(curr->GetRight());
		}

		visit(curr->GetData());
	}
}
#endif