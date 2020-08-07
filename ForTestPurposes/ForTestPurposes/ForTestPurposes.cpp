// ForTestPurposes.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <queue>

using namespace std;

template<class T>
struct cless
{
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};
template<class T>
struct cgreater
{
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

////////////////////////////////11/////////////////////////////////////////////////////////111
///////////////////////////////////////////////////////////////////////////////////////
//NODO TREE

template<class T>
struct nodo
{
	/*
		T v;
		//nodo *l,*r;
		nodo<T>*nodos[2];
		nodo(T _v)
		{
			v=_v;
			nodos[0]=nodos[1]=0;

		}

	*/
	T m_data;
	int niv;
	nodo* m_nodes[3];
	nodo(T m_data_, nodo* padre) {
		m_data = m_data_;
		niv = 0;
		m_nodes[0] = padre;
		m_nodes[1] = NULL;
		m_nodes[2] = NULL;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//NODO Pila

template<class T>
struct Snodo
{
	nodo<T>* S_Node;
	Snodo<T>* next;
	//T v;
	int state;

	/*
	Snodo(T _valor,Snodo* _next=nullptr)
	{ valor = _valor; next = _next;};*/
	Snodo(nodo<T>* p, int s = 0) {
		S_Node = p;
		state = s;
		next = 0;
	}
};

//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class pila
{
	//Snodo<T>* top= nullptr;
public:
	Snodo<T>* head;
	Snodo<T>* tail;
	bool vacio(); //indica si la pila está vacía
	//void push(T elemento); //agrega un elemento
	bool push(nodo<T>* ptr, short int state = 0);
	pila() { head = tail = 0; }
	Snodo<T>* pop(); //retirua un elemento y devuelve su valor
	Snodo<T>* top();
	void print(); //imprime el contenido de la pila
	void printtop();
	//~pila();
	//nodo<T>* top= nullptr;
};

template<class T>
void pila<T>::printtop() {
	cout << top->valor << " ";
}
template<class T>
bool pila<T>::vacio()
{
	return head == NULL;
}

template<class T>
void pila<T>::print()
{
	Snodo<T> tmp = top;
	cout << "cima" << endl;
	for (; tmp; tmp = tmp->next)
		cout << tmp->valor << endl;
	cout << "base" << endl;
	Snodo<T>* temp = head;
	cout << "R: ";
	while (temp) {
		cout << "[ " << temp->S_Node->M_x << " s: " << temp->state << " ] ";
		temp = temp->S_Next;
	}
	cout << " -/ " << endl;
}

template<class T>
bool pila<T>::push(nodo<T>* ptr, short int state)
{
	if (!head) {
		head = new Snodo<T>(ptr, state);
		tail = head;
		return 1;
	}
	Snodo<T>* temp = new Snodo<T>(ptr, state);
	temp->next = head;
	head = temp;
	return 1;
}
/*void pila<T>::push(T elemento)
{
	//TO DO
	if(vacio())
	{
		top = new struct Snodo<T>(elemento);
	}
	else
	{
		Snodo<T> *temp = new struct Snodo<T>(elemento, top);
		top = temp;
	}
}*/

template<typename T>
Snodo<T>* pila<T>::pop()
{/*
	if(!vacio())
	{
		Snodo<T> *temp = top();
		top() = top()->next;
		T valueTemp = temp->valor;
		delete temp;
		return valueTemp;
	}
	return 0;*/
	if (head == tail) {
		Snodo<T>* val_return = head;
		delete head;
		head = tail = 0;
		return val_return;
	}
	else {
		Snodo<T>* Recorre = head;
		Snodo<T>* val_return = head;
		head = head->next;
		delete Recorre;
		return val_return;
	}
}

template<class T>
Snodo<T>* pila<T>::top()
{
	if (!head) {
		return 0;
	}
	return head;
}
/*
template<typename T>
pila<T>::~pila()
{
	while(!vacio()){
		pop();
	}
	cout<<endl;
	cout<<"Pila Destruida:";
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CLASS DE ITERADORES
template<class T>
class CIteratorLevels
{
public:
	queue<nodo<T>*> colita;
	nodo<T>* aux;
	CIteratorLevels(nodo<T>* p = 0) {
		colita.push(p);
		aux = p;
	}
	CIteratorLevels<T> operator = (CIteratorLevels<T> It1);
	bool operator !=(CIteratorLevels<T> It);
	CIteratorLevels<T> operator ++(int);
	T operator *();
};
template<class T>
class CItx {
public:
	pila<T> stock;
	nodo<T>* CItx_Head;
	nodo<T>* aux;
	CItx(nodo<T>* p = 0) {
		CItx_Head = p;
	}
	int state_print() { return 1; }
	CItx<T> operator = (CItx<T> It1);
	bool operator!= (CItx<T> It);
	CItx<T> operator ++(int);
	T operator *();
};
template<class T>
class cIteratorPostOrder {
public:
	pila<T> stock;
	nodo<T>* CItx_Head;
	nodo<T>* aux;
	cIteratorPostOrder(nodo<T>* p = 0) {
		CItx_Head = p;
	}
	int state_print() { return 2; }
	cIteratorPostOrder<T> operator = (cIteratorPostOrder<T> It1);
	bool operator!= (cIteratorPostOrder<T> It);
	cIteratorPostOrder<T> operator ++(int);
	T operator *();
};
template<class T>
class CItxPreOrder {
public:
	pila<T> stock;
	nodo<T>* CItx_Head;
	nodo<T>* aux;
	CItxPreOrder(nodo<T>* p = 0) {
		CItx_Head = p;
	}
	int state_print() { return 1; }
	CItxPreOrder<T> operator = (CItxPreOrder<T> It1);
	bool operator!= (CItxPreOrder<T> It);
	CItxPreOrder<T> operator ++(int);
	T operator *();
};
template<class T>
class CItxReverse {
public:
	pila<T> stock;
	nodo<T>* CItx_Head;
	nodo<T>* aux;
	CItxReverse(nodo<T>* p = 0) {
		CItx_Head = p;
	}
	int state_print() { return 1; }
	CItxReverse<T> operator = (CItxReverse<T> It1);
	bool operator!= (CItxReverse<T> It);
	CItxReverse<T> operator ++(int);
	T operator *();
};

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//ARBOL
template<class T, class C>	class ctree {
public:
	C cmp;
	ctree() { m_root = 0; }
	~ctree() {
		while (m_root) {
			nodo<T>* tmp = m_root;
			remove(tmp->m_data);
		}
		cout << endl;
		cout << "Arbol Destruido:";
	}

	bool find(T x, nodo<T>**& p);
	bool insert(T x);
	bool remove(T x);

	void balancear(nodo<T>*);
	nodo<T>* rot_sim_i(nodo<T>*);
	nodo<T>* rot_sim_d(nodo<T>*);
	nodo<T>* rot_i_d(nodo<T>*);
	nodo<T>* rot_d_i(nodo<T>*);

	int altura(nodo<T>*);
	void col_bal(nodo<T>*);

	void mostrarArbolito(nodo<T>* m_root, int auxY);
	nodo<T>* Rep(nodo<T>* p);
	void print();
	void rec_print(nodo<T>* nodo, int space);
	typedef CItx<T> InOrderIterator;
	typedef cIteratorPostOrder<T> PostOrderiterator;
	typedef CItxPreOrder<T> PreOrderIterator;
	typedef CItxReverse<T> ReverseIterator;
	typedef CIteratorLevels<T> LevelsIterator;

	//private:
	nodo<T>* m_root;

	InOrderIterator InOrderBegin() {
		nodo<T>* temp = m_root;
		InOrderIterator It;
		It.stock.push(m_root);
		while (temp && temp->m_nodes[1]) {
			temp = temp->m_nodes[1];
		}
		It.CItx_Head = temp;
		return It;
	}
	InOrderIterator InOrderEnd() {
		return InOrderIterator();
	}

	PostOrderiterator PostOrderBegin()
	{
		nodo<T>* temp = m_root;
		PostOrderiterator It;
		It.stock.push(m_root);
		while (temp && temp->m_nodes[1]) {
			temp = temp->m_nodes[1];
		}
		It.CItx_Head = temp;
		return It;
	}
	PostOrderiterator PostOrderEnd()
	{
		return PostOrderiterator();
	}

	PreOrderIterator PreOrderBegin()
	{
		nodo<T>* temp = m_root;
		PreOrderIterator It;
		It.stock.push(m_root);
		It.CItx_Head = temp;
		return It;
	}
	PreOrderIterator PreOrderEnd()
	{
		return PreOrderIterator();
	}

	ReverseIterator ReverseBegin()
	{
		nodo<T>* temp = m_root;
		ReverseIterator It;
		It.stock.push(m_root);
		while (temp && temp->m_nodes[2]) {
			temp = temp->m_nodes[2];
		}
		It.CItx_Head = temp;
		return It;
	}
	ReverseIterator ReverseEnd()
	{
		return ReverseIterator();
	}
	LevelsIterator LevelsBegin()
	{
		LevelsIterator It(m_root);
		return It;
	}
	LevelsIterator LevelsEnd()
	{
		return LevelsIterator();
	}

};


template<class T, class C>
bool ctree<T, C>::find(T x, nodo<T>**& p) {
	/*p=&m_root;
	while(*p&&(*p)->v!=x)
		p=&((*p)->nodos[cmp((*p)->v,x) ]);
	return p!=0;/
	for (p = &m_root; *p && (*p)->v != x; p = &(*p)->nodos[cmp((*p)->v, x)]);
	return *p != NULL;
}
template<class T,class C>
bool ctree<T,C>::insert(T x){
	/*nodo<T> **p;
	if(find(x,p))
		return 0;
	*p=new nodo<T>(x);
	return 1;	*/

	if (x == 0)
		return 0;

	bool seguir = true;
	if (!m_root)
		m_root = new nodo<T>(x, nullptr);
	else
	{
		nodo<T>* temp = m_root;
		nodo<T>* temp2;
		while (seguir) {
			if (temp->m_data == x)
				break;

			temp2 = temp;

			bool dir = cmp(temp->m_data, x);

			if (dir)
				temp = temp->m_nodes[1];
			else
				temp = temp->m_nodes[2];

			if (!temp)
			{
				if (dir)
					temp2->m_nodes[1] = new nodo<T>(x, temp2);
				else
					temp2->m_nodes[2] = new nodo<T>(x, temp2);

				balancear(temp2);
				seguir = false;
			}
		}
	}
	return 0;
}

template<class T, class C>
bool ctree<T, C>::remove(T x)
{
	/*
	nodo<T>** p;
	if ( !find(x,p) ) return 0;
	if ( (*p)->nodos[2] && (*p)->nodos[1] )
	{
		nodo<T>** q = Rep(p);
		(*p)->v = (*q)->v;
		p = q;
	}
	nodo<T>* t = *p;
	*p = (*p)->nodos[ !(*p)->nodos[2] ];
	delete t;
	return 0;//chrcar*/
	if (!m_root)
		return 0;

	nodo<T>* temp = m_root;
	nodo<T>* temp2 = m_root;
	nodo<T>* hijo = m_root;
	nodo<T>* to_delete = NULL;
	while (hijo)
	{
		temp2 = temp;
		temp = hijo;
		if (x < temp->m_data)
			hijo = temp->m_nodes[2];
		else
			hijo = temp->m_nodes[1];


		if (x == temp->m_data)
			to_delete = temp;
	}

	if (to_delete)
	{
		to_delete->m_data = temp->m_data;

		if (temp->m_nodes[1])
			hijo = temp->m_nodes[1];
		else
			hijo = temp->m_nodes[2];

		if (m_root->m_data == x)
			m_root = hijo;
		else
		{
			if (temp2->m_nodes[1] == temp)
				temp2->m_nodes[1] = hijo;
			else
				temp2->m_nodes[2] = hijo;

			balancear(temp2);
		}
	}
	return 0;
}
template<class T, class C>
nodo<T>* ctree<T, C>::Rep(nodo<T>* p)
{
	bool b = rand() % 2;
	for (p = &((*p)->nodos[b]); (*p)->nodos[!b]; p = &((*p)->nodos[!b]));
	return p;
}
template<class T, class C>
nodo<T>* ctree<T, C>::rot_sim_i(nodo<T>* a)
{
	nodo<T>* temp = a->m_nodes[2];
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
nodo<T>* ctree<T, C>::rot_sim_d(nodo<T>* a)
{
	nodo<T>* temp = a->m_nodes[1];
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
nodo<T>* ctree<T, C>::rot_i_d(nodo<T>* a)
{
	a->m_nodes[1] = rot_sim_i(a->m_nodes[1]);
	return rot_sim_d(a);
}

template<class T, class C>
nodo<T>* ctree<T, C>::rot_d_i(nodo<T>* a)
{
	a->m_nodes[2] = rot_sim_d(a->m_nodes[2]);
	return rot_sim_i(a);
}

template<class T, class C>
int ctree<T, C>::altura(nodo<T>* a)
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
void ctree<T, C>::balancear(nodo<T>* a)
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
		m_root = a;
}


template<class T, class C>
void ctree<T, C>::col_bal(nodo<T>* a)
{
	a->niv = altura(a->m_nodes[2]) - altura(a->m_nodes[1]);
}

template<class T, class C>
void ctree<T, C>::rec_print(nodo<T>* nodo, int space)
{
	if (nodo == NULL)
		return;
	else
	{
		space += 3;

		rec_print(nodo->m_nodes[1], space);

		cout << endl;
		for (int i = 3; i < space; i++)
			cout << " ";
		cout << nodo->m_data << endl;

		rec_print(nodo->m_nodes[2], space);
	}
}

template<class T, class C>
void ctree<T, C>::print() {
	cout << "ARBOL:" << endl << endl;
	rec_print(m_root, 0);
	cout << endl;
	cout << endl;
	//cout<<"Inorder: ";inorder(m_root);
	//cout<<endl;
	//cout<<"Preorder: ";preorder(m_root);
	//cout<<endl;
	//cout<<"Posorder: ";posorder(m_root);
	//cout<<endl;
	//cout<<"Reverse: ";reverse(m_root);
}
////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//ITERADORES

template<class T>
CIteratorLevels<T> CIteratorLevels<T>::operator= (CIteratorLevels<T> Itxd) {
	colita = Itxd.colita;
	aux = Itxd.aux;
	return Itxd;

}
template<class T>
bool CIteratorLevels<T>::operator!=(CIteratorLevels<T> Itxd)
{
	return colita.size() > 0;
}
template<class T>
CIteratorLevels<T> CIteratorLevels<T>::operator ++(int)
{

	if (aux->m_nodes[2])

		colita.push(aux->m_nodes[2]);
	if (aux->m_nodes[1])
		colita.push(aux->m_nodes[1]);

	colita.pop();

	if (!colita.empty())
		aux = colita.front();
	return *this;
}
template<class T>
T CIteratorLevels<T>::operator * () {
	if (aux)
		return aux->m_data;
	return -1;
}
template<class T>
CItx<T> CItx<T>::operator = (CItx<T> It1) {
	CItx_Head = It1.CItx_Head;
	stock.head = It1.stock.head;
	return It1;
}
template<class T>
bool CItx<T>::operator != (CItx<T> It) {
	return !stock.vacio();
}
template<class T>
CItx<T> CItx<T>::operator ++(int) {
	Snodo<T>* Comp = stock.top();
	aux = Comp->S_Node;
	switch (Comp->state)
	{
	case 0:
		if (aux->m_nodes[2] == NULL) {
			Comp->state = 1;
			break;
		}
		Comp->state = 1;
		stock.push(aux->m_nodes[2], 0);
		break;


	case 1:
		Comp->state = 2;
		break;
	case 2:
		if (aux->m_nodes[1] == NULL) {
			Comp->state = 3;
			break;
		}
		stock.push(aux->m_nodes[1], 0);
		Comp->state = 3;
		break;
	case 3:
		stock.pop();
		break;
	}
	return *this;
}
template<class T>
T CItx<T>::operator * () {
	if (stock.top()->state == 1) {
		return stock.top()->S_Node->m_data;
	}
	return -1;
}
template<class T>
cIteratorPostOrder<T> cIteratorPostOrder<T>::operator = (cIteratorPostOrder<T> It1)
{
	CItx_Head = It1.CItx_Head;
	stock.head = It1.stock.head;
	return It1;
}
template<class T>
bool cIteratorPostOrder<T>::operator!= (cIteratorPostOrder<T> It)
{
	return !stock.vacio();
}
template<class T>
cIteratorPostOrder<T> cIteratorPostOrder<T>::operator ++(int)
{
	Snodo<T>* Comp = stock.top();
	aux = Comp->S_Node;
	switch (Comp->state)
	{
	case 0:
		if (aux->m_nodes[2] == NULL) {
			Comp->state = 1;
			break;
		}
		Comp->state = 1;
		stock.push(aux->m_nodes[2], 0);
		break;
	case 1:
		if (aux->m_nodes[1] == NULL) {
			Comp->state = 2;
			break;
		}
		stock.push(aux->m_nodes[1], 0);
		Comp->state = 2;
		break;
	case 2:
		Comp->state = 3;
		break;
	case 3:
		stock.pop();
		break;

	}
	return *this;
}
template<class T>
T cIteratorPostOrder<T>::operator *()
{
	if (stock.top()->state == 2) {
		return stock.top()->S_Node->m_data;
	}
	return -1;
}
template<class T>
CItxPreOrder<T> CItxPreOrder<T>::operator = (CItxPreOrder<T> It1)
{
	CItx_Head = It1.CItx_Head;
	stock.head = It1.stock.head;
	return It1;
}
template<class T>
bool CItxPreOrder<T>::operator!= (CItxPreOrder<T> It)
{
	return !stock.vacio();
}
template<class T>
CItxPreOrder<T> CItxPreOrder<T>::operator ++(int)
{
	Snodo<T>* Comp = stock.top();
	aux = Comp->S_Node;
	switch (Comp->state)
	{
	case 0:
		Comp->state = 1;
		break;

	case 1:
		if (aux->m_nodes[2] == NULL) {
			Comp->state = 2;
			break;
		}
		Comp->state = 2;
		stock.push(aux->m_nodes[2], 0);
		break;
	case 2:
		if (aux->m_nodes[1] == NULL) {
			Comp->state = 3;
			break;
		}
		stock.push(aux->m_nodes[1], 0);
		Comp->state = 3;
		break;
	case 3:
		stock.pop();
		break;
	}
	return *this;
}
template<class T>
T CItxPreOrder<T>::operator *()
{
	return stock.top()->S_Node->m_data;
}
template<class T>
CItxReverse<T> CItxReverse<T>::operator = (CItxReverse<T> It1)
{
	CItx_Head = It1.CItx_Head;
	stock.head = It1.stock.head;
	return It1;
}
template<class T>
bool CItxReverse<T>::operator!= (CItxReverse<T> It)
{
	return !stock.vacio();
}
template<class T>
CItxReverse<T> CItxReverse<T>::operator ++(int)
{
	Snodo<T>* Comp = stock.top();
	aux = Comp->S_Node;
	switch (Comp->state)
	{
	case 0:
		if (aux->m_nodes[2] == NULL) {
			Comp->state = 1;
			break;
		}
		stock.push(aux->m_nodes[1], 0);
		Comp->state = 1;
		break;
	case 1:
		Comp->state = 2;
		break;
	case 2:
		if (aux->m_nodes[2] == NULL) {
			Comp->state = 3;
			break;
		}
		Comp->state = 3;
		stock.push(aux->m_nodes[2], 0);
		break;
	case 3:
		stock.pop();
		break;
	}
	return *this;
}
template<class T>
T CItxReverse<T>::operator *()
{
	return stock.top()->S_Node->m_data;
}

///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void pausa();
int main()
{

	ctree<int, cless<int>> a;
	ctree<int, cless<int>> ::InOrderIterator i;
	ctree<int, cless<int>> ::PreOrderIterator k;
	ctree<int, cless<int>> ::PostOrderiterator j;
	ctree<int, cless<int>> ::ReverseIterator l;
	ctree<int, cless<int>> ::LevelsIterator m;


	int n = 0;
	bool bandera = false;
	char tecla;


	do
	{
		system("cls");
		cin.clear();
		cout << "Arbol AVL: " << endl;
		cout << "-----------" << endl << endl;
		cout << "\t1 .- Insertar" << endl;
		cout << "\t2 .- Eliminar" << endl;
		cout << "\t3 .- Imprimir" << endl;
		cout << "\t4 .- Niveles" << endl;
		cout << "\t0 .- Salir" << endl << endl;
		cout << "Elije una opcion: ";

		cin >> tecla;

		switch (tecla)
		{
		case '1':
			system("cls");
			cout << "Has elejido: Insertar.\n" << endl;
			a.print();
			cout << endl;
			cout << "Ingresa numero a insertar.\n" << endl;
			cin >> n;
			a.insert(n);
			a.print();
			cout << endl;
			pausa();
			break;

		case '2':
			system("cls");
			cout << "Has elejido: Eliminar.\n" << endl;
			a.print();
			cout << endl;
			cout << "Ingresa numero a eliminar.\n" << endl;
			cin >> n;
			a.remove(n);
			cout << endl;
			a.print();
			cout << endl;
			pausa();
			break;

		case '3':
			system("cls");
			cout << "Has elejido: Imprimir.\n" << endl;
			a.print();
			if (a.m_root) {
				cout << "Inorder: ";

				for (i = a.InOrderBegin(); i != a.InOrderEnd(); i++) {
					if (i.stock.top()->state == i.state_print()) {
						cout << *i << " ";
					}
				}
				cout << endl;


				cout << "Preorder: ";

				for (k = a.PreOrderBegin(); k != a.PreOrderEnd(); k++) {
					if (k.stock.top()->state == k.state_print()) {
						cout << *k << " ";
					}
				}

				cout << endl;

				cout << "Posorder: ";

				for (j = a.PostOrderBegin(); j != a.PostOrderEnd(); j++) {
					if (j.stock.top()->state == j.state_print()) {
						cout << *j << " ";
					}
				}

				cout << endl;

				cout << "Reverse: ";

				for (l = a.ReverseBegin(); l != a.ReverseEnd(); l++) {
					if (l.stock.top()->state == l.state_print()) {
						cout << *l << " ";
					}
				}
				cout << endl;
			}
			pausa();
			break;

		case '4':
			system("cls");
			cout << endl;

			cout << "Por niveles: ";
			if (a.m_root) {
				for (m = a.LevelsBegin(); m != a.LevelsEnd(); m++) {
					cout << *m << " ";
				}
				cout << endl;
				cout << endl;
				cout << endl;
				a.print();

			}
			cout << endl;
			pausa();
			break;

		case '0':
			bandera = true;
			//exit(1);
			break;

		default:
			system("cls");
			cout << "Opcion no valida.\a\n";
			pausa();
			break;
		}
	} while (bandera != true);

	return 0;
}

void pausa()
{
	cout << "Pulsa enter para continuar...";
	getwchar();
	getwchar();
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
