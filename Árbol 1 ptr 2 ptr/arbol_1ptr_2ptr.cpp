// arbol_1ptr_2ptr.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <stack>

using namespace std;

//Clase menor
template <class T>
class menor 
{
public:
	inline bool operator()(T x, T y) 
	{
		return x < y;
	}
};

//Clase mayor
template <class T>
class mayor 
{
public:
	inline bool operator()(T x, T y) 
	{ 
		return x > y;
	}
};

template <class T>
class Node 
{
public:
	Node(T x) 
	{ 
		data = x; 
		nodes[0] = nodes[1] = nullptr; 
	}

	T data;
	Node* nodes[2];
};

template <class T, class C>
class SimpleBinTree 
{
public:
	SimpleBinTree() 
	{
		root = 0;
	}
	bool find(T x, Node<T>*&p, Node<T>*&prev);
	bool insert(T x);
	bool erase(T x);
	void eraseP(Node<T>*&node);
	void print(Node<T>*p, int level);
	void inOrder();
	void verticalOrder();
	void printVerticalLine(Node<T>*, int, int);
	void findMinMax(Node<T>*, int*, int*, int);
	//Elementos
	Node<T>*root;
	C cmp; //Functor
};

template <class T, class C>
bool SimpleBinTree<T, C>::find(T x, Node<T>*&p, Node<T>*&prev) {
	p = root;
	while (p) 
	{
		prev = p;
		if (x == p->data) 
			return 1;
		p = p->nodes[!cmp(x, p->data)];
	}
	return 0;
}

template <class T, class C>
bool SimpleBinTree<T, C>::insert(T x) 
{
	Node<T>*p, *prev;
	if (find(x, p, prev)) 
		return 0;
	if (!root) 
		root = new Node<T>(x); //root
	else
		prev->nodes[!cmp(x, prev->data)] = new Node<T>(x);
	return 1;
}

template <class T, class C>
void SimpleBinTree<T, C>::eraseP(Node<T>*&node) 
{
	Node<T> *prev, *tmp = node;

	if(node->nodes[0] && node->nodes[1])
	{
		tmp = node->nodes[0];
		prev = node;
		while (tmp->nodes[1] != 0) 
		{
			prev = tmp;
			tmp = tmp->nodes[1];
		}
		node->data = tmp->data;
		prev->nodes[!(prev == node)] = tmp->nodes[0];
	}
	else
		node = node->nodes[!!node->nodes[1]];
	//cout << node << endl;
	delete tmp;
}


template <class T, class C>
bool SimpleBinTree<T, C>::erase(T x) 
{
	Node<T> *node, *prev;
	if (!find(x, node, prev)) 
		return 0;
	eraseP(node);
	//cout << prev->nodes[0] << endl;
	return 1;
}

template <class T, class C>
void SimpleBinTree<T, C>::print(Node<T>* p, int level) 
{
	if (!p) 
		return;
	print(p->nodes[1], level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "\t";
	std::cout << p->data << std::endl;
	print(p->nodes[0], level + 1);
}
//
//template <class T, class C>
//void SimpleBinTree<T, C>::findMinMax(Node<T> *node, int *min, int *max, int hd)
//{
//	// Base case 
//	if (node == NULL) return;
//
//	// Update min and max 
//	if (hd < *min)  *min = hd;
//	else if (hd > *max) *max = hd;
//
//	// Recur for nodes[0] and nodes[1] subtrees 
//	findMinMax(node->nodes[0], min, max, hd - 1);
//	findMinMax(node->nodes[1], min, max, hd + 1);
//}
//
//template <class T, class C>
//void SimpleBinTree<T, C>::printVerticalLine(Node<T>* node, int line_no, int hd)
//{
//	// Base case 
//	if (node == NULL) return;
//
//	// If this node is on the given line number 
//	if (hd == line_no)
//		cout << node->data << " ";
//
//	// Recur for nodes[0] and nodes[1] subtrees 
//	printVerticalLine(node->nodes[0], line_no, hd - 1);
//	printVerticalLine(node->nodes[1], line_no, hd + 1);
//}
//
//template <class T, class C>
//void SimpleBinTree<T, C>::verticalOrder()
//{
//	// Find min and max distances with resepect to root 
//	int min = 0, max = 0;
//	findMinMax(root, &min, &max, 0);
//
//	// Iterate through all possible vertical lines starting 
//	// from the nodes[0]most line and print nodes line by line 
//	for (int line_no = min; line_no <= max; line_no++)
//	{
//		printVerticalLine(root, line_no, 0);
//		cout << endl;
//	}
//}

//// ///////////////////////////////////////
template <class T, class C>
class BinTree 
{
public:
	BinTree() 
	{
		root = 0;
	}
	bool find(T x, Node<T>**&p);
	bool insert(T x);
	bool erase(T x);
	void print(Node<T>*p, int level);
	void rep(Node<T>**&q);
	void inOrder();
	//Elementos
	C cmp; //Function Object
	Node<T>* root;
};

template <class T, class C>
bool BinTree<T, C>::find(T x, Node<T>**&p) 
{
	for (
			p = &root;
			*p && (*p)->data != x;
			p = &((*p)->nodes[cmp((*p)->data, x)])
		);
	return !!(*p);
}

template <class T, class C>
bool BinTree<T, C>::insert(T x) 
{
	Node<T>**p;
	if (find(x, p)) 
		return 0;
	*p = new Node<T>(x);
	return 1;
}

template<class T, class C>
void BinTree<T, C>::rep(Node<T> **&q) 
{
	srand(time(NULL));
	int num = rand() % 2;
	//int num = 1;
	if (num) 
	{
		q = &((*q)->nodes[1]);
		while ((*q)->nodes[0]) q = &((*q)->nodes[0]);
	}
	else 
	{
		q = &((*q)->nodes[0]);
		while ((*q)->nodes[1])q = &((*q)->nodes[1]);
	}
}

template<class T, class C>
bool BinTree<T, C>::erase(T x) 
{
	Node<T> **p;
	if (!find(x, p)) 
		return 0;
	//CASO 2
	if ((*p)->nodes[0] && (*p)->nodes[1]) 
	{
		Node<T>**q = p;
		rep(q);
		(*p)->data = (*q)->data;
		p = q;
	}
	//CASO 0,1
	Node<T> *t = *p;
	*p = (*p)->nodes[!(*p)->nodes[0]];
	delete t;
	//std::cout << t->data << std::endl;
	/*if ((*p)->nodes[1]) 
		*p = (*p)->nodes[1];
	else  
		*p = (*p)->nodes[0];*/

	return 1;
}

template <class T, class C>
void BinTree<T, C>::print(Node<T>*p, int level) 
{
	if (!p) 
		return;
	print(p->nodes[1], level + 1);
	for (int i = 0; i < level; i++)
		cout << "\t";
	cout << p->data << endl;
	print(p->nodes[0], level + 1);
}

/////////////////////////////////////////////////////////////////}
template <class T>
class T_Node
{
public:
	T_Node(T x)
	{
		data = x;
		nodes[0] = nodes[1] = nodes[2] = nullptr;
	}

	T data;
	T_Node* nodes[3];
};

template <class T, class C>
class T_BinTree
{
public:
	T_BinTree()
	{
		root = nullptr;
	}
	bool find(T x, Node<T>**&p);
	bool insert(T x);
	bool erase(T x);
	void print(Node<T>*p, int level);
	void rep(Node<T>**&q);
	void inOrder();
	//Elementos
	C cmp; //Function Object
	Node<T>* root;
};

template <class T, class C>
bool T_BinTree<T, C>::find(T x, Node<T>**&p)
{
	for (
			p = &root;
			*p && (*p)->data != x;
			p = &((*p)->nodes[cmp((*p)->data, x)])
		);
	return (*p);
}

template <class T, class C>
bool T_BinTree<T, C>::insert(T x)
{
	Node<T>** b_tmp;
	if (find(x, b_tmp))
		return 0;
	*b_tmp = new Node<T>(x);
	return 1;
}

template <class T, class C>
void T_BinTree<T, C>::print(Node<T>*p, int level)
{
	if (!p)
		return;
	print(p->nodes[1], level + 1);
	for (int i = 0; i < level; i++)
		cout << "\t";
	cout << p->data << endl;
	print(p->nodes[0], level + 1);
}


template <class T, class C>
void T_BinTree<T, C>::inOrder()
{
	stack<Node<T>*> s;
	Node<T>*curr = root;

	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			curr = curr->nodes[0];
		}
		curr = s.top();
		s.pop();

		cout << curr->data << " ";

		curr = curr->nodes[1];
	} 
}

void print_lines()
{
	cout << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << "-";
	}
	cout << endl;
}

int main()
{
	T_BinTree<int, menor<int>> arbol;
	arbol.insert(5);
	arbol.insert(1);
	arbol.insert(25);
	arbol.insert(3);
	arbol.insert(20);
	arbol.insert(15);
	arbol.insert(10);
	arbol.insert(33);
	arbol.insert(201);
	arbol.print(arbol.root, 1);
	print_lines();

	arbol.erase(25);
	arbol.inOrder();
	//arbol.verticalOrder();
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
