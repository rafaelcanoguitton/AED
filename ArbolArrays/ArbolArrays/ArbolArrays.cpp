// ArbolArrays.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
using namespace std;
template<class T>
class ArrTree
{
public:
	T ele;
	T arr[3][100];
	ArrTree(T e) { arr[0][0] = e;arr[1][0] = -1;arr[2][0] = -1;ele = 1; };
	void Insert(T x);
	void Delete(T x);
	void Print();
};
template <class T>
void ArrTree<T>::Insert(T x)
{
	bool i = true;
	int num = 0;
	while (i)
	{
		if (x > arr[0][num])
		{
			if (arr[2][num] == -1)
			{
				arr[2][num] = ele;
				arr[0][ele] = x;
				arr[1][ele] = -1;
				arr[2][ele] = -1;
				ele++;
				i = false;
			}
			else
				num = arr[2][num];
		}
		else
		{
			if (arr[1][num] == -1)
			{
				arr[1][num] = ele;
				arr[0][ele] = x;
				arr[1][ele] = -1;
				arr[2][ele] = -1;
				ele++;
				i = false;
			}
			else
				num = arr[1][num];
		}
	}
};

template<class T>
void ArrTree<T>::Delete(T x)
{
	int pos;int posi;
	bool i = true;bool change = false;
	for (int i = 0;i < ele;i++)
	{
		if (arr[0][i] == x)
		{
			pos = i;
			posi = i;
			i = ele;
		}
	}
	while (i)
	{
		if (arr[1][pos] == -1 && arr[2][pos] == -1)
		{
			if (change = true)
			{
				int temp = arr[0][posi];
				arr[0][posi] = arr[0][pos];
				arr[0][pos] = temp;
			}
			arr[0][pos] = -1;
			i = false;
		}
		else if (arr[1][pos] != -1 && arr[2][pos] != -1)
		{
			pos = arr[2][pos];
			change = true;
		}
		else if (arr[1][pos] == -1)
		{
			cout << arr[1][pos];
			pos = arr[2][pos];
			change = true;
		}
		else if (arr[2][pos] == -1)
		{
			pos = arr[1][pos];
			change = true;
		}

	}
};
template<class T>
void ArrTree<T>::Print()
{
	cout << "PADRE --> HI,HD" << endl;
	for (int i = 0;i < ele;i++)
	{
		if (arr[0][i] != -1)
		{
			cout << arr[0][i];
			if (arr[1][i] == -1)
				cout << "---> " << "NUAI" << " , ";
			else
				cout << "---> " << arr[0][arr[1][i]] << " , ";
			if (arr[2][i] == -1)
				cout << "NUAI" << endl;
			else
				cout << arr[0][arr[2][i]] << endl;
		}
	}
	/*for (int i = 0;i < ele;i++)
	{
		cout << arr[0][i];
	}
	cout << endl;
	for (int i = 0;i < ele;i++)
	{
		cout << arr[1][i];
	}
	cout << endl;
	for (int i = 0;i < ele;i++)
	{
		cout << arr[2][i];
	}
	cout << endl;*/

};
int main()
{
	ArrTree<int> test(5);
	test.Insert(3);
	test.Insert(1);
	test.Insert(4);
	test.Print();
	test.Delete(5);
	test.Print();
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
