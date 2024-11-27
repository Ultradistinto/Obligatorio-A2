#include <iostream>
#include <cmath>
using namespace std;
#include "tads/nuevoPar.cpp"

void countingSort(Par<Par<int, int>, int> *puntos, int n, int exp)
{
    Par<Par<int, int>, int> *output = new Par<Par<int, int>, int>[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(puntos[i].fst.fst / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (puntos[i].fst.fst / exp) % 10;
        output[count[digit] - 1] = puntos[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++)
        puntos[i] = output[i];

    delete[] output;
}

void radixSort(Par<Par<int, int>, int> *puntos, int n)
{
    int maxX = puntos[0].fst.fst;
    for (int i = 1; i < n; i++)
        maxX = max(maxX, puntos[i].fst.fst);

    for (int exp = 1; maxX / exp > 0; exp *= 10)
        countingSort(puntos, n, exp);
}

float distancia(Par<Par<int, int>, int> ciudad1, Par<Par<int, int>, int> ciudad2)
{
    float dist = sqrt((ciudad1.fst.fst - ciudad2.fst.fst) * (ciudad1.fst.fst - ciudad2.fst.fst) + (ciudad1.fst.snd - ciudad2.fst.snd) * (ciudad1.fst.snd - ciudad2.fst.snd));
    float diffPoblacion = abs(ciudad1.snd - ciudad2.snd) / (float)max(ciudad1.snd, ciudad2.snd);

    return dist + diffPoblacion;
}

Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> minimoPuntos(Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> ciudad1, Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> ciudad2)
{
    if (distancia(ciudad1.fst, ciudad1.snd) > distancia(ciudad2.fst, ciudad2.snd))
    {
        return ciudad2;
    }
    else
    {
        return ciudad1;
    }
}

Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> casoBase(Par<Par<int, int>, int> *puntos, int left, int right)
{
    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> retorno;
    float minDist = 100000;
    for (int i = left; i <= right; i++)
    {
        for (int j = i + 1; j <= right; j++)
        {
            float dist = distancia(puntos[i], puntos[j]);
            if (dist < minDist)
            {
                minDist = dist;
                retorno.fst = puntos[i];
                retorno.snd = puntos[j];
            }
        }
    }
    return retorno;
}

Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> masCercano(Par<Par<int, int>, int> *puntosMasCercanos, int tamaño, Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> distanciaMinima)
{
    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> retorno = distanciaMinima;
    for (int i = 0; i < tamaño; i++)
    {
        for (int j = i + 1; j < tamaño; j++)
        {
            if (distancia(retorno.fst, retorno.snd) > distancia(puntosMasCercanos[i], puntosMasCercanos[j]))
            {
                retorno.fst = puntosMasCercanos[i];
                retorno.snd = puntosMasCercanos[j];
            }
        }
    }
    return retorno;
}

Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> intMinimaDistancia(Par<Par<int, int>, int> *puntos, int left, int right)
{
    if (right - left + 1 <= 3)
    {
        return casoBase(puntos, left, right);
    }
    int mid = (left + right) / 2;
    Par<Par<int, int>, int> puntoMedio = puntos[mid];

    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> minimoIzquierda = intMinimaDistancia(puntos, left, mid);
    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> minimoDerecha = intMinimaDistancia(puntos, mid + 1, right);

    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> minDist = minimoPuntos(minimoIzquierda, minimoDerecha);

    Par<Par<int, int>, int> *puntosMasCercanos = new Par<Par<int, int>, int>[right - left + 1];

    int j = 0;
    for (int i = left; i <= right; i++)
    {
        if (distancia(minDist.fst, minDist.snd) > abs(puntos[i].fst.fst - puntoMedio.fst.fst))
        {
            puntosMasCercanos[j] = puntos[i];
            j++;
        }
    }
    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> masCercanoEnStrip = masCercano(puntosMasCercanos, j, minDist);
    return masCercanoEnStrip;
}

int main()
{
    int n, x, y, poblacion;
    cin >> n;

    Par<Par<int, int>, int> *puntos = new Par<Par<int, int>, int>[n];

    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> poblacion;
        puntos[i].fst.fst = x;
        puntos[i].fst.snd = y;
        puntos[i].snd = poblacion;
    }
    radixSort(puntos, n);
    Par<Par<Par<int, int>, int>, Par<Par<int, int>, int>> ciudadesMasCercanas = intMinimaDistancia(puntos, 0, n - 1);
    if (ciudadesMasCercanas.fst.fst.fst == ciudadesMasCercanas.snd.fst.fst && ciudadesMasCercanas.fst.fst.snd < ciudadesMasCercanas.snd.fst.snd)
    {
        cout << ciudadesMasCercanas.fst.fst.fst << " " << ciudadesMasCercanas.fst.fst.snd << " " << ciudadesMasCercanas.fst.snd << endl;
        cout << ciudadesMasCercanas.snd.fst.fst << " " << ciudadesMasCercanas.snd.fst.snd << " " << ciudadesMasCercanas.snd.snd << endl;
    }
    else if (ciudadesMasCercanas.fst.fst.fst == ciudadesMasCercanas.snd.fst.fst && ciudadesMasCercanas.fst.fst.snd > ciudadesMasCercanas.snd.fst.snd)
    {
        cout << ciudadesMasCercanas.snd.fst.fst << " " << ciudadesMasCercanas.snd.fst.snd << " " << ciudadesMasCercanas.snd.snd << endl;
        cout << ciudadesMasCercanas.fst.fst.fst << " " << ciudadesMasCercanas.fst.fst.snd << " " << ciudadesMasCercanas.fst.snd << endl;
    }
    else if (ciudadesMasCercanas.fst.fst.fst > ciudadesMasCercanas.snd.fst.fst)
    {
        cout << ciudadesMasCercanas.snd.fst.fst << " " << ciudadesMasCercanas.snd.fst.snd << " " << ciudadesMasCercanas.snd.snd << endl;
        cout << ciudadesMasCercanas.fst.fst.fst << " " << ciudadesMasCercanas.fst.fst.snd << " " << ciudadesMasCercanas.fst.snd << endl;
    }
    else
    {
        cout << ciudadesMasCercanas.fst.fst.fst << " " << ciudadesMasCercanas.fst.fst.snd << " " << ciudadesMasCercanas.fst.snd << endl;
        cout << ciudadesMasCercanas.snd.fst.fst << " " << ciudadesMasCercanas.snd.fst.snd << " " << ciudadesMasCercanas.snd.snd << endl;
    }

    return 0;
}