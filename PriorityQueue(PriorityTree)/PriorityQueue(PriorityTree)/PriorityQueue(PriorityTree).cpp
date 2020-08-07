// PriorityQueue(PriorityTree).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
using namespace std;
template<class T>
class asc
{
public:
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

template<class T>
class des
{
public:
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};
template<class T>
struct Node
{
	Node(T x)
	{
		N_nodes[0] = NULL; // HIJO IZQUIERDO
		N_nodes[1] = NULL; // HJO DERECHO
		n_x = x;
	}
	Node<T> *N_nodes[2];
	T n_x;
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
struct Tree
{
	Node<T> *n_root;
	O Compare;
	Tree() { n_root = 0; }
	~Tree() {};
	void push(T x) {

	}
	void pop() {

	}
	void preorder(struct Node* root)
	{
		if (root == NULL)return;
		max_heapify(root, NULL);
		preorder(root->N_nodes[0]);
		preorder(root->N_nodes[1]);
	}
	void max_heapify(struct Node* root, struct Node* prev)
	{
		if (root == NULL)
			return;
		max_heapify(root->N_nodes[0], root);
		max_heapify(root->N_nodes[1], root);
		if (prev != NULL && root->n_x > prev->n_x)
		{
			swapper(root, prev);
		}
	}
	void swapper(struct Node* node1, struct Node* node2)
	{
		int temp = node1->n_x;
		node1->n_x = node2->n_x;
		node2->n_x = temp;
	}
	void print(Node<T> *p) {
		if (p) {
			if (p->N_nodes[1])
				cout << p->N_nodes[1]->n_x << " --- ";// << "(" << p->height << ")" << "(" << p->balanceFactor << ")";
			else
				cout << "       ";
			if (p->N_nodes[!!p->N_nodes[1]])
				cout << " " << p->n_x;// << "(" << p->height << ")" << "(" << p->balanceFactor << ")";
			if (p->N_nodes[0]) {
				cout << " --- " << p->N_nodes[0]->n_x;//<< "(" << p->height << ")" << "(" << p->balanceFactor << ")";
				cout << endl;
			}
			else {
				cout << endl;
			}
			Print(p->nodes[1]);
			Print(p->nodes[0]);

		}
	}
	void printProfundidad() {
		queue < Node<int>* > q;
		//queue <int> q_auxiliar;
		q.push(root);
		while (q.size() > 0)
		{
			Node<T> *p = q.front();
			q.pop();
			cout << p->n_x << " ";
			if (p->N_nodes[0])
			{
				q.push(p->N_nodes[0]);
			}
			if (p->N_nodes[1])
			{
				q.push(p->N_nodes[1]);
			}
		}
	}
};
int main()
{
    std::cout << "Hello World!\n"; 
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

/*
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
using namespace std;
class BHeap {
private:
	vector <int> heap;
	int l(int parent);
	int r(int parent);
	int par(int child);
	void heapifyup(int index);
	void heapifydown(int index);
public:
	BHeap() {}
	void Insert(int element);
	void DeleteMin();
	int ExtractMin();
	void showHeap();
	int Size();
};
int main() {
	BHeap h;
	while (1) {
		cout << "1.Insert Element" << endl;
		cout << "2.Delete Minimum Element" << endl;
		cout << "3.Extract Minimum Element" << endl;
		cout << "4.Show Heap" << endl;
		cout << "5.Exit" << endl;
		int c, e;
		cout << "Enter your choice: ";
		cin >> c;
		switch (c) {
		case 1:
			cout << "Enter the element to be inserted: ";
			cin >> e;
			h.Insert(e);
			break;
		case 2:
			h.DeleteMin();
			break;
		case 3:
			if (h.ExtractMin() == -1) {
				cout << "Heap is Empty" << endl;
			}
			else
				cout << "Minimum Element: " << h.ExtractMin() << endl;
			break;
		case 4:
			cout << "Displaying elements of Hwap: ";
			h.showHeap();
			break;
		case 5:
			exit(1);
		default:
			cout << "Enter Correct Choice" << endl;
		}
	}
	return 0;
}
int BHeap::Size() {
	return heap.size();
}
void BHeap::Insert(int ele) {
	heap.push_back(ele);
	heapifyup(heap.size() - 1);
}
void BHeap::DeleteMin() {
	if (heap.size() == 0) {
		cout << "Heap is Empty" << endl;
		return;
	}
	heap[0] = heap.at(heap.size() - 1);
	heap.pop_back();
	heapifydown(0);
	cout << "Element Deleted" << endl;
}
int BHeap::ExtractMin() {
	if (heap.size() == 0) {
		return -1;
	}
	else
		return heap.front();
}
void BHeap::showHeap() {
	vector <int>::iterator pos = heap.begin();
	cout << "Heap --> ";
	while (pos != heap.end()) {
		cout << *pos << " ";
		pos++;
	}
	cout << endl;
}
int BHeap::l(int parent) {
	int l = 2 * parent + 1;
	if (l < heap.size())
		return l;
	else
		return -1;
}
int BHeap::r(int parent) {
	int r = 2 * parent + 2;
	if (r < heap.size())
		return r;
	else
		return -1;
}
int BHeap::par(int child) {
	int p = (child - 1) / 2;
	if (child == 0)
		return -1;
	else
		return p;
}
void BHeap::heapifyup(int in) {
	if (in >= 0 && par(in) >= 0 && heap[par(in)] > heap[in]) {
		int temp = heap[in];
		heap[in] = heap[par(in)];
		heap[par(in)] = temp;
		heapifyup(par(in));
	}
}
void BHeap::heapifydown(int in) {
	int child = l(in);
	int child1 = r(in);
	if (child >= 0 && child1 >= 0 && heap[child] > heap[child1]) {
		child = child1;
	}
	if (child > 0 && heap[in] > heap[child]) {
		int t = heap[in];
		heap[in] = heap[child];
		heap[child] = t;
		heapifydown(child);
	}
}*/