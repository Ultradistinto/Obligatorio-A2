#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct HashNodeLibro
{
    int id;
    string titulo;
    string estado;

    HashNodeLibro(int id, string titulo)
    {
        this->id = id;
        this->estado = "H";
        this->titulo = titulo;
    }
};

class tablaHash
{
private:
    int largo;
    int totales = 0;
    int habilitados = 0;
    HashNodeLibro **buckets;

    int hashFunction(int id)
    {
        return id % largo;
    }
    int hashFunction2(int id)
    {
        return 1 + (id % (largo - 1));
    }

    int siguientePrimo(int n)
    {
        int retorno = n;
        while (true)
        {
            bool esPrimo = true;
            if (retorno <= 1)
            {
                esPrimo = false;
            }
            else if (retorno == 2)
            {
                esPrimo = true;
            }
            else if (retorno % 2 == 0)
            {
                esPrimo = false;
            }
            else
            {

                for (int i = 3; i <= sqrt(retorno); i++)
                {
                    if (retorno % i == 0)
                    {
                        esPrimo = false;
                        break;
                    }
                }
            }
            if (esPrimo)
            {
                return retorno;
            }
            retorno++;
        }
    }
    void resize()
    {
        int nuevoLargo = siguientePrimo(largo * 2);
        int largoViejo = largo;
        largo = nuevoLargo;
        int totales = 0;
        int habilitados = 0;
        HashNodeLibro **nuevo = new HashNodeLibro *[nuevoLargo];
        HashNodeLibro **aux = buckets;
        buckets = nuevo;
        for (int i = 0; i < largoViejo; i++)
        {
            if (aux[i] != nullptr)
            {
                add(aux[i]->id, aux[i]->titulo);
            }
            delete aux[i];
        }
        delete[] aux;
    }

public:
    tablaHash(int largoSupuesto)
    {
        this->largo = siguientePrimo(largoSupuesto);
        this->buckets = new HashNodeLibro *[largo];
    }
    void add(int id, string titulo)
    {
        int pos = hashFunction(id);
        if (buckets[pos] == nullptr)
        {
            HashNodeLibro *nuevo = new HashNodeLibro(id, titulo);
            buckets[pos] = nuevo;
        }
        else
        {
            int i = 1;
            while (true)
            {
                pos = (hashFunction(id) + (i * hashFunction2(id))) % largo;
                if (buckets[pos] == nullptr)
                {
                    HashNodeLibro *nuevo = new HashNodeLibro(id, titulo);
                    buckets[pos] = nuevo;
                    break;
                }
                else if (buckets[pos]->id == id)
                {
                    buckets[pos]->titulo = titulo;
                    break;
                }
                i++;
            }
        }
        totales++;
        habilitados++;
        if (this->totales * 2 > this->largo)
        {
            resize();
        }
    }
    string find(int id)
    {
        int i = 0;
        while (i < largo)
        {
            int pos = (hashFunction(id) + i * hashFunction2(id)) % largo;
            if (buckets[pos] != nullptr)
            {
                if (buckets[pos]->id == id)
                {
                    return buckets[pos]->titulo + " " + buckets[pos]->estado;
                }
            }
            i++;
        }
        return "libro_no_encontrado";
    }
    string toggle(int id)
    {
        int i = 0;
        while (i < largo)
        {
            int pos = (hashFunction(id) + i * hashFunction2(id)) % largo;
            if (buckets[pos] != nullptr)
            {
                if (buckets[pos]->id == id)
                {
                    if (buckets[pos]->estado == "H")
                    {
                        buckets[pos]->estado = "D";
                        habilitados--;
                    }
                    else
                    {
                        buckets[pos]->estado = "H";
                        habilitados++;
                    }
                    break;
                }
            }
            i++;
        }
        return "libro_no_encontrado";
    }

    int totalesF()
    {
        return totales;
    }

    int habilitadosF()
    {
        return habilitados;
    }

    int deshabilitados()
    {
        return totales - habilitados;
    }
};