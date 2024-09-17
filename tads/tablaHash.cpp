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
    int cantidad = 0;
    HashNodeLibro **buckets;

    int hashFunction(int id)
    {
        return id % largo;
    }
    int hashFunction2(int id)
    {
        return 1 + (id % (largo - 1));
    }
    // Function to find the next prime (for resizing or rehashing)
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

public:
    tablaHash(int largoSupuesto)
    {
        this->largo = siguientePrimo(largoSupuesto);
        this->buckets = new HashNodeLibro *[largo];
    }
    void agregar(int id, string titulo)
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
                i++;
            }
        }
        cantidad++;
    }
};