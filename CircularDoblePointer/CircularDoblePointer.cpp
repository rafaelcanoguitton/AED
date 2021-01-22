// CircularDoblePointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

template <class T>
struct Node
{
	T n_x;
	Node<T>*n_next;
	Node(T x, Node<T> *next = NULL)
	{
		n_x = x;
		n_next = next;
	}
};

template<class T>
struct Less
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};


template<class T, class O>
struct List
{

	List() { head = NULL; }
	bool Find(T x, Node<T>**&p);
	bool Insert(T x);
	bool Delete(T x);
	void Print();
	void josephus(int x, int y);
	Node<T> *head;
	O Compare;

	~List()
	{
		if (head != 0)
		{
			Node<T> *t = head;
			while (t)
			{
				Node<T> *n_next = t->n_next;
				delete t;
				t = n_next;
			}
		}
	}

};

template<class T, class C>
bool List <T, C> ::Find(T x, Node <T>**&p)
{

	for (p = &head; *p and Compare((*p)->n_x, x) and (*p)->n_next != head;p = &((*p)->n_next));
	return *p and (*p)->n_x == x;


}

template<class T, class O>
bool List<T, O>::Insert(T x)
{

	Node<T> **p;
	if (Find(x, p)) { return 0; }
	Node<T> *t = new Node<T>(x);
	if (head == NULL)
	{
		*p = t;
		t->n_next = (*p);
		return 1;
	}
	Node<T> *last = head;
	while (last->n_next != head)
		last = last->n_next;
	if (Compare(x, head->n_x))
	{
		t->n_next = head;
		head = t;
		last->n_next = t;
		return 1;
	}
	if ((*p == last) and Compare((*p)->n_x, x))
		p = &((*p)->n_next);
	t->n_next = (*p);
	*p = t;
	return 1;


}

template<class T, class O>
bool List<T, O>::Delete(T x)
{
	Node<T> **p;
	if (!Find(x, p)) return 0;
	Node<T> *last = head;
	while (last->n_next != head)
		last = last->n_next;
	Node<T> *t = (*p);
	*p = t->n_next;
	delete t;
	last->n_next = head;
	return 1;
}

template <class T, class O>
void List<T, O>::Print()
{
	if (head != 0)
	{
		Node<T> *temp = head;

		do
		{
			cout << temp->n_x << " ";
			if (temp->n_next)
				cout << "-> " << temp->n_next->n_x << endl;
			temp = temp->n_next;
		} while (temp != head);
	}
}

template <class T, class O>
void List<T, O>::josephus(int n, int k)
{
	int Nmuertos = 0;
	for (int i = 1;i <= n;i++)
		Insert(i);
	Print();
	Node<T> *ptr = head; Node<T> *prev = head;
	while (Nmuertos < n)
	{
		for (int i = 0; i < k - 1;i++)
			ptr = ptr->n_next;
		while (prev->n_next != ptr)
			prev = prev->n_next;
		if (ptr == head)
			head = head->n_next;
		prev->n_next = ptr->n_next;
		ptr = prev->n_next;
		Nmuertos++;
	}
	cout << "Playing the Josephus Game with " << n << " people, eliminating every " << k << " people, leaves person " << head->n_x << " as the last survivor." << endl;
		cout << "\n";

}
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


int main()
{
	List<int, Less<int> > *CircDobP = new List<int, Less<int> >;
	int n, k;
	std::ifstream Reader("art.txt");
	std::string Art = getFileContents(Reader);
	std::cout << Art << std::endl;
	Reader.close();
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "n: ";cin >> n;
	cout << "k: ";cin >> k;
	CircDobP->josephus(n, k);
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
