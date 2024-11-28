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

    cout << "Número de ciudades: " << cantCiudades << endl; // Debugging

    string *listaCiudades = new string[cantCiudades + 1];

    for (int i = 0; i < cantCiudades; i++)
    {
        cin >> idCiudad >> nombreCiudad;
        listaCiudades[idCiudad] = nombreCiudad;
        cout << "Ciudad " << idCiudad << ": " << nombreCiudad << endl; // Debugging
    }

    int S, E, T, P;
    cin >> S >> E >> T >> P;
    cout << "Datos de entrada: S=" << S << ", E=" << E << ", T=" << T << ", P=" << P << endl; // Debugging

    nuevoGrafo grafoCiudadesE(cantCiudades, 0);
    nuevoGrafo grafoCiudadesT(cantCiudades, 0);

    int cantAristas, ciudadSalida, ciudadLlegada, tiempo;
    cin >> cantAristas;
    cout << "Número de aristas: " << cantAristas << endl; // Debugging

    for (int i = 0; i < cantAristas; i++)
    {
        cin >> ciudadSalida >> ciudadLlegada >> tiempo;
        grafoCiudadesE.agregarAristaNoDirigida(ciudadSalida, ciudadLlegada, tiempo);
        grafoCiudadesT.agregarAristaNoDirigida(ciudadSalida, ciudadLlegada, tiempo);
        cout << "Arista: " << ciudadSalida << " -> " << ciudadLlegada << " con tiempo " << tiempo << endl; // Debugging
    }

    int **arraysDijkstraInicial = grafoCiudadesE.dijkstra(S);
    int *costos = arraysDijkstraInicial[0];
    int *ant = arraysDijkstraInicial[1];

    // Entity es nuestro destino
    int costoTotalE = costos[E];
    int *caminoS_E = new int[10];
    int contadorE1 = 1;

    cout << "Costo inicial de E: " << costoTotalE << endl; // Debugging

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
        cout << "En el camino de S a E: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }

    contadorE1--;
    int **arraysDijkstraE_T = grafoCiudadesE.dijkstra(E);
    int *costosE_T = arraysDijkstraE_T[0];
    int *antE_T = arraysDijkstraE_T[1];
    costoTotalE += costosE_T[T];

    int *caminoE_T = new int[10];
    int contadorE2 = 1;

    cout << "Costo de E a T: " << costosE_T[T] << endl; // Debugging

    indice = T;
    while (indice != E && indice != 0)
    {
        caminoE_T[contadorE2] = antE_T[indice];
        contadorE2++;
        aux = indice;
        indice = antE_T[indice];
        int nuevoPeso = grafoCiudadesE.pesoArista(indice, aux) * 2;
        grafoCiudadesE.agregarAristaNoDirigida(indice, aux, nuevoPeso);
        cout << "En el camino de E a T: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }
    contadorE2--;

    int **arraysDijkstraT_P = grafoCiudadesE.dijkstra(T);
    int *costosT_P = arraysDijkstraT_P[0];
    int *antT_P = arraysDijkstraT_P[1];
    costoTotalE += costosT_P[P];

    int *caminoT_P = new int[10];
    int contadorE3 = 1;

    cout << "Costo de T a P: " << costosT_P[P] << endl; // Debugging

    indice = P;
    while (indice != T && indice != 0)
    {
        caminoT_P[contadorE3] = antT_P[indice];
        contadorE3++;
        aux = indice;
        indice = antT_P[indice];
        int nuevoPeso = grafoCiudadesE.pesoArista(indice, aux) * 2;
        grafoCiudadesE.agregarAristaNoDirigida(indice, aux, nuevoPeso);
        cout << "En el camino de T a P: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }
    contadorE3--;

    // Team es nuestro destino
    int costoTotalT = costos[T];

    int *caminoS_T = new int[10];
    int contadorT1 = 1;

    cout << "Costo inicial de T: " << costoTotalT << endl; // Debugging

    indice = T;
    while (indice != S && indice != 0)
    {
        caminoS_T[contadorT1] = ant[indice];
        contadorT1++;

        aux = indice;
        indice = ant[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
        cout << "En el camino de S a T: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }
    contadorT1--;

    int **arraysDijkstraT_E = grafoCiudadesT.dijkstra(T);
    int *costosT_E = arraysDijkstraT_E[0];
    int *antT_E = arraysDijkstraT_E[1];
    costoTotalT += costosT_E[E];

    int *caminoT_E = new int[10];
    int contadorT2 = 1;

    cout << "Costo de T a E: " << costosT_E[E] << endl; // Debugging

    indice = E;
    while (indice != T && indice != 0)
    {
        caminoT_E[contadorT2] = antT_E[indice];
        contadorT2++;

        aux = indice;
        indice = antT_E[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
        cout << "En el camino de T a E: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }
    contadorT2--;

    int **arraysDijkstraE_P = grafoCiudadesT.dijkstra(T);
    int *costosE_P = arraysDijkstraE_P[0];
    int *antE_P = arraysDijkstraE_P[1];
    costoTotalT += costosE_P[P];

    int *caminoE_P = new int[10];
    int contadorT3 = 1;

    cout << "Costo de E a P: " << costosE_P[P] << endl; // Debugging

    indice = P;
    while (indice != E && indice != 0)
    {
        caminoE_P[contadorT3] = antE_P[indice];
        contadorT3++;

        aux = indice;
        indice = antE_P[indice];
        int nuevoPeso = grafoCiudadesT.pesoArista(indice, aux) * 2;
        grafoCiudadesT.agregarAristaNoDirigida(indice, aux, nuevoPeso);
        cout << "En el camino de E a P: ciudad " << indice << " -> " << aux << " con nuevo peso " << nuevoPeso << endl; // Debugging
    }
    contadorT3--;

    // Debugging - showing final costs
    cout << "Costo total E: " << costoTotalE << endl;
    cout << "Costo total T: " << costoTotalT << endl;

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
