// Final1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m;
int matrix[50][50]
{
    {31,31,42,51,20,58,18,83,97,18,60,40,83,63,38,11,49,93,50,15,48,7,8,61,20,66,31,61,40,14,56,97,75,26,38,86,95,62,78,60,89,50,83,25,79,90,60,84,40,5},
    {65,62,4,7,34,73,85,80,87,79,64,85,18,13,55,9,98,88,0,86,74,46,80,86,53,25,58,73,96,27,53,89,65,91,14,80,13,38,60,50,98,84,62,47,45,42,63,41,10,51},
    {1,60,87,79,3,75,57,40,67,35,75,54,53,26,11,62,88,44,69,72,51,25,62,71,67,67,72,2,90,93,94,17,14,25,48,91,33,96,61,54,83,25,15,59,90,59,9,81,97,15},
    {36,30,84,58,11,70,45,39,24,99,73,83,11,97,99,43,33,37,19,33,4,74,91,61,10,71,11,99,89,72,22,82,18,4,99,40,70,60,25,93,66,57,81,48,7,3,84,30,99,48},
    {50,75,16,3,84,92,42,42,6,58,99,78,46,5,87,37,79,63,37,94,71,22,77,61,16,37,69,17,7,14,33,13,39,41,64,38,93,91,11,59,75,3,40,90,56,29,90,62,96,11},
    {90,63,68,31,46,30,46,30,20,77,89,25,33,80,37,29,21,84,37,67,98,74,18,36,9,98,80,40,1,77,86,65,18,75,38,22,94,20,62,79,26,91,28,94,10,90,64,91,57,2},
    {99,12,53,74,58,3,77,63,44,29,78,28,47,47,79,61,79,88,22,41,51,81,38,78,23,99,19,26,76,34,63,79,32,57,96,58,77,22,90,25,55,93,58,31,64,80,83,15,27,48},
    {84,10,10,66,54,28,17,11,9,97,50,42,94,26,81,70,62,52,90,42,92,24,9,56,73,14,57,74,96,41,52,98,81,20,69,20,4,93,69,92,4,40,93,29,34,91,41,67,53,44},
    {33,21,81,53,27,15,91,80,56,38,71,45,64,86,89,44,50,24,69,2,48,91,9,51,82,11,96,9,27,56,27,43,85,32,79,34,9,9,83,4,99,20,9,34,62,18,1,51,47,29},
    {12,97,58,89,31,35,22,6,39,74,83,97,6,68,5,99,32,21,20,20,11,45,55,65,37,58,90,84,3,59,29,42,47,98,79,50,42,93,34,60,10,26,2,99,14,54,6,44,43,24},
    {0,93,47,94,75,8,18,59,32,12,68,7,74,49,24,93,40,8,51,18,68,98,18,81,87,30,32,92,42,77,12,61,92,81,13,32,67,81,78,58,24,45,84,53,19,57,42,50,15,80},
    {10,33,37,93,23,67,19,58,86,88,30,97,22,34,5,19,49,32,90,50,66,61,94,46,94,96,45,66,88,56,45,93,43,36,78,72,60,2,63,20,58,48,91,23,29,31,97,18,1,68},
    {81,83,37,93,28,22,73,27,80,54,99,81,80,47,96,88,43,39,79,81,97,9,16,90,16,52,98,52,80,89,39,61,7,31,57,53,58,79,27,99,27,5,51,68,52,1,24,13,4,21},
    {17,4,62,88,80,76,63,38,45,61,56,89,96,44,32,44,32,0,76,1,8,26,25,47,70,45,74,77,83,26,94,48,92,14,37,37,2,79,69,99,16,61,74,89,40,55,23,5,70,56},
    {75,51,71,9,24,21,73,64,54,97,70,92,67,50,21,73,44,9,79,64,97,49,89,93,17,79,56,55,67,96,59,44,15,98,38,79,91,75,30,67,46,45,67,2,84,81,65,51,77,29},
    {84,98,2,51,97,70,3,79,72,65,26,83,75,41,7,74,1,75,42,85,48,71,20,43,29,77,25,71,98,53,47,2,33,90,26,1,78,19,26,94,91,41,8,27,15,61,35,46,42,39},
    {96,93,92,84,57,69,77,1,25,98,4,58,65,61,60,47,10,32,53,64,8,82,63,56,67,24,51,66,89,24,79,42,57,80,15,45,68,86,37,71,38,92,89,90,44,24,36,62,44,46},
    {26,24,88,51,76,27,25,66,13,94,33,87,41,27,14,58,26,85,44,2,86,79,17,53,33,18,22,92,99,26,29,70,7,40,25,79,67,48,23,28,97,21,94,33,66,88,79,88,75,17},
    {22,53,34,17,33,7,56,69,18,58,14,61,71,35,65,25,36,64,69,65,93,79,96,39,77,62,19,67,34,24,68,52,87,16,29,4,7,78,11,77,7,53,59,80,1,84,4,45,50,94},
    {76,59,60,23,53,66,2,74,43,71,17,82,6,32,85,39,80,42,72,88,7,53,23,4,37,76,16,4,59,14,95,42,29,72,63,55,51,81,73,1,32,31,26,33,43,1,76,1,17,94},
    {59,82,48,80,84,35,5,32,46,79,29,24,3,89,40,42,4,56,11,74,63,58,23,64,48,19,81,88,99,97,67,93,12,75,6,32,48,71,39,52,48,73,19,96,46,73,26,74,26,99},
    {29,38,31,18,27,79,12,1,76,22,74,47,56,62,19,33,16,17,87,85,18,28,22,34,22,54,94,54,80,29,4,88,33,68,63,21,68,97,76,24,81,75,16,30,40,80,78,66,92,53},
    {88,64,30,24,57,29,16,30,97,18,59,44,78,22,59,0,31,95,60,98,26,13,7,20,85,43,59,52,80,56,73,58,84,93,15,81,93,93,93,87,92,94,4,70,96,79,65,64,91,16},
    {3,98,6,88,12,23,57,83,11,18,22,7,92,70,3,79,15,61,19,19,4,72,42,2,75,43,88,32,59,70,87,77,5,44,80,12,12,56,18,61,63,81,46,19,70,96,47,84,65,2},
    {91,56,40,92,86,25,24,73,70,82,56,12,2,2,33,38,3,55,20,35,85,30,72,64,95,87,37,77,90,94,4,7,69,43,28,13,31,4,80,62,61,25,60,4,14,62,79,83,34,91},
    {11,86,53,51,45,83,3,26,73,88,12,7,4,51,89,68,61,92,53,60,69,46,37,34,71,36,88,37,61,62,60,12,6,30,65,69,13,60,5,21,80,54,45,53,36,20,56,42,44,21},
    {36,44,55,62,4,74,15,53,92,89,46,29,57,79,90,3,7,29,37,45,77,5,74,97,51,28,50,70,60,13,73,10,24,3,4,38,94,42,5,72,35,67,98,39,64,82,44,86,31,7},
    {36,74,91,50,8,6,27,64,87,13,18,90,33,81,11,81,76,13,94,23,17,2,33,33,45,88,95,38,14,78,0,69,41,49,7,2,11,29,31,18,16,29,45,2,26,3,46,37,42,76},
    {88,80,3,14,97,17,84,96,63,11,95,77,55,56,74,40,81,23,61,0,30,86,90,97,42,81,18,36,66,97,24,37,39,71,15,12,47,92,96,97,38,51,44,99,18,93,49,15,5,70},
    {79,76,83,46,32,61,18,65,17,10,55,18,62,12,82,77,71,51,56,81,99,64,27,64,21,15,7,22,3,97,63,92,47,13,41,20,48,16,30,27,76,27,26,91,5,48,50,71,28,60},
    {8,80,19,63,79,9,49,14,84,62,50,39,25,58,51,57,70,68,57,11,52,38,11,85,32,60,25,58,23,4,96,7,92,15,84,15,17,11,3,93,26,93,58,32,49,3,53,67,10,1},
    {53,93,68,41,59,34,98,68,62,91,0,15,63,79,16,17,51,7,89,8,25,70,18,65,54,33,27,5,86,57,47,20,91,66,88,60,49,45,78,31,87,27,4,70,58,86,45,25,51,3},
    {53,19,58,23,79,33,52,20,40,85,69,70,17,85,97,71,90,32,5,18,40,32,95,86,96,26,28,99,67,16,61,3,76,35,12,53,4,14,5,69,45,28,54,69,32,4,99,4,92,60},
    {71,4,74,43,18,77,33,12,48,6,82,57,2,6,73,43,50,75,36,73,87,64,90,40,96,59,32,46,92,47,40,95,58,59,23,74,71,63,37,49,51,90,16,82,63,18,53,62,4,30},
    {60,29,94,18,47,13,45,32,66,84,19,31,30,44,26,18,46,40,15,51,97,81,83,45,63,92,45,66,5,17,10,22,27,96,73,36,76,36,66,38,88,60,83,21,45,99,78,99,97,63},
    {46,10,88,41,90,0,45,92,37,53,1,31,71,88,96,33,77,88,8,8,85,78,86,73,81,24,28,94,91,25,35,89,17,14,27,37,21,80,6,32,8,28,28,43,48,79,11,35,41,18},
    {60,96,56,23,38,98,64,30,72,83,61,80,58,38,74,8,41,64,57,93,24,95,37,84,41,52,69,78,88,39,90,69,70,8,55,64,84,24,23,68,40,51,85,83,60,73,26,98,66,40},
    {75,28,53,92,53,84,42,84,71,40,43,59,63,41,58,90,3,77,30,20,96,93,2,41,55,88,14,98,30,72,78,71,25,97,84,97,14,4,91,89,60,52,36,44,67,70,11,54,5,20},
    {75,24,6,98,11,11,87,14,82,80,14,39,32,36,35,85,36,93,97,12,30,53,1,24,38,64,61,29,99,24,22,53,64,60,18,49,89,15,72,92,47,93,17,96,44,0,49,38,74,54},
    {28,60,40,50,27,5,34,19,52,62,8,15,67,84,64,79,28,43,48,11,48,43,73,93,49,21,84,53,76,67,42,48,22,14,24,3,83,15,37,68,29,36,0,30,20,37,65,21,67,98},
    {30,87,5,81,85,12,89,88,6,66,79,83,34,62,63,96,7,82,85,15,36,96,15,18,4,85,76,48,9,8,42,62,78,23,8,38,80,82,0,13,90,88,77,54,79,58,95,61,72,20},
    {8,96,70,93,45,87,24,60,12,85,43,62,91,45,27,67,47,14,60,79,65,15,21,48,79,83,57,48,46,94,11,57,3,87,19,64,70,53,75,70,81,94,90,37,71,86,21,44,14,53},
    {90,96,60,13,88,99,38,25,40,98,78,32,5,10,27,99,28,64,87,22,48,72,33,66,60,93,66,34,56,85,2,48,80,38,40,40,5,80,37,9,54,58,58,14,33,65,16,87,50,57},
    {90,66,93,81,61,36,71,81,23,61,50,85,32,65,97,47,59,87,59,97,93,4,71,10,52,53,98,95,64,39,22,97,51,33,31,27,63,0,0,61,12,95,32,82,2,92,93,46,7,67},
    {91,44,88,95,22,52,53,34,85,4,41,89,53,42,21,77,92,23,44,62,66,41,8,85,61,64,64,18,67,10,80,10,85,33,27,96,36,94,25,39,40,97,32,57,52,86,63,7,76,71},
    {32,2,27,44,5,82,71,0,24,35,48,65,68,77,1,61,21,80,8,92,74,92,75,71,94,13,70,16,99,73,37,84,20,74,10,96,49,51,35,95,67,62,3,7,74,6,18,92,92,33},
    {83,97,50,35,98,35,52,62,73,99,97,64,97,35,41,22,58,41,99,11,61,72,6,96,68,50,52,72,10,76,3,45,75,34,65,24,70,52,4,65,34,90,65,44,83,32,57,28,16,86},
    {7,88,6,78,62,93,11,99,77,88,46,82,21,9,6,4,43,56,83,11,66,69,58,65,90,1,86,18,79,82,23,61,34,7,24,15,59,62,10,43,31,14,11,58,90,58,68,15,91,10},
    {65,14,29,78,26,83,82,29,49,96,15,75,48,12,85,99,26,93,54,97,67,79,24,3,58,24,45,23,16,30,96,28,12,2,52,39,66,67,58,30,77,81,35,21,34,15,61,39,82,16},
    {86,25,35,58,33,66,80,81,41,12,80,49,50,8,45,93,72,55,49,15,46,48,76,68,67,1,82,18,53,4,30,86,49,85,81,58,66,66,10,46,9,20,5,9,93,28,82,53,43,24}
};
void calcular_Multiplo(int x)
{
    int count = 0;
    for (int i = 0; i < 50; i++)
    {
        for (int j=0; j < 50; j++)
        {
            if (matrix[i][j] % x==0)
            {
                count += matrix[i][j];
            }
        }
    }
    m.lock();
    cout << "La suma de multiplos de" << x << " es: " <<count<< endl; // para imprimir ordenadito y que no se atropellen
    m.unlock();
}
int main()
{

    int count = 1;
    thread numeros[10];
    for (int i = 0; i < 10; i++)
    {
        numeros[i] = thread(calcular_Multiplo, count); count++;
    }
    for (int i = 0; i < 10; i++)
    {
        numeros[i].join();
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