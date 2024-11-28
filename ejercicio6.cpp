#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/nuevoGrafo.cpp"
#include "tads/pair.cpp"

using namespace std;

int main()
{
    int cantCiudades, idCiudad;
    string nombreCiudad;
    cin >> cantCiudades;

    string *listaCiudades = new string[cantCiudades + 1];

    for (int i = 0; i < cantCiudades; i++)
    {
        cin >> idCiudad >> nombreCiudad;
        listaCiudades[idCiudad] = nombreCiudad;
    }

    int S, E, T, P;
    cin >> S >> E >> T >> P;

    nuevoGrafo grafoCiudadesE(cantCiudades, 0);
    nuevoGrafo grafoCiudadesT(cantCiudades, 0);

    int cantAristas, ciudadSalida, ciudadLlegada, tiempo;
    cin >> cantAristas;

    for (int i = 0; i < cantAristas; i++)
    {
        cin >> ciudadSalida >> ciudadLlegada >> tiempo;
        grafoCiudadesE.agregarAristaNoDirigida(ciudadSalida, ciudadLlegada, tiempo);
        grafoCiudadesT.agregarAristaNoDirigida(ciudadSalida, ciudadLlegada, tiempo);
    }

    int **arraysDijkstraInicial = grafoCiudadesE.dijkstra(S);
    int *costos = arraysDijkstraInicial[0];
    int *ant = arraysDijkstraInicial[1];

    int costoTotalE = costos[E];
    int *caminoS_E = new int[10];
    int contadorE1 = 1;

    int indice = E;
    int aux;
    while (indice != S && indice != 0)
    {
        caminoS_E[contadorE1] = ant[indice];
        contadorE1++;
        aux = indice;
        indice = ant[indice];
        int nuevoPeso = grafoCiudadesE.pesoArista(indice, aux) * 2;
        grafoCiudadesE.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorE1--;

    int **arraysDijkstraE_T = grafoCiudadesE.dijkstra(E);
    int *costosE_T = arraysDijkstraE_T[0];
    int *antE_T = arraysDijkstraE_T[1];
    costoTotalE += costosE_T[T];

    int *caminoE_T = new int[10];
    int contadorE2 = 1;

    indice = T;
    while (indice != E && indice != 0)
    {
        caminoE_T[contadorE2] = antE_T[indice];
        contadorE2++;
        aux = indice;
        indice = antE_T[indice];
        int nuevoPeso = grafoCiudadesE.pesoArista(indice, aux) * 2;
        grafoCiudadesE.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorE2--;

    int **arraysDijkstraT_P = grafoCiudadesE.dijkstra(T);
    int *costosT_P = arraysDijkstraT_P[0];
    int *antT_P = arraysDijkstraT_P[1];
    costoTotalE += costosT_P[P];

    int *caminoT_P = new int[10];
    int contadorE3 = 1;

    indice = P;
    while (indice != T && indice != 0)
    {
        caminoT_P[contadorE3] = antT_P[indice];
        contadorE3++;
        aux = indice;
        indice = antT_P[indice];
        int nuevoPeso = grafoCiudadesE.pesoArista(indice, aux) * 2;
        grafoCiudadesE.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorE3--;

    // Team es nuestro destino
    int costoTotalT = costos[T];

    int *caminoS_T = new int[10];
    int contadorT1 = 1;

    indice = T;
    while (indice != S && indice != 0)
    {
        caminoS_T[contadorT1] = ant[indice];
        contadorT1++;
        aux = indice;
        indice = ant[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorT1--;

    int **arraysDijkstraT_E = grafoCiudadesT.dijkstra(T);
    int *costosT_E = arraysDijkstraT_E[0];
    int *antT_E = arraysDijkstraT_E[1];
    costoTotalT += costosT_E[E];

    int *caminoT_E = new int[10];
    int contadorT2 = 1;

    indice = E;
    while (indice != T && indice != 0)
    {
        caminoT_E[contadorT2] = antT_E[indice];
        contadorT2++;
        aux = indice;
        indice = antT_E[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorT2--;

    int **arraysDijkstraE_P = grafoCiudadesT.dijkstra(E);
    int *costosE_P = arraysDijkstraE_P[0];
    int *antE_P = arraysDijkstraE_P[1];
    costoTotalT += costosE_P[P];

    int *caminoE_P = new int[10];
    int contadorT3 = 1;

    indice = P;
    while (indice != E && indice != 0)
    {
        caminoE_P[contadorT3] = antE_P[indice];
        contadorT3++;
        aux = indice;
        indice = antE_P[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
    }
    contadorT3--;

    if (costoTotalE <= costoTotalT)
    {
        cout << "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " << costoTotalE << endl;
        cout << "La otra opcion tiene un costo de " << costoTotalT << endl;

        cout << "Paso 1: ";
        while (contadorE1 != 0)
        {
            cout << listaCiudades[caminoS_E[contadorE1]] << " -> ";
            contadorE1--;
        }
        cout << listaCiudades[E] << " -> ";
        cout << "Desactivar la Entidad" << endl;

        cout << "Paso 2: ";
        while (contadorE2 != 0)
        {
            cout << listaCiudades[caminoE_T[contadorE2]] << " -> ";
            contadorE2--;
        }
        cout << listaCiudades[T] << " -> ";
        cout << "Buscar equipo" << endl;

        cout << "Paso 3: ";
        while (contadorE3 != 0)
        {
            cout << listaCiudades[caminoT_P[contadorE3]] << " -> ";
            contadorE3--;
        }
        cout << listaCiudades[P] << " -> ";
        cout << "Ir a Punto de extraccion" << endl;
    }
    else
    {
        cout << "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " << costoTotalT << endl;
        cout << "La otra opcion tiene un costo de " << costoTotalE << endl;

        cout << "Paso 1: ";
        while (contadorT1 != 0)
        {
            cout << listaCiudades[caminoS_T[contadorT1]] << " -> ";
            contadorT1--;
        }
        cout << listaCiudades[T] << " -> ";
        cout << "Buscar equipo" << endl;

        cout << "Paso 2: ";
        while (contadorT2 != 0)
        {
            cout << listaCiudades[caminoT_E[contadorT2]] << " -> ";
            contadorT2--;
        }
        cout << listaCiudades[E] << " -> ";
        cout << "Desactivar la Entidad" << endl;

        cout << "Paso 3: ";
        while (contadorT3 != 0)
        {
            cout << listaCiudades[caminoE_P[contadorT3]] << " -> ";
            contadorT3--;
        }
        cout << listaCiudades[P] << " -> ";
        cout << "Ir a Punto de extraccion" << endl;
    }

    return 0;
}
