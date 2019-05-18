#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <tgmath.h>

using namespace std;

int N, gyokN, T;
long long osszeg, valtElem;
int Tomb[1000000];
int Elofordul[1000001] = {};
long long Eredmeny[1000000];

class Kerdes
{
public:
    int tol, ig, sorszam;
    /// összehasonlítás N gyöke szerinti blokkok alapján
    bool operator()(const Kerdes &A, const Kerdes& B) const
    {
        if (A.tol / gyokN < B.tol / gyokN)
        {
            return true;
        }
        else if (A.tol / gyokN == B.tol / gyokN && A.ig < B.ig)
        {
            return true;
        }
        return false;
    }
};

Kerdes aktualis;
vector <Kerdes> kerdesek;

int main()
{
    cin >> N >> T;
    gyokN = (int) ceil(sqrt(N));

    for (int i=0;i<N;i++)
    {
        cin >> Tomb[i];
    }
    for (int i=0;i<T;i++)
    {
        cin >> aktualis.tol >> aktualis.ig;
        --aktualis.tol; --aktualis.ig;
        aktualis.sorszam = i;
        kerdesek.push_back(aktualis);
    }

    sort(kerdesek.begin(), kerdesek.end(), Kerdes());

    osszeg = 0;
    int bal = 0;
    int jobb = -1;
    for (int i=0;i<T;i++)
    {
        while (bal > kerdesek[i].tol)
        {
            bal--;
            valtElem = Tomb[bal];
            osszeg += valtElem * (2 * Elofordul[valtElem] + 1);
            ++Elofordul[valtElem];
        }
        while (jobb < kerdesek[i].ig)
        {
            jobb++;
            valtElem = Tomb[jobb];
            osszeg += valtElem * (2 * Elofordul[valtElem] + 1);
            ++Elofordul[valtElem];
        }
        while (bal < kerdesek[i].tol)
        {
            valtElem = Tomb[bal];
            --Elofordul[valtElem];
            osszeg -= valtElem * (2 * Elofordul[valtElem] + 1);
            bal++;
        }
        while (jobb > kerdesek[i].ig)
        {
            valtElem = Tomb[jobb];
            --Elofordul[valtElem];
            osszeg -= valtElem * (2 * Elofordul[valtElem] + 1);
            jobb--;
        }
        Eredmeny[kerdesek[i].sorszam] = osszeg;
    }

    for (int i=0;i<T;i++)
    {
        cout << Eredmeny[i] << endl;
    }
    return 0;
}
