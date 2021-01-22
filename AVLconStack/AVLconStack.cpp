// AVLconStack.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <queue>
using namespace std;
template<class T>
class Nodo {
public:
	T dato;
	int balance;
	int level;
	Nodo() {
		dato = 0;
		balance = 0;
	}
	Nodo(T d) : dato(d) { balance = 0; }
	Nodo<T>* M_Nodes[3] = { 0,0,0 };
};
template<typename T>
class pila
{

public:
	Nodo<T>* top = nullptr; Nodo<T>* rear = nullptr;
	bool vacio(); //indica si la pila está vacía
	void push(Nodo<T>* elemento); //agrega un elemento
	Nodo<T>* pop(); //retirua un elemento y devuelve su valor 
	Nodo<T>* poprear();
	void print(); //imprime el contenido de la pila
	void levels(Nodo<T>* M_Root);
	void inorder(Nodo<T>* M_Root);
	~pila();
	void preorder(Nodo<T>* M_Root);
	void postorder(Nodo<T>* M_Root);
	void reverse(Nodo<T>* M_Root);
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
	Nodo<T>* tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->m_data << endl;
	cout << "base" << endl;
}

template<typename T>
void pila<T>::levels(Nodo<T>* M_Root)
{
	int alt = alturita(M_Root)*4; int tempal = alt;
	if (alt % 2 != 0)
	{
		alt++; tempal++;
	}
	int count = 0;
	string espacio = "";
	while (alt != 0)
	{
		espacio += " ";
		alt--;
	}
	if (M_Root)
		push(M_Root);
	while (!vacio())
	{
		Nodo<T>* temp = top;
		if (count != temp->level) {
			cout << endl; count++;
			int tempal2xd=tempal;
			while (tempal != tempal2xd / 2)
			{
				espacio.pop_back();
				tempal--;
			}
		}
		cout <<espacio<< temp->dato << " ";

		if (temp->M_Nodes[0])
			push(temp->M_Nodes[0]);
		if (temp->M_Nodes[1])
			push(temp->M_Nodes[1]);
		pop();
	}

}

template<typename T>
void pila<T>::inorder(Nodo<T>* M_Root)
{
	Nodo<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->M_Nodes[0];
		}
		temp = rear;
		poprear();
		cout << temp->dato << " ";
		temp = temp->M_Nodes[1];
	}
}
template<typename T>
void pila<T>::preorder(Nodo<T>* M_Root)
{
	Nodo<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			cout << temp->dato << " ";
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
void pila<T>::postorder(Nodo<T>* M_Root)
{
	Nodo<T>* temp = M_Root;
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
			cout << temp->dato << " ";
			temp = NULL;
		}
	}
}
template<typename T>
void pila<T>::reverse(Nodo<T>* M_Root)
{
	Nodo<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->M_Nodes[1];
		}
		temp = rear;
		poprear();
		cout << temp->dato << " ";
		temp = temp->M_Nodes[0];
	}
}
template<typename T>
void pila<T>::push(Nodo<T>* elemento)
{
	if (top)
	{
		Nodo<T>* temp = elemento; Nodo<T>* enqueue = top;
		while (enqueue->M_Nodes[2])
			enqueue = enqueue->M_Nodes[2];
		enqueue->M_Nodes[2] = temp;
		rear = temp;
	}
	else
		top = elemento; rear = elemento;

}

template<typename T>
Nodo<T>* pila<T>::pop()
{
	if (top)
	{
		Nodo<T>* temp = top;
		top = top->M_Nodes[2];
		//delete temp;
		temp->M_Nodes[2] = NULL;
		return temp;
	}
}
template<typename T>
Nodo<T>* pila<T>::poprear()
{
	if (top != rear)
	{
		Nodo<T>* temp = top;
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
		Nodo<T>* temp = top;
		top = top->M_Nodes[2];
		delete temp;
	}
}
//USO DE OTRA COLA PARA LAS ROTACIONES PORQUE
//Error	C2664	'void pila<Nodo<T> *>::push(Nodo<Nodo<T>*> *)':
//el argumento 1 no puede convertirse de 'Nodo<T> *' a 'Nodo<T> *'
//Y SON LAS 3 DE LA MAÑANA Y YA ME QUIERO IR A DORMIR
template <class T>
class PilaRotaciones {
public:
	Nodo<T>* cabeza = 0;
	Nodo<T>* cola = 0;
	void push(T d) {
		Nodo<T>* nuevo = new Nodo<T>(d);
		if (!cabeza) {
			cola = nuevo;
			cabeza = nuevo;
			return;
		}
		nuevo->M_Nodes[2] = cabeza;
		cabeza = nuevo;
	}
	T pop() {
		Nodo<T>* temp;
		T val;
		if (cabeza == cola) {
			temp = cabeza;
			val = cabeza->dato;
			cola = 0;
			cabeza = 0;
		}
		else {
			temp = cabeza;
			val = temp->dato;
			cabeza = cabeza->M_Nodes[2];
		}
		temp->M_Nodes[2]=nullptr;
		return val;
	}
	bool vacia() {
		return (cabeza == 0);
	}
};
template <class T>
class Arbol {
	void formaArbol(Nodo<T>* node) {
		int height = altura(node);
		queue<Nodo<T>*> cola;
		int level = 0;
		const int SPACE = 2;
		int nodePrintLocation = 0;
		int cnt = 0;
		Nodo<T>* special = new Nodo<T>(0);
		cola.push(node);
		cout << endl << "                                                 " << endl;
		while (!cola.empty) {
			node = cola.pop();
			cnt++;
			nodePrintLocation = ((int)pow(2, height - level)) * SPACE;
			cout << imprimirLinea(node, nodePrintLocation);
			if (level < height) {
				cola.push(node->M_Nodes[0] != 0 ? node->M_Nodes[0] : special);
				cola.push(node->M_Nodes[1] != 0 ? node->M_Nodes[1] : special);
			}
			if (cnt == (int)pow(2, level)) {
				cout << endl;
				cnt = 0;
				level++;
			}
		}
		delete special;
	}
	string imprimirLinea(Nodo<T>* node, int spaces) {
		stringstream sb, sv;
		if (raiz == nullptr) {
			return "arbol vacio";
		}
		if (node->dato == 0) {
			for (int i = 0; i < 2 * spaces; i++) {
				sb << " ";
			}

			return sb.str();
		}
		int i = 0;
		int to = spaces / 2;
		for (; i < spaces / 2; i++) {
			sb << " ";
		}
		to += spaces / 2;
		char ch = ' ';
		if (node->M_Nodes[0]) {
			ch = ' ';
		}
		for (; i < to; i++) {
			sb << ch;
		}
		sv << node->dato;
		to += spaces / 2;
		ch = ' ';
		if (node->M_Nodes[1]) {
			ch = ' ';
		}
		sb << sv.str();
		for (i += sv.str().length(); i <= to; i++) {
			sb << ch;
		}

		to += spaces / 2;
		for (; i < to; i++) {
			sb << " ";
		}

		return sb.str();
	}
	int altura(Nodo<T>* node) {
		if (!node) {
			return -1;
		}

		if (!node->M_Nodes[0] && !node->M_Nodes[1]) {
			return 0;
		}
		return 1 + mayor(altura(node->M_Nodes[0]), altura(node->M_Nodes[1]));
	}
	int mayor(int a, int b) {
		return a > b ? a : b;
	}
	void balancear() {
		Nodo<T>** temp;
		Nodo<T>** temp3;
		Nodo<T>* temp2;
		int izq, der;
		while (!rotaciones.vacia()) {
			izq = 0;
			der = 0;
			temp2 = rotaciones.pop();
			temp = &temp2;
			if ((*temp)->M_Nodes[0])
				izq = (*temp)->M_Nodes[0]->balance + 1;
			if ((*temp)->M_Nodes[1])
				der = (*temp)->M_Nodes[1]->balance + 1;
			(*temp)->balance = mayor(der, izq);
			if (der - izq == 2) {
				if (!(*temp)->M_Nodes[1]->M_Nodes[1] || ((*temp)->M_Nodes[1]->M_Nodes[0] && (*temp)->M_Nodes[1]->M_Nodes[0]->balance > (*temp)->M_Nodes[1]->M_Nodes[1]->balance)) {
					temp3 = &((*temp)->M_Nodes[1]);
					LL(temp3);
				}
				RR(temp);
				rotaciones.push(temp2);
				rotaciones.push(temp2->M_Nodes[0]);
				balancear();
				return;
			}
			if (der - izq == -2) {
				if (!(*temp)->M_Nodes[0]->M_Nodes[0] || ((*temp)->M_Nodes[0]->M_Nodes[1] && (*temp)->M_Nodes[0]->M_Nodes[1]->balance > (*temp)->M_Nodes[0]->M_Nodes[0]->balance)) {
					temp3 = &((*temp)->M_Nodes[0]);
					RR(temp3);
				}
				LL(temp);
				rotaciones.push(temp2);
				rotaciones.push(temp2->M_Nodes[1]);
				balancear();
				return;
			}
		}
	}
	void RR(Nodo<T>**& pNodo) {
		T tempval;
		Nodo<T>* tempNode;
		//A con B
		tempval = (*pNodo)->dato;
		(*pNodo)->dato = (*pNodo)->M_Nodes[1]->dato;
		(*pNodo)->M_Nodes[1]->dato = tempval;
		//B apunta a C (derecha) y a A (izquierda)
		tempNode = (*pNodo)->M_Nodes[1];
		(*pNodo)->M_Nodes[1] = (*pNodo)->M_Nodes[1]->M_Nodes[1];
		tempNode->M_Nodes[1] = (*pNodo)->M_Nodes[0];
		(*pNodo)->M_Nodes[0] = tempNode;
		//bl con al
		tempNode = (*pNodo)->M_Nodes[0]->M_Nodes[0];
		(*pNodo)->M_Nodes[0]->M_Nodes[0] = (*pNodo)->M_Nodes[0]->M_Nodes[1];
		(*pNodo)->M_Nodes[0]->M_Nodes[1] = tempNode;
	}
	void LL(Nodo<T>**& pNodo) {
		T tempval;
		Nodo<T>* tempNode;
		//A con B
		tempval = (*pNodo)->dato;
		(*pNodo)->dato = (*pNodo)->M_Nodes[0]->dato;
		(*pNodo)->M_Nodes[0]->dato = tempval;
		//B apunta a C (izquierda) y a A (derecha)
		tempNode = (*pNodo)->M_Nodes[0];
		(*pNodo)->M_Nodes[0] = (*pNodo)->M_Nodes[0]->M_Nodes[0];
		tempNode->M_Nodes[0] = (*pNodo)->M_Nodes[1];
		(*pNodo)->M_Nodes[1] = tempNode;
		//ar con br
		tempNode = (*pNodo)->M_Nodes[1]->M_Nodes[1];
		(*pNodo)->M_Nodes[1]->M_Nodes[1] = (*pNodo)->M_Nodes[1]->M_Nodes[0];
		(*pNodo)->M_Nodes[1]->M_Nodes[0] = tempNode;
	}
	void recursivoDeleterino(Nodo<T>* rootsito)
	{
		recursivoDeleterino(rootsito->M_Nodes[0]);
		recursivoDeleterino(rootsito->M_Nodes[1]);
		delete rootsito;
	}

public:
	PilaRotaciones<Nodo<T>*> rotaciones;
	Nodo<T>* raiz = 0;
	bool buscar(T valor, Nodo<T>**& pNodo) {
		pNodo = &raiz;
		while (*pNodo) {
			if ((*pNodo)->dato == valor)
				return 1;
			rotaciones.push(*pNodo);
			pNodo = &(*pNodo)->M_Nodes[valor > (*pNodo)->dato];
		}
		return 0;
	}
	bool insertar(T valor) {
		Nodo<T>** pNodo;
		if (buscar(valor, pNodo))
			return 0;
		Nodo<T>* n = new Nodo<T>(valor);
		*pNodo = n;
		balancear();
		return 1;
	}
	bool eliminar(T valor) {
		Nodo<T>** pNodo;
		Nodo<T>* temp;

		if (!buscar(valor, pNodo))
			return 0;
		temp = (*pNodo);
		rotaciones.push(*pNodo);
		if ((*pNodo)->M_Nodes[0] && (*pNodo)->M_Nodes[1]) {
			for (pNodo = &((*pNodo)->M_Nodes[0]); (*pNodo)->M_Nodes[1]; pNodo = &((*pNodo)->M_Nodes[1]))
				rotaciones.push(*pNodo);
			temp->dato = (*pNodo)->dato;
		}
		temp = (*pNodo);
		(*pNodo) = (*pNodo)->M_Nodes[!(*pNodo)->M_Nodes[0]];
		if (temp == rotaciones.cabeza->dato)
		{
			rotaciones.pop();
		}
		delete temp;
		balancear();
		return 1;
	}
	void anchura() {
		Nodo<T>* pNodo = raiz;
		pila<Nodo<T>*> col;
		if (pNodo)
			col.push(pNodo);
		while (!col.vacia()) {
			pNodo = col.pop();
			cout << pNodo->dato << " ";
			if (pNodo->M_Nodes[0])
				col.push(pNodo->M_Nodes[0]);
			if (pNodo->M_Nodes[1])
				col.push(pNodo->M_Nodes[1]);
		}
		cout << endl;
		return;
	}
	void formaArbol() {
		formaArbol(raiz);
	}
	~Arbol()
	{
		recursivoDeleterino(raiz);
	}
};

template <class T>
void assign(Nodo<T>* M_Root, int curr = 0)
{
	int current = curr;
	if (M_Root != NULL) {
		assign(M_Root->M_Nodes[0], current + 1);
		assign(M_Root->M_Nodes[1], current + 1);
		M_Root->level = current;
	}
}
template <class T>
int alturita(Nodo<T>* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int izquierda = alturita(node->M_Nodes[0]);
		int derecha = alturita(node->M_Nodes[1]);

		if (izquierda > derecha)
			return(izquierda + 1);
		else return(derecha + 1);
	}
}
int main() {
	Arbol<int> arbolito;
	int x = 0;
	while (x != 9)
	{
		cout << "Seleccione una opcion: " << endl;
		cout << "Insertar = 1 " << endl;
		cout << "Eliminar = 2" << endl;
		cout << "Impresion Inorder = 3" << endl;
		cout << "Impresion Postorder = 4" << endl;
		cout << "Impresion Preorder = 5" << endl;
		cout << "Impresion Reverse = 6" << endl;
		cout << "Impresion Niveles = 7 " << endl;
		cout << "Salir = 9" << endl;
		cin >> x;
		if (x == 1)
		{
			int temp;
			cout << "Que elemento desea agregar?" << endl; cin >> temp; arbolito.insertar(temp);
		}
		if (x == 2)
		{
			int temp;
			cout << "Que elemento desea borrar?" << endl; cin >> temp; arbolito.eliminar(temp);
		}
		if (x == 3)
		{
			pila <int>q;
			q.inorder(arbolito.raiz);
			system("pause");
		}
		if (x == 4)
		{
			pila <int>q;
			q.postorder(arbolito.raiz);
			system("pause");
		}
		if (x == 5)
		{
			pila <int>q;
			q.preorder(arbolito.raiz);
			system("pause");
		}
		if (x == 6)
		{
			pila <int>q;
			q.reverse(arbolito.raiz);
			system("pause");
		}
		if (x == 7)
		{
			assign(arbolito.raiz);
			pila <int>q;
			q.levels(arbolito.raiz);
			cout << endl;
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
