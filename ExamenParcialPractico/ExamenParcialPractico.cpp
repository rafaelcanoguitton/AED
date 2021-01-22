// ExamenParcialPractico.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;
template<class T>
class nodo {
public:
	T dato = 0;
	nodo *next = nullptr;
	nodo *sublist = nullptr;
	nodo(T a = 0) {
		dato = a;
	}
};
template<class T>
class lista {
public:
	nodo<T> *head = nullptr;
	////////////////////////////////////////////////////////
	bool buscar(T d, nodo<T>*&p) {
		bool been_inserted = 0;
		bool did_the_thing = 0;
		for (p = head;p->next != head ;p = p->next)
		{
			did_the_thing = 1;
			bool stop = 0;
			if ((d%p->dato) == 0) {
				been_inserted = 1;
				nodo<T>*temperino = 0;
				if (p->sublist == NULL)
				{
					p->sublist = new nodo<T>(d);
				}
				else
				{
					temperino = p;
				}
				while (temperino&&(!stop))
				{
					if (temperino->dato > d)
					{
						nodo<T> *temp = new nodo<T>(d);
						temp->sublist = temperino;
						temperino->sublist = temp;
						stop = 1;

					}
					if (temperino->sublist == NULL) {
						nodo<T> *temp = new nodo<T>(d);
						temperino->sublist = temp;
						stop = 1;
					}
					temperino = temperino->sublist;
				}
			}
			if (p->dato%d == 0)
			{
				been_inserted = 1;
				nodo<T> *c = new nodo<T>(d);
				c->next = p->next;
				c->sublist = p;
				p->next = NULL;
				return 0;
			}

		}

		
		if (did_the_thing == 0)
		{
			p = head;
			bool stop = 0;
			if ((d%p->dato) == 0) {
				been_inserted = 1;
				nodo<T>*temperino = 0;
				if (p->sublist == NULL)
				{
					p->sublist = new nodo<T>(d);
				}
				else
				{
					temperino = p;
				}
				while (temperino&&(!stop))
				{
					if (temperino->dato > d)
					{
						nodo<T> *temp = new nodo<T>(d);
						temp->sublist = temperino;
						temperino->sublist = temp;
						stop = 1;

					}
					if (temperino->sublist == NULL) {
						nodo<T> *temp = new nodo<T>(d);
						temperino->sublist = temp;
						stop = 1;
					}
					temperino = temperino->sublist;
				}
			}
			if (p->dato%d == 0)
			{
				been_inserted = 1;
				nodo<T> *c = new nodo<T>(d);
				c->next = p->next;
				c->sublist = p;
				p->next = NULL;
				return 0;
			}
		}


	//return p->next && p->dato == d;
	return p->dato == d || been_inserted;

	}



	bool agregar(T d) {
		if (head == nullptr) {
			head = new nodo<T>(d);
			head->next = head;
			return true;
		}
		if (d < head->dato) {
			nodo<T> *p;
			for (p = head;p->next != head;p = p->next);
			nodo<T> *temp = new nodo<T>(d);
			temp->next = head;
			head = temp;
			p->next = temp;
			return true;
		}
		nodo<T>*p;
		if (buscar(d, p)) { return 0; }
		nodo<T> *temp = new nodo<T>(d);
		temp->next = p->next;
		p->next = temp;
		return true;
	}
	///////////////////////////////////////////////////////////////////////////////
	bool borrar(T d) {
		nodo<T>*temp = head;
		if (head->next == head) {
			delete head;
			head = nullptr;
			return true;
		}
		if (head->dato == d) {
			nodo<T>*temp1 = temp->next;
			nodo<T> *p;
			for (p = head;p->next != head;p = p->next);
			p->next = temp1;
			delete temp;
			head = temp1;
			return true;
		}
		while (temp->next && (temp->next->dato != d)) {
			temp = temp->next;
		}
		if (!temp->next) {
			return 0;
		}
		nodo<T>*temp1 = temp->next;
		temp->next = temp1->next;
		delete temp1;
		return true;
	}
	/*void Balance() {
		//CHECK WITH EVERY OTHER SUBLIST NODE FROM MAIN NODES SO BALANCE FIrST
		nodo<T>*l = head;
		nodo<T>*z = head->sublist;
		vector <T> h;
		bool xd=1;
		while (l != head|| xd)
		{
			xd = 0;
			while (z != NULL)
			{
				h.push_back(z->dato);
				z = z->sublist;
			}
			l = l->next;
			z = l->sublist;
		}
		l = head;xd = 1;
		while (l != head || xd)
			xd = 0;
			{
				for (int i = 0;i < h.size();i++)
				{
					bool stop = 0;
					if ((h[i]%l->dato) == 0) {
						nodo<T>*temperino = 0;
						if (l->sublist == NULL)
						{
							l->sublist = new nodo<T>(h[i]);
						}
						else
						{
							temperino = l;
						}
						while (temperino && (!stop))
						{
							cout << "acasesalsd" << endl;
							if (temperino->dato > h[i])
							{
								nodo<T> *temp = new nodo<T>(h[i]);
								temp->sublist = temperino;
								temperino->sublist = temp;
								stop = 1;

							}
							if (temperino->sublist == NULL) {
								nodo<T> *temp = new nodo<T>(h[i]);
								temperino->sublist = temp;
								stop = 1;
							}
							temperino = temperino->sublist;
						}
					}
					if (l->dato%h[i] == 0)
					{
						nodo<T> *c = new nodo<T>(h[i]);
						c->next = l->next;
						c->sublist = l;
						l->next = NULL;
					}
				}
				l = l->next;
			}
	}*/
	///////////////////////////////////////////////////////////////////////////////
	bool imprimir() {
		
		//Balance();
		cout << "Lista Principal: " << endl;
		if (head == nullptr) {
			cout << "esta vacia" << endl;
			return false;
		}
		nodo<T>*p = head;
		while (p->next != head) {
			cout << p->dato << "->";
			p = p->next;
		}
		cout << p->dato << endl;
		cout << "Listas individuales: " << endl;
		p = head;
		nodo<T>*q = 0;
		while (p->next != head) {
			q = p;
			while (q != NULL){
				cout << q->dato << "->";
			q = q->sublist;
		}
			cout << endl;
			p = p->next;
		}
		q = p;
		while (q!= NULL) {
			cout << q->dato << "->";
			q = q->sublist;
		}
		return true;
	}
};
int main()
{

	lista<int> a;
	int x;
	cout << "Ingrese sus numeros, para ya no agregar mas ingrese 1 como input" << endl;
	cin >> x;
	for (int i = 0;i != 1;i=x)
	{
		
		a.agregar(x);
		cin >> x;
	}
	/*a.agregar(2);
	a.agregar(3);
	a.agregar(4);
	//a.agregar(8);
	a.agregar(12);
	a.agregar(16);
	a.agregar(18);
	a.agregar(7);
	a.agregar(21);
	//a.Balance();*/
	a.imprimir();

	return 0;
}