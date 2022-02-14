#include <iostream>
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
class CNode {
public:
	T C_Data;
	CNode<T> *C_Next;
	CNode<T> *C_Prev;
	CNode(T x) {
		C_Data = x;
		C_Next = C_Prev = 0;
	}
};

template<class T, class Op>
class CList {
public:
	CNode<T> *C_Head;
	CNode<T> *C_Tail;
	Op o;
	CList() { C_Head = C_Tail = 0; }
	~CList() 
	{
		cout << "Destruccion xd" << endl;
	}
	
	bool find(T x, CNode<T> **&p_next, CNode<T> **&p_prev);
	bool insert(T x);
	bool remove(T x);
	void print();
};

template<class T, class Op>
bool CList<T,Op>::find(T x, CNode<T> **&p_next, CNode<T> **&p_prev){
	
	for(p_next = &C_Head; (*p_next) && o((*p_next)->C_Data,x); p_next = &((*p_next)->C_Next));
	for(p_prev = &C_Tail; (*p_prev) && o(x,(*p_next)->C_Data); p_prev = &((*p_prev)->C_Prev));
	
	return (*p_next) && (*p_next)->C_Data == x;
	
}

template<class T, class Op>
bool CList<T,Op>::insert(T x){
	CNode<T> **p;
	CNode<T> **q;
	if (find(x,p,q)){ return 0; }
	//q = &(*p)->C_Prev;	
	CNode<T> *temp = new CNode<T>(x);
	temp->C_Next = *p;
	temp->C_Prev = *q;
	*p = temp;
	return 1;
	
}

template<class T, class Op>
bool CList<T,Op>::remove(T x){
	CNode<T> **p;
	CNode<T> **q;
	if (!find(x,p,q)){ return 0; }
	CNode<T> *temp = *p;
	//CNode<T> *temp2 = *q;
	*p = temp->C_Next;
	*q = temp->C_Prev;
	delete temp;
	return 1;
}

template<class T, class Op>
void CList<T,Op>::print(){
	CNode<T>*temp = C_Head;
	while (temp) {
		cout << temp->C_Data << ' ';
		temp = temp->C_Next;
	}
	cout<<"-/"<<endl;
}
int main(int argc, char *argv[]) {
	
	CList<int,Menor<int>> lista_pes;
	cout<<"INSERTADO"<<endl;
	lista_pes.insert(5);
	lista_pes.print();
	lista_pes.insert(1);
	lista_pes.print();
	lista_pes.insert(2);
	lista_pes.print();
	lista_pes.insert(6);
	lista_pes.print();
	lista_pes.insert(4);
	lista_pes.print();
	lista_pes.insert(7);
	lista_pes.print();
	lista_pes.insert(3);
	lista_pes.print();	
	cout<<"BORRADO"<<endl;
	lista_pes.remove(1);
	lista_pes.print();	
	lista_pes.remove(3);
	lista_pes.print();	
	lista_pes.remove(5);
	lista_pes.print();	
	lista_pes.remove(7);
	lista_pes.print();	
	
	return 0;
}

