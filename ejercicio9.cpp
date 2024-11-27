#include <iostream>
#include <string>
using namespace std;

int main()
{
    int j;
    cin >> j;

    cout << "Number of players: " << j << endl;

    int **jugadores = new int *[j];
    for (int i = 0; i < j; i++)
    {
        jugadores[i] = new int[3];
    }
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
        cout << valoracion << endl;
    }

    cin >> presupuesto >> cupoExtranjeros;

    cout << "Presupuesto: " << presupuesto << ", Cupo Extranjeros: " << cupoExtranjeros << endl;
    if (cupoExtranjeros > 0)
    {
        int ****respuesta = new int ***[j + 1];
        for (int i = 0; i <= j; i++)
        {
            respuesta[i] = new int **[presupuesto + 1];
            for (int k = 0; k <= presupuesto; k++)
            {
                respuesta[i][k] = new int *[12];
                for (int m = 0; m <= 11; m++)
                {
                    respuesta[i][k][m] = new int[cupoExtranjeros + 1]();
                }
            }
        }

        for (int i = 1; i <= j; i++)
        {
            for (int k = 0; k <= presupuesto; k++)
            {
                for (int m = 1; m <= 11; m++)
                {
                    for (int r = 1; r <= cupoExtranjeros; r++)
                    {

                        if (jugadores[i - 1][1] <= k)
                        {
                            if (jugadores[i - 1][2] == 1)
                            {
                                respuesta[i][k][m][r] = max(respuesta[i - 1][k][m][r], respuesta[i - 1][k - jugadores[i - 1][1]][m - 1][r - 1] + jugadores[i - 1][0]);
                            }
                            else if (jugadores[i - 1][2] == 0)
                            {
                                respuesta[i][k][m][r] = max(respuesta[i - 1][k][m][r], respuesta[i - 1][k - jugadores[i - 1][1]][m - 1][r] + jugadores[i - 1][0]);
                            }
                        }
                        else
                        {
                            respuesta[i][k][m][r] = respuesta[i - 1][k][m][r];
                        }
                    }
                }
            }
        }
        int final = respuesta[j][presupuesto][11][cupoExtranjeros] / 11;
        cout << final;
    }
    else
    {
        int ***respuesta = new int **[j + 1];
        for (int i = 0; i <= j; i++)
        {
            respuesta[i] = new int *[presupuesto + 1];
            for (int k = 0; k <= presupuesto; k++)
            {
                respuesta[i][k] = new int[12]();
            }
        }
        for (int i = 1; i <= j; i++)
        {
            for (int k = 0; k <= presupuesto; k++)
            {
                for (int m = 1; m <= 11; m++)
                {
                    if (jugadores[i - 1][1] <= k)
                    {
                        if (jugadores[i - 1][2] == 1)
                        {
                            respuesta[i][k][m] = respuesta[i - 1][k][m];
                        }
                        else if (jugadores[i - 1][2] == 0)
                        {
                            respuesta[i][k][m] = max(respuesta[i - 1][k][m], respuesta[i - 1][k - jugadores[i - 1][1]][m - 1] + jugadores[i - 1][0]);
                        }
                    }
                    else
                    {
                        respuesta[i][k][m] = respuesta[i - 1][k][m];
                    }
                }
            }
        }
        int final = respuesta[j][presupuesto][11] / 11;
        cout << final;
    }

    return 0;
}