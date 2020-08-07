// Dijkstra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iostream>
#include <vector>

using namespace std;

template <typename G>
struct CNode {
	typedef typename G::Edge Edge;
	typedef typename G::n N;
	N m_data;
	int id;
	vector<Edge*> m_edges;
	CNode(N valor) { m_data = valor; };
};

template <class G>
struct CEdge {
	typedef typename G::Node Node;
	typedef typename G::e E;
	Node* m_nodes[2];
	E m_data;
	bool m_dir;
	CEdge(E valor) { m_data = valor; };
};

template <class G>
struct Cam {
	typedef typename G::Node Node;
	typedef typename G::e E;
	vector<Node*> nodos_recorrido;
	E peso_actual;
	Cam(Node *actual) { nodos_recorrido.push_back(actual); peso_actual = 0; };
	void imprimir() {
		int i;
		for (i = 0; i < nodos_recorrido.size() - 1; i++) {
			cout << nodos_recorrido[i]->m_data << "---->";
		}
		cout << nodos_recorrido[i]->m_data << " " << peso_actual << endl;
	};
};

template <class N, class E>
class CGraph {
public:
	typedef CGraph<N, E> Self;
	typedef CNode<Self> Node;
	typedef CEdge<Self> Edge;
	typedef Cam<Self> Recorrido;
	typedef N n;
	typedef E e;
	vector<Node*> m_node;
	bool buscar_nodo(n dato, int &pos) {
		for (int i = 0; i < m_node.size(); i++) {
			if (m_node[i]->m_data == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	bool buscar_arista(e dato, int indice, int &pos) {
		for (int i = 0; i < m_node[indice]->m_edges.size(); i++) {
			if (m_node[indice]->m_edges[i]->m_data == dato) {
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	bool search_arista(e dato, int indice) {
		for (int i = 0; i < m_node[indice]->m_edges.size(); i++) {
			if (m_node[indice]->m_edges[i]->m_data == dato) {
				return 1;
			}
		}
		return 0;
	}
	bool insertNode(n dato) {
		int pos;
		if (buscar_nodo(dato, pos)) return 0;
		Node *nuevo = new Node(dato);
		nuevo->id = m_node.size();
		m_node.push_back(nuevo);
		return 1;
	}
	bool insertEdge(n nodo1, n nodo2, e dato, bool direccion) {
		int actual1, actual2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (search_arista(dato, actual1) && search_arista(dato, actual2)) return 0;
		if (direccion) {
			Edge *nuevo = new Edge(dato);
			nuevo->m_dir = direccion;
			nuevo->m_nodes[0] = m_node[actual1];
			nuevo->m_nodes[1] = m_node[actual2];
			m_node[actual1]->m_edges.push_back(nuevo);
			m_node[actual2]->m_edges.push_back(nuevo);
			return 1;
		}
		direccion = true;
		Edge *nuevo = new Edge(dato);
		Edge *nuevo1 = new Edge(dato);
		nuevo->m_dir = direccion;
		nuevo1->m_dir = direccion;
		nuevo->m_nodes[0] = m_node[actual1];
		nuevo->m_nodes[1] = m_node[actual2];
		nuevo1->m_nodes[0] = m_node[actual2];
		nuevo1->m_nodes[1] = m_node[actual1];
		m_node[actual1]->m_edges.push_back(nuevo);
		/*m_node[actual2]->m_edges.push_back(nuevo);
		m_node[actual1]->m_edges.push_back(nuevo1);*/
		m_node[actual2]->m_edges.push_back(nuevo1);
		return 1;
	}
	bool removeEdge(n nodo1, n nodo2, e dato) {
		int actual1, actual2, pos1, pos2;
		if (!(buscar_nodo(nodo1, actual1) && buscar_nodo(nodo2, actual2))) return 0;
		if (!(buscar_arista(dato, actual1, pos1) && buscar_arista(dato, actual2, pos2))) return 0;
		m_node[actual1]->m_edges.erase(m_node[actual1]->m_edges.begin() + pos1);
		m_node[actual2]->m_edges.erase(m_node[actual2]->m_edges.begin() + pos2);
		return 1;
	}
	bool deleteNode(n dato) {
		int actual;
		if (!buscar_nodo(dato, actual)) return 0;
		for (int i = 0; i < m_node[actual]->m_edges.size(); i++) {
			removeEdge(m_node[actual]->m_edges[i]->m_nodes[0]->m_data, m_node[actual]->m_edges[i]->m_nodes[1]->m_data, m_node[actual]->m_edges[i]->m_data);
		}
		m_node.erase(m_node.begin() + actual);
		return 1;
	}
	void imprimir_nodos() {
		for (int i = 0; i < m_node.size(); i++) {
			cout << m_node[i]->m_data << " " << m_node[i]->id << endl;
		}
	}
	void imprimir_edge() {
		for (int i = 0; i < m_node.size(); i++) {
			for (int j = 0; j < m_node[i]->m_edges.size(); j++) {
				if (!(pos_node(m_node[i]->m_edges[j], m_node[i]))) {
					cout << m_node[i]->m_edges[j]->m_data << ": " << m_node[i]->m_edges[j]->m_nodes[0]->m_data << " " << m_node[i]->m_edges[j]->m_nodes[1]->m_data << endl;
				}
			}
		}
	}
	bool pos_node(Edge *arista, Node *actual) {
		if (arista->m_nodes[0]->m_data == actual->m_data) return 0;
		return 1;
	}
	Recorrido camino(vector<Recorrido> lerute, Node *actual) {
		for (int i = 0; i < lerute.size(); i++) {
			if (lerute[i].nodos_recorrido[lerute[i].nodos_recorrido.size() - 1]->m_data == actual->m_data) return lerute[i];
		}
		return Recorrido(actual);
	}
	bool bus_rec(Recorrido r, Node *n) {
		for (int i = 0; i < r.nodos_recorrido.size(); i++) {
			if (r.nodos_recorrido[i]->m_data == n->m_data) {
				return 1;
			}
		}
		return 0;
	}
	void nivelar(vector<Recorrido> &res) {
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
	void busqueda(vector<Recorrido> &res, Node *n, Edge *arista) {
		Recorrido act = camino(res, arista->m_nodes[0]);
		act.nodos_recorrido.push_back(arista->m_nodes[1]);
		act.peso_actual += arista->m_data;
		res.push_back(act);
		for (int i = 0; i < n->m_edges.size(); i++) {
			if (!(pos_node(n->m_edges[i], n))) {
				if (!bus_rec(act, n->m_edges[i]->m_nodes[1])) {
					nivelar(res);
					busqueda(res, n->m_edges[i]->m_nodes[1], n->m_edges[i]);
				}
			}
		}
	}
	vector<Recorrido> Dikjstra(n nombre) {
		vector<Recorrido> resultado;
		int pos;
		if (buscar_nodo(nombre, pos)) {
			Recorrido actual(m_node[pos]);
			resultado.push_back(actual);
			for (int i = 0; i < m_node[pos]->m_edges.size(); i++) {
				if (!(pos_node(m_node[pos]->m_edges[i], m_node[pos]))) {
					busqueda(resultado, m_node[pos]->m_edges[i]->m_nodes[1], m_node[pos]->m_edges[i]);
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
	void cam_mas_corto(n nodo1,n nodo2) {
		vector<Recorrido> rpta = Dikjstra(m_node[0]->m_data);
	}
	int cam_menos_nodos(n nodo1, n nombre, int count = 0)
	{
		int tempcount = count;
		vector<Recorrido> resultado = cam_menos_ciudades(n nodo1, n nombre, int count);

	}
	vector<Recorrido> cam_menos_ciudades(n nodo1, n nombre,int count=0)
	{
		if (buscar_nodo(nombre, pos))
		{
			if (m_edges[1])
			{
				vector<Recorrido>cam1= cam_menos_ciudades(actual->m_edges[1]->m_nodes[1], nombre,count);
			}
			if (m_edges[2])
			{
				vector<Recorrido>cam2= cam_menos_ciudades(actual->m_edges[2]->m_nodes[1], nombre,count);
			}
		}
		//return resultado;
	}
};

int main() {
	CGraph<char, int> hola;
	hola.insertNode('0');
	hola.insertNode('1');
	hola.insertNode('2');
	hola.insertNode('3');
	hola.insertNode('4');
	hola.insertNode('5');
	hola.insertNode('6');
	hola.insertNode('7');
	hola.insertNode('8');
	hola.insertNode('9');
	hola.insertNode('10');
	hola.insertNode('11');
	hola.insertNode('12');
	hola.insertNode('13');
	hola.insertNode('14');
	hola.insertNode('15');
	hola.insertNode('16');
	hola.insertNode('17');
	hola.insertNode('18');
	hola.insertNode('19');
	hola.insertNode('20');
	hola.imprimir_nodos();
	cout << endl;

	hola.insertEdge('0', '1', 1, 0);
	hola.insertEdge('0', '2', 1, 0);
	hola.insertEdge('0', '3', 1, 0);
	hola.insertEdge('1', '4', 1, 0);
	hola.insertEdge('4', '7', 1, 0);
	hola.insertEdge('7', '10', 1, 0);
	hola.insertEdge('10', '14', 1, 0);
	hola.insertEdge('14', '20', 1, 0);
	hola.insertEdge('2', '5', 1, 0);
	hola.insertEdge('8', '11', 1, 0);
	hola.insertEdge('11', '7', 1, 0);
	hola.insertEdge('8', '12', 1, 0);
	hola.insertEdge('12', '16', 1, 0);
	hola.insertEdge('16', '17', 1, 0);
	hola.insertEdge('16', '19', 1, 0);
	hola.insertEdge('19', '10', 1, 0);
	hola.insertEdge('10', '15', 1, 0);
	hola.insertEdge('3', '6', 1, 0);
	hola.insertEdge('6', '9', 1, 0);
	hola.insertEdge('9', '13', 1, 0);
	hola.insertEdge('13', '17', 1, 0);
	hola.insertEdge('17', '15', 1, 0);
	hola.insertEdge('15', '18', 1, 0);
	hola.insertEdge('18', '20', 1, 0);

	hola.insertEdge('0', '1', 1, 1);
	hola.insertEdge('0', '2', 1, 1);
	hola.insertEdge('0', '3', 1, 1);
	hola.insertEdge('1', '4', 1, 1);
	hola.insertEdge('4', '7', 1, 1);
	hola.insertEdge('7', '10', 1, 1);
	hola.insertEdge('10', '14', 1, 1);
	hola.insertEdge('14', '20', 1, 1);
	hola.insertEdge('2', '5', 1, 1);
	hola.insertEdge('8', '11', 1, 1);
	hola.insertEdge('11', '7', 1, 1);
	hola.insertEdge('8', '12', 1, 1);
	hola.insertEdge('12', '16', 1, 1);
	hola.insertEdge('16', '17', 1, 1);
	hola.insertEdge('16', '19', 1, 1);
	hola.insertEdge('19', '10', 1, 1);
	hola.insertEdge('10', '15', 1, 1);
	hola.insertEdge('3', '6', 1, 1);
	hola.insertEdge('6', '9', 1, 1);
	hola.insertEdge('9', '13', 1, 1);
	hola.insertEdge('13', '17', 1, 1);
	hola.insertEdge('17', '15', 1, 1);
	hola.insertEdge('15', '18', 1, 1);
	hola.insertEdge('18', '20', 1, 1);
	hola.cam_menos_nodos('0', '20');
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
