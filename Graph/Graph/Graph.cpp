// Graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
//#include <list>
#include <vector>
#include <stdio.h>
#include <math.h>

using namespace std;

template<class G>
class Nodo
{
public:
	typedef typename G::N N;
	typedef typename G::Arista Arista;
	N n_v;
	int id;
	vector<Arista*> aristas;
	Nodo(N valor) { n_v = valor; }
};

template<class G>
class Arista
{
public:
	typedef typename G::E E;
	typedef typename G::Nodo Nodo;
	E m_v;
	Nodo* m_nodos[2];
	bool m_dir;
	Arista(E valor) { m_v = valor; }
};

template <class G>
class Cam {
public:
	typedef typename G::Nodo Nodo;
	typedef typename G::E E;
	vector<Nodo*> nodos_recorrido;
	E peso_actual;
	Cam(Nodo* actual) { nodos_recorrido.push_back(actual); peso_actual = 0; };
	void imprimir() {
		int i;
		for (i = 0; i < nodos_recorrido.size() - 1; i++) {
			cout << nodos_recorrido[i]->n_v << "---->";
		}
		cout << nodos_recorrido[i]->n_v << " " << peso_actual << endl;
	};
};

template<class N, class E>
class Graf
{
public:
	typedef Graf<N, E> G;
	typedef Nodo<G> Nodo;
	typedef Arista<G> Arista;
	//typedef Cam<G> Recorrido; doble def this not needed
	typedef N N;
	typedef E E;
	bitset<>
	vector<Nodo*> g_node;
	bool buscar_nodo(N dato, int& pos) {
		for (int i = 0; i < g_node.size(); i++) {
			if (g_node[i]->n_v == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	bool buscar_arista(E dato, int indice, int& pos) {
		for (int i = 0; i < g_node[indice]->aristas.size(); i++) {
			if (g_node[indice]->aristas[i]->m_v == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	bool search_arista(E dato, int indice) {
		for (int i = 0; i < g_node[indice]->aristas.size(); i++) {
			if (g_node[indice]->aristas[i]->m_v == dato) {
				return 1;
			}
		}
		return 0;
	}
	bool insertNode(N dato) {
		int pos;
		if (buscar_nodo(dato, pos)) return 0;
		Nodo* nuevo = new Nodo(dato);
		nuevo->id = g_node.size();
		g_node.push_back(nuevo);
		return 1;
	}
	bool insertArista(N nodo1, N nodo2, E dato, bool direccion) {
		int actual1, actual2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (search_arista(dato, actual1) && search_arista(dato, actual2)) return 0;//no comtempla aristas de iguales nodos
		if (direccion) {
			Arista* nuevo = new Arista(dato);
			nuevo->m_dir = direccion;
			nuevo->m_nodos[0] = g_node[actual1];
			nuevo->m_nodos[1] = g_node[actual2];
			g_node[actual1]->aristas.push_back(nuevo);
			g_node[actual2]->aristas.push_back(nuevo);
			return 1;
		}
		direccion = true;
		Arista* nuevo = new Arista(dato);
		Arista* nuevo1 = new Arista(dato);
		nuevo->m_dir = direccion;
		nuevo1->m_dir = direccion;
		nuevo->m_nodos[0] = g_node[actual1];
		nuevo->m_nodos[1] = g_node[actual2];
		nuevo1->m_nodos[0] = g_node[actual2];
		nuevo1->m_nodos[1] = g_node[actual1];
		g_node[actual1]->aristas.push_back(nuevo);
		/*m_node[actual2]->m_edges.push_back(nuevo);
		m_node[actual1]->m_edges.push_back(nuevo1);*/
		g_node[actual2]->aristas.push_back(nuevo1);
		return 1;
	}
	bool removeEdge(N nodo1, N nodo2, E dato) {
		int actual1, actual2, pos1, pos2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (!(buscar_arista(dato, actual1, pos1) && buscar_arista(dato, actual2, pos2))) return 0;
		g_node[actual1]->aristas.erase(g_node[actual1]->aristas.begin() + pos1);
		g_node[actual2]->aristas.erase(g_node[actual2]->aristas.begin() + pos2);
		return 1;
	}
	bool deleteNode(N dato) {
		int actual;
		if (!buscar_nodo(dato, actual)) return 0;
		for (int i = 0; i < g_node[actual]->aristas.size(); i++) {
			removeEdge(g_node[actual]->aristas[i]->m_nodos[0]->n_v, g_node[actual]->aristas[i]->m_nodos[1]->n_v, g_node[actual]->aristas[i]->m_v);
		}
		g_node.erase(g_node.begin() + actual);
		return 1;
	}
	void imprimir_nodos() {
		for (int i = 0; i < g_node.size(); i++) {
			cout << g_node[i]->n_v << " " << g_node[i]->id << endl;
		}
	}
	bool pos_node(Arista* arista, Nodo* actual) {
		if (arista->m_nodos[0]->n_v == actual->n_v) return 0;
		return 1;
	}
	void imprimir_aristas() {
		for (int i = 0; i < g_node.size(); i++) {
			for (int j = 0; j < g_node[i]->aristas.size(); j++) {
				if (!(pos_node(g_node[i]->aristas[j], g_node[i]))) {
					cout << g_node[i]->aristas[j]->m_v << ": " << g_node[i]->aristas[j]->m_nodos[0]->n_v << " " << g_node[i]->aristas[j]->m_nodos[1]->n_v << endl;
				}
			}
		}
	}
};

class Coord {
public:
	int n1;
	int n2;
	Coord(int a, int b) { n1 = a; n2 = b; }
};

class GrafCoord : public Graf<Coord, int> {
public:
	typedef typename G::Nodo Nodo;
	int distanciaEuclid(Nodo nano, Nodo norm) {
		int res = 0;
		int temp = (nano.n_v.n1) - (norm.n_v.n1);
		temp = temp * temp;
		int temp2 = (nano.n_v.n2) - (norm.n_v.n2);
		temp2 = temp2 * temp2;
		res = temp + temp2;
		res = sqrt(res);
		return res;
	}
};

class GrafChar : public Graf<char, int> {
public:
	typedef Cam<G> Recorrido;
	Recorrido camino(vector<Recorrido> lerute, Nodo* actual) {
		for (int i = 0; i < lerute.size(); i++) {
			if (lerute[i].nodos_recorrido[lerute[i].nodos_recorrido.size() - 1]->n_v == actual->n_v) return lerute[i];
		}
		return Recorrido(actual);
	}
	bool bus_rec(Recorrido r, Nodo* n) {
		for (int i = 0; i < r.nodos_recorrido.size(); i++) {
			if (r.nodos_recorrido[i]->n_v == n->n_v) {
				return 1;
			}
		}
		return 0;
	}
	void nivelar(vector<Recorrido>& res) {
		bool rpta = true;
		while (rpta) {
			rpta = false;
			for (int i = 0; i < res.size(); i++) {
				for (int j = i + 1; j < res.size(); j++) {
					if (res[i].nodos_recorrido[0] == res[j].nodos_recorrido[0] && res[i].nodos_recorrido[res[i].nodos_recorrido.size() - 1] == res[j].nodos_recorrido[res[j].nodos_recorrido.size() - 1]) {
						if (res[i].peso_actual < res[j].peso_actual) {
							res.erase(res.begin() + j);
						}
						else {
							res.erase(res.begin() + i);
						}
						rpta = true;
					}
				}
			}
		}
	}
	void busqueda(vector<Recorrido>& res, Nodo* n, Arista* arista) {
		Recorrido act = camino(res, arista->m_nodos[0]);
		act.nodos_recorrido.push_back(arista->m_nodos[1]);
		act.peso_actual += arista->m_v;
		res.push_back(act);
		for (int i = 0; i < n->aristas.size(); i++) {
			if (!(pos_node(n->aristas[i], n))) {
				if (!bus_rec(act, n->aristas[i]->m_nodos[1])) {
					nivelar(res);
					busqueda(res, n->aristas[i]->m_nodos[1], n->aristas[i]);
				}
			}
		}
	}
	vector<Recorrido> Dikjstra(N nombre) {
		vector<Recorrido> resultado;
		int pos;
		if (buscar_nodo(nombre, pos)) {
			Recorrido actual(g_node[pos]);
			resultado.push_back(actual);
			for (int i = 0; i < g_node[pos]->aristas.size(); i++) {
				if (!(pos_node(g_node[pos]->aristas[i], g_node[pos]))) {
					busqueda(resultado, g_node[pos]->aristas[i]->m_nodos[1], g_node[pos]->aristas[i]);
				}
			}
		}
		nivelar(resultado);
		imp_vec(resultado);
		return resultado;
	}
	void imp_vec(vector<Recorrido> res) {
		for (int i = 0; i < res.size(); i++) {
			res[i].imprimir();
		}
		cout << endl;
	}
	void cam_mas_corto(N nodo1, N nodo2) {
		vector<Recorrido> rpta = Dikjstra(g_node[0]->n_v);

	}
	void cam_menos_nodos(N nodo1, N nodo2) {
		vector < Recorrido> rpta
	}
};


int main()
{
	GrafChar Final2;
	Final2.insertNode('0');
	Final2.insertNode('1');
	Final2.insertNode('2');
	Final2.insertNode('3');
	Final2.insertNode('4');
	Final2.insertNode('5');
	Final2.insertNode('6');
	Final2.insertNode('7');
	Final2.insertNode('8');
	Final2.insertNode('9');
	Final2.insertNode('10');
	Final2.insertNode('11');
	Final2.insertNode('12');
	Final2.insertNode('13');
	Final2.insertNode('14');
	Final2.insertNode('15');
	Final2.insertNode('16');
	Final2.insertNode('17');
	Final2.insertNode('18');
	Final2.insertNode('19');
	Final2.insertNode('20');
	cout << endl;
	Final2.insertArista('0', '1', 1, 0);
	Final2.insertArista('0', '2', 1, 0);
	Final2.insertArista('0', '3', 1, 0);
	Final2.insertArista('1', '4', 1, 0);
	Final2.insertArista('4', '7', 1, 0);
	Final2.insertArista('7', '10', 1, 0);
	Final2.insertArista('10', '14', 1, 0);
	Final2.insertArista('14', '20', 1, 0);
	Final2.insertArista('2', '5', 1, 0);
	Final2.insertArista('8', '11', 1, 0);
	Final2.insertArista('11', '7', 1, 0);
	Final2.insertArista('8', '12', 1, 0);
	Final2.insertArista('12', '16', 1, 0);
	Final2.insertArista('16', '17', 1, 0);
	Final2.insertArista('16', '19', 1, 0);
	Final2.insertArista('19', '10', 1, 0);
	Final2.insertArista('10', '15', 1, 0);
	Final2.insertArista('3', '6', 1, 0);
	Final2.insertArista('6', '9', 1, 0);
	Final2.insertArista('9', '13', 1, 0);
	Final2.insertArista('13', '17', 1, 0);
	Final2.insertArista('17', '15', 1, 0);
	Final2.insertArista('15', '18', 1, 0);
	Final2.insertArista('18', '20', 1, 0);

	Final2.insertArista('0', '1', 1, 1);
	Final2.insertArista('0', '2', 1, 1);
	Final2.insertArista('0', '3', 1, 1);
	Final2.insertArista('1', '4', 1, 1);
	Final2.insertArista('4', '7', 1, 1);
	Final2.insertArista('7', '10', 1,1);
	Final2.insertArista('10', '14', 1,1);
	Final2.insertArista('14', '20', 1, 1);
	Final2.insertArista('2', '5', 1, 1);
	Final2.insertArista('8', '11', 1, 1);
	Final2.insertArista('11', '7', 1, 1);
	Final2.insertArista('8', '12', 1, 1);
	Final2.insertArista('12', '16', 1, 1);
	Final2.insertArista('16', '17', 1, 1);
	Final2.insertArista('16', '19', 1, 1);
	Final2.insertArista('19', '10', 1, 1);
	Final2.insertArista('10', '15', 1, 1);
	Final2.insertArista('3', '6', 1, 1);
	Final2.insertArista('6', '9', 1, 1);
	Final2.insertArista('9', '13', 1, 1);
	Final2.insertArista('13', '17', 1, 1);
	Final2.insertArista('17', '15', 1, 1);
	Final2.insertArista('15', '18', 1, 1);
	Final2.insertArista('18', '20', 1, 1);


	cout << endl;
	cout << "Hello World!\n";
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
