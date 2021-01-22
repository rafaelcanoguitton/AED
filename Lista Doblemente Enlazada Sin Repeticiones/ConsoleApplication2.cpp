// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
template<class T>
class Mayor {
public:
	inline bool operator() (T a, T b) { return a > b; }
};

template<class T>
class Menor {
public:
	inline bool operator() (T a, T b) { return a < b; }
};
template<class T>
struct C_Node {
	T C_Value;
	C_Node<T>* C_Next = NULL, *C_Prev = NULL;
	C_Node() {};
	C_Node(T dato) { C_Value = dato; C_Prev = NULL; C_Next = NULL; };
	C_Node(T dato, C_Node<T>* ant, C_Node<T>* sgt) { C_Value = dato; C_Prev = ant; C_Next = sgt; };
};
template<class T, class Op>
class C_List {
public:
	C_Node<T>* C_Head;
	Op o;
	C_List() { C_Head = NULL; };
	bool buscar(T dato, C_Node<T>*& actual);
	bool insertar(T dato);
	bool borrar(T dato);
	void print();
	~C_List() {
		C_Node<T>* p = C_Head;
		while (p)
		{
			C_Node<T>* p2 = p;
			p = p->C_Next;
			delete p2;
		}
	}
};
template<class T, class Op>
bool C_List<T, Op>::buscar(T dato, C_Node<T>*& actual) {
	actual = C_Head;
	if (C_Head->C_Value == dato) return 1;
	if(C_Head->C_Next)
		while (o(actual->C_Value, dato)) {
			if (actual->C_Next == NULL)
				return 0;
			actual = actual->C_Next;
			
		}
	return (actual->C_Value == dato);
}
template<class T, class Op>
bool C_List<T, Op>::insertar(T dato) {
	if (C_Head == NULL) {
		C_Head = new C_Node<T>(dato);
		C_Head->C_Next = NULL;
		C_Head->C_Prev = NULL;
		return 1;
	}
	if (o(dato, C_Head->C_Value)) {
		C_Node<T>* nuevo = new C_Node<T>(dato, C_Head->C_Prev, C_Head);
		C_Head->C_Prev = nuevo;
		C_Head = nuevo;
		return 1;
	}
	C_Node<T>* actual;
	if (buscar(dato, actual)) return 0;
	if (o(dato, actual->C_Value))
	{
		C_Node<T>* nuevo = new C_Node<T>(dato, actual->C_Prev, actual);
		actual->C_Prev->C_Next = nuevo;
		actual->C_Prev = nuevo;
	}
	else
	{
		C_Node<T>* nuevo = new C_Node<T>(dato, actual, actual->C_Next);
		actual->C_Next = nuevo;
	}
	return 1;
}
template<class T, class Op>
bool C_List<T, Op>::borrar(T dato) {
	C_Node<T>* actual;
	if (!buscar(dato, actual)) return 0;
	if (actual == C_Head) {
		C_Head->C_Next->C_Prev = C_Head->C_Prev;
		C_Head->C_Prev->C_Next = C_Head->C_Next;
		return 1;
	}
	C_Node<T>* temp = actual;
	actual->C_Prev->C_Next = actual->C_Next;
	actual->C_Next->C_Prev = actual->C_Prev;
	delete temp;
	return 1;

}
template<class T, class Op>
void C_List<T, Op>::print()
{
	C_Node<T>* actual=C_Head;
	while (actual)
	{
		cout << actual->C_Value << " ";
		actual = actual->C_Next;
	}
}
int main()
{
	C_List<int,Menor<int> > listita;
	cout << "Lista Doblemente Enlazada Sin Repeticiones" << endl << endl;
	string menu = "Para agregar un elemento presione 1, para eliminar un elemento presione 2, para salir presione 3";
	int x = 0;
	while (x != 3)
	{
		cout<< menu << endl; cout << "Su lista: "; listita.print(); cout << endl; cin >> x;
		if (x == 1)
		{
			int temp;
			cout << "Que elemento desea agregar?" << endl; cin >> temp; listita.insertar(temp);
		}
		if (x == 2)
		{
			int temp;
			cout << "Que elemento desea borrar?" << endl; cin >> temp; listita.borrar(temp);
		}
		system("cls");
	}
}

