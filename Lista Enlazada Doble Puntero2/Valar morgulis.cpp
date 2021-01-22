// Valar morgulis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

using namespace std;


template <class T>
struct Node
{
	T n_x;
	Node<T>*n_next;
	Node(T x, Node<T> *next = NULL)
	{
		n_x = x;
		n_next = next;
	}
};

template<class T>
struct Higher
{
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

template<class T>
struct Less
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};

template<class T, class O>
struct List
{

	List() { head = NULL; }
	bool Find(T x, Node<T>**&p);
	bool Insert(T x);
	bool Delete(T x);
	void Print();
	Node<T> *head;
	O Compare;

	~List()
	{
		if (head != 0)
		{
			Node<T> *t = head;
			while (t)
			{
				Node<T> *n_next = t->n_next;
				delete t;
				t = n_next;
			}
		}
	}

};



template<class T, class C>
bool List <T, C> ::Find(T x, Node <T>**&p)
{

	for (p = &head; *p and Compare((*p)->n_x, x);p = &((*p)->n_next));

	return *p and (*p)->n_x == x;

}


template<class T, class O>
bool List<T, O>::Insert(T x)
{
	Node<T> **p;
	if (Find(x, p))
	{
		cout << "REPEATED ELEMENT" << endl;
		cout << "\n";
		return 0;
	}
	Node<T> *t = new Node<T>(x);
	t->n_next = (*p);
	*p = t;
	return 1;
}

template<class T, class O>
bool List<T, O>::Delete(T x)
{
	Node<T> **p;
	if (!Find(x, p)) return 0;
	Node<T> *t = (*p);
	*p = t->n_next;
	delete t;
	return 1;
}

template <class T, class O>
void List<T, O>::Print()
{
	if (head != 0)
	{
		Node<T> *t = head;
		while (t)
		{
			cout << "[" << t->n_x << "]" << " " << endl;
			t = t->n_next;
		}
	}
}


int main()
{
	List<int, Less<int> > *List_1 = new List<int, Less<int> >;

	List_1->Insert(1);
	List_1->Insert(4);
	List_1->Insert(3);
	List_1->Insert(5);
	List_1->Insert(7);
	List_1->Insert(6);
	List_1->Insert(2);

	List_1->Delete(1);
	List_1->Delete(4);
	List_1->Delete(7);



	cout << "          LINKED LIST WHIT DOUBLE POINTER: " << endl;
	cout << "\n";
	List_1->Print();




	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
