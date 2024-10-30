#include <iostream>
#include "tads/minHeapExtra.cpp"

using namespace std;

int main()
{
    cout << boolalpha;
    int n, O, id, prio;
    string entrada, pedido, llevar;

    cin >> n >> O;

    bool lista[100001][2];
    for (int i = 0; i < 100001; i++)
    {
        lista[i][0] = false;
        lista[i][1] = true;
    }

    minHeapExtra objetos = minHeapExtra(n + 1);

    for (int i = 0; i < O; i++)
    {
        cin >> entrada;

        if (entrada == "I")
        {
            cin >> id >> prio >> llevar >> pedido;
            lista[id][0] = (llevar == "true");
            objetos.add(id, prio, pedido);
        }
        else if (entrada == "E")
        {
            int entregar;
            cin >> entregar;
            lista[entregar][1] = false;
        }
        else if (entrada == "C")
        {
            int cambiar;
            cin >> cambiar;
            lista[cambiar][0] = !lista[cambiar][0];
        }
    }

    minHeapExtra listaLlevar = minHeapExtra(n + 1);
    minHeapExtra listaNormal = minHeapExtra(n + 1);

    while (!objetos.isEmpty())
    {
        myTrio popeado = objetos.pop();

        if (lista[popeado.getFst()][1])
        {
            if (lista[popeado.getFst()][0])
            {
                listaLlevar.add(popeado.getFst(), popeado.getSnd(), popeado.getTrd());
            }
            else
            {
                listaNormal.add(popeado.getFst(), popeado.getSnd(), popeado.getTrd());
            }
        }
    }

    while (!listaNormal.isEmpty() || !listaLlevar.isEmpty())
    {
        myTrio popeado;
        if (!listaNormal.isEmpty() && (listaLlevar.isEmpty() || listaNormal.peek() < listaLlevar.peek()))
        {
            popeado = listaNormal.pop();
        }
        else
        {
            popeado = listaLlevar.pop();
        }
        cout << popeado.getFst() << " " << popeado.getSnd() << " " << lista[popeado.getFst()][0] << " " << popeado.getTrd() << endl;
    }
    return 0;
}
