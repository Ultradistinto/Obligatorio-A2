#include <iostream>
#include <string>
#include "pair.cpp"
using namespace std;

class minHeap
{
private:
    myPair *array;
    int cantidad;

    void swap(int pos1, int pos2)
    {
        myPair aux = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = aux;
    }
    void siftDown(int pos)
    {
        if (pos > cantidad)
        {
            return;
        }

        int izq = pos * 2;
        int der = (pos * 2) + 1;
        int min = pos;

        if (izq > cantidad)
        {
            return;
        }
        else if (der > cantidad)
        {
        }
        else if (array[izq].getSnd() < array[min].getSnd())
        {
            min = izq;
        }
        if (array[der].getSnd() < array[min].getSnd())
        {
            min = der;
        }
        if (min != pos)
        {
            swap(pos, min);
            siftDown(min);
        }
    }

    void siftUp(int pos)
    {
        if (pos == 1)
        {
            return;
        }
        if (((array[pos / 2])).getSnd() > array[pos].getSnd())
        {
            swap(pos, pos / 2);
            siftUp(pos / 2);
        }
    }

public:
    minHeap(int cantidadEsperada)
    {
        array = new myPair[cantidadEsperada + 1];
        cantidad = 0;
    }
    void add(int id, int precio)
    {
        myPair par = myPair(id, precio);
        cantidad++;
        array[cantidad] = par;
        siftUp(cantidad);
    }

    myPair pop()
    {
        myPair retorno = array[1];
        array[1] = array[cantidad];
        cantidad--;
        siftDown(1);
        return retorno;
    }
};