// Avl(FINAL ARREGLADO).cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <time.h>
#include <queue>
#include <Windows.h>

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

template<class G>
class Node {
public:
	G m_data;
	int niv;
	int level;
	Node* m_nodes[4];
	Node(G m_data_, Node* padre) {
		m_data = m_data_;
		niv = 0;
		m_nodes[0] = padre;
		m_nodes[1] = NULL;
		m_nodes[2] = NULL;
		m_nodes[3] = NULL;
	}
};

template<class T, class C>
class c_AVL_T {
public:

	Node<T>* root;
	C cmp;
	c_AVL_T();
	bool Is_empty();

	void insert(T);
	void remove(T);

	void balancear(Node<T>*);
	Node<T>* rot_sim_i(Node<T>*);
	Node<T>* rot_sim_d(Node<T>*);
	Node<T>* rot_i_d(Node<T>*);
	Node<T>* rot_d_i(Node<T>*);

	int altura(Node<T>*);
	void col_bal(Node<T>*);
	void mostrarArbolito(Node<T>*, int);
	void recursivoDeleterino(Node<T>* rootsito);
	~c_AVL_T()
	{
		recursivoDeleterino(root);
	}
};
template<class T, class C>
void c_AVL_T<T, C>::recursivoDeleterino(Node<T>* rootsito)
{
	if (rootsito) {
		if (rootsito->m_nodes[0])
			recursivoDeleterino(rootsito->m_nodes[0]);
		if (rootsito->m_nodes[1])
			recursivoDeleterino(rootsito->m_nodes[1]);
	}
	delete rootsito;
}

template<class T, class C>
c_AVL_T<T, C>::c_AVL_T()
{
	root = NULL;
}

template<class T, class C>
bool c_AVL_T<T, C>::Is_empty()
{
	return root == nullptr;
}

template<class T, class C>
void c_AVL_T<T, C>::insert(T valor)
{
	if (valor == 0)
		return;

	bool seguir = true;
	if (!root)
		root = new Node<T>(valor, nullptr);
	else
	{
		Node<T>* temp = root;
		Node<T>* temp2;
		while (seguir) {
			if (temp->m_data == valor)
				break;

			temp2 = temp;

			bool dir = cmp(temp->m_data, valor);

			if (dir)
				temp = temp->m_nodes[1];
			else
				temp = temp->m_nodes[2];

			if (!temp)
			{
				if (dir)
					temp2->m_nodes[1] = new Node<T>(valor, temp2);
				else
					temp2->m_nodes[2] = new Node<T>(valor, temp2);

				balancear(temp2);
				seguir = false;
			}
		}
	}
}

template<class T, class C>
void c_AVL_T<T, C>::remove(T valor)
{
	if (!root)
		return;

	Node<T>* temp = root;
	Node<T>* temp2 = root;
	Node<T>* hijo = root;
	Node<T>* to_delete = NULL;
	while (hijo)
	{
		temp2 = temp;
		temp = hijo;
		if (valor < temp->m_data)
			hijo = temp->m_nodes[1];
		else
			hijo = temp->m_nodes[2];

		if (valor == temp->m_data)
			to_delete = temp;
	}

	if (to_delete)
	{
		to_delete->m_data = temp->m_data;

		if (temp->m_nodes[1])
			hijo = temp->m_nodes[1];
		else
			hijo = temp->m_nodes[2];

		if (root->m_data == valor)
			root = hijo;
		else
		{
			if (temp2->m_nodes[1] == temp)
				temp2->m_nodes[1] = hijo;
			else
				temp2->m_nodes[2] = hijo;

			balancear(temp2);
		}
	}
}

template<class T, class C>
Node<T>* c_AVL_T<T, C>::rot_sim_i(Node<T>* a)
{
	Node<T>* temp = a->m_nodes[2];
	temp->m_nodes[0] = a->m_nodes[0];
	a->m_nodes[2] = temp->m_nodes[1];
	if (a->m_nodes[2])
		a->m_nodes[2]->m_nodes[0] = a;
	temp->m_nodes[1] = a;
	a->m_nodes[0] = temp;

	if (temp->m_nodes[0])
	{
		if (temp->m_nodes[0]->m_nodes[2] == a)
			temp->m_nodes[0]->m_nodes[2] = temp;
		else
			temp->m_nodes[0]->m_nodes[1] = temp;
	}
	col_bal(a);
	col_bal(temp);
	return temp;
}

template<class T, class C>
Node<T>* c_AVL_T<T, C>::rot_sim_d(Node<T>* a)
{
	Node<T>* temp = a->m_nodes[1];
	temp->m_nodes[0] = a->m_nodes[0];
	a->m_nodes[1] = temp->m_nodes[2];

	if (a->m_nodes[1])
		a->m_nodes[1]->m_nodes[0] = a;
	temp->m_nodes[2] = a;
	a->m_nodes[0] = temp;

	if (temp->m_nodes[0])
	{
		if (temp->m_nodes[0]->m_nodes[2] == a)
			temp->m_nodes[0]->m_nodes[2] = temp;
		else
			temp->m_nodes[0]->m_nodes[1] = temp;
	}
	col_bal(a);
	col_bal(temp);
	return temp;
}

template<class T, class C>
Node<T>* c_AVL_T<T, C>::rot_i_d(Node<T>* a)
{
	a->m_nodes[1] = rot_sim_i(a->m_nodes[1]);
	return rot_sim_d(a);
}

template<class T, class C>
Node<T>* c_AVL_T<T, C>::rot_d_i(Node<T>* a)
{
	a->m_nodes[2] = rot_sim_d(a->m_nodes[2]);
	return rot_sim_i(a);
}

template<class T, class C>
int c_AVL_T<T, C>::altura(Node<T>* a)
{
	if (!a)
		return -1;

	int mayor;
	if (altura(a->m_nodes[1]) > altura(a->m_nodes[2]))
		mayor = altura(a->m_nodes[1]);
	else
		mayor = altura(a->m_nodes[2]);

	return 1 + mayor;
}

template<class T, class C>
void c_AVL_T<T, C>::balancear(Node<T>* a)
{
	col_bal(a);
	if (a->niv == -2)
	{
		if (altura(a->m_nodes[1]->m_nodes[1]) >= altura(a->m_nodes[1]->m_nodes[2]))
			a = rot_sim_d(a);
		else
			a = rot_i_d(a);
	}
	else if (a->niv == 2)
	{
		if (altura(a->m_nodes[2]->m_nodes[2]) >= altura(a->m_nodes[2]->m_nodes[1]))
			a = rot_sim_i(a);
		else
			a = rot_d_i(a);
	}

	if (a->m_nodes[0])
		balancear(a->m_nodes[0]);
	else
		root = a;
}


template<class T, class C>
void c_AVL_T<T, C>::col_bal(Node<T>* a)
{
	a->niv = altura(a->m_nodes[2]) - altura(a->m_nodes[1]);
}

int auxX = 0;

void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}


template<class T, class C>
void c_AVL_T<T, C>::mostrarArbolito(Node<T>* root, int auxY)
{
	if (!root)
		return;

	auxX += 5;
	mostrarArbolito(root->m_nodes[1], auxY + 2);
	gotoxy(auxX - auxY, auxY);
	cout << root->m_data << endl << endl;
	mostrarArbolito(root->m_nodes[2], auxY + 2);
}
template<typename T>
class pila
{

public:
	Node<T>* top = nullptr; Node<T>* rear = nullptr;
	bool vacio(); //indica si la pila está vacía
	void push(Node<T>* elemento); //agrega un elemento
	Node<T>* pop(); //retirua un elemento y devuelve su valor 
	Node<T>* poprear();
	void print(); //imprime el contenido de la pila
	void levels(Node<T>* M_Root);
	void inorder(Node<T>* M_Root);
	~pila();
	void preorder(Node<T>* M_Root);
	void postorder(Node<T>* M_Root);
	void reverse(Node<T>* M_Root);
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
	Node<T>* tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->m_data << endl;
	cout << "base" << endl;
}

template<typename T>
void pila<T>::levels(Node<T>* M_Root)
{
	int count = 0;
	if (M_Root)
		push(M_Root);
	while (!vacio())
	{
		Node<T>* temp = top;
		if (count != temp->level) {
			cout << endl; count++;
		}
		cout << temp->m_data << " ";

		if (temp->m_nodes[1])
			push(temp->m_nodes[1]);
		if (temp->m_nodes[2])
			push(temp->m_nodes[2]);
		pop();
	}

}

template<typename T>
void pila<T>::inorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->m_nodes[1];
		}
		temp = rear;
		poprear();
		cout << temp->m_data << " ";
		temp = temp->m_nodes[2];
	}
}
template<typename T>
void pila<T>::preorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			cout << temp->m_data << " ";
			if (temp->m_nodes[2])
				push(temp->m_nodes[2]);
			temp = temp->m_nodes[1];
		}
		if (!vacio())
		{
			temp = rear;
			poprear();
		}
	}
}
template<typename T>
void pila<T>::postorder(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			if (temp->m_nodes[2])
				push(temp->m_nodes[2]);
			push(temp);
			temp = temp->m_nodes[1];
		}
		temp = rear; poprear();
		if (temp->m_nodes[2] && rear == temp->m_nodes[2])
		{
			poprear();
			push(temp);
			temp = temp->m_nodes[2];
		}
		else
		{
			cout << temp->m_data << " ";
			temp = NULL;
		}
	}
}
template<typename T>
void pila<T>::reverse(Node<T>* M_Root)
{
	Node<T>* temp = M_Root;
	while (temp || !vacio())
	{
		while (temp)
		{
			push(temp);
			temp = temp->m_nodes[2];
		}
		temp = rear;
		poprear();
		cout << temp->m_data << " ";
		temp = temp->m_nodes[1];
	}
}
template<typename T>
void pila<T>::push(Node<T>* elemento)
{
	if (top)
	{
		Node<T>* temp = elemento; Node<T>* enqueue = top;
		while (enqueue->m_nodes[3])
			enqueue = enqueue->m_nodes[3];
		enqueue->m_nodes[3] = temp;
		rear = temp;
	}
	else
		top = elemento; rear = elemento;

}

template<typename T>
Node<T>* pila<T>::pop()
{
	if (top)
	{
		Node<T>* temp = top;
		top = top->m_nodes[3];
		//delete temp;
		temp->m_nodes[3] = NULL;
		return temp;
	}
}
template<typename T>
Node<T>* pila<T>::poprear()
{
	if (top != rear)
	{
		Node<T>* temp = top;
		while (temp->m_nodes[3] != rear)
		{
			temp = temp->m_nodes[3];
		}
		temp->m_nodes[3] = NULL;
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
		Node<T>* temp = top;
		top = top->m_nodes[3];
		delete temp;
	}
}
template <class T>
void assign(Node<T>* M_Root, int curr = 0)
{
	int current = curr;
	if (M_Root != NULL) {
		assign(M_Root->m_nodes[1], current + 1);
		assign(M_Root->m_nodes[2], current + 1);
		M_Root->level = current;
	}
}
int main()
{
	c_AVL_T<int, Mayor<int>> avlTree;



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
		cout << "Impresion Niveles = 7" << endl;
		cout << "Impresion Niveles sin usar Pila pero mas decente: 8" << endl;
		cout << "Salir = 9" << endl;
		cin >> x;
		if (x == 1)
		{
			int temp;
			cout << "Que elemento desea agregar?" << endl; cin >> temp; avlTree.insert(temp);
		}
		if (x == 2)
		{
			int temp;
			cout << "Que elemento desea borrar?" << endl; cin >> temp; avlTree.remove(temp);
		}
		if (x == 3)
		{
			pila <int>q;
			q.inorder(avlTree.root);
			//Inorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 4)
		{
			pila <int>q;
			q.postorder(avlTree.root);
			//Postorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 5)
		{
			pila <int>q;
			q.preorder(avlTree.root);
			//Preorder(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 6)
		{
			pila <int>q;
			q.reverse(avlTree.root);
			//Reverse(ItTree.M_Root); cout << endl;
			system("pause");
		}
		if (x == 7)
		{
			assign(avlTree.root);
			pila <int>q;
			q.levels(avlTree.root);
			system("pause");
		}
		if (x == 8)
		{
			system("cls");
			avlTree.mostrarArbolito(avlTree.root, 1);
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
