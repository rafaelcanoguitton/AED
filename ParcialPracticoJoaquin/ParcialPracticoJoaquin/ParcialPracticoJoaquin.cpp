// ParcialPracticoJoaquin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;

template<class T>
struct Less
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};


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
bool Coprimo(T &a, T &b)
{
	int min, m = 0;
	if (a > b) {
		min = b;
	}
	else {
		min = a;
	}
	for (int i = 1;i <= min;i++) {
		if ((a%i == 0) && (b%i == 0))
			m = m + 1;
	}
	if (m == 1)
		return 1;
	return 0;
}
template<class T, class O>
struct List_Circular
{

	List_Circular() { head = NULL; }

	bool Find(T x, Node<T>**&p);
	bool Insert(T x);
	bool Delete(T x);
	bool Print();
	Node<T> *head;
	List_Circular<T, O> *next;
	O Compare;

	~List_Circular() {};
};

template<class T, class C>
bool List_Circular <T, C> ::Find(T x, Node <T>**&p)
{

	for (p = &head; *p and Compare((*p)->n_x, x) and (*p)->n_next != head;p = &((*p)->n_next));
	return *p and (*p)->n_x == x;


}

template<class T, class O>
bool List_Circular<T, O>::Insert(T x)
{
	Node<T> **p;
	if (Find(x, p)) { return 0; }
	Node<T> *t = new Node<T>(x);
	if (head == NULL)
	{
		*p = t;
		t->n_next = (*p);
		return 1;
	}
	Node<T> *last = head;
	while (last->n_next != head)
		last = last->n_next;
	if (Compare(x, head->n_x))
	{
		t->n_next = head;
		head = t;
		last->n_next = t;
		return 1;
	}
	else if ((*p == last) and Compare((*p)->n_x, x))
		p = &((*p)->n_next);
	t->n_next = (*p);
	*p = t;
	return 1;


}

template <class T, class O>
bool List_Circular<T, O>::Print()
{
	if (head != 0)
	{
		Node<T> *temp = head;

		do
		{
			cout << "[" << temp->n_x << "]" << " ";
			if (temp->n_next)
				cout << "-> " << "[" << temp->n_next->n_x << "]" << endl;
			temp = temp->n_next;
		} while (temp != head);
	}
	return 0;
}

template<class T, class O>
struct List
{

	List() { head = NULL; }
	bool Find(T x, List_Circular<T, O>**&p);
	bool Insert(T x);
	bool Delete(T x);
	bool Print();
	List_Circular<T, O> *head;
	O Compare;
	~List() {};

};

template<class T, class O>
bool List <T, O> ::Find(T x, List_Circular<T, O>**&p)
{

	for (;*p and Compare((*p)->head->n_x, x) and Coprimo((*p)->head->n_x, x);p = &((*p)->next));

	return *p and (*p)->head->n_x == x;

}


template<class T, class O>
bool List<T, O>::Insert(T x)
{
	List_Circular<T, Less<int> > **p = &head;
	bool cont = true;
	Find(x, p);
	while ((*p))
	{
		int a, b;
		if ((*p)->head->n_x > x)
		{
			a = (*p)->head->n_x;
			b = x;
		}
		else
		{
			b = (*p)->head->n_x;
			a = x;
		}

		if (!Coprimo(a, b))
		{
			(*p)->Insert(x);
			cont = false;
		}
		p = &((*p)->next);
		Find(x, p);
	}
	if ((*p) == NULL and cont)
	{
		(*p) = new List_Circular<T, Less<int> >();
		(*p)->Insert(x);
		(*p)->next = 0;
	}


	return 1;

}



template <class T, class O>
bool List<T, O>::Print()
{
	if (head != 0)
	{
		List_Circular<T, Less<int> > *t = head;
		while (t)
		{
			t->Print();
			cout << endl;
			t = t->next;
		}
	}
	return 0;
}


int main()
{
	List<int, Less<int> > *List_1 = new List<int, Less<int> >;


	List_1->Insert(3);
	List_1->Insert(5);
	List_1->Insert(2);
	List_1->Insert(6);
	List_1->Insert(12);






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
