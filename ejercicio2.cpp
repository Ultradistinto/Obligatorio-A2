#include <iostream>
#include <string>
#include "tads/tablaHash.cpp"
using namespace std;

string entrada;
bool flag = true;
int n;

int main()
{
    cin >> n;
    // creo arbol
    //
    tablaHash biblioteca = tablaHash(10);
    for (int i = 0; i < n; i++)
    {
        cin >> entrada;
        if (entrada == "ADD")
        {
            int id;
            string titulo;
            cin >> id >> titulo;
            // libro con "id" , "titulo" y "estado"

            // agrego libro a tabla
            biblioteca.add(id, titulo, "H");
        }
        else if (entrada == "FIND")
        {
            int id;
            cin >> id;

            // find en hash y lo printea
            cout << biblioteca.find(id) << endl;
        }
        else if (entrada == "TOGGLE")
        {
            int id;
            cin >> id;
            // toggle en el estado del libro con el id
            if (biblioteca.toggle(id) == "libro_no_encontrado")
            {
                cout << "libro_no_encontrado" << endl;
            }
        }
        else if (entrada == "COUNT")
        {
            // printea total, habilitados y deshabilitados
            cout << biblioteca.totalesF() << " " << biblioteca.habilitadosF() << " " << biblioteca.deshabilitados() << endl;
        }
    }

    return 0;
}
