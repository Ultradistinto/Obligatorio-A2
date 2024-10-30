#include <iostream>
#include <string>
#include "trio.cpp"
using namespace std;

class minHeapExtra
{
private:
    myTrio *array;
    int cantidad;

    void swap(int pos1, int pos2)
    {
        myTrio aux = array[pos1];
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
                (array[izq].getSnd() == array[min].getSnd() && array[izq].getFst() < array[min].getFst()))
            {
                min = izq;
            }
        }
        if (der <= cantidad)
        {
            if (array[der].getSnd() < array[min].getSnd() ||
                (array[der].getSnd() == array[min].getSnd() && array[der].getFst() < array[min].getFst()))
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
            (array[parent].getSnd() == array[pos].getSnd() && array[parent].getFst() > array[pos].getFst()))
        {
            swap(pos, parent);
            siftUp(parent);
        }
    }

public:
    minHeapExtra(int cantidadEsperada)
    {
        array = new myTrio[cantidadEsperada + 1];
        cantidad = 0;
    }
    void add(int id, int prioridad, string pedido)
    {
        myTrio trio = myTrio(id, prioridad, pedido);
        cantidad++;
        array[cantidad] = trio;
        siftUp(cantidad);
    }
    bool isEmpty()
    {
        return cantidad == 0;
    }

    myTrio pop()
    {
        myTrio retorno = array[1];
        array[1] = array[cantidad];
        cantidad--;
        siftDown(1);
        return retorno;
    }
    int peek()
    {
        return array[1].getSnd();
    }
};