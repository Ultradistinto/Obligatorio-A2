#include <iostream>
#include <string>
#include "tads/nuevoGrafo.cpp"

using namespace std;
int *caminoInvertido(int *aRecorrer, int desde)
{
    int largo = 1;
    int paso = desde;
    while (paso != 0)
    {
        largo++;
        paso = aRecorrer[paso];
    }
    int *ret = new int[largo];
    paso = desde;
    while (paso != 0)
    {
        ret[largo] = paso;
        paso = aRecorrer[paso];
        largo--;
    }
    ret[0] = largo - 1;
    return ret;
}

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
            grafoMisiones.agregarAristaDirigida(dep, idMision, 1);
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
    cout << "Ciudad inicial: ";
    cout << ciudadSalida;
    int *posiblesMisiones = grafoMisiones.getMisionesPosibles();
    while (posiblesMisiones[0] != 0)
    {
        int min = 2147483647;
        int **minimaDistancia = grafoCiudades.dijkstra(C);
        int idSiguienteMision = 0;
        for (int i = 0; i < M && posiblesMisiones[i] != 0; i++)
        {
            if (minimaDistancia[0][i] < min)
            {
                min = minimaDistancia[0][i];
                idSiguienteMision = posiblesMisiones[i];
            }
        }
        int *caminoAlaMision = caminoInvertido(minimaDistancia[1], C);
        for (int i = 1; i < caminoAlaMision[0]; i++)
        {
            cout << listaNombreCiudades[caminoAlaMision[i]]; // recorrido desde C hasta donde se hace la mision
            cout << " -> ";
        }
        cout << "Mision: ";
        cout << listaNombreMisiones[idSiguienteMision];
        cout << " - ";
        cout << listaIdCiudadMisiones[idSiguienteMision];
        cout << " - Tiempo de viaje: ";
        cout << min << endl;
        grafoMisiones.misionCompletada(idSiguienteMision);
        posiblesMisiones = grafoMisiones.getMisionesPosibles();
    }

    return 0;
}
