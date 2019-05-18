#include <iostream>
#include <tgmath.h>
#include <bits/stdc++.h>

using namespace std;

/// Sparse table
int minimumok[100000][17];

int main()
{
    ios_base::sync_with_stdio(false);
    int N, Q, tol, ig, k;
    cin >> N;
    for (int i=0;i<N;i++)
    {
        cin >> minimumok[i][0];
    }
    cin >> Q;
    /// Sparse table kitöltése
    for (int j=1;(1 << j)<=N;j++)
    {
        for (int i=0;(i + (1 << j) - 1)<N;i++)
        {
            if (minimumok[i][j-1] < minimumok[i + (1 << (j - 1))][j-1])
            {
                minimumok[i][j] = minimumok[i][j-1];
            }
            else
            {
                minimumok[i][j] = minimumok[i + (1 << (j - 1))][j-1];
            }
        }
    }
    /// Kérdések megválaszolása
    for (int i=0;i<Q;i++)
    {
        cin >> tol >> ig;
        k = log2(ig - tol + 1);
        if (minimumok[tol][k] <= minimumok[ig + 1 - (1 << k)][k])
        {
            cout << minimumok[tol][k] << endl;
        }
        else
        {
            cout << minimumok[ig + 1 - (1 << k)][k] << endl;
        }
    }
    return 0;
}
