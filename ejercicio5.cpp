#include <iostream>
#include <string>
#include "tads/minHeap.cpp"
#include "tads/nuevoGrafo.cpp"

using namespace std;

int main()
{
    int M, idMision, idCiudad, dep, cant;
    string nombreMision, nombreCiudad;
    cin >> M;
    nuevoGrafo grafoMisiones(M, 0);
    int *listaIdCiudadMisiones = new int[M + 1];
    string *listaNombreMisiones = new string[M + 1];

    for (int i = 0; i < M; i++)
    {
        cin >> idMision >> nombreMision >> idCiudad >> dep;

        while (dep != 0)
        {
            grafoMisiones.agregarAristaDirigida(idMision, dep, 1);
            cin >> dep;
        }
        listaIdCiudadMisiones[idMision] = idCiudad;
        listaNombreMisiones[idMision] = nombreMision;
    }
    int C, O;
    cin >> C >> O;
    int ciudadInicio = O;
    nuevoGrafo grafoCiudades(C, 0);
    string *listaNombreCiudades = new string[C + 1];
    for (int i = 0; i < C; i++)
    {
        cin >> idCiudad >> nombreCiudad;
        listaNombreCiudades[idCiudad] = nombreCiudad;
    }
    int E, ciudadSalida, ciudadEntrada, tiempo;
    cin >> E;
    for (int i = 0; i < E; i++)
    {
        cin >> ciudadSalida >> ciudadEntrada >> tiempo;
        grafoCiudades.agregarAristaNoDirigida(ciudadSalida, ciudadEntrada, tiempo);
    }

    return 0;
}