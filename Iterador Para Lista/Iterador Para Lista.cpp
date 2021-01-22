// Iterador Para Lista.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

template<class T>
struct Nodo
{
	T dato;
	Nodo<T> *next;
	Nodo(T x)
	{
		dato = x;
		next = NULL;
	}
};

template<class T>
struct Iterador
{
	Nodo<T> *mv;//puntero valor
	Iterador(Nodo<T> *x = NULL)
	{
		mv = x;
	}
	Iterador<T> operator = (Iterador<T> x)
	{
		mv = x.mv;
		return *this;
	}
	bool operator != (Iterador<T> x)
	{
		return mv != NULL; //ult elemento
	}
	void operator ++()
	{
		mv = mv->next; //++ mv
	}
	//T operator *(){return mv->dato;}; // es lo mismo
	T & operator *() {
		return mv->dato; //contenido del nodo *(a+i)
	}
};

template<class T>
struct LS
{
	Nodo<T> *head;
	typedef Iterador<T> iterador; //llamar al iterador iterator en este caso
	LS()
	{
		head = NULL;
	}
	~LS() {};
	bool buscar(T x)
	{
		Nodo<T> *p;
		for (p = head; p && p->dato < x; p = p->next);
		return p && p->dato == x;
	}
	bool insertar(T x)
	{
		Nodo<T> *nuevo = new Nodo<T>(x);
		if (head == NULL) { head = nuevo;return 1; }
		else
		{
			if (!buscar(x))
			{
				Nodo<T> *p = head;
				if (x < p->dato)
				{
					head = nuevo;
					nuevo->next = p;
				}
				else
				{
					while (p->next != NULL && p->next->dato < x) p = p->next;
					nuevo->next = p->next;
					p->next = nuevo;
				}
			}
		}
	}
	iterador begin()
	{
		return iterador(head);// inicio head
	}
	iterador end()
	{
		return iterador();// final != null
	}
};


int main()
{
	LS<int> l;
	LS<int>::iterador i;// creamos un i de tipo iterator
	l.insertar(2);
	l.insertar(1);
	l.insertar(3);
	l.insertar(4);
	l.insertar(5);
	l.insertar(6);
	l.insertar(7);

	for (i = l.begin();i != l.end();++i)
		cout << *i << " ";
	cout << endl;

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
