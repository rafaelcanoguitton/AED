// Matriz Esparza.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;

template<typename T>
class nodo_smx {
public:
	T m_data;
	int x_data, y_data;
	nodo_smx<T>* next;
	nodo_smx<T>* down;

	nodo_smx(T info, int x, int y) {
		this->m_data = info;
		this->x_data = x;
		this->y_data = y;
		next = down = NULL;
	}
};

template<typename M>
class nodo_temp {
public:
	typedef typename M::Tt T;
	T info;
	int x_, y_;
	M* matrix;

	nodo_temp(T info, int x, int y, M* ma) {
		this->info = info;
		this->x_ = x;
		this->y_ = y;
		matrix = ma;
	}
	operator T();
	nodo_temp<M>& operator =(T dato) {
		cout << "dato:" << dato;
		cout << "\t" << info << " (" << x_ << " , " << y_ << ")" << endl;
		if (dato == matrix->var_nul) {
			matrix->eliminar(x_, y_);
		}
		else {
			matrix->insertar(x_, y_, dato);
		}
		return *this;
	}

	nodo_temp<M>& operator =(nodo_temp<M> dato) {
		cout << "dato:" << dato;
		cout << "\t" << info << " (" << x_ << " , " << y_ << ")" << endl;
		if (dato == matrix->var_nul) {
			matrix->eliminar(x_, y_);
		}
		else {
			matrix->insertar(x_, y_, dato);
		}
		return *this;
	}
};

template<typename M>
nodo_temp<M>::operator T() {
	return info;
}


template <class T, int filas, int columnas, T nulo_char >
class Csparsa {
public:

	typedef Csparsa<T, filas, columnas, nulo_char> self;
	typedef T  Tt;

	T var_nul = nulo_char;

	nodo_smx<T>* x_[filas];
	nodo_smx<T>* y_[columnas];

	Csparsa() {
		for (int i = 0; i < filas; i++) {
			x_[i] = 0;
		}
		for (int i = 0; i < columnas; i++) {
			y_[i] = 0;
		}
	}


	bool insertar(int i, int j, T dato);
	bool eliminar(int i, int j);
	void debug_fila(nodo_smx<T>* cent);
	bool find_x(int i, int j, nodo_smx<T>**& p);
	bool find_y(int i, int j, nodo_smx<T>**& p);
	void print_matrix_x();
	void print_matrix_y();
	nodo_temp<self> operator()(int i, int j);

};



template <class T, int filas, int columnas, T nulo_char>
inline bool Csparsa<T, filas, columnas, nulo_char > ::insertar(int i, int j, T dato) { // Probar enviar en ptr al pseudonodo
	nodo_smx<T>** ptr;
	//cout<<"dato in:"<<dato<<endl;
	if (i >= 0 && i < filas && j >= 0 && j < columnas) {
		if (find_x(i, j, ptr)) { //si lo encuentra, ya existe, entonces cambio su valor
			if (dato == nulo_char) {
				eliminar(i, j);
			}
			else {
				(*ptr)->m_data = dato;
				return 1;
			}

			return 0;
		}
		else {
			nodo_smx<T>* tmp = new nodo_smx<T>(dato, i, j);
			tmp->down = *ptr;
			*ptr = tmp;

			find_y(i, j, ptr);
			tmp->next = *ptr;
			*ptr = tmp;

			return 1;
		}
	}
	else {
		cout << "\nout of range\n";

		return 0;
	}

}

template <class T, int filas, int columnas, T nulo_char>
inline bool Csparsa<T, filas, columnas, nulo_char > ::eliminar(int i, int j) {
	nodo_smx<T>** ptrY;
	nodo_smx<T>** ptrX;
	if (!find_y(i, j, ptrY))
	{
		return 0;
	}

	find_x(i, j, ptrX);
	nodo_smx<T>* tmpY = (*ptrY)->down;
	nodo_smx<T>* tmpX = (*ptrX)->next;
	delete* ptrY;
	*ptrY = tmpY;
	*ptrX = tmpX;
	//cout<<"s";
	return true;
}

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::debug_fila(nodo_smx<T>* cent) {
	while (cent) {
		cout << cent->m_data;
		cout << "-> ";
		cent = cent->next;
	}
}

template <class T, int filas, int columnas, T nulo_char >
inline bool Csparsa<T, filas, columnas, nulo_char> ::find_x(int i, int j, nodo_smx<T>**& p) {
	p = &(x_[i]);
	while (*p && (*p)->y_data < j) {
		p = &((*p)->next);
	}
	return *p && (*p)->y_data == j;
}

template <class T, int filas, int columnas, T nulo_char >
inline bool Csparsa<T, filas, columnas, nulo_char> ::find_y(int i, int j, nodo_smx<T>**& p) {
	p = &(y_[j]);
	while (*p && (*p)->x_data < i) {
		p = &((*p)->down);
	}
	return *p && (*p)->x_data == i;
}

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::print_matrix_x() {
	cout << "\n";
	for (int i = 0; i < filas; i++) {
		cout << "\t";
		//cout<<i;
		//debug_fila(x_[i]);
		int cont = 0;
		nodo_smx<T>* q = x_[i];
		while (q) {
			while (q->y_data > cont) {
				cout << nulo_char << " ";
				cont++;
			}
			cout << q->m_data << " ";
			q = q->next;
			cont++;
		}
		while (columnas - cont > 0) {
			cout << nulo_char << " ";
			cont++;
		}
		cout << "\n";
	}
	cout << "\n";
}

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::print_matrix_y() {
	for (int i = 0; i < columnas; i++) {
		int cont = 0;
		nodo_smx<T>* q = y_[i];
		while (q) {
			while (q->x_data > cont) {
				cout << nulo_char << " ";
				cont++;
			}
			cout << q->m_data << " ";
			q = q->down;
			cont++;
		}
		while (filas - cont > 0) {
			cout << nulo_char << " ";
			cont++;
		}
		cout << "\n";
	}
}


template <class T, int filas, int columnas, T nulo_char>
nodo_temp<Csparsa<T, filas, columnas, nulo_char >> Csparsa<T, filas, columnas, nulo_char > :: operator()(int i, int j) {
	nodo_smx<T>** p;
	T f;
	if (find_x(i, j, p)) {
		f = (*p)->m_data;
	}
	else {
		f = nulo_char;
	}
	return nodo_temp<self>(f, i, j, this);
}


int main() {

	Csparsa<int, 4, 6, 0> The;

	cout << "\nMatriz A \n";
	The.print_matrix_x();//matrix vacia

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			The.insertar(i, j, i + 1);
		}
	}

	The.insertar(0, 0, 0);
	The.print_matrix_x();

	cout << "THE[2][2]    : " << The(2, 2) << endl;//it WORKS
	int gg;
	gg = The(2, 2);//it WORKS
	cout << "THE[2][2] +2 : " << gg + 2;
	gg = The(2, 8);//it WORKS
	cout << "\nTHE[2][8]    :" << gg << " out of range\n";
	cout << "THE[2][2]    : " << The(2, 2) << endl;//it WORKS


	for (int i = 0; i < 4; i++) {
		The.eliminar(i, 3);
	}
	cout << "\n";
	The.print_matrix_x(); cout << "\n";
	cout << "\n y la traspuesta; xD\n";
	The.print_matrix_y();//la traspuesta

	The.insertar(1, 3, '+');
	The.print_matrix_x(); cout << "\n";

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
