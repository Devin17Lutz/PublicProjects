/************************************************************************
* Class: LinkedList
*
* Purpose: This class will handle any inserting, purging or printing the
*
* Manager functions:
*	LinkedList()
*	LinkedList(const LinkedList &copy)
*	LinkedList & operator=(const LinkedList &rhs)
*	~LinkedList()
*
* Methods:
*	void Prepend(T data)							-Adds a node at the beginning of the list
*	void Append(T data)								-Adds a node at the end of the list
*	void InsertBefore(T searchData, T data)			-Adds data before a specifed node data
*	void InsertAfter(T searchData, T data)			-Adds data after a specidfied node data
*	void PrintForwards()							-Prints list normally
*	void PrintBackwards()							-Prints list backwards
*	bool isEmpty()									-Checks to see if the list is empty
*	void Purge()									-Deletes all the nodes in the list
*	void Extract(T data)							-Deletes one node specified by the data
*
* Data Members:
*	Node<T> *head
*	Node<T> *tail
*
*************************************************************************/
#pragma once
#include "Node.h"
#include "Exception.h"

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList &copy);
	LinkedList & operator=(const LinkedList &rhs);

	void Prepend(T data);
	void Append(T data);
	void InsertBefore(T searchData, T data);
	void InsertAfter(T searchData, T data);
	void PrintForwards();
	void PrintBackwards();
	bool isEmpty();
	void Purge();
	void Extract(T &data);

	//Getter
	const T & First()const;
	const T & Last()const;
	Node<T> *getTail()const;
	Node<T> *getHead()const;


	void Move();

	~LinkedList();
private:
	Node<T> *head;									//Holds the starting point of the list
	Node<T> *tail;									//Holds the end point of the list
};
#endif

template<typename T>
inline LinkedList<T>::LinkedList()
	: head(nullptr), tail(nullptr)
{
	//cout << "In LinkedList c'tor" << endl;
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList & copy)
	: head(nullptr), tail(nullptr)
{
	//cout << "In LinkedList Copy c'tor" << endl;
	Node<T> * rhsTravel = copy.head;

	Purge();

	while (rhsTravel != nullptr)
	{
		Append(rhsTravel->GetData());
		rhsTravel = rhsTravel->GetNext();
	}
}

template<typename T>
inline LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs)
{
	//cout << "In LinkedList op=" << endl;
	Node<T> * rhsTravel = rhs.head;

	if (this != &rhs)
	{
		Purge();
		/*head = rhs.head;
		tail = rhs.tail;*/
		
		while (rhsTravel != nullptr)
		{
			Append(rhsTravel->GetData());
			rhsTravel = rhsTravel->GetNext();
		}
	}
	return *this;
}

template<typename T>
inline void LinkedList<T>::Prepend(T data)
{
	Node<T> *newNode = new Node<T>();							//the node that will be inserted into the list
	newNode->SetData(data);

	if (isEmpty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->SetNext(head);
		head->SetPrev(newNode);
		head = newNode;
	}
}

template<typename T>
inline void LinkedList<T>::Append(T data)
{
	Node<T> *newNode = new Node<T>();							//the node that will be inserted into the list
	newNode->SetData(data);

	if (isEmpty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->SetPrev(tail);
		tail->SetNext(newNode);
		tail = newNode;
	}
}

template<typename T>
inline void LinkedList<T>::InsertBefore(T searchData, T data)
{
	if (isEmpty())
	{
		throw Exception("No list to insert");
	}
	bool inserted = false;												//we know that the data was inserted
	Node<T> *travel = head,												//node that will traverse the list
		*prev = nullptr,												//need to have the previous node ptr to insert before travel data
		*newNode = new Node<T>();										//the node that will be inserted into the list
	newNode->SetData(data);

	while (travel != nullptr && !inserted)
	{
		if (travel->GetData() == searchData)
		{
			if (travel == head)
			{
				Prepend(data);
			}
			else
			{
				prev = travel->GetPrev();
				prev->SetNext(newNode);
				newNode->SetPrev(prev);
				newNode->SetNext(travel);
				travel->SetPrev(newNode);
			}
			inserted = true;
		}
		else
		{
			travel = travel->GetNext();
		}
	}
	if (!inserted)
	{
		throw Exception("Searched data wasn't in the list");
	}
}

template<typename T>
inline void LinkedList<T>::InsertAfter(T searchData, T data)
{
	if (isEmpty())
	{
		throw Exception("No list to insert");
	}
	bool inserted = false;												//we know that the data was inserted
	Node<T> *travel = head,												//node that will traverse the list
		*next = nullptr,												//need to have the next node ptr to insert after travel data
		*newNode = new Node<T>();										//the node that will be inserted into the list
	newNode->SetData(data);

	while (travel != nullptr && !inserted)
	{
		if (travel->GetData() == searchData)
		{
			if (travel == tail)
			{
				Append(data);
			}
			else
			{
				next = travel->GetNext();
				next->SetPrev(newNode);
				newNode->SetNext(next);
				newNode->SetPrev(travel);
				travel->SetNext(newNode);
			}
			inserted = true;
		}
		else
		{
			travel = travel->GetNext();
		}
	}
	if (!inserted)
	{
		throw Exception("Searched data wasn't in the list");
	}

}

template<typename T>
inline void LinkedList<T>::PrintForwards()
{
	Node<T> *travel = head;											//Node pointer to travel the list

	while (travel != nullptr)
	{
		cout << travel->GetData() << " ";
		travel = travel->GetNext();
	}
	cout << endl;
}

template<typename T>
inline void LinkedList<T>::PrintBackwards()
{
	Node<T> *travel = tail;											//Node pointer to travel the list backwards

	while (travel != nullptr)
	{
		cout << travel->GetData() << " ";
		travel = travel->GetPrev();
	}
	cout << endl;
}

template<typename T>
inline bool LinkedList<T>::isEmpty()
{
	bool pass = false;												//check to see if the list is empty or not

	if (head == nullptr && tail == nullptr)
	{
		pass = true;
	}
	return pass;
}

template<typename T>
inline void LinkedList<T>::Purge()
{
	if (!isEmpty())
	{
		Node<T> *travel = head;											//Node pointer to travel the list and delete

		while (travel != nullptr)
		{
			head = head->GetNext();
			delete travel;
			travel = head;
		}
		tail = nullptr;
	}
}

template<typename T>
inline void LinkedList<T>::Extract(T & data)
{
	if (isEmpty())
	{
		throw Exception("List is empty");
	}

	Node<T> *travel = head;

	while (travel != nullptr && data != travel->GetData())
	{
		travel = travel->GetNext();
	}
	if (travel == nullptr)
	{
		throw Exception("Data Not in the list");
	}

	if (travel->GetPrev() == nullptr && travel->GetNext() == nullptr)
	{
		head = nullptr;
		tail = nullptr;
		delete travel;
	}
	else if (travel->GetPrev() == nullptr)
	{
		head = head->GetNext();
		travel->GetNext()->SetPrev(nullptr);
		delete travel;
	}
	else if (travel->GetNext() == nullptr)
	{
		tail = tail->GetPrev();
		travel->GetPrev()->SetNext(nullptr);
		delete travel;
	}
	else
	{
		travel->GetPrev()->SetNext(travel->GetNext());
		travel->GetNext()->SetPrev(travel->GetPrev());
		delete travel;
	}
}

template<typename T>
inline const T & LinkedList<T>::First() const
{
	return head->GetData();
}

template<typename T>
inline const T & LinkedList<T>::Last() const
{
	return tail->GetData();
}

template<typename T>
inline Node<T> * LinkedList<T>::getTail() const
{
	return tail;
}

template<typename T>
inline Node<T> * LinkedList<T>::getHead() const
{
	return head;
}

template<typename T>
inline void LinkedList<T>::Move()
{
	head = head->GetNext();
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	//cout << "In Linked List d'tor" << endl;
	head = nullptr;
	tail = nullptr;
}

