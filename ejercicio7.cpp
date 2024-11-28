#include <iostream>
using namespace std;

bool sePuede(int *array, int n, int t, int maxSum)
{
    int currentSum = 0, particiones = 1;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > maxSum)
        {
            return false;
        }
        if (currentSum + array[i] > maxSum)
        {
            particiones++;
            currentSum = array[i];
            if (particiones > t)
            {
                return false;
            }
        }
        else
        {
            currentSum += array[i];
        }
    }
    return true;
}

int sumaIdeal(int *array, int n, int t, int max, int total)
{
    int izq = max;
    int der = total;
    int resultado = der;

    while (izq <= der)
    {
        int mid = izq + (der - izq) / 2;
        if (sePuede(array, n, t, mid))
        {
            resultado = mid;
            der = mid - 1;
        }
        else
        {
            izq = mid + 1;
        }
    }
    return resultado;
}

int main()
{
    int n, t;
    cin >> n;
    int array[n];
    int maxCancion = 0, sumaTotal = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
        if (maxCancion < array[i])
        {
            maxCancion = array[i];
        }
        sumaTotal += array[i];
    }
    cin >> t;
    int maximo = sumaIdeal(array, n, t, maxCancion, sumaTotal);
    int estudiantes[t][3];
    for (int i = 0; i < t; i++)
    {
        estudiantes[i][0] = 0;
        estudiantes[i][1] = 0;
        estudiantes[i][2] = 0;
    }
    int actual = 0, pos = 0, inicio = 1;
    for (int i = 0; i < n; i++)
    {
        if (actual + array[i] > maximo)
        {
            estudiantes[pos][0] = actual;
            estudiantes[pos][1] = inicio;
            estudiantes[pos][2] = i;
            inicio = i + 1;
            pos++;
            actual = array[i];
        }
        else
        {
            actual += array[i];
        }
    }
    estudiantes[pos][0] = actual;
    estudiantes[pos][1] = estudiantes[pos - 1][2] + 1;
    estudiantes[pos][2] = n;
    for (int i = 0; i < t; i++)
    {
        if (estudiantes[i][0] != 0)
        {
            cout << estudiantes[i][0] << " " << estudiantes[i][1] << " " << estudiantes[i][2] << endl;
        }
    }
    cout << maximo << endl;
}