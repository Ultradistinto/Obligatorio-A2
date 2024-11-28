#include <iostream>
#include <climits>
#include "minHeap.cpp"
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
    void misionCompletada(int i)
    {
        for (int j = 0; j <= cantVertices; j++)
        {
            matriz[j][i] = 0;
            matriz[i][j] = -1;
        }
    }
    int *getMisionesPosibles()
    {
        bool conseguiMision = false;
        int *ret = new int[cantVertices + 1]();
        int mison = 0;
        for (int i = 1; i <= cantVertices; i++)
        {
            if (!conseguiMision)
            {
                int dependencia = 0;
                for (int j = 1; j <= cantVertices; j++)
                {
                    if (matriz[i][j] == 1 || matriz[i][j] == -1)
                    {
                        dependencia++;
                    }
                    if (j == cantVertices && dependencia == 0)
                    {
                        ret[mison] = i;
                        mison++;
                        conseguiMision = true;
                    }
                }
            }
        }
        return ret;
    }
    int minDistancia(int *ret, bool *visitado)
    {
        int min = 2147483647;
        int minIndex = -1;
        for (int i = 0; i <= cantVertices; i++)
        {
            if (!visitado[i] && ret[i] <= min)
            {
                min = ret[i];
                minIndex = i;
            }
        }
        return minIndex;
    }
     bool *initVisitados(int n)
    {
        bool *visitados = new bool[n + 1];
        for (int i = 0; i < n + 1; i++)
        {
            visitados[i] = false;
        }
        return visitados;
    }
    int *initCostos(int n, int origen)
    {
        if (origen < 0)
        {
            cerr << "Error: origen está fuera del rango en initCostos." << endl;
            return nullptr;
        }
        if (origen > n)
        {
            cerr << "Error: origen es mayor a n." << " El n es: " << n << " El origen es: " << origen << endl;
            return nullptr;
        }

        int *costos = new int[n + 1];
        for (int i = 0; i < n + 1; i++)
        {
            costos[i] = INT_MAX;
        }
        costos[origen] = 0;
        return costos;
    }
    int *initAnterior(int n)
    {
        int *ant = new int[n + 1];
        for (int i = 0; i < n + 1; i++)
        {
            ant[i] = -1;
        }
        return ant;
    }
    int contarAdyacentes(int v)
    {
        int numAdyacentes = 0;
        for (int i = 1; i <= cantVertices; i++)
        {
            if (matriz[v][i] != 0)
            {
                numAdyacentes++;
            }
        }
        return numAdyacentes;
    }

    int *verticesAdy(int v, int numAdyacentes)
    {
        int *adyacentes = new int[numAdyacentes];
        int indice = 0;
        for (int i = 1; i <= cantVertices; i++)
        {
            if (matriz[v][i] != 0)
            {
                adyacentes[indice] = i;
                indice++;
            }
        }
        return adyacentes;
    }
    myPair<int *, int *> dijkstra(int origen)
    {

        bool *visitados = initVisitados(cantVertices);
        int *costos = initCostos(cantVertices, origen);

        int *ant = initAnterior(cantVertices);
        minHeap CP(cantVertices * cantVertices);

        CP.add(origen, 0);

        while (!CP.isEmpty())
        {
            int v = CP.pop().getFst();
            visitados[v] = true;

            int numAdyacentes = contarAdyacentes(v);
            int *adyacentes = verticesAdy(v, numAdyacentes);

            for (int i = 0; i < numAdyacentes; i++)
            {
                int w = adyacentes[i];
                int newCost = costos[v] + matriz[v][w];
                if (!visitados[w] && costos[w] > newCost)
                {
                    costos[w] = newCost;
                    ant[w] = v;
                    CP.add(w, newCost);
                }
            }

            delete[] adyacentes;
        }

        delete[] visitados;
        return myPair<int *, int *>(costos, ant);
    }
    int pesoArista(int i, int j)
    {
        return matriz[i][j];
    }
};