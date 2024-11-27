#include <iostream>
#include <string>
using namespace std;

void ponerFlor(int **mat, int i, int j, int Flor)
{
    mat[i][j] = Flor;
}
void sacarFlor(int **mat, int i, int j)
{
    mat[i][j] = -1;
}

bool esValido(int **mat, int n, int *restricciones, int i, int j, int f)
{
    if (restricciones[f] == -1 || restricciones[f] == i)
    {
        if (i - 1 >= 0 && mat[i - 1][j] == f)
        {
            return false;
        }
        if (i + 1 < n && mat[i + 1][j] == f)
        {
            return false;
        }
        if (j - 1 >= 0 && mat[i][j - 1] == f)
        {
            return false;
        }
        if (j + 1 < n && mat[i][j + 1] == f)
        {
            return false;
        }
        if (i - 1 >= 0 && j - 1 >= 0 && mat[i - 1][j - 1] == f)
        {
            return false;
        }
        if (i - 1 >= 0 && j + 1 < n && mat[i - 1][j + 1] == f)
        {
            return false;
        }
        if (i + 1 < n && j - 1 >= 0 && mat[i + 1][j - 1] == f)
        {
            return false;
        }
        if (i + 1 < n && j + 1 < n && mat[i + 1][j + 1] == f)
        {
            return false;
        }
        return true;
    }
    return false;
}

void floresBT(int **mat, int *restricciones, int n, int fila, int columna, int cantFlores, int floresActuales, int &floresMax)
{
    if (floresActuales + (n - fila) * n < floresMax)
    {
        return;
    }

    if (fila >= n)
    {
        if (floresMax < floresActuales)
        {
            floresMax = floresActuales;
        }
        return;
    }
    if (columna >= n)
    {
        floresBT(mat, restricciones, n, fila + 1, 0, cantFlores, floresActuales, floresMax);
        return;
    }

    for (int f = 0; f < cantFlores; f++)
    {
        if (esValido(mat, n, restricciones, fila, columna, f))
        {
            ponerFlor(mat, fila, columna, f);
            floresBT(mat, restricciones, n, fila, columna + 1, cantFlores, floresActuales + 1, floresMax);
            sacarFlor(mat, fila, columna);
        }
    }
    floresBT(mat, restricciones, n, fila, columna + 1, cantFlores, floresActuales, floresMax);
}

int main()
{
    int n;
    cin >> n;
    int **jardin = new int *[n];
    for (int i = 0; i < n; i++)
    {
        jardin[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            jardin[i][j] = -1;
        }
    }
    int F;
    cin >> F;
    int *restricciones = new int[F];
    string cosa;
    int rest;
    for (int i = 0; i < F; i++)
    {
        cin >> cosa >> rest;
        restricciones[i] = rest;
    }
    int floresMax = 0;

    floresBT(jardin, restricciones, n, 0, 0, F, 0, floresMax);
    cout << floresMax << endl;
    return 0;
}