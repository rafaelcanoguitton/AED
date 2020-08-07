// Arbol Digital.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include "pch.h"
#include <iostream>
#include <stack>
using namespace std;

//template<class T>
struct node {
	string w;
	node* h[2];
	node *down;
	bool flag;
	node(string word) {
		w = word;
		h[0] = nullptr;
		h[1] = nullptr;
		down = nullptr;
		flag = 0;
	}
};

struct digitalT {
	node* root = nullptr;

	bool find(string &word, node** &ptr, node** &tmp1, int &i) {

		while (*ptr) {
			i = 0;
			tmp1 = ptr;
			while ((*ptr)->w[i] == word[i]) //recorre la palabra
				i++;
			if (i == 0) {                  // si no tienen similitud la palabra con el nodo comparado
				ptr = &((*ptr)->h[int(word[0]) > int((*ptr)->w[0])]); //ptr apunta al hijo derecho o izquierdo dependiendo del caso
			}
			else if (i != 0) {              // si tiene similitud
				if (word.size() > (*ptr)->w.size()) { //si la longitud de la palabra es mayor a la del nodo comparado
					word = word.substr(i);            //significa que la palabra puede existir en el arbol
					ptr = &((*ptr)->down);
				}
				else if (word.size() == (*ptr)->w.size()) // si la palabra tiene igual longitud que la palabra comparada, entonces se encontró la palabra
					return 1;
				else if (word.size() < (*ptr)->w.size()) // si la palabra tiene menor longitud que la palabra comparada, entonces no existe en el arbol
					return 0;
			}
		}
		return 0; //si no hay ninguna nodo, entonces no existe la palabra en el arbol
	}

	bool insert(string word) {
		node** ptr = &root;
		node** tmp1;
		int i = 0;
		if (find(word, ptr, tmp1, i))
			return false;
		node* nn = new node(word);
		if (!*ptr && i == 0) { // si no hay ningún elemento se agrega el valor al root
			*ptr = nn;
			nn->flag = 1;
		}
		else if (*ptr && i > 0) {
			node* tmp = new node((*ptr)->w.substr(i));
			tmp->flag = 1;
			(*ptr)->w = (*ptr)->w.substr(0, i);
			(*ptr)->flag = 0;
			(*ptr)->down = tmp;
			nn->w = nn->w.substr(i);
			ptr = &tmp;
			find(nn->w, ptr, tmp1, i);
			*ptr = nn;
			nn->flag = 1;
		}
		else if (!*ptr && i > 0) {
			string tmp = (*tmp1)->w;
			(*tmp1)->w = tmp.substr(0, i);
			(*tmp1)->flag = 0;
			*ptr = new node(tmp.substr(i));
			(*ptr)->flag = 1;
			find(nn->w, ptr, tmp1, i);
			*ptr = nn;
			nn->flag = 1;
		}
	}
};

int main()
{
	/*string a = "hola";
	string b = "hola mundo hola mundo";
	size_t pos = b.find("mundo");
	a= b.substr(pos);

	for (int i = 0; i < a.size(); i++)
		cout << a[i];
	cout << endl;
	b = b.substr(0, pos);
	for (int i = 0; i < b.size(); i++)
		cout << b[i];*/
	digitalT a;
	string str = "hola";
	a.insert(str);
	a.insert("hay");
	a.insert("carro");
	a.insert("hacienda");
	a.insert("auto");
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
