// REDBLACK.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <list>
#include <stdio.h>      
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}


template <class T>
struct CNode {
	T m_x;
	CNode<T>* m_nodes[2];
	bool colour; //0 = red, 1 = black
	CNode(T x) {
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
		colour = 0;
	}
};
template <class T>
struct Menor {
	inline bool operator()(T a, T b) {
		return a < b;
	}
};
template <class T, class C>
class RedBlack {
public:
	CNode<T>* m_root;
	RedBlack();
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void inorder(CNode<T>* p);
	void printTree(CNode<T>* p);
private:
	CNode<T>** Rep(CNode<T>** p);
	C mc;
	list<CNode<T>* > path;
	void RU(CNode<T>* uncle, CNode<T>* father, CNode<T>* gfather); //Red Uncle
	void BUT(CNode<T>* p); //Black Uncle Triangular
	void BUL(CNode<T>* p); //Black Uncle Linear
	void LL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Simlar to LL in AVL
	void RR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to RR in AVL
	void LR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to RL in AVL
	void RL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp); //Similar to LR in AVL
	void findCase(CNode<T>* p);
};
template <class T, class C>
CNode<T>** RedBlack<T, C>::Rep(CNode<T>** p) {
	for (p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[1]);
	return p;
}
template <class T, class C>
RedBlack<T, C>::RedBlack() {
	this->m_root = 0;
}
template <class T, class C>
void RedBlack<T, C>::findCase(CNode<T>* p) {
	if (p == m_root) {
		p->colour = 1;
		return;
	}
	typename list<CNode<T>* >::reverse_iterator it;
	for (it = path.rbegin(); *it != p; it++);
	CNode<T>* gfather, *father, *uncle, *temp = 0;
	if (++it == path.rend()) return; //no father
	father = (*it++);
	if (it == path.rend()) return; //no grand father
	gfather = (*it);
	if (*it != m_root) {
		temp = (*++it);
		it--;
	}
	if (gfather->m_nodes[0] == father) uncle = gfather->m_nodes[1];
	else uncle = gfather->m_nodes[0];
	if (uncle && !uncle->colour) {
		RU(uncle, father, gfather);
		return;
	}
	if (!uncle) { //LL or RR
		if (father == gfather->m_nodes[0]) {
			if (!father->m_nodes[0]) {
				RL(father, gfather, temp);
				return;
			}
			LL(father, gfather, temp);
			father->colour = 1;
			father->m_nodes[1]->colour = 0;
		}
		else {
			if (!father->m_nodes[1]) {
				LR(father, gfather, temp);
				return;
			}
			RR(father, gfather, temp);
			father->colour = 1;
			father->m_nodes[0]->colour = 0;
		}
		return;
	}
}
template <class T, class C>
void RedBlack<T, C>::RU(CNode<T>* uncle, CNode<T>* father, CNode<T>* gfather) {
	uncle->colour = 1;
	father->colour = 1;
	if (gfather != m_root) gfather->colour = 0;
	else gfather->colour = 1;
}
template <class T, class C>
void RedBlack<T, C>::LL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp) {
	CNode<T> *br = father->m_nodes[1];
	father->m_nodes[1] = gfather;
	gfather->m_nodes[0] = br;
	if (m_root == gfather) {
		m_root = father;
	}
	else {
		temp->m_nodes[1] = father;
	}
	return;
}
template <class T, class C>
void RedBlack<T, C>::RR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp) {
	CNode<T> *bl = father->m_nodes[0];
	father->m_nodes[0] = gfather;
	gfather->m_nodes[1] = bl;
	if (m_root == gfather) {
		m_root = father;
	}
	else {
		temp->m_nodes[0] = father;
	}
}
template <class T, class C>
void RedBlack<T, C>::LR(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp) {
	LL(father->m_nodes[0], father, gfather);
	gfather->m_nodes[1]->colour = 1;
	gfather->colour = 0;
	RR(gfather->m_nodes[1], gfather, temp);
}
template <class T, class C>
void RedBlack<T, C>::RL(CNode<T>* father, CNode<T>* gfather, CNode<T>* temp) {
	RR(father->m_nodes[1], father, gfather);
	gfather->m_nodes[0]->colour = 1;
	gfather->colour = 0;
	LL(gfather->m_nodes[0], gfather, temp);
}

template <class T, class C>
bool RedBlack<T, C>::find(T x, CNode<T>**& p) {
	for (p = &m_root; *p && (*p)->m_x != x; p = &((*p)->m_nodes[mc((*p)->m_x, x)])) {
		path.push_back(*p);
	}
	return !!*p;
}

template <class T, class C>
bool RedBlack<T, C>::insert(T x) {
	CNode<T>** p;
	if (find(x, p)) return 0;
	*p = new CNode<T>(x);
	path.push_back(*p);
	/*if (*p == this->m_root)
	(*p)->colour = 1;*/
	findCase(*p);
	path.clear();
	return 1;
}

template<class T, class C>
bool RedBlack<T, C>::remove(T x) {
	CNode<T>** p;
	if (!(find(x, p))) return 0;
	if ((*p)->m_nodes[0] && (*p)->m_nodes[1]) {
		CNode<T>** q = Rep(p);
		(*p)->m_x = (*q)->m_x;
		p = q;
	}
	CNode<T>* temp = *p;
	*p = (*p)->m_nodes[(*p)->m_nodes[1] != 0];
	delete temp;
	return 1;
}
template <class T, class C>
void RedBlack<T, C>::printTree(CNode<T>* p) {
	if (!p) return;
	cout << "Valor: " << p->m_x << " color: ";
	if (p->colour) cout << "Negro" << endl;
	else cout << "Rojo" << endl;
	if (p->m_nodes[0]) cout << "Hijo izquierdo: " << p->m_nodes[0]->m_x << ' ';
	if (p->m_nodes[1]) cout << "Hijo derecho: " << p->m_nodes[1]->m_x << endl;
	printTree(p->m_nodes[0]);
	printTree(p->m_nodes[1]);
}
/*template <class T>
void Print(CNode<T> *p) {
	if (p) {
		if (p->m_nodes[1])
			cout << p->m_nodes[1]->m_x << " --- ";
		else
			cout << "       ";
		if (p->m_nodes[!!p->m_nodes[1]])
			cout << " " << p->m_x;
		if (p->m_nodes[0]) {
			cout << " --- " << p->m_nodes[0]->m_x;
			cout << endl;
		}
		else {
			cout << endl;
		}
		Print(p->m_nodes[1]);
		Print(p->m_nodes[0]);

	}
}*/
template <class T>
void Print(CNode<T> *p) {
	if (p) {
		if (p->m_nodes[0])
			cout << p->m_nodes[0]->m_x << " --- ";
		else
			cout << "       ";
		if (p->m_nodes[!!p->m_nodes[0]])
			cout << " " << p->m_x;
		if (p->m_nodes[1]) {
			cout << " --- " << p->m_nodes[1]->m_x;
			cout << endl;
		}
		else {
			cout << endl;
		}
		Print(p->m_nodes[0]);
		Print(p->m_nodes[1]);

	}
}

int main(int argc, char *argv[]) {
	
	std::ifstream Reader("art.txt");
	std::string Art = getFileContents(Reader);
	std::cout << Art << std::endl;

	RedBlack<int, Menor<int> > RB;

/*	RB.insert(1); //LL test + RU
	RB.printTree(RB.m_root);
	RB.insert(2);
	RB.printTree(RB.m_root);
	RB.insert(3);
	RB.printTree(RB.m_root);
	RB.insert(4);
	RB.printTree(RB.m_root);*/
	
	RB.insert(5);
	RB.insert(6);
	RB.insert(7);
	RB.printTree(RB.m_root);

	Print(RB.m_root);
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
