

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
void swap_cuock(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T, class Op>
int partition(T arr[], int low, int high)
{
	Op o;
	T pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		//if (arr[j] < pivot)
		//if ((p.*o)(arr[j], pivot))
		if (o(arr[j], pivot))
		{
			i++;
			swap_cuock(arr[i], arr[j]);
		}
	}
	swap_cuock(arr[i + 1], arr[high]);
	return (i + 1);
}

template<class T, class Op>
void quickSort(T arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition<T, Op>(arr, low, high);
		quickSort<T, Op>(arr, low, pi - 1);
		quickSort<T, Op>(arr, pi + 1, high);
	}
}
template<class T>
struct C_Node {
	T C_Value;
	C_Node<T> *C_Next, *C_Prev;
	C_Node() {};
	C_Node(T dato) { C_Value = dato; C_Prev = NULL; C_Next = NULL; };
	C_Node(T dato, C_Node<T> *ant, C_Node<T> *sgt) { C_Value = dato; C_Prev = ant; C_Next = sgt; };
};

template<class T, class Op>
class C_List {
public:
	C_Node<T> *C_Head;
	Op o;
	C_List() { C_Head = NULL; };
	bool buscar(T dato, C_Node<T> *&actual);
	bool insertar(T dato);
	bool borrar(T dato);
	void print();
	void Josephus(int k);
};
template<class T, class Op>
bool C_List<T,Op>::buscar(T dato, C_Node<T> *&actual) {
	actual = C_Head;
	if (C_Head->C_Value == dato) return 1;
	actual = C_Head->C_Next;
	while (actual != C_Head && o(actual->C_Value,dato)) {
		actual = actual->C_Next;
	}
	return (actual->C_Value == dato);
}
template<class T, class Op>
bool C_List<T,Op>::insertar(T dato) {
	if (C_Head == NULL) {
		C_Head = new C_Node<T>(dato);
		C_Head->C_Next = C_Head;
		C_Head->C_Prev = C_Head;
		return 1;
	}
	if (o(dato, C_Head->C_Value)) {
		C_Node<T> *nuevo = new C_Node<T>(dato, C_Head->C_Prev, C_Head);
		C_Head->C_Prev->C_Next = nuevo;
		C_Head->C_Prev = nuevo;
		C_Head = nuevo;
		return 1;
	}
	C_Node<T> *actual;
	if (buscar(dato, actual)) return 0;
	C_Node<T> *nuevo = new C_Node<T>(dato, actual->C_Prev, actual);
	actual->C_Prev->C_Next = nuevo;
	actual->C_Prev = nuevo;
	return 1;
}
template<class T, class Op>
bool C_List<T,Op>::borrar(T dato) {
	C_Node<T> *actual;
	if (!buscar(dato, actual)) return 0;
	if (actual == C_Head) {
		C_Head->C_Prev->C_Next = C_Head->C_Next;
		C_Head->C_Next->C_Prev = C_Head->C_Prev;
		C_Head = C_Head->C_Next;
		delete actual;
		return 1;
	}
	C_Node<T> *temp = actual;
	actual->C_Prev->C_Next = actual->C_Next;
	actual->C_Next->C_Prev = actual->C_Prev;
	delete temp;
	return 1;

}
template<class T, class Op>
void C_List<T,Op>::print() {
	C_Node<T> *actual = C_Head;
	cout << actual->C_Value << " ";
	actual = actual->C_Next;
	while (actual != C_Head) {
		cout << actual->C_Value << " ";
		actual = actual->C_Next;
	}
	cout << endl;
}
template<class T, class Op>
void C_List<T,Op>::Josephus(int k) {
	
	C_Node<int> *ptr = C_Head->C_Prev;
	//print();
	while (C_Head->C_Next->C_Next != C_Head) {
		for (int j = 0; j < k; j++) {
			ptr = ptr->C_Next;
		}
		ptr = ptr->C_Next;
		borrar(ptr->C_Prev->C_Value);
		ptr = ptr->C_Prev;
		print();
	}
	cout << "Primer sobreviviente = " << C_Head->C_Value << endl;
	cout << "Segundo sobreviviente = " << C_Head->C_Next->C_Value << endl;

}

int main() {
	C_List<int,Menor<int>> list_cueck;
	int len;
	cout << "Creando Lista" << endl;
	cout << "Ingrese la cantidad de elementos que tendra la lista: ";
	cin >> len;
	for (int i = len; i >= 1; i--) {
		list_cueck.insertar(i);
	};
	int watashiwaldes;
	list_cueck.print();
	cout << "Ingrese los ciclos del Josephus: ";
	cin >> watashiwaldes;
	list_cueck.Josephus(watashiwaldes);
	/*C_List<int, Menor<int>> list_cueck;
	list_cueck.insertar(10);
	list_cueck.insertar(1);
	list_cueck.insertar(2);
	list_cueck.insertar(9);
	list_cueck.insertar(8);
	list_cueck.insertar(7);
	list_cueck.insertar(3);
	list_cueck.insertar(4);
	list_cueck.insertar(5);
	list_cueck.insertar(6);
	list_cueck.print();
	list_cueck.Josephus(3);*/

	return 0;
}
