// CircularsSinglePointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

template <class T>
class Nodo
{
public:
	T valor;
	Nodo *next;
	Nodo<T>(T _valor, Nodo<T>* _next = NULL)
	{
		valor = _valor;
		next = _next;
	}


};


template <class T>
class Lista
{
public:
	Nodo<T> *head;


	Lista(){head = NULL;}
	bool Buscar(T valor)
	{
		Nodo<T> *temp = head;
		if (head != 0)
		{
			if (temp->valor == valor)
			{
				return 1;
			}
			temp = temp->next;
			while (temp != head)
			{
				if (temp->valor == valor)
				{
					return 1;
				}
				temp = temp->next;

			}
		}
		return 0;

	}
	void Agregar(T valor)
	{
		if (!Buscar(valor))
		{
			if (head == 0)
			{
				head = new Nodo<T>(valor);
				head->next = head;
				return;
			}

			Nodo<T> *temp = head;

			do {

				if (temp->valor > valor) //NO PERDER LA CABEZA CUANDO EXISTA UN VALOR MENOR A ESTA
				{
					Nodo<T> *last = head;
					while (last->next != head)
					{
						last = last->next;
					}
					head = new Nodo<T>(valor, temp);
					last->next = head;
					return;

				}
				else if (temp->next->valor > valor)//MEDIO
				{
					temp->next = new Nodo<T>(valor, temp->next);
					return;
				}

				else if (temp->next == head) //FINAL
				{
					temp->next = new Nodo<T>(valor, head);
					return;
				}
				temp = temp->next;

			} while (temp != head);

		}

	}
	void Eliminar(T valor)
	{
		if (head != 0 and Buscar(valor))
		{
			Nodo<T> *temp = head;
			if (head->valor == valor)
			{
				Nodo<T> *last = head;
				while (last->next != head)
				{
					last = last->next;
				}
				last->next = head->next;
				delete head;
				head = last->next;
				return;
			}
			do
			{
				if (temp->next->next == head) // FINAL
				{
					delete temp->next;
					temp->next = head;
					return;
				}
				else if (temp->next->valor == valor) // MEDIO
				{
					Nodo<T> *next = temp->next->next;
					delete temp->next;
					temp->next = next;
					return;
				}
				temp = temp->next;
			} while (temp != head);
		}

	}


	~Lista()
	{
		if (head != 0)
		{
			Nodo<T> *temp = head;
			while (temp)
			{
				Nodo<T> *next = temp->next;
				delete temp;
				temp = next;
			}
		}

	}


	void Imprimir()
	{
		if (head != 0)
		{
			Nodo<T> *temp = head;

			do
			{
				cout << temp->valor << " ";
				if (temp->next)
					cout << "-> " << temp->next->valor << endl;
				temp = temp->next;
			} while (temp != head);
		}
	}

	void josephus(int n, int k)
	{
		int Nmuertos = 0;
		for (int i = 1;i <= n;i++)
			Agregar(i);
		Imprimir();
		Nodo<T> *ptr = head; Nodo<T> *prev = head;
		while (Nmuertos < n)
		{
			for (int i = 0; i < k - 1;i++)
				ptr = ptr->next;
			while (prev->next != ptr)
				prev = prev->next;
			if (ptr == head)
				head = head->next;
			prev->next = ptr->next;
			ptr = prev->next;
			Nmuertos++;
		}
		cout << "Playing the Josephus Game with " << n << " people, eliminating every " << k << " people, leaves person " << head->valor << " as the last survivor." << endl;
		cout << "\n";

	}

};
std::string getFileContents(std::ifstream& File)
{
	std::string Lines = "";        //All lines

	if (File)                      //Check if everything is good
	{
		while (File.good())
		{
			std::string TempLine;                  //Temp line
			std::getline(File, TempLine);        //Get temp line
			TempLine += "\n";                      //Add newline character

			Lines += TempLine;                     //Add newline
		}
		return Lines;
	}
	else                           //Return error
	{
		return "ERROR File does not exist.";
	}
}


int main()
{

	Lista<int> *CircSinP = new Lista<int>();
	int n, k;
	std::ifstream Reader("art.txt");
	std::string Art = getFileContents(Reader);
	std::cout << Art << std::endl;
	Reader.close();
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "n: ";cin >> n;
	cout << "k: ";cin >> k;
	CircSinP->josephus(n, k);
	return 0;
}