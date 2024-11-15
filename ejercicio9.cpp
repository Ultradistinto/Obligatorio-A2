#include <iostream>
#include <string>
using namespace std;

int main()
{
    int j;
    cin >> j;
    int** jugadores = new int*[j];
    for(int i = 0; i < j; i++){
        jugadores[i] = new int[3];
    }

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

    int**** respuesta = new int***[j + 1];
    for(int i = 0; i <= j; i++){
        respuesta[i] = new int**[presupuesto + 1];
        for(int k = 0; k <= presupuesto; k++){
            respuesta[i][k] = new int* [12];
            for(int m = 0; m <= 11; m++){
                respuesta[i][k][m] = new int[cupoExtranjeros];
            }
        }
    }

    

    for (int i = 1; i <= j; i++)
    {
        for (int k = 0; k <= presupuesto; k++)
        {
            for (int m = 1; m <= 11; m++)
            {
                for(int r = 1; r <= cupoExtranjeros; r++){
                    if(jugadores[i - 1][1] <=k){
                        respuesta[i][k][m][r] = max(respuesta[i - 1][k][m][r], respuesta[i - 1][k - jugadores[i - 1][1]][m][r] + jugadores[i - 1][0]);
                    }
                    else{
                        respuesta[i][k][m][r] = respuesta[i - 1][k][m][r];
                    }
                }
            }
        }
    }
    cout << respuesta[j][presupuesto][11][cupoExtranjeros];

    return 0;
}