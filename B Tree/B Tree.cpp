// B Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include "pch.h"
#include <iostream>

using namespace std;

template<class T>
struct asc {
	T operator()(T a, T b) {
		return a < b;
	}
};

template<class T>
struct des {
	T operator()(T a, T b) {
		return a > b;
	}
};

template<class B, int t>
struct node {
	typedef typename B::T T;
	typedef typename B::node Node;

	T ar[t];
	Node* ptr[t + 1];
	Node* p;
	node() {
		for (int i = 0; i < t; i++)
			ar[i] = -1;
		for (int i = 0; i < t + 1; i++)
			ptr[i] = nullptr;
		p = nullptr;
	}
};

template<class B, class ord, int N>
struct BTree {
	B a;
	ord orden;
	typedef typename B::node Node;                  //los nodos contienen un arreglo de los objX que son los objetos que gardan el valor
	typedef typename B::O O;
	typedef typename B::T T;
	O t = a.t;

	Node* root = nullptr;

	bool find(T v, Node** &ptr, int &i) {
		ptr = &root;
		while (*ptr) {         //busca en los nodos
			i = 0;

			while ((*ptr)->ar[i] >= 0 && orden((*ptr)->ar[i], v) && i < t) {  //verifica si v es mayor que los valores ya colocados
				i++;
			}
			if ((*ptr)->ar[i] == v)                          //si se encuentra un valor igual, significa que ya lo encontró
				return 1;

			if (i <= t && !(*ptr)->ptr[i]) {
				return 0;
			}

			else if (i <= t && (*ptr)->ptr[i]) {
				ptr = &((*ptr)->ptr[i]);
			}

			/*else if (!(*ptr)->ptr[i] && i==t && (*ptr)->ar[t-1]>=0) {
				ptr = &((*ptr)->p);
				return 0;
			}*/
			/*else if (i  t && (*ptr)->ptr[i]) {
				ptr = &((*ptr)->ptr[i]);
			}*/
		}
		return 0;                                         //si los punteros son nulos es porque ya no se pudo encontrar el valor v
	}
	bool insert(T v) {
		Node** ptr;
		int i = 0;;
		if (find(v, ptr, i))
			return 0;
		if (!*ptr) {
			Node *nn = new Node;
			*ptr = nn;
			(*ptr)->ar[i] = v;
		}
		else if (*ptr && (*ptr)->ar[i] < 0) {
			(*ptr)->ar[i] = v;
		}
		else if (*ptr && (*ptr)->ar[i] >= 0 && (*ptr)->ar[t - 1] < 0) {  // pregunta si esta lleno el nodo, y si la posición esta ocupada
			for (int tmp = 0; tmp < (t - i - 1); tmp++) {
				(*ptr)->ar[t - 1 - tmp] = (*ptr)->ar[t - 2 - tmp];
			}
			(*ptr)->ar[i] = v;
		}

		else if (*ptr && (*ptr)->ar[i] >= 0 && (*ptr)->ar[t - 1] >= 0) {
			T ar1[N];
			ar1[i] = v;
			for (int tm = 0; tm < i; tm++)
				ar1[tm] = (*ptr)->ar[tm];
			for (int tm = i + 1; tm < N; tm++)
				ar1[tm] = (*ptr)->ar[tm - 1];

			int m = t / 2;

			if ((*ptr)->p == nullptr) {
				Node *nn1 = new Node;
				nn1->ar[0] = ar1[m];
				(*ptr)->p = nn1;
				nn1->ptr[1] = *ptr;
				for (int tm = 0; tm < t; tm++)
					(*ptr)->ar[tm] = -1;
				for (int tm = m + 1, tm2 = m + 1; tm < N; tm++)
					(*ptr)->ar[tm - tm2] = ar1[tm];
				*ptr = nn1;
				Node *nn2 = new Node;
				nn2->p = *ptr;
				(*ptr)->ptr[0] = nn2;
				ptr = &nn2;
				for (int tm = 0; tm < m; tm++)
					(*ptr)->ar[tm] = ar1[tm];
			}
			else {
				Node *nn1 = new Node;

			}

			//nn1->ar[0]=(*ptr)->ar[m];

		}
		return 1;
	}
};

template<class T, class O, O N>
struct bidoof {                               // bidoof es mi caja de herramientas
	typedef typename bidoof<T, O, N> B;
	typedef typename node<B, N> node;
	typedef typename O O;
	typedef typename T T;
	O t = N;
};

int main()
{
	BTree<bidoof<int, int, 4>, asc<int>, 5> a;
	a.insert(1);
	a.insert(8);
	a.insert(3);
	a.insert(2);
	a.insert(5);
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
