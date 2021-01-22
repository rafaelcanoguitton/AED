// IteratorVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

template<class T>
class Iterador
{
	int m_i;
	T *m_v;
public:
	Iterador<T>(T *v = 0, int i = 0)
	{
		m_i = i;
		m_v = v;
	}
	Iterador<T> operator =(Iterador<T> x)
	{
		m_i = x.m_i;
		m_v = x.m_v;
		return *this;

	}
	bool operator !=(Iterador<T> x)
	{
		return m_i != x.m_i;

	}
	Iterador<T> operator ++()
	{
		m_i++;
		return *this;
	}
	void operator --()
	{
		--m_i;
	}
	T operator *()
	{
		return m_v[m_i];
	}
};

template<class T>
struct Vector
{
	int n;
	T *ptr;
	typedef Iterador<T> iterador;
	Vector(T _n)
	{
		n = _n;
		ptr = new T[_n];
	}
	T & operator [](int x)
	{
		return *(ptr + x); //the position *(p) *(p+1)....*(p+n) and any other
	}
	iterador begin()
	{
		return iterador(ptr, 0); //begin whit 0 and valor
	}
	iterador end()
	{
		return iterador(ptr, n); //end of the vector
	}
	//reverse
	iterador beginr()
	{
		return iterador(ptr, n - 1);
	}
	iterador endr()
	{
		return iterador(ptr, -1);
	}
};


int main()
{
	cout << "ITERATOR TO VECTOR" << endl;
	cout << "\n";
	Vector<int> v(5);
	Vector<int>::iterador i;

	for (int j = 0; j < 5; j++)
		v[j] = j;

	for (i = v.begin(); i != v.end(); ++i)
		cout << *i << " ";

	cout << "\n";
	cout << "Reverse" << endl;
	for (i = v.beginr(); i != v.endr(); --i)
		cout << *i << " ";



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
