#include <iostream>
#include <string>
#include "tads/arbolLibros.cpp"
using namespace std;

string entrada;
bool flag = true;
int n;

int main()
{
    cin >> n;
    // creo arbol
    //
    AVLArbol biblioteca;
    for (int i = 0; i < n; i++)
    {
        cin >> entrada;
        if (entrada == "ADD")
        {
            int id;
            string titulo;
            cin >> id >> titulo;
            // libro con "id" , "titulo" y "estado"

            // agrego libro a avl
            biblioteca.add(id, titulo);
        }
        else if (entrada == "FIND")
        {
            int id;
            cin >> id;

            // find en avl y lo printea
            cout << biblioteca.find(id);
        }
        else if (entrada == "TOGGLE")
        {
            int id;
            cin >> id;
            // toggle en el estado del libro con el id
            biblioteca.toggle(id);
        }
        else if (entrada == "COUNT")
        {
            // printea total, habilitados y deshabilitados
            cout << biblioteca.totales() << " " << biblioteca.habilitadosF() << " " << biblioteca.deshabilitados();
        }
    }

    return 0;
}
