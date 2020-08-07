// Final4.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

template <class T>
struct CSparseNode
{
    T m_data;
    CSparseNode<T>* m_next_node;
    int m_y, m_x;
    CSparseNode(int valor, int x, int y, CSparseNode* _next = nullptr) {
        m_data = valor; m_y = y;
        m_x = x;
        m_next_node = _next;
    }
};
/*template <class T>
struct CSparseList
{
};*/
template <class T, T NE>
class CSparseMatrix
{
public:


   // CSparseNode<T>** m_Head;


    CSparseNode<T>* Head; 
    unsigned long m_YSize, m_XSize;
    CSparseMatrix(int xsize, int yzise)
    {
        m_YSize = m_XSize = 0;
        //m_Head = 0;
    }
    bool Insert(T n, int x, int y)
    {
        if (!Head) {
            return 0;
        }
        Head = new CSparseNode<T>(n, x, y, Head);
        return 1;
        //Haciendo la implementación con lista enlazada
    }

    bool Remove(T n, int x, int y)
    {
        CSparseNode<T>* PTemporal = Head;
        while (PTemporal != 0) {
            if (PTemporal->m_x == x && PTemporal->m_y == y) {
                delete PTemporal;
                return 1;
            }
            PTemporal = PTemporal->m_next_node;
        }
        return 1;
    }

    bool Set(int x, int y, int n)
    {
        CSparseNode<T>* PTemporal = Head;
        while (PTemporal != 0) {
            if (PTemporal->m_x == x && PTemporal->m_y == y) {
                PTemporal->m_data = n;
                return 1;
            }
            PTemporal = PTemporal->m_next_node;
        }
        Head = new CSparseNode<T>(n, x, y, Head);
        return 1;
    }

    T Get(int x, int y)
    {
        CSparseNode<T>* PTemporal = Head;
        while (PTemporal != 0) {
            if (PTemporal->m_x == x && PTemporal->m_y == y) {
                return PTemporal->m_data;
            }
            PTemporal = PTemporal->m_next_node;
        }
        return 0;
    }

    //////////////////////////////////////////////////////////
    void recursivoDeleterino(CSparseNode<T>* p)
    {
        if (p) {
            recursivoDeleterino(p->m_next_node);
            delete p;
        }
    }
    ~CSparseMatrix()
    {
        recursivoDeleterino(Head);
    }
};


int main()
{
    CSparseMatrix<int, 0> sm(5,5);

    sm.Set(3, 2, 1);
    sm.Set(1, 1, 8);
    sm.Set(1, 2, 0);
    sm.Set(2, 2, 9);
    sm.Set(4, 1, 12);
    sm.Set(2, 2, 0);
    sm.Set(3, 3, 0);

    int x, y;
    for (x = 0; x < 5; x++)
    {
        for (y = 0; y < 5; y++)
            cout << sm.Get(x, y);
        cout << "\n";
    }



}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
