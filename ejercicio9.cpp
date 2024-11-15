#include <iostream>
#include <string>
using namespace std;

int main()
{
    int j;
    cin >> j;
    int jugadores[j][3];
    int valoracion, Ritmo, Tiro, Pase, Regate, Defensa, Fisico, Salario, presupuesto, cupoExtranjeros;
    string formaFisica, Extranjero, Confianza;
    for (int i = 0; i < j; i++)
    {
        cin >> Ritmo >> Tiro >> Pase >> Regate >> Defensa >> Fisico >> Salario >> formaFisica >> Extranjero >> Confianza;

        valoracion = (Ritmo + Tiro + Pase + Regate + Defensa + Fisico) / 6;

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

        if (formaFisica == "Alta")
        {
            valoracion += 5;
        }
        else if (formaFisica == "Baja")
        {
            valoracion -= 5;
        }

        jugadores[i][0] = valoracion;
        jugadores[i][1] = Salario;

        if (Extranjero == "Si")
        {
            jugadores[i][2] = 1;
        }
        else
        {
            jugadores[i][2] = 0;
        }
    }
    cin >> presupuesto >> cupoExtranjeros;

    int respuesta[j + 1][presupuesto + 1][12];

    for (int i = 0; i <= j; i++)
    {
        respuesta[i][0][0] = 0;
    }
    for (int i = 0; i <= presupuesto; i++)
    {
        respuesta[0][i][0] = 0;
    }
    for (int i = 0; i <= 11; i++)
    {
        respuesta[0][0][i] = 0;
    }

    for (int i = 1; i <= j; i++)
    {
        for (int k = 0; k <= presupuesto; k++)
        {
            for (int m = 1; m <= 11; m++)
            {
                if (jugadores[i - 1][1] <= k)
                {
                    if (respuesta[i - 1][k][m] > respuesta[i - 1][k - jugadores[i - 1][1]][m - 1] + jugadores[i - 1][0])
                    {
                        respuesta[i][k][m] = respuesta[i - 1][k][m];
                    }
                    else
                    {
                        respuesta[i][k][m] = respuesta[i - 1][k - jugadores[i - 1][1]][m - 1] + jugadores[i - 1][0];
                    }
                }
                else
                {
                    respuesta[i][k][m] = respuesta[i - 1][k][m];
                }
            }
        }
    }
    cout << respuesta[j][presupuesto][12];

    return 0;
}