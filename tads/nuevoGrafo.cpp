#include <iostream>
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
    int **dijkstra(int desde)
    {
        int **ret = new int *[2];
        // Distancia desde el origen al resto del grafo
        ret[0] = new int[cantVertices];
        // Anterior desde cualquier valor hasta el origen
        ret[1] = new int[cantVertices];
        bool *visitado = new bool[cantVertices];

        for (int i = 0; i < cantVertices; i++)
        {
            ret[0][i] = 2147483647;
            visitado[i] = false;
        }
        ret[0][desde] = 0;
        ret[1][desde] = 0;
        for (int i = 0; i <= cantVertices; i++)
        {

            int u = minDistancia(ret[0], visitado);
            visitado[u] = true;
            for (int v = 0; v < cantVertices; v++)
            {
                if (!visitado[v] && matriz[u][v] != 0 && ret[0][u] != 2147483647 && ret[0][u] + matriz[u][v] < ret[0][v])
                {
                    ret[0][v] = ret[0][u] + matriz[u][v];
                    ret[1][v] = u;
                }
            }
        }
        return ret;
    }
    int pesoArista(int i, int j)
    {
        return matriz[i][j];
    }
};