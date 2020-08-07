// avl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<windows.h>
#include <stdio.h>      
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
#include<queue>
using namespace std;
template<class T>
class asc
{
public:
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

template<class T>
class des
{
public:
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};


template<class T>
class Node {
public:
	T value;
	int balanceFactor;
	int height;
	int level;
	Node<T> *nodes[3];

	Node(T value, Node<T> **&p) {
		this->value = value;
		if (*p) {
			this->nodes[0] = (*p)->nodes[0];
			this->nodes[1] = (*p)->nodes[1];
			this->nodes[2] = NULL;
			return;
		}
		this->nodes[0] = NULL;
		this->nodes[1] = NULL;
		this->nodes[2] = NULL;
	}
};

template<typename T>
class pila
{

public:
	Node<T>* top = nullptr; Node<T>* rear = nullptr;
	bool vacio(); //indica si la pila está vacía
	void push(Node<T>* elemento); //agrega un elemento
	Node<T>* pop(); //retirua un elemento y devuelve su valor 
	Node<T>* poprear();
	void print(); //imprime el contenido de la pila
	void levels(Node<T>* M_Root);
	void inorder(Node<T>* M_Root);
	~pila();
	void preorder(Node<T>* M_Root);
	void postorder(Node<T>* M_Root);
	void reverse(Node<T>* M_Root);
};

template<typename T>
bool pila<T>::vacio()
{
	if (top)
		return false;
	else
		return true;
}

template<typename T>
void pila<T>::print()
{
	Node<T>* tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->value << endl;
	cout << "base" << endl;
}
template<typename T>
void pila<T>::levels(Node<T>* M_Root)
{
	int count = 0;
	if (M_Root)
		push(M_Root);
	while (!vacio())
	{
		Node<T>* temp = top;
		if (count != temp->level) {
			cout << endl; count++;
		}
		cout << temp->value << " ";

		if (temp->nodes[0])
			push(temp->nodes[0]);
		if (temp->nodes[1])
			push(temp->nodes[1]);
		pop();
	}

}

template<typename T>
void pila<T>::inorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->nodes[0];
		}
		temp = rear;
		poprear();
		cout << temp->value << " ";
		temp = temp->nodes[1];
	}
}
template<typename T>
void pila<T>::preorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			cout << temp->value << " ";
			if (temp->nodes[1])
				push(temp->nodes[1]);
			temp = temp->nodes[0];
		}
		if (!vacio())
		{
			temp = rear;
			poprear();
		}
	}
}
template<typename T>
void pila<T>::postorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			if (temp->nodes[1])
				push(temp->nodes[1]);
			push(temp);
			temp = temp->nodes[0];
		}
		temp = rear; poprear();
		if (temp->nodes[1] && rear == temp->nodes[1])
		{
			poprear();
			push(temp);
			temp = temp->nodes[1];
		}
		else
		{
			cout << temp->value << " ";
			temp = NULL;
		}
	}
}
template<typename T>
void pila<T>::reverse(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->nodes[1];
		}
		temp = rear;
		poprear();
		cout << temp->value << " ";
		temp = temp->nodes[0];
	}
}
template<typename T>
void pila<T>::push(Node<T>* elemento)
{
	if (top)
	{
		Node<T>* temp = elemento; Node<T>* enqueue = top;
		while (enqueue->nodes[2])
			enqueue = enqueue->nodes[2];
		enqueue->nodes[2] = temp;
		rear = temp;
	}
	else
		top = elemento; rear = elemento;

}

template<typename T>
Node<T>* pila<T>::pop()
{
	if (top)
	{
		Node<T>* temp = top;
		top = top->nodes[2];
		//delete temp;
		return temp;
	}
}
template<typename T>
Node<T>* pila<T>::poprear()
{
	if (top != rear)
	{
		Node<T>* temp = top;
		while (temp->nodes[2] != rear)
		{
			temp = temp->nodes[2];
		}
		temp->nodes[2] = NULL;
		rear = temp;
		//delete temp;
		return temp;
	}
	else
		top = NULL; rear = NULL;
}
template<typename T>
pila<T>::~pila()
{
	while (top)
	{
		Node<T>* temp = top;
		top = top->nodes[2];
		delete temp;
	}
}
template<class T, class Q>
class Tree
{
	Node<T> *root;
	Q Compare;
public:
	Tree()
	{
		root = NULL;
	}

	void RR(Node<T> **&p)
	{
		Node<T> *temp = (*p)->nodes[1]->nodes[0];
		(*p)->nodes[1]->nodes[0] = *p;
		*p = (*p)->nodes[1];
		(*p)->nodes[0]->nodes[1] = temp;

	}
	void LL(Node<T> **&p)
	{
		Node<T> *temp = (*p)->nodes[0]->nodes[1];
		(*p)->nodes[0]->nodes[1] = *p;
		*p = (*p)->nodes[0];
		(*p)->nodes[1]->nodes[0] = temp;
	}
	void LR(Node<T> **&p)
	{
		Node<T> *temp_left = (*p)->nodes[0]->nodes[1]->nodes[0];
		Node<T> *temp_right = (*p)->nodes[0]->nodes[1]->nodes[1];
		(*p)->nodes[0]->nodes[1]->nodes[0] = (*p)->nodes[0];
		(*p)->nodes[0]->nodes[1]->nodes[1] = *p;
		*p = (*p)->nodes[0]->nodes[1];
		(*p)->nodes[0]->nodes[1] = temp_left;
		(*p)->nodes[1]->nodes[0] = temp_right;
	}
	void RL(Node<T> **&p)
	{
		Node<T> *temp_left = (*p)->nodes[1]->nodes[0]->nodes[0];
		Node<T> *temp_right = (*p)->nodes[1]->nodes[0]->nodes[1];
		(*p)->nodes[1]->nodes[0]->nodes[1] = (*p)->nodes[1];
		(*p)->nodes[1]->nodes[0]->nodes[0] = *p;
		*p = (*p)->nodes[1]->nodes[0];
		(*p)->nodes[1]->nodes[0] = temp_right;
		(*p)->nodes[0]->nodes[1] = temp_left;

	}
	void NeoBalance(Node<T> **p)
	{
		if (*p)
		{
			NeoBalance(&(*p)->nodes[0]);
			NeoBalance(&(*p)->nodes[1]);
			(*p)->balanceFactor = 0;
			(*p)->height = 0;

			if ((*p)->nodes[0])
			{
				(*p)->height = (*p)->nodes[0]->height + 1;
				(*p)->balanceFactor -= (*p)->height;
			}
			if ((*p)->nodes[1])
			{
				if ((*p)->nodes[0] and (*p)->nodes[0]->height < (*p)->nodes[1]->height)
					(*p)->height = (*p)->nodes[1]->height + 1;
				(*p)->balanceFactor += (*p)->nodes[1]->height + 1;
			}
			if ((*p)->balanceFactor < -1)
			{
				if ((*p)->nodes[0]->balanceFactor < 1 and (*p)->nodes[0]->nodes[0])

					LL(p);

				else if ((*p)->nodes[0]->balanceFactor >= 1 and (*p)->nodes[0]->nodes[1])

					LR(p);

				NeoBalance(p);
				return;
			}

			else if ((*p)->balanceFactor > 1)
			{
				if ((*p)->nodes[1]->balanceFactor > -1 and (*p)->nodes[1]->nodes[1])
					RR(p);

				else if ((*p)->nodes[1]->balanceFactor <= -1 and (*p)->nodes[1]->nodes[0])
					RL(p);

				NeoBalance(p);
				return;

			}
		}
	}

	Node<T> *returnRoot()
	{
		return root;
	}
	void rep(Node<T> **&p) {
		bool jump = !!((*p)->nodes[1]);
		p = &(*p)->nodes[jump];
		while ((*p)->nodes[!jump]) {
			p = &(*p)->nodes[!jump];
		}
	}

	bool find(T x, Node<T> **&p) {
		p = &root;
		for (;
			*p and (*p)->value != x;
			p = &(*p)->nodes[Compare((*p)->value, x)]
			);
		return !!*p;
	}


	void insert(T x) {
		Node<T> **p;
		if (!find(x, p)) {
			*p = new Node<T>(x, p);
		}
		NeoBalance(&root);
	}

	void remove(T x) {
		Node<T> **p;
		if (find(x, p)) { // si lo encuentro hago algo
			if ((*p)->nodes[0] and (*p)->nodes[1]) { // caso 2 creo, si tiene dos hijos
				Node<T> *q = *p;
				rep(p);
				q->value = (*p)->value;
			}
			Node<T> *t = *p;
			*p = (*p)->nodes[!!(*p)->nodes[1]];// p va a ser el hijo izquierdo si existe, sino sera el hijo derecho
			delete t;// borro t y debo balancear el arbol
			NeoBalance(&root);
		}
	}

	void Print(Node<T> *p) {
		if (p) {
			if (p->nodes[1])
				cout << p->nodes[1]->value << " --- ";// << "(" << p->height << ")" << "(" << p->balanceFactor << ")";
			else
				cout << "       ";
			if (p->nodes[!!p->nodes[1]])
				cout << " " << p->value;// << "(" << p->height << ")" << "(" << p->balanceFactor << ")";
			if (p->nodes[0]) {
				cout << " --- " << p->nodes[0]->value;//<< "(" << p->height << ")" << "(" << p->balanceFactor << ")";
				cout << endl;
			}
			else {
				cout << endl;
			}
			Print(p->nodes[1]);
			Print(p->nodes[0]);

		}
	}

	void PrintLevels()
	{
		queue < Node<int>* > q;
		//queue <int> q_auxiliar;
		q.push(root);
		while (q.size() > 0)
		{
			Node<T> *p = q.front();
			q.pop();
			cout << p->value << " ";
			if (p->nodes[0])
			{
				q.push(p->nodes[0]);
			}
			if (p->nodes[1])
			{
				q.push(p->nodes[1]);
			}
		}
	}
	void recursivoDeleterino(Node<T>* Temp_Root)
	{
		recursivoDeleterino(Temp_Root->nodes[0]);
		recursivoDeleterino(Temp_Root->nodes[1]);
		delete Temp_Root;
	}


	~Tree()
	{
		recursivoDeleterino(returnRoot());
	}
};
template <class T>
void assign(Node<T>* M_Root, int curr = 0)
{
	int current = curr;
	if (M_Root != NULL) {
		assign(M_Root->nodes[0], current + 1);
		assign(M_Root->nodes[1], current + 1);
		M_Root->level = current;
	}

}

int main()
{

	Tree<int, des<int> > *arbol = new Tree<int, des<int> >;

	int x = 0;
	while (x != 9)
	{
		cout << "Seleccione una opción: " << endl;
		cout << "Insertar = 1 " << endl;
		cout << "Eliminar = 2" << endl;
		cout << "Impresion Inorder = 3" << endl;
		cout << "Impresion Postorder = 4" << endl;
		cout << "Impresion Preorder = 5" << endl;
		cout << "Impresion Reverse = 6" << endl;
		cout << "Impresion Niveles = 7" << endl;
		cout << "GETROOT 8" << endl;
		cin >> x;
		if (x == 1)
		{
			int temp;
			cout << "Que elemento desea agregar?" << endl; cin >> temp; arbol->insert(temp);
		}
		if (x == 2)
		{
			int temp;
			cout << "Que elemento desea borrar?" << endl; cin >> temp; arbol->remove(temp);
		}
		if (x == 3)
		{
			pila <int>q;
			q.inorder(arbol->returnRoot());
			//Inorder(arbol.M_Root); cout << endl;
			system("pause");
		}
		if (x == 4)
		{
			pila <int>q;
			q.postorder(arbol->returnRoot());
			//Postorder(arbol.M_Root); cout << endl;
			system("pause");
		}
		if (x == 5)
		{
			pila <int>q;
			q.preorder(arbol->returnRoot());
			//Preorder(arbol.M_Root); cout << endl;
			system("pause");
		}
		if (x == 6)
		{
			pila <int>q;
			q.reverse(arbol->returnRoot());
			//Reverse(arbol.M_Root); cout << endl;
			system("pause");
		}
		if (x == 7)
		{
			assign(arbol->returnRoot());
			pila <int>q;
			q.levels(arbol->returnRoot());
			system("pause");
		}
		if (x == 8)
		{
			arbol->Print(arbol->returnRoot());
			system("pause");
		}

		system("cls");
	}

	/*arbol->insert(5);
	arbol->insert(6);
	arbol->insert(7);
	arbol->insert(1);
	arbol->insert(2);
	arbol->insert(9);
	//cout << endl;
	arbol->Print(arbol->returnRoot());
	cout << endl;
	//arbol->PrintLevels();
	cout << endl;
	cout << "getroot" << arbol->returnRoot()->value;
	cout << endl;
	cout << endl;
	cout << endl;*/


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
