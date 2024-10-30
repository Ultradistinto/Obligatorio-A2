#include <iostream>
#include "lista.cpp"
using namespace std;
template <typename T>
class grafo
{
private:
    lista<T> **nodos;
    int *gradosEntrada;
    int largo;

public:
    grafo(int cantNodos)
    {
        nodos = new lista<T> *[cantNodos + 1];
        gradosEntrada = new int[cantNodos + 1];
        largo = cantNodos;
        for (int i = 1; i <= cantNodos; i++)
        {
            nodos[i] = new lista<T>();
            gradosEntrada[i] = 0;
        }
    }

    void addEdge(int from, int to)
    {
        nodos[from]->agregar(to);
        gradosEntrada[to]++;
    }
    lista<T> grado0()
    {
        lista<T> retorno = lista<T>();
        for (int i = 1; i <= largo; i++)
        {
            if (gradosEntrada[i] == 0)
            {
                retorno.agregar(i);
            }
        }
        return retorno;
    }
};