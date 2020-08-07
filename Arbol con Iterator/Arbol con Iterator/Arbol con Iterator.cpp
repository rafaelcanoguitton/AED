// Árbol Binario de Búsqueda - Pila.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
using namespace std;

template<class T>
class CNode {
public:
	CNode<T>* M_Nodes[2];
	T M_x;
	CNode(T x) {
		M_Nodes[0] = M_Nodes[1] = 0;
		M_x = x;
	}
};

template<typename T>
class pila
{
	CNode<T>* top = nullptr;
public:
	bool vacio(); //indica si la pila está vacía
	void push(T elemento); //agrega un elemento
	T pop(); //retirua un elemento y devuelve su valor
	void print(); //imprime el contenido de la pila
	CNode<T> Top(){return top;}
	~pila();
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
		cout << tmp->valor << endl;
	cout << "base" << endl;
}

template<typename T>
void pila<T>::push(T elemento)
{
	if (top)
	{
		CNode<T>* temp = top;
		top = new CNode<T>(elemento);
		top->next = temp;
	}
	else
		top = new CNode<T>(elemento);

}

template<typename T>
T pila<T>::pop()
{
	if (top)
	{
		CNode<T>* temp = top;
		top = top->next;
		T store = temp->valor;
		delete temp;
		return store;
	}
}

template<typename T>
pila<T>::~pila()
{
	/*while (top)
	{
		CNode<T>* temp = top;
		top = top->next;
		delete temp;
	}*/
}
template<class T>
class cLess {
public:
	inline bool operator() (T a, T b) { return a < b; }
};
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
	recursivoDeleterino(Temp_Root->M_CNodes[0]);
	recursivoDeleterino(Temp_Root->M_CNodes[1]);
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
template<class T>
void Levels(CNode<T>* root)
{
	pila<T> q;
	if (root)
		q.push(root);
	while (!q.vacio())
	{
		CNode<T>* temp = q.Top();
		q.pop();
		cout << temp->M_x << endl;
		if (temp->M_Nodes[0])
			q.push(temp->M_Nodes[0]);
		if (temp->M_Nodes[1])
			q.push(temp->M_Nodes[1]);
	}
}
int main()
{
	CTree<int, cLess<int>> ItTree;
	int x = 0;
	while (x != 7)
	{
		cout << "Seleccione una opción: " << endl;
		cout << "Insertar = 1 " << endl;
		cout << "Eliminar = 2" << endl;
		cout << "Impresion Inorder = 3" << endl;
		cout << "Impresion Postorder = 4" << endl;
		cout << "Impresion Preorder = 5" << endl;
		cout << "Impresion Reverse = 6" << endl;
		cout << "Impresion por Niveles = 7" << endl;
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
			Inorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 4)
		{
			Postorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 5)
		{
			Preorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 6)
		{
			Reverse(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 7)
		{
			Levels(ItTree.M_Root);
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
