// Mediator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// A demonstrative hello world program using `cpp-mediator`.
#include "pch.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector> 
#include <algorithm>
using namespace std;
struct MediatorSalaDeChat {
	virtual void transmitir(string from, string msg) = 0;
	virtual void mensaje(string from, string to, string msg) = 0;
};
struct Persona {
	string              m_nombre;
	MediatorSalaDeChat*           m_sala{ nullptr };
	vector<string>      m_registro_de_chat;
	Persona(string n) : m_nombre(n) {}
	void enviar(string msg) const { m_sala->transmitir(m_nombre, msg); }
	void pm(string to, string msg) const { m_sala->mensaje(m_nombre, to, msg); }
	void recibir(string from, string msg) {
		string s{ from + ": \"" + msg + "\"" };
		cout << "[ ventana de " << m_nombre <<"  ]"<< s << "\n";
		m_registro_de_chat.emplace_back(s);
	}
};
struct MediatorChatUCSP : MediatorSalaDeChat
{
	vector<Persona*>     m_persona;
	void transmitir(string from, string msg) {
		for (auto p : m_persona)
			if (p->m_nombre != from)
				p->recibir(from, msg);
	}
	void unirse(Persona *p) {
		string unirse_msg = p->m_nombre + " se unio a la conversacion.";
		transmitir("sala", unirse_msg);
		p->m_sala = this;
		m_persona.push_back(p);
	}
	void mensaje(string from, string to, string msg) {
		auto objetivo = find_if(begin(m_persona), end(m_persona),
			[&](const Persona *p) {
				return p->m_nombre == to;
			});
		if (objetivo != end(m_persona)) (*objetivo)->recibir(from, msg);
	}
};
int main() {
	MediatorChatUCSP sala;
	Persona Rafael{ "Rafael" };
	Persona Jhorel{ "Jhorel" };
	sala.unirse(&Rafael);
	sala.unirse(&Jhorel);
	Rafael.enviar("Hola :D");
	Jhorel.enviar("oh, hola Rafa");
	Persona Victor{ "Victor" };
	sala.unirse(&Victor);
	Victor.enviar("Hola Chicos!");
	Jhorel.pm("Victor", "encontraste el link en Moodle :D");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other mensajes
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
