#include <iostream>
#include <cmath>
using namespace std;

void ordenar(int **&puntos, int parte, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (puntos[j][parte] < puntos[min_idx][parte])
            {
                min_idx = j;
            }
        }
        int *aux = puntos[i];
        puntos[i] = puntos[min_idx];
        puntos[min_idx] = aux;
    }
}

double distancia(int *A, int *B)
{
    double distFisica = sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]));
    double distPob = abs(A[2] - B[2]) / max(A[2], B[2]);

    return distFisica + distPob;
}

double casoBase(int **puntos, int left, int right)
{
    double minDist = INT8_MAX;
    for (int i = left; i < right; i++)
    {
        for (int j = i + 1; j < right; j++)
        {
            if (distancia(puntos[i], puntos[j]) < minDist)
            {
                minDist = distancia(puntos[i], puntos[j]);
            }
        }
    }
    return minDist;
}

double elMasCercano(int **puntos, int final, int minDist)
{
    double minimo = minDist;

    ordenar(puntos, 1, final);

    for (int i = 0; i < final; i++)
    {
        for (int j = i + 1; j < final && (puntos[j][1] - puntos[i][1]) < minimo; j++)
        {
            if (distancia(puntos[j], puntos[i]) < minimo)
            {
                minimo = distancia(puntos[j], puntos[i]);
            }
        }
    }
    return minimo;
}

double minimaDistancia(int **&puntos, int left, int right)
{
    if (right - left <= 3)
    {
        return casoBase(puntos, left, right);
    }

    int mid = left + (right - left) / 2;

    double dl = minimaDistancia(puntos, left, mid);
    double dr = minimaDistancia(puntos, mid + 1, right);

    double minDist = min(dl, dr);

    int **masCercanos = new int *[right - left];
    for (int i = left; i < right; i++)
    {
        masCercanos[i] = new int[3];
    }
    int j = 0;
    for (int i = left; i < right; i++)
    {
        if (abs(puntos[i][0] - puntos[mid][0]) < minDist)
        {
            masCercanos[j] = puntos[i];
            j++;
        }
    }
    return min(minDist, elMasCercano(masCercanos, j, minDist));
}

int main()
{
    int n;
    cin >> n;
    int **ciudades = new int *[n];
    for (int i = 0; i < n; i++)
    {
        ciudades[i] = new int[3];
        cin >> ciudades[i][0] >> ciudades[i][1] >> ciudades[i][2];
    }
    ordenar(ciudades, 0, n);
    for (int i = 0; i < n; i++)
    {
        cout << ciudades[i][0] << " " << ciudades[i][1] << " " << ciudades[i][2] << endl;
    }

    cout << minimaDistancia(ciudades, 0, n - 1);
}