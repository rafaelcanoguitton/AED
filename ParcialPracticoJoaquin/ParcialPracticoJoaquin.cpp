// HopesAndDreams.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include <stdio.h>

using namespace std;


template <class T>
struct Node
{
	T n_x;
	Node<T>*n_next;
	Node<T>*n_list;
	Node(T x, Node<T> *next = NULL)
	{
		n_x = x;
		n_list = 0;
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
	bool Print();
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
	Node<T>*hope=head;
	bool entro = 0;
	while (hope != NULL)
	{
		if ((x%hope->n_x) == 0) {
			entro = 1;bool halt = 1;
			Node<T>*temp = 0;
			if (hope->n_list == NULL) {
				hope->n_list = new Node<T>(x);
				hope->n_list->n_list = hope; halt = 0;
			}
			else
				temp = hope;
			while (temp != hope && halt) {
				if (temp->n_x > x)
				{
					Node<T> *tem = new Node<T>(x);
					tem->n_list = temp;
					temp->n_list = tem;
					halt = 1;
				}
				if (temp->n_list == NULL)
				{
					Node<T> *tem = new Node<T>(x);
					temp->n_list = tem;
					tem->n_list = hope;
					halt = 1;
				}
				if (temp->n_list != NULL)
					temp = temp->n_list;
			}
			if ((hope->n_x%x) == 0)
			{
				entro = 1;
				Node<T>*h = new Node<T>(x);
				h->n_next = hope->n_next;
				h->n_list = hope;
				hope->n_next = NULL;
			}
		}
		hope = hope->n_next;
	}
	if (entro) return 0;
	Node<T> **p;
	if (Find(x, p)) return 0;

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
bool List<T, O>::Print()
{
	if (head != 0)
	{
		Node<T> *t = head;
		while (t)
		{
			cout << "[" << t->n_x << "]" << " -> ";
			t = t->n_next;
		}
	}
	cout << "ListasCirculares: " << endl;
	Node<T>*p = head;
	Node<T>*q;bool xd=1;
	while (p) {
		q = p;
		while ((q != p||xd)&&q) {
			xd = 0;
			cout << q->n_x << "->";
			q = q->n_list;
		}
		cout << endl;
		p = p->n_next;xd = 1;
	}
	return 0;
}

int main()
{
	Node<int>**x;
	List<int, Less<int> > *List_1 = new List<int, Less<int> >;

	/*List_1->Insert(2);
	List_1->Insert(4);
	List_1->Insert(5);
	List_1->Insert(15);
	List_1->Insert(35);
	List_1->Insert(7);
	List_1->Insert(21);*/
	cout << "\n";

	int y;
	cout << "Ingrese sus numeros, para parar ingrese -1" << endl;
	cin >> y;
	for (int i = 0;i != -1;i = y)
	{

		List_1->Insert(y);
		cin >> y;
	}

	cout << "          LINKED LIST WITH DOUBLE POINTER: " << endl;
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
