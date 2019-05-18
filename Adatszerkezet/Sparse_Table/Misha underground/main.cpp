#include <iostream>
#include <vector>
#include <tgmath.h>

using namespace std;

int N, lgN, Q, a, b, c, akt, maxKozos;
int gyokerTav[100000];
/// Sparse table az i. csúcs 2^j szülõjének tárolására
int szulo[100000][17];
vector <int> elek[100000];

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

/// Két csúcs távolságát kiszámító függvény (ismert l.k. őssel)
int tav(int a, int b, int lko)
{
    return gyokerTav[a] + gyokerTav[b] - 2 * gyokerTav[lko];
}

/// u-ból w-be és v-ből w-be vezető utak közös csúcsainak száma
int kozosUthossz(int u, int v, int w, int lko_uv, int lko_uw, int lko_vw)
{
    return (tav(u, w, lko_uw) + tav(v, w, lko_vw) - tav(u, v, lko_uv)) / 2 + 1;
}

int main()
{
    cin >> N >> Q;
    lgN = (int) log2(N) + 1;
    for (int i=1;i<N;i++)
    {
        cin >> szulo[i][0];
        --szulo[i][0];
        elek[i].push_back(szulo[i][0]);
        elek[szulo[i][0]].push_back(i);
    }

    /// gyökértől való távolságok kiszámítása
    gyokerTav[0] = 0;
    melyBejar(0, 0);

    /// Sparse table felépítése
    for (int i=1;i<lgN;i++)
    {
        for (int j=0;j<N;j++)
        {
            if (szulo[j][i-1] != 0)
            {
                szulo[j][i] = szulo[szulo[j][i-1]][i-1];
            }
        }
    }

    int lko_ab, lko_ac, lko_bc;
    for (int i=0;i<Q;i++)
    {
        cin >> a >> b >> c;
        --a; --b; --c;
        lko_ab = kozosOs(a, b);
        lko_ac = kozosOs(a, c);
        lko_bc = kozosOs(b, c);
        maxKozos = 0;
        maxKozos = max(kozosUthossz(a, b, c, lko_ab, lko_ac, lko_bc),
                       kozosUthossz(a, c, b, lko_ac, lko_ab, lko_bc));
        maxKozos = max(maxKozos, kozosUthossz(b, c, a, lko_bc, lko_ab, lko_ac));
        cout << maxKozos << endl;
    }
    return 0;
}

/*
cin >> a >> b >> c;
        --a; --b; --c;
        if (gyokerTav[a]<gyokerTav[b])
        {
            swap(a,b);
        }
        if (gyokerTav[a]<gyokerTav[c])
        {
            swap(a,c);
        }
        if (gyokerTav[b]<gyokerTav[c])
        {
            swap(b,c);
        }
        /// gyökértől való távolság már csökkenő sorrendben
        lko_ab = kozosOs(a, b);
        if (lko_ab == b)
        {
            cout << max(gyokerTav[a] - gyokerTav[b], tav(b, c)) + 1 << endl;
        }
        else
        {
            lko_ac = kozosOs(a, c);
            if (lko_ac == lko_ab)
            {
                lko_bc = kozosOs(b, c);
                if (lko_bc == lko_ab)
                {
                    cout << gyokerTav[a] - gyokerTav[lko_ab] + 1 << endl;
                }
                else if (lko_bc == c)
                {
                    cout << tav(a, c, lko_ac) + 1 << endl;
                }
                else
                {
                    cout << tav(lko_bc, a, lko_ac) + 1 << endl;
                }
            }
            else if (lko_ac == c)
            {
                if (gyokerTav[lko_ab] < gyokerTav[lko_ac])
                {
                    cout << max(gyokerTav[a] - gyokerTav[lko_ac],
                                tav(lko_ac, b, lko_ab)) + 1 << endl;
                }
                else
                {
                    cout << max(gyokerTav[a] - gyokerTav[lko_ab],
                                gyokerTav[lko_ab] - gyokerTav[c]) + 1 << endl;
                }
            }
            else
            {
                if (gyokerTav[lko_ab] < gyokerTav[lko_ac])
                {
                    cout << max(gyokerTav[a] - gyokerTav[lko_ac],
                                tav(lko_ac, b, lko_ab)) + 1 << endl;
                }
                else
                {
                    cout << max(gyokerTav[a] - gyokerTav[lko_ab],
                                tav(lko_ab, c, lko_ac)) + 1 << endl;
                }
            }
        }
        */
