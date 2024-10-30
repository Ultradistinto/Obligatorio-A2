#include <iostream>
#include <string>
#include "pair.cpp"

using namespace std;

class minHeap
{
private:
    myPair<int, int> *array;
    int cantidad;

    void swap(int pos1, int pos2)
    {
        myPair<int, int> aux = array[pos1];
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

        if (izq <= cantidad)
        {
            if (array[izq].getSnd() < array[min].getSnd() ||
                (array[izq].getSnd() == array[min].getSnd() && array[izq].getFst() > array[min].getFst()))
            {
                min = izq;
            }
        }

        if (der <= cantidad)
        {
            if (array[der].getSnd() < array[min].getSnd() ||
                (array[der].getSnd() == array[min].getSnd() && array[der].getFst() > array[min].getFst()))
            {
                min = der;
            }
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

        int parent = pos / 2;
        if (array[parent].getSnd() > array[pos].getSnd() ||
            (array[parent].getSnd() == array[pos].getSnd() && array[parent].getFst() < array[pos].getFst()))
        {
            swap(pos, parent);
            siftUp(parent);
        }
    }

public:
    minHeap(int cantidadEsperada)
    {
        array = new myPair<int, int>[cantidadEsperada + 1];
        cantidad = 0;
    }

    void add(int id, int precio)
    {
        myPair<int, int> par(id, precio);
        cantidad++;
        array[cantidad] = par;
        siftUp(cantidad);
    }

    myPair<int, int> pop()
    {
        myPair<int, int> retorno = array[1];
        array[1] = array[cantidad];
        cantidad--;
        siftDown(1);
        return retorno;
    }
};
