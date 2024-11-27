#include <iostream>
#include "minHeap.cpp"
#include "pair.cpp"

using namespace std;

class nuevoGrafo
{
private:
    int **matriz;
    int cantVertices;
    int cantAristas;

public:
    nuevoGrafo(int vertices, int aristas)
    {
        cantAristas = aristas;
        cantVertices = vertices;
        matriz = new int *[cantVertices + 1];
        for (int i = 0; i <= cantVertices; i++)
        {
            matriz[i] = new int[cantVertices + 1];
            for (int j = 0; j <= cantVertices; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }
    void agregarAristaNoDirigida(int i, int j, int peso)
    {
        matriz[i][j] = peso;
        matriz[j][i] = peso;
    }
    void agregarAristaDirigida(int i, int j, int peso)
    {
        matriz[i][j] = peso;
    }
};