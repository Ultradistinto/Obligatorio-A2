#include <iostream>
#include <string>
using namespace std;

struct AVLNodeLibro
{
    int id;
    string titulo;
    string estado;
    AVLNodeLibro *izq;
    AVLNodeLibro *der;

    int altura = 1;

    AVLNodeLibro(int id, string titulo)
    {
        this->id = id;
        this->estado = "H";
        this->titulo = titulo;
    }
};

class AVLArbol
{
private:
    AVLNodeLibro *root = nullptr;
    int habilitados = 0;
    int total = 0;

    int altura(AVLNodeLibro *n)
    {
        if (n == nullptr)
        {
            return 0;
        }

        return n->altura;
    }
    int balanceFactor(AVLNodeLibro *n)
    {
        return altura(n->der) - altura(n->izq);
    }

    AVLNodeLibro *rotacionIzquierda(AVLNodeLibro *node)
    {
        AVLNodeLibro *z = node;
        AVLNodeLibro *y = node->der;

        z->der = y->izq;
        y->izq = z;

        z->altura = 1 + max(altura(z->izq), altura(z->der));
        y->altura = 1 + max(altura(y->izq), altura(y->der));

        return y;
    }

    AVLNodeLibro *rotacionDerecha(AVLNodeLibro *node)
    {
        AVLNodeLibro *z = node;
        AVLNodeLibro *y = node->izq;

        z->izq = y->der;
        y->der = z;

        z->altura = 1 + max(altura(z->izq), altura(z->der));
        y->altura = 1 + max(altura(y->izq), altura(y->der));

        return y;
    }

    AVLNodeLibro *rotacionDerechaIzquierda(AVLNodeLibro *node)
    {
        node->der = rotacionDerecha(node->der);

        return rotacionIzquierda(node);
    }

    AVLNodeLibro *rotacionIzquierdaDerecha(AVLNodeLibro *node)
    {
        node->izq = rotacionIzquierda(node->izq);

        return rotacionDerecha(node);
    }

    AVLNodeLibro *rebalanceo(AVLNodeLibro *node)
    {
        int bf = balanceFactor(node);
        if (bf > 1)
        {
            int bfDer = balanceFactor(node->der);
            if (bfDer >= 0)
            {
                node = rotacionIzquierda(node);
            }
            else if (bfDer < 0)
            {
                node = rotacionDerechaIzquierda(node);
            }
        }
        if (bf < -1)
        {
            int bfIzq = balanceFactor(node->izq);
            if (bfIzq > 0)
            {
                node = rotacionIzquierdaDerecha(node);
            }
            else if (bfIzq <= 0)
            {
                node = rotacionDerecha(node);
            }
        }
        return node;
    }

    AVLNodeLibro *addAux(AVLNodeLibro *node, int id, string titulo)
    {
        if (node == nullptr)
        {
            habilitados++;
            total++;
            return new AVLNodeLibro(id, titulo);
        }
        if (id > node->id)
        {
            node->der = addAux(node->der, id, titulo);
        }
        else if (id < node->id)
        {
            node->izq = addAux(node->izq, id, titulo);
        }
        else
        {
            node->titulo = titulo;
            node->estado = "H";
            return node;
        }

        node->altura = 1 + max(altura(node->izq), altura(node->der));
        node = rebalanceo(node);

        return node;
    }

    string findAux(AVLNodeLibro *node, int id)
    {
        if (node == nullptr)
        {
            return "libro_no_encontrado";
        }
        if (id > node->id)
        {
            return findAux(node->der, id);
        }
        else if (id < node->id)
        {
            return findAux(node->izq, id);
        }
        else
        {
            return node->titulo + " " + node->estado;
        }
    }

    string toggleAux(AVLNodeLibro *&node, int id)
    {
        if (node == nullptr)
        {
            return "libro_no_encontrado";
        }
        if (id > node->id)
        {
            return toggleAux(node->der, id);
        }
        else if (id < node->id)
        {
            return toggleAux(node->izq, id);
        }
        else
        {
            if (node->estado == "H")
            {
                node->estado = "D";
                habilitados--;
                return "";
            }
            else
            {
                node->estado = "H";
                habilitados++;
                return "";
            }
        }
    }

public:
    void add(int id, string titulo)
    {
        root = addAux(root, id, titulo);
    }

    string find(int id)
    {
        return findAux(root, id);
    }

    string toggle(int id)
    {
        return toggleAux(root, id);
    }

    int totales()
    {
        return total;
    }

    int habilitadosF()
    {
        return habilitados;
    }
    int deshabilitados()
    {
        return total - habilitados;
    }
};