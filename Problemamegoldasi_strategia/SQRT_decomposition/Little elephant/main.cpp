#include <iostream>
#include <algorithm>
#include <vector>
#include <tgmath.h>

using namespace std;

int N, gyokN, M, valasz, valtElem;
int A[100000];
int Elofordul[100001] = {};
int Eredmeny[100000];

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

void Hozzaad(const int ertek)
{
    if (ertek < 100001)
    {
        if (Elofordul[ertek] == ertek)
        {
            --valasz;
        }
        ++Elofordul[ertek];
        if (Elofordul[ertek] == ertek)
        {
            ++valasz;
        }
    }
}

void Kivesz(const int ertek)
{
    if (ertek < 100001)
    {
        if (Elofordul[ertek] == ertek)
        {
            --valasz;
        }
        --Elofordul[ertek];
        if (Elofordul[ertek] == ertek)
        {
            ++valasz;
        }
    }
}

vector <Kerdes> kerdesek;
Kerdes aktualis;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin >> N >> M;
    gyokN = (int) ceil(sqrt(N));

    for (int i=0;i<N;i++)
    {
        cin >> A[i];
    }
    for (int i=0;i<M;i++)
    {
        cin >> aktualis.tol >> aktualis.ig;
        --aktualis.tol; --aktualis.ig;
        aktualis.sorszam = i;
        kerdesek.push_back(aktualis);
    }

    sort(kerdesek.begin(), kerdesek.end(), Kerdes());

    valasz = 0;
    int bal = 0;
    int jobb = -1;
    for (int i=0;i<M;i++)
    {
        while (bal > kerdesek[i].tol)
        {
            bal--;
            Hozzaad(A[bal]);
        }
        while (jobb < kerdesek[i].ig)
        {
            jobb++;
            Hozzaad(A[jobb]);
        }
        while (bal < kerdesek[i].tol)
        {
            Kivesz(A[bal]);
            bal++;
        }
        while (jobb > kerdesek[i].ig)
        {
            Kivesz(A[jobb]);
            jobb--;
        }
        Eredmeny[kerdesek[i].sorszam] = valasz;
    }

    for (int i=0;i<M;i++)
    {
        cout << Eredmeny[i] << endl;
    }
    return 0;
}
