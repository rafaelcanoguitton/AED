//Copyright Jhorel Revilla 2018
#include <iostream>
using namespace std;
template<class T>
class nodo{
public:
	T dato=0;
	nodo *next=nullptr;
	nodo(T a=0){
		dato=a;
	}
};
template<class T>
class lista{
public:
	nodo<T> *head=nullptr;
	////////////////////////////////////////////////////////
	bool buscar(T d,nodo<T>*&p){
		for(p=head;p->next!=head && d > p->dato ;p=p->next);
		return p->next && p->dato==d;
	}
	bool agregar(T d){
		if(head==nullptr){
			head=new nodo<T>(d);
			head->next=head;
			return true;
		}
		if(d<head->dato){
			nodo<T> *p;
			for(p=head;p->next!=head;p=p->next);
			nodo<T> *temp=new nodo<T>(d);
			temp->next=head;
			head=temp;
			p->next=temp;
			return true;
		}
		nodo<T>*p;
		if(buscar(d,p)){return 0;}
		nodo<T> *temp=new nodo<T>(d);
		temp->next=p->next;
		p->next=temp;
		return true;
	}
///////////////////////////////////////////////////////////////////////////////
	bool borrar(T d){
		nodo<T>*temp=head;
		if(head->next==head){
			delete head;
			head=nullptr;
			return true;
		}
		if(head->dato==d){
			nodo<T>*temp1=temp->next;
			nodo<T> *p;
			for(p=head;p->next!=head;p=p->next);
			p->next=temp1;
			delete temp;
			head=temp1;
			return true;
		}
		while(temp->next && (temp->next->dato != d)){
			temp=temp->next;
		}
		if(!temp->next){
			return 0;
		}
		nodo<T>*temp1=temp->next;
		temp->next=temp1->next;
		delete temp1;
		return true;
	}
///////////////////////////////////////////////////////////////////////////////
	bool josephus(int n){
		int cont=1;
		nodo<T> *p=head;
		while(head){
			nodo<T> *q=p->next;
			if(cont==n){
				cout<<"se borra "<<p->dato<<endl;
				borrar(p->dato);
				cont=0;
			}
			cont++;
			p=q;
		}
	}
	bool imprimir(){
		cout<<"imprimir "<<endl;		
		if(head==nullptr){
			cout<<"esta vacia"<<endl;
			return false;
		}
		nodo<T>*p=head;
		while(p->next!=head){
			cout<<p->dato<<"->";
			p=p->next;
		}
		cout<<p->dato<<endl;
		return true;
	}
};
int main()
{
	
	lista<int> a;
	a.agregar(1);
	a.agregar(2);
	a.agregar(3);
	a.agregar(4);
	a.agregar(5);
	
	//a.imprimir();
	a.josephus(2);
	
	
	return 0;
}

