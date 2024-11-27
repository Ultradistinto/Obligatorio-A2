#include <iostream>
#include <cmath>
using namespace std;

double max(double A, double B)
{
    if (A >= B)
        return A;
    return B;
}
double min(double A, double B)
{
    if (A <= B)
        return A;
    return B;
}

void ordenar(double **puntos, int parte, int n)
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
        double *aux = puntos[i];
        puntos[i] = puntos[min_idx];
        puntos[min_idx] = aux;
    }
}

double distancia(double *A, double *B)
{
    double distFisica = sqrt((A[0] - B[0]) * (A[0] - B[0]) + (A[1] - B[1]) * (A[1] - B[1]));
    double distPob = abs(A[2] - B[2]) / max(A[2], B[2]);

    return distFisica + distPob;
}

double casoBase(double **puntos, int left, int right, double **&shaco)
{
    double minDist = double(INT8_MAX);
    for (int i = left; i < right; i++)
    {
        for (int j = i + 1; j < right; j++)
        {
            double dist = distancia(puntos[i], puntos[j]);

            if (dist < minDist)
            {
                minDist = dist;
                shaco[0] = puntos[i];
                shaco[1] = puntos[j];
            }
        }
    }
    return minDist;
}

double elMasCercano(double **puntos, int final, double minDist, double **&shaco)
{
    double minimo = minDist;

    for (int i = 0; i < final; i++)
    {
        for (int j = i + 1; j < final && (puntos[j][1] - puntos[i][1]) < minimo; j++)
        {
            double dist = distancia(puntos[j], puntos[i]);

            if (dist < minimo)
            {
                minimo = dist;
                shaco[0] = puntos[j];
                shaco[1] = puntos[i];
            }
        }
    }
    return minimo;
}

double minimaDistancia(double **puntos, int left, int right, double **&shaco)
{
    if (right - left <= 3)
    {
        return casoBase(puntos, left, right, shaco);
    }

    int mid = left + (right - left) / 2;

    double dl = minimaDistancia(puntos, left, mid, shaco);
    double dr = minimaDistancia(puntos, mid + 1, right, shaco);

    double minDist = min(dl, dr);

    double **masCercanos = new double *[right - left + 1];
    for (int i = 0; i < right - left; i++)
    {
        masCercanos[i] = nullptr;
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
    double retorno = min(minDist, elMasCercano(masCercanos, j, minDist, shaco));

    delete[] masCercanos;

    return retorno;
}

int main()
{
    double **shaco = new double *[2];
    shaco[0] = new double[3];
    shaco[1] = new double[3];

    int n;
    cin >> n;
    double **ciudades = new double *[n];
    for (int i = 0; i < n; i++)
    {
        ciudades[i] = new double[3];
        cin >> ciudades[i][0] >> ciudades[i][1] >> ciudades[i][2];
    }
    ordenar(ciudades, 0, n);

    minimaDistancia(ciudades, 0, n - 1, shaco);
    cout << shaco[0][0] << " " << shaco[0][1] << " " << shaco[0][2] << endl;
    cout << shaco[1][0] << " " << shaco[1][1] << " " << shaco[1][2];

    for (int i = 0; i < n; i++)
    {
        delete[] ciudades[i];
    }
    delete[] ciudades;
    delete[] shaco;

    return 0;
}
