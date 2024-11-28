#include <iostream>
#include <string>
#include "tads/nuevoGrafo.cpp"
#include "tads/lista.cpp"

using namespace std;
lista<int> caminoInvertido(int *aRecorrer, int desde)
{
    int paso = desde;
    lista<int> ret;
    ret.agregar(paso);
    while (paso != 0)
    {
        paso = aRecorrer[paso];
        if(paso != 0){
            ret.agregar(paso); 
        }
    }
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

    cout << listaNombreCiudades[ciudadInicio] << endl;
    int distanciaTotal = 0;
    int *posiblesMisiones = grafoMisiones.getMisionesPosibles();
    while (posiblesMisiones[0] != 0)
    {
        int min = 2147483647;
        myPair<int *, int *>minimaDistancia = grafoCiudades.dijkstra(ciudadInicio);
        int* distancias = minimaDistancia.getFst();
        int* anteriores = minimaDistancia.getSnd();
        int idSiguienteMision = 0;
        for (int i = 0; i < M && posiblesMisiones[i] != 0; i++)
        {
            if (distancias[listaIdCiudadMisiones[posiblesMisiones[i]]] < min)
            {
                min = distancias[listaIdCiudadMisiones[posiblesMisiones[i]]];
                idSiguienteMision = posiblesMisiones[i];
                ciudadInicio = listaIdCiudadMisiones[posiblesMisiones[i]];
            }
        }
        lista<int> caminoAlaMision = caminoInvertido(anteriores, ciudadInicio);
        int aux = 0;
        while (caminoAlaMision.obtenerCantidad() != 0)
        {   
            if(aux != 0){
                int ciudadAprintear = caminoAlaMision.obtenerHead();
                cout << listaNombreCiudades[ciudadAprintear]; // recorrido desde C hasta donde se hace la mision
                cout << " -> ";
            }
            aux++;
        }
        cout << "Mision: ";
        cout << listaNombreMisiones[idSiguienteMision];
        cout << " - ";
        cout << listaNombreCiudades[listaIdCiudadMisiones[idSiguienteMision]];
        cout << " - Tiempo de viaje: ";
        cout << min << endl;
        distanciaTotal += min;
        grafoMisiones.misionCompletada(idSiguienteMision);
        posiblesMisiones = grafoMisiones.getMisionesPosibles();
    }
    cout << "Misiones ejecutadas con exito." << endl;
    cout << "Tiempo total de viaje: ";
    cout << distanciaTotal << endl;
    return 0;
}
