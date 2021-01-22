// CircuDoblemente.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;
class Nodo
{
public:
	int valor;
	Nodo *next;
	Nodo *prev;
	Nodo(int _valor, Nodo* _next = NULL, Nodo *_prev = NULL)
	{
		valor = _valor;
		next = _next;
		prev = _prev;
	}
	~Nodo()
	{
		next = 0;
		prev = 0;
	}

};


class Lista
{
public:
	Nodo *head;


	Lista()
	{
		head = NULL;
	}
	Lista(int valor, Nodo *prev = 0, Nodo *next = 0)
	{
		head = new Nodo(valor);
		head->next = head;
		head->prev = head;
	}

	bool Buscar(int valor)
	{
		if (head != 0)
		{
			return 1;
		}
		Nodo *temp = head;
		do
		{
			if (temp->valor == valor)
			{
				return 0;
			}
			temp = temp->next;
		} while (temp != head);
		return 1;
	}


	void Agregar(int valor, Nodo *next = 0)
	{
		if (head == 0)
		{
			head = new Nodo(valor);
			head->next = head;
			head->prev = head;
			return;
		}
		else if (Buscar(valor))
		{
			Nodo *temp = head;

			do
			{
				if (temp->valor < valor)
				{

					if (temp->next == head) //FINAL
					{
						temp->next = new Nodo(valor, temp);
						temp->next->next = head;
						head->prev = temp->next;
						temp->next->prev = temp;
						break;
					}

					else if ((temp->next->valor) > valor) //MEDIO
					{
						temp->next = new Nodo(valor, temp->next, temp);
						temp->next->next->prev = temp->next;
						break;
					}
				}
				else//INICIO
				{
					Nodo *last = head;
					while (last->next != head)
					{
						last = last->next;
					}
					head = new Nodo(valor, last, temp);
					temp->next->prev = temp;
					temp->prev = head;
					last->next = head;
					break;
				}
				temp = temp->next;
			} while (temp != head);
		}

	}

	void Eliminar(int valor)
	{
		if (Buscar(valor) and head != 0)
		{
			Nodo* temp = head;

			if (head->valor == valor)
			{

				if (head == head->next)
				{
					delete head;
					head = NULL;
					return;
				}

				Nodo* last = head;
				while (last->next != head)
				{
					last = last->next;
				}
				Nodo* headSgt = head->next;
				delete head;
				head = headSgt;
				head->prev = last;

				last->next = head;
				return;
			}
			temp = temp->next;
			while (temp != head)
			{

				if (temp->next == head)          //FINAL
				{
					temp->prev->next = head;
					head->prev = temp->prev;
					delete temp;
					return;
				}

				if (temp->valor == valor)        //MEDIO
				{
					(temp->prev)->next = temp->next;
					(temp->next)->prev = temp->prev;
					delete temp;
					return;
				}
				temp = temp->next;
			}
		}
	}


	~Lista()
	{
		if (head != 0)
		{
			Nodo *temp = head;
			while (temp)
			{
				Nodo *next = temp->next;
				delete temp;
				temp = next;
			}
		}

	}


	void Imprimir()
	{
		if (head != 0)
		{
			Nodo *temp = head;

			do
			{
				if (temp->prev)
				{
					cout << temp->prev->valor << " <- ";
				}
				else
				{
					cout << "       ";
				}
				cout << temp->valor;
				if (temp->next)
				{
					cout << " -> " << temp->next->valor;
				}
				cout << endl;
				temp = temp->next;


			} while (temp != head);

		}


	}
	void josephus(int n, int k_muertes)
	{
		int Nmuertos = 0;
		for (int i = 1;i <= n;i++)
			Agregar(i);
		Imprimir();
		Nodo *ptr = head; Nodo*prev = head;
		while (Nmuertos < n)
		{
			for (int i = 0; i < k_muertes - 1;i++)
				ptr = ptr->next;
			while (prev->next != ptr)
				prev = prev->next;
			if (ptr == head)
				head = head->next;
			prev->next = ptr->next;
			ptr = prev->next;
			Nmuertos++;
		}
		cout << "Playing the Josephus Game with " << n << " people, eliminating every " << k_muertes << " people, leaves person " << head->valor<< " as the last survivor." << endl;
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

	Lista *CircDobl = new Lista();
	cout << "\n";
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
	CircDobl->josephus(n, k);
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
