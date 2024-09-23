#include <iostream>
#include "tads/minHeap.cpp"
using namespace std;

int n;
int main()
{
    cin >> n;
    int id, precio;
    bool lista[n + 1];
    minHeap objetos = minHeap(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> id >> precio;
        objetos.add(id, precio);
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        myPair popeado = objetos.pop();
        if (!lista[popeado.getFst()])
        {
            cout << popeado.getFst() << endl;
            lista[popeado.getFst()] = true;
        }
    }
    return 0;
}