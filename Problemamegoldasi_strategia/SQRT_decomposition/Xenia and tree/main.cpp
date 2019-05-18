#include <iostream>
#include <vector>
#include <queue>
#include <tgmath.h>

using namespace std;

int N, lgN, gyokM, MperGyok, M, a, b, ujDarab, ujTav, akt;
int gyokerTav[100000], minPiros[100000];
/// Ritka mátrix az i. csúcs 2^j szülõjének tárolására
int szulo[100000][17];
vector <int> elek[100000];
vector <int> ujPiros;
queue <int> bejarSor;

struct Kerdes
{
    int tipus, csucs;
};

Kerdes aktualis;

/// Mélységi bejárás a szülõk és a gyökértõl való távolság megállapítására
void melyBejar(int akt, int elozo)
{
    szulo[akt][0] = elozo;

    for (int cs : elek[akt])
    {
        if (cs != elozo)
        {
            gyokerTav[cs] = gyokerTav[akt] + 1;
            melyBejar(cs, akt);
        }
    }
}

/// Szélességi bejárás a piros csúcstól való legkisebb távolságok frissítésére
void szelBejar()
{
    while (!bejarSor.empty())
    {
        akt = bejarSor.front();
        bejarSor.pop();
        for (int cs : elek[akt])
        {
            if (minPiros[akt] + 1 < minPiros[cs])
            {
                minPiros[cs] = minPiros[akt] + 1;
                bejarSor.push(cs);
            }
        }
    }
}

/// A legmélyebben lévõ közös õst visszaadó függvény
int kozosOs(int a, int b)
{
    if (gyokerTav[a] < gyokerTav[b])
    {
        swap(a, b);
    }

    for (int i=lgN-1;i>=0;i--)
    {
        if (gyokerTav[szulo[a][i]] >= gyokerTav[b])
        {
            a = szulo[a][i];
        }
    }

    if (a == b)
    {
        return a;
    }

    for (int i=lgN-1;i>=0;i--)
    {
        if (szulo[a][i] != szulo[b][i])
        {
            a = szulo[a][i];
            b = szulo[b][i];
        }
    }

    return szulo[a][0];
}

/// Két csúcs távolságát kiszámító függvény
int tav(int a, int b)
{
    return gyokerTav[a] + gyokerTav[b] - 2 * gyokerTav[kozosOs(a, b)];
}

/// Legközelebbi piros csúcs távolságának kiszámítása az aktuális blokkban
/// pirossá váló csúcsok közül
int ujMin(int a)
{
    ujTav = minPiros[a];
    for (int i=0;i<ujDarab;i++)
    {
        ujTav = min(ujTav, tav(a, ujPiros[i]));
    }
    return ujTav;
}

vector <Kerdes> kerdesek;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin >> N >> M;
    lgN = (int) log2(N) + 1;
    gyokM = (int) sqrt(M);
    MperGyok = M / gyokM;

    for (int i=0;i<N-1;i++)
    {
        cin >> a >> b;
        --a; --b;
        elek[a].push_back(b);
        elek[b].push_back(a);
    }
    for (int i=0;i<M;i++)
    {
        cin >> aktualis.tipus >> aktualis.csucs;
        --aktualis.csucs;
        kerdesek.push_back(aktualis);
    }

    gyokerTav[0] = 0;
    melyBejar(0, 0);

    /// Ritka mátrix feltöltése
    for (int i=1;i<lgN;i++)
    {
        for (int j=0;j<N;j++)
        {
            minPiros[j] = gyokerTav[j];
            if (szulo[j][i-1] != 0)
            {
                szulo[j][i] = szulo[szulo[j][i-1]][i-1];
            }
        }
    }

    /// Az egyes szakaszok kéréseinek feldolgozása
    for (int i=0;i<gyokM;i++)
    {
        ujDarab = 0;
        ujPiros.clear();
        for (int j=0;j<MperGyok;j++)
        {
            akt = kerdesek[i*gyokM + j].csucs;
            if (kerdesek[i*gyokM + j].tipus == 2)
            {
                cout << ujMin(akt) << endl;
            }
            else
            {
                minPiros[akt] = 0;
                ++ujDarab;
                ujPiros.push_back(akt);
            }
        }

        /// Minden csúcsra frissítjük a legközelebbi piros távolságát
        /// a mostani szakaszban pirossá változott csúcsokból indulva.
        for (int i : ujPiros)
        {
            bejarSor.push(i);
        }
        szelBejar();
    }

    /// Utolsó, kevesebb elembõl álló szakasz (ha van)
    for (int j=0;j<M-gyokM*MperGyok;j++)
    {
        akt = kerdesek[gyokM*gyokM + j].csucs;
        if (kerdesek[gyokM*gyokM + j].tipus == 2)
        {
            cout << ujMin(akt) << endl;
        }
        else
        {
            minPiros[akt] = 0;
            ++ujDarab;
            ujPiros.push_back(akt);
        }
    }

    return 0;
}
