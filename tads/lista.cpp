#include <iostream>
using namespace std;

template <typename T>
class nodoLista
{
public:
    T dato;
    nodoLista *sig;
    nodoLista(T dato)
    {
        this->dato = dato;
        this->sig = nullptr;
    }
};

template <typename T>
class lista
{
private:
    int cantidad;
    nodoLista<T> *head;

public:
    lista()
    {
        cantidad = 0;
        head = nullptr;
    }

    void agregar(T dato)
    {
        nodoLista<T> *nuevo = new nodoLista<T>(dato);
        nuevo->sig = head;
        head = nuevo;
        cantidad++;
    }

    void mostrar()
    {
        nodoLista<T> *actual = head;
        while (actual != nullptr)
        {
            cout << actual->dato << " ";
            actual = actual->sig;
        }
        cout << endl;
    }

    int obtenerCantidad()
    {
        return cantidad;
    }
};
