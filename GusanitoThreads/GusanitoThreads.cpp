// GusanitoThreads.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <mutex>
#include <thread>
#include <time.h>

using namespace std;

char mapa[10][30] = {
'|','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','|',
'|','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','|'
};
/////////////////////////////////////////////
void dibujar_mapa() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 30; j++) {
			cout << mapa[i][j];
		}
		cout << "\n";
	}
}
//////////////////////////////////////////////////////////
class pos {
public:
	int x = 0;
	int y = 0;
	char c = 'o';
};
//////////////////////////////////////////////////////////
class gusanito {
public:
	int dir = 1;
	int pos_x;
	int pos_y;
	pos body[5];
	gusanito(int i, int j) {
		pos_x = j;
		pos_y = i;
		for (int w = 0; w < 5; w++) {
			body[w].x = j;
			body[w].y = i - w;
		}
		body[0].c = '8';
	}
	void borra_serp() {
		for (int i = 0; i < 5; i++) {
			mapa[body[i].x][body[i].y] = '.';
		}
	}
	void dibuja_serp() {
		for (int i = 0; i < 5; i++) {
			mapa[body[i].x][body[i].y] = body[i].c;
		}
	}
	void dir_act() {
		switch (dir) {
		case 1://derecha
			if (mapa[body[0].x][body[0].y + 1] == '|' && mapa[body[0].x + 1][body[0].y] == '=') {
				dir = 4;
				break;
			}
			if (mapa[body[0].x][body[0].y + 1] == '|' && mapa[body[0].x - 1][body[0].y] == '=') {
				dir = 2;
				break;
			}
			if (mapa[body[0].x][body[0].y + 1] == '|') {
				dir = ((rand() % 2) + 1) * 2;
				break;
			}
			break;
		case 2://abajo
			if (mapa[body[0].x + 1][body[0].y] == '=' && mapa[body[0].x][body[0].y + 1] == '|') {
				dir = 3;
				break;
			}
			if (mapa[body[0].x + 1][body[0].y] == '=' && mapa[body[0].x][body[0].y - 1] == '|') {
				dir = 1;
				break;
			}
			if (mapa[body[0].x + 1][body[0].y] == '=') {
				dir = ((rand() % 2) * 2) + 1;
				break;
			}
			break;
		case 3://izquierda 
			if (mapa[body[0].x][body[0].y - 1] == '|' && mapa[body[0].x + 1][body[0].y] == '=') {
				dir = 4;
				break;
			}
			if (mapa[body[0].x][body[0].y - 1] == '|' && mapa[body[0].x - 1][body[0].y] == '=') {
				dir = 2;
				break;
			}
			if (mapa[body[0].x][body[0].y - 1] == '|') {
				dir = ((rand() % 2) + 1) * 2;
				break;
			}
			break;
		case 4://arriba
			if (mapa[body[0].x - 1][body[0].y] == '=' && mapa[body[0].x][body[0].y - 1] == '|') {
				dir = 1;
				break;
			}
			if (mapa[body[0].x - 1][body[0].y] == '=' && mapa[body[0].x][body[0].y + 1] == '|') {
				dir = 3;
				break;
			}
			if (mapa[body[0].x - 1][body[0].y] == '=') {
				dir = ((rand() % 2) * 2) + 1;
				break;
			}
			break;
		default:
			dir = (rand() % 4) + 1;
			break;
		}
	}
	void actualizar() {
		dir_act();
		///////////////////////////////////////////////////derecha///////////////////////////////////////////////////////////
		if (dir == 1) {
			char temp_1 = mapa[body[0].x][body[0].y + 1];
			while (temp_1 == 'o') {
				lock_guard<mutex> lock(mutex i_o);
				temp_1 = mapa[body[0].x][body[0].y + 1];
			}
			borra_serp();
			//cout << "derecha " << mapa[body[0].x][body[0].y + 1] << endl;
			pos temp[5];
			for (int i = 0; i < 5; i++) {
				temp[i].x = body[i].x;
				temp[i].y = body[i].y;
			}
			for (int i = 1; i < 5; i++) {
				body[i] = temp[i - 1];
				body[i] = temp[i - 1];
			}
			body[0].y += 1;
			return;
		}

		///////////////////////////////////////////////////abajo ///////////////////////////////////////////////////////////
		if (dir == 2) {
			char temp_1 = mapa[body[0].x + 1][body[0].y];
			while (temp_1 == 'o') {
				lock_guard<mutex> lock(mutex i_o);
				temp_1 = mapa[body[0].x + 1][body[0].y];
			}
			borra_serp();
			//cout << "abajo " << mapa[body[0].x + 1][body[0].y] << endl;
			pos temp[5];
			for (int i = 0; i < 5; i++) {
				temp[i].x = body[i].x;
				temp[i].y = body[i].y;
			}
			for (int i = 1; i < 5; i++) {
				body[i] = temp[i - 1];
				body[i] = temp[i - 1];
			}
			body[0].x += 1;
			return;
		}
		///////////////////////////////////////////////////izquierda///////////////////////////////////////////////////////////
		if (dir == 3) {
			while (mapa[body[0].x][body[0].y - 1] == 'o') {
				lock_guard<mutex> lock(mutex i_o);
			}
			borra_serp();
			//cout << "izquierda " << mapa[body[0].x][body[0].y - 1]<< endl;
			pos temp[5];
			for (int i = 0; i < 5; i++) {
				temp[i].x = body[i].x;
				temp[i].y = body[i].y;
			}
			for (int i = 1; i < 5; i++) {
				body[i] = temp[i - 1];
				body[i] = temp[i - 1];
			}
			body[0].y -= 1;
			return;
		}
		///////////////////////////////////////////////////arriba///////////////////////////////////////////////////////////
		if (dir == 4) {
			char temp_1 = mapa[body[0].x - 1][body[0].y];
			while (temp_1 == 'o') {
				lock_guard<mutex> lock(mutex i_o);
				temp_1 = mapa[body[0].x - 1][body[0].y];
				//cout << temp_1 << endl;
			}
			borra_serp();
			//cout << "arriba " << mapa[body[0].x - 1][body[0].y] << endl;
			pos temp[5];
			for (int i = 0; i < 5; i++) {
				temp[i].x = body[i].x;
				temp[i].y = body[i].y;
			}
			for (int i = 1; i < 5; i++) {
				body[i] = temp[i - 1];
				body[i] = temp[i - 1];
			}
			body[0].x -= 1;
			return;
		}
	}
	void operator()() {
		while (true) {
			actualizar();
			dibuja_serp();
			Sleep(250);
		}
	}
};
int main() {

	//gusanito a(7, 4);
	//thread t1(a);

	gusanito b(7, 6);
	thread t2(b);
	gusanito c(7, 8);
	thread t3(c);
	//gusanito d(7, 2);
	//thread t4(d);

	while (1) {
		dibujar_mapa();
		Sleep(250);
		system("cls");
	}

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
