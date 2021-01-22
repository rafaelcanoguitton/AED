//Árbol Binario de Búsqueda - Pila.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
using namespace std;
template<class T>
class cLess {
public:
	inline bool operator() (T a, T b) { return a < b; }
};

template<class T>
class CNode {
public:
	CNode<T>* M_Nodes[3];
	//int state;
	T M_x;
	int level;
	CNode(T x,int lvl=0){
		M_Nodes[0] = M_Nodes[1] =  M_Nodes[2] = 0;
		M_x = x;
		level =lvl;
	}
};
template<typename T>
class pila
{
	
public:
	CNode<T>* top = nullptr; CNode<T>* rear = nullptr;
	bool vacio(); //indica si la pila está vacía
	void push(CNode<T>* elemento); //agrega un elemento
	CNode<T>* pop(); //retirua un elemento y devuelve su valor 
	CNode<T>* poprear();
	void print(); //imprime el contenido de la pila
	void levels(CNode<T>* M_Root);
	void inorder(CNode<T>* M_Root);
	~pila();
	void preorder(CNode<T>* M_Root);
	void postorder(CNode<T>* M_Root);
	void reverse(CNode<T>* M_Root);
};

template<typename T>
bool pila<T>::vacio()
{
	if (top)
		return false;
	else
		return true;
}

template<typename T>
void pila<T>::print()
{
	CNode<T>* tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->M_x << endl;
	cout << "base" << endl;
}

template<typename T>
void pila<T>::levels(CNode<T>* M_Root)
{
	int count = 0;
	if (M_Root)
		push(M_Root);
	while (!vacio())
	{
		CNode<T>* temp = top;
		if (count != temp->level) {
			cout << endl; count++;
		}	
		cout << temp->M_x<< " ";
		
		if (temp->M_Nodes[0])
			push(temp->M_Nodes[0]);
		if (temp->M_Nodes[1])
			push(temp->M_Nodes[1]);
		pop();
	}

}

template<typename T>
void pila<T>::inorder(CNode<T>* M_Root)
{
	CNode<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->M_Nodes[0];
		}
		temp = rear;
		poprear();
		cout << temp->M_x << " ";
		temp=temp->M_Nodes[1];
	}
}
template<typename T>
void pila<T>::preorder(CNode<T>* M_Root)
{
	CNode<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			cout << temp->M_x << " ";
			if (temp->M_Nodes[1])
				push(temp->M_Nodes[1]);
			temp = temp->M_Nodes[0];
		}
		if (!vacio())
		{
			temp = rear;
			poprear();
		}
	}
}
template<typename T>
void pila<T>::postorder(CNode<T>* M_Root)
{
	CNode<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			if (temp->M_Nodes[1])
				push(temp->M_Nodes[1]);
			push(temp);
			temp = temp->M_Nodes[0];
		}
		temp = rear; poprear();
		if (temp->M_Nodes[1] && rear == temp->M_Nodes[1])
		{
			poprear();
			push(temp);
			temp = temp->M_Nodes[1];
		}
		else
		{
			cout << temp->M_x << " ";
			temp = NULL;
		}
	}
}
template<typename T>
void pila<T>::reverse(CNode<T>* M_Root)
{
	CNode<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->M_Nodes[1];
		}
		temp = rear;
		poprear();
		cout << temp->M_x << " ";
		temp=temp->M_Nodes[0];
	}
}
template<typename T>
void pila<T>::push(CNode<T>* elemento)
{
	if (top)
	{
		CNode<T>* temp = elemento; CNode<T>* enqueue = top;
		while (enqueue->M_Nodes[2])
			enqueue= enqueue->M_Nodes[2];
		enqueue->M_Nodes[2] = temp;
		rear = temp;
	}
	else
		top = elemento; rear = elemento;

}

template<typename T>
CNode<T>* pila<T>::pop()
{
	if (top)
	{
		CNode<T>* temp = top;
		top = top->M_Nodes[2];
		//delete temp;
		return temp;
	}
}
template<typename T>
CNode<T>* pila<T>::poprear()
{
	if (top != rear)
	{
		CNode<T>* temp = top;
		while (temp->M_Nodes[2] != rear)
		{
			temp = temp->M_Nodes[2];
		}
		temp->M_Nodes[2] = NULL;
		rear = temp;
		//delete temp;
		return temp;
	}
	else
		top = NULL; rear = NULL;
}
template<typename T>
pila<T>::~pila()
{
	while (top)
	{
		CNode<T>* temp = top;
		top = top->M_Nodes[2]; 
		delete temp;
	}
}
template<class T, class Op>
class CTree {
public:
	CNode<T>* M_Root;
	Op o;
	CTree() { M_Root = 0; }
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void recursivoDeleterino(CNode<T>* M_Root);
	CNode<T>** Rep(CNode<T>** p);

};
template<class T, class Op>
void CTree<T, Op>::recursivoDeleterino(CNode<T>* Temp_Root)
{
	recursivoDeleterino(Temp_Root->M_Nodes[0]);
	recursivoDeleterino(Temp_Root->M_Nodes[1]);
	delete Temp_Root;
}

template <class T>
void Inorder(CNode<T>* M_Root)
{
	if (M_Root != NULL) {
		Inorder(M_Root->M_Nodes[0]);
		cout << M_Root->M_x << " ";
		Inorder(M_Root->M_Nodes[1]);
	}
}
template <class T>
void assign(CNode<T>* M_Root,int curr=0)
{
	int current = curr;
	if (M_Root != NULL) {
		assign(M_Root->M_Nodes[0],current+1);
		assign(M_Root->M_Nodes[1], current+1);
		M_Root->level = current;
	}

}
template <class T>
void Postorder(CNode<T>* M_Root)
{
	if (M_Root != NULL) {
		Postorder(M_Root->M_Nodes[0]);
		Postorder(M_Root->M_Nodes[1]);
		cout << M_Root->M_x << " ";
	}

}
template <class T>
void Preorder(CNode<T>* M_Root)
{
	if (M_Root != NULL) {
		cout << M_Root->M_x << " ";
		Preorder(M_Root->M_Nodes[0]);
		Preorder(M_Root->M_Nodes[1]);
	}
}
template <class T>
void Reverse(CNode<T>* M_Root)
{
	if (M_Root != NULL) {
		Inorder(M_Root->M_Nodes[1]);
		cout << M_Root->M_x << " ";
		Inorder(M_Root->M_Nodes[0]);
	}
}
template<class T, class Op>
bool CTree<T, Op>::find(T x, CNode<T>**& p)
{
	for (p = &M_Root; *p && (*p)->M_x != x; p = &(*p)->M_Nodes[o((*p)->M_x, x)]);
	return *p != NULL;
}
template<class T, class Op>
bool CTree<T, Op>::insert(T x)
{
	CNode<T>** p;
	if (find(x, p)) { return 0; }
	*p = new CNode<T>(x);
	return 1;
}
template<class T, class Op>
CNode<T>** CTree<T, Op>::Rep(CNode<T>** p)
{
	int r = rand() % 2;
	cout << "A: " << r << endl;
	p = &(*p)->M_Nodes[r];
	while ((*p)->M_Nodes[!r] != NULL) { p = &(*p)->M_Nodes[!r]; }
	cout << "P: " << (*p)->M_x << endl;
	return p;
}
template<class T, class Op>
bool CTree<T, Op>::remove(T x)
{
	CNode<T>** p;
	if (!find(x, p)) { return 0; }
	if ((*p)->M_Nodes[0] && (*p)->M_Nodes[1]) {
		CNode<T>** q = Rep(p);
		(*p)->M_x = (*q)->M_x;
		p = q;
	}
	CNode<T>* t = *p;
	*p = (*p)->M_Nodes[(*p)->M_Nodes[0] == 0];
	delete t;
	return 1;
}
int main()
{
	CTree<int, cLess<int>> ItTree;
	int x = 0;
	pila <int>q;
	//q.levels(ItTree.M_Root);
	//levels(ItTree.M_Root);
	while (x != 8)
	{
		cout << "Seleccione una opción: " << endl;
		cout << "Insertar = 1 " << endl;
		cout << "Eliminar = 2" << endl;
		cout << "Impresion Inorder = 3" << endl;
		cout << "Impresion Postorder = 4" << endl;
		cout << "Impresion Preorder = 5" << endl;
		cout << "Impresion Reverse = 6" << endl;
		cout << "Impresion Niveles = 7" << endl;
		cout << "Salir = 8" << endl;
		cin >> x;
		if (x == 1)
		{
			int temp;
			cout << "Que elemento desea agregar?" << endl; cin >> temp; ItTree.insert(temp);
		}
		if (x == 2)
		{
			int temp;
			cout << "Que elemento desea borrar?" << endl; cin >> temp; ItTree.remove(temp);
		}
		if (x == 3)
		{
			pila <int>q;
			q.inorder(ItTree.M_Root);
			//Inorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 4)
		{
			pila <int>q;
			q.postorder(ItTree.M_Root);
			//Postorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 5)
		{
			pila <int>q;
			q.preorder(ItTree.M_Root);
			//Preorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 6)
		{
			pila <int>q;
			q.reverse(ItTree.M_Root);
			//Reverse(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 7)
		{
			assign(ItTree.M_Root);
			pila <int>q;
			q.levels(ItTree.M_Root);
			system("pause");
		}

		system("cls");
	}
	return 0;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
