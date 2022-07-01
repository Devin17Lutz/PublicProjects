/************************************************************************
* Class: BSTBSTNode
*
* Purpose: This class will handle the data and to see whats left and right
*	for the Binary Search Tree.
*
* Manager functions:
*	BSTNode()
*	BSTNode(const BSTNode &copy)
*	BSTNode & operator=(const BSTNode &rhs)
*	~BSTNode()
*
* Methods:
*	void SetData(T data)						-Sets the data
*	void SetNext(BSTNode *next)					-Sets the next pointer
*	void SetPrev(BSTNode *prev)					-Sets the prev pointer
*	T GetData()const							-Returns the data
*	BSTNode *GetNext()const						-Returns the next pointer
*	BSTNode *GetPrev()const						-Returns the prev pointer
*
* Data Members:
*	T m_data									-Holds the data
*	BSTNode *m_right							-Holds the next pointer
*	BSTNode *m_left								-Holds the prev pointer
*
*************************************************************************/
#pragma once
#ifndef BSTNode_H
#define BSTNode_H

template <typename T>
class BSTNode
{
public:
	BSTNode();
	BSTNode(const BSTNode &copy);
	BSTNode & operator=(const BSTNode &rhs);

	template <typename T>
	friend class AVLTree;

	//Setters
	void SetData(T data);
	void SetLeft(BSTNode *left);
	void SetRight(BSTNode *right);
	void SetBalance(int balance);
	//Getters
	T & GetData();
	BSTNode * GetLeft() const;
	BSTNode * GetRight() const;
	int GetBalance() const;

	~BSTNode();
private:
	T m_data;
	BSTNode *m_right;
	BSTNode *m_left;
	int m_balance;
};

template<typename T>
inline BSTNode<T>::BSTNode()
	: m_right(nullptr), m_left(nullptr), m_balance(0)
{
	//cout << "In BSTNode c'tor" << endl;
}

template<typename T>
inline BSTNode<T>::BSTNode(const BSTNode & copy)
	: m_data(copy.m_data), m_right(copy.m_right), m_left(copy.m_left), m_balance(copy.m_balance)
{
	//cout << "In BSTNode copy c'tor" << endl;
}

template<typename T>
inline BSTNode<T> & BSTNode<T>::operator=(const BSTNode & rhs)
{
	//cout << "In BSTNode op=" << endl;
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_right = rhs.m_right;
		m_left = rhs.m_left;
		m_balance = rhs.m_balance;
	}
	return *this;
}

template<typename T>
inline void BSTNode<T>::SetData(T data)
{
	m_data = data;
}

template<typename T>
inline void BSTNode<T>::SetLeft(BSTNode *left)
{
	m_left = left;
}

template<typename T>
inline void BSTNode<T>::SetRight(BSTNode *right)
{
	m_right = right;
}

template<typename T>
inline void BSTNode<T>::SetBalance(int balance)
{
	m_balance = balance;
}

template<typename T>
inline T & BSTNode<T>::GetData()
{
	return m_data;
}

template<typename T>
inline BSTNode<T> * BSTNode<T>::GetRight() const
{
	return m_right;
}

template<typename T>
inline int BSTNode<T>::GetBalance() const
{
	return m_balance;
}

template<typename T>
inline BSTNode<T> * BSTNode<T>::GetLeft() const
{
	return m_left;
}

template<typename T>
inline BSTNode<T>::~BSTNode()
{
	//cout << "In BSTNode d'tor" << endl;
	m_right = nullptr;
	m_left = nullptr;
}
#endif
