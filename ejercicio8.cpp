#include <iostream>
#include <cmath>
using namespace std;

double** shaco = new double*[2];

double max(double A, double B){
    if(A >= B)
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

double casoBase(double **puntos, int left, int right, double** &shaco)
{
    double minDist = double(INT8_MAX);
    double** retorno = new double*[2];
    for (int i = left; i < right; i++)
    {
        for (int j = i + 1; j < right; j++)
        {
            if (distancia(puntos[i], puntos[j]) < minDist)
            {
                minDist = distancia(puntos[i], puntos[j]);
                
                shaco[0] = puntos[i];
                shaco[1] = puntos[j];
            }
        }
    }
    return minDist;
}

double elMasCercano(double **puntos, int final, double minDist)
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
                shaco[0] = puntos[j];
                shaco[1] = puntos[i];
            }
        }
    }
    return minimo;
}

double minimaDistancia(double **puntos, int left, int right)
{
    if (right - left <= 3)
    {
        return casoBase(puntos, left, right, shaco);
    }

    int mid = left + (right - left) / 2;

    double dl = minimaDistancia(puntos, left, mid);
    double dr = minimaDistancia(puntos, mid + 1, right);

    double minDist = min(dl, dr);

    double **masCercanos = new double *[right - left];
    for (int i = left; i < right; i++)
    {
        masCercanos[i] = new double[3];
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
    double **ciudades = new double *[n];
    for (int i = 0; i < n; i++)
    {
        ciudades[i] = new double[3];
        cin >> ciudades[i][0] >> ciudades[i][1] >> ciudades[i][2];
    }
    ordenar(ciudades, 0, n);

    minimaDistancia(ciudades, 0, n - 1);
    cout<<shaco[0][0]<<" " << shaco[0][1] << " " << shaco[0][2] << endl;
    cout<<shaco[1][0]<<" " << shaco[1][1] << " " << shaco[1][2];
}