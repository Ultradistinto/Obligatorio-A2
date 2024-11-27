#include <iostream>
#include <string>
using namespace std;

struct HashNodeLibro
{
    int id;
    string titulo;
    string estado;

    HashNodeLibro(int id, string titulo, string estado)
    {
        this->id = id;
        this->estado = estado;
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
                for (int i = 3; i < retorno; i += 2)
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
        HashNodeLibro **nuevo = new HashNodeLibro *[nuevoLargo]();
        HashNodeLibro **aux = buckets;
        buckets = nuevo;
        totales = 0;
        habilitados = 0;
        for (int i = 0; i < largoViejo; i++)
        {
            if (aux[i] != nullptr)
            {
                add(aux[i]->id, aux[i]->titulo, aux[i]->estado);
                delete aux[i];
            }
        }
        delete[] aux;
    }

public:
    tablaHash(int largoSupuesto)
    {
        this->largo = siguientePrimo(largoSupuesto);
        this->buckets = new HashNodeLibro *[largo]();
    }

    void add(int id, string titulo, string estado)
    {
        int pos = hashFunction(id);
        int i = 0;
        while (buckets[pos] != nullptr && buckets[pos]->id != id)
        {
            i++;
            pos = (hashFunction(id) + (i * hashFunction2(id))) % largo;
        }
        if (buckets[pos] == nullptr)
        {
            HashNodeLibro *nuevo = new HashNodeLibro(id, titulo, estado);
            buckets[pos] = nuevo;
            totales++;
            if (estado == "H")
            {
                habilitados++;
            }
        }
        else
        {
            buckets[pos]->titulo = titulo;
            if (buckets[pos]->estado == "D")
            {
                habilitados++;
            }
            buckets[pos]->estado = "H";
        }
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
                        return "";
                    }
                    else
                    {
                        buckets[pos]->estado = "H";
                        habilitados++;
                        return "";
                    }
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
