// ArbolIteratoryanoya.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;

template <class T>
struct Node
{
	Node(T x)
	{
		N_nodes[0] = NULL; // HIJO IZQUIERDO
		N_nodes[1] = NULL; // HJO DERECHO
		n_x = x;
	}
	Node<T> *N_nodes[2];
	T n_x;

};
template<class T>
struct Less
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};
template <class T, class O>
struct Tree
{
	Node<T> *n_root;
	O Compare;
	Tree() { n_root = 0; }
	~Tree() {};
	bool Find(T x, Node<T>**&p);
	bool Insert(T x);
	bool Delete(T x);
	Node<T> **rep(T x, Node<T> **p);
	void InOrden(Node<T> *p);


};

template<class T, class O>
Node<T> **Tree<T, O>::rep(T x, Node<T> **p)
{
	for (p = &((*p)->N_nodes[0]); *p && (*p)->N_nodes[1]; p = &((*p)->N_nodes[Compare((*p)->n_x, x)]));//MAYOR DE LOS MENORES

	return p; // DIRECCION DEL NODO IZQ
}

template<class T, class O>
bool Tree<T, O>::Find(T x, Node<T>**&p)
{
	for (p = &n_root; *p and (*p)->n_x != x; p = &((*p)->N_nodes[Compare((*p)->n_x, x)]));
	return !!*p;
}

template<class T, class O>
bool Tree<T, O>::Insert(T x)
{
	Node<T> **p;
	if (Find(x, p)) return 0;
	*p = new Node<T>(x);
	return 1;
}

template<class T, class O>
bool Tree<T, O>::Delete(T x)
{
	Node<T> **p;
	if (!Find(x, p)) return 0;
	if ((*p)->N_nodes[0] and (*p)->N_nodes[1])//TIENE DOS HIJOS
	{
		Node<T> **q = rep(x, p);
		(*p)->n_x = (*q)->n_x;
		p = q;
	}
	Node<T> *temp = *p;
	*p = (*p)->N_nodes[(*p)->N_nodes[1] != 0];
	delete temp;
	return 1;

}

template<class T, class O>
void Tree<T, O>::InOrden(Node<T> *p)
{
	if (!p) return;
	InOrden(p->N_nodes[0]);
	cout << p->n_x << " <<->> ";
	InOrden(p->N_nodes[1]);

}



int main()
{
	Tree<int, Less<int> > Ent;
	Ent.Insert(8);
	Ent.Insert(3);
	Ent.Insert(10);
	Ent.Insert(1);
	Ent.Insert(14);
	Ent.Insert(6);
	Ent.Insert(5);
	Ent.Insert(4);
	Ent.Insert(7);
	Ent.Insert(13);
	Ent.Insert(2);
	Ent.Delete(1);
	Ent.Delete(6);
	Ent.Delete(14);
	Ent.Delete(3);
	Ent.Delete(5);


	cout << "-----BINARY TREE-----" << endl;
	cout << "\n";

	Ent.InOrden(Ent.n_root);

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
