#include <iostream>
#include <string>
using namespace std;

int doraLaExploradora(int cantJugadores, int *valorJugadores, int *precioJugadores, int *nacionalidadJugadores, int presupuesto, int maxExtranjeros, int totalJugadores)
{
    if (cantJugadores == 0 || presupuesto == 0 || totalJugadores == 0)
        return 0;

    if (precioJugadores[cantJugadores - 1] > presupuesto)
        return doraLaExploradora(cantJugadores - 1, valorJugadores, precioJugadores, nacionalidadJugadores, presupuesto, maxExtranjeros, totalJugadores);

    else if (nacionalidadJugadores[cantJugadores - 1] == 1 && maxExtranjeros > 0)
    {
        return max(valorJugadores[cantJugadores - 1] +
                       doraLaExploradora(cantJugadores - 1, valorJugadores, precioJugadores, nacionalidadJugadores, presupuesto - precioJugadores[cantJugadores - 1], maxExtranjeros - 1, totalJugadores - 1),
                   doraLaExploradora(cantJugadores - 1, valorJugadores, precioJugadores, nacionalidadJugadores, presupuesto, maxExtranjeros, totalJugadores));
    }
    else if (nacionalidadJugadores[cantJugadores - 1] == 0)
    {
        return max(valorJugadores[cantJugadores - 1] +
                       doraLaExploradora(cantJugadores - 1, valorJugadores, precioJugadores, nacionalidadJugadores, presupuesto - precioJugadores[cantJugadores - 1], maxExtranjeros, totalJugadores - 1),
                   doraLaExploradora(cantJugadores - 1, valorJugadores, precioJugadores, nacionalidadJugadores, presupuesto, maxExtranjeros, totalJugadores));
    }
    return 0;
}

int main()
{
    int j;
    cin >> j;
    int *valor = new int[j];
    int *precio = new int[j];
    int *extranjero = new int[j];

    int valoracion, Ritmo, Tiro, Pase, Regate, Defensa, Fisico, Salario, presupuesto, cupoExtranjeros;
    string formaFisica, Extranjero, Confianza;
    for (int i = 0; i < j; i++)
    {
        cin >> Ritmo >> Tiro >> Pase >> Regate >> Defensa >> Fisico >> formaFisica >> Salario >> Extranjero >> Confianza;
        cout << "Ritmo: " << Ritmo << " Tiro: " << Tiro << " Pase: " << Pase << " Regate: " << Regate << " Defensa: " << Defensa << " Fisico: " << Fisico << " Salario: " << Salario << " formaFisica: " << formaFisica << " Extranjero: " << Extranjero << " Confianza: " << Confianza << endl;
        valoracion = (Ritmo + Tiro + Pase + Regate + Defensa + Fisico) / 6;

        if (Confianza == "Alta")
        {
            valoracion += 5;
        }
        else if (Confianza == "Baja")
        {
            valoracion -= 5;
        }

        if (formaFisica == "Buena")
        {
            valoracion += 5;
        }
        else if (formaFisica == "Mala")
        {
            valoracion -= 5;
        }
        else if (formaFisica == "Lesionado")
        {
            valoracion = 0;
        }

        valor[i] = valoracion;
        precio[i] = Salario;

        if (Extranjero == "Si")
        {
            extranjero[i] = 1;
        }
        else
        {
            extranjero[i] = 0;
        }
        cout << valoracion << endl;
    }
    cin >> presupuesto >> cupoExtranjeros;

    cout << "Presupuesto: " << presupuesto << ", Cupo Extranjeros: " << cupoExtranjeros << endl;

    cout << doraLaExploradora(j, valor, precio, extranjero, presupuesto, cupoExtranjeros, 11) / 11 << endl;
}