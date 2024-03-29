// Functor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
template<class T>
class CLess
{
public:
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};

template<class T>
class CGreater
{
public:
	inline bool operator()(T a, T b)
	{
		return a < b;
	}
};
void randGen(int *arr, long tam)
{
	srand(time(NULL));
	for (int i = 0; i < tam; i++)
	{
		*(arr + i) = ((rand() % (int)(10001)));
	}
}
void swap(int &a, int &b)
{
	int aux;
	aux = a;
	a = b;
	b = aux;
}
template<class T>
int partition(int *A, int low, int high, T functor)
{
	int *pivot = A + high;    // pivote 
	int i = (low - 1);  // Index del element m�s peque�o peee 
	for (int j = low; j <= high - 1; j++)
	{
		// Ta que si el elemento actual es m�s peque�o o 
		// igual al pivote 
		if (functor(*(A + j), *pivot)) //FUNCTOR
		{
			i++;    // incrementar index del elemento m�s peque�o
			swap(*(A + i), *(A + j));
		}
	}
	swap(*(A + i + 1), *(A + high));
	return (i + 1);
} 
template<class T>
void quickSort(int *A, int low, int high,T functor)
{
	if (low < high)
	{
		// pi is partitioning index, arr[p] is now
		 //  at right place
		int pi = partition(A, low, high,functor);

		// Separately sort elements before
		// partition and after partition
		quickSort(A, low, pi - 1,functor);
		quickSort(A, pi + 1, high,functor);
	}
}
int main()
{
	long int tam = 1000;
	int *arr = NULL;
	arr = new int[tam];
	randGen(arr, tam);

	CGreater<int> GSort;
	CLess<int> LSort;
	clock_t inicio;
	float duracion;
	srand(time(NULL));
	inicio = clock();
	quickSort(arr,0,tam-1, LSort);
	duracion = (clock() - inicio) / (float)CLOCKS_PER_SEC;
	//impresi�n del array para verificar errores
	/*
	for (int *p = arr;p < arr + tam;p++)
	{
		cout << *p << endl;
	}
	cout << endl;*/
	cout << " Tiempo :" << duracion << endl;

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
