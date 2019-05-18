#include <iostream>

using namespace std;

/// Ennél a konstansnál minden költség kisebb lesz (maxR * maxL).
const long long maxosszeg = 10000000000;

long long R, L, B;
long long X[100000];
long long Balra[100001]; // Prefix összegek tömbje
long long minAr, opt;

/// Beolvasás és prefix összegek elõállítása.
void Beolvas()
{
	cin >> R >> L >> B;
	cin >> X[0];
	Balra[0] = 0;
	for (size_t i = 1; i < R; i++)
	{
		cin >> X[i];
		Balra[i] = Balra[i-1] + X[i-1];
	}
	Balra[R] = Balra[R-1] + X[R-1];
}

/**
 * Teljes költség kiszámítására szolgáló függvény.
 *
 * A függvény két megadott rizsföld közé, a sorszámok különbségének
 * felénél elhelyezett hub alapján számol. Ehhez a korábban
 * kiszámolt prefix összegeket hívja segítségül.
 *
 * @param tol A bal szélsõ rizsföld indexe.
 * @param ig A jobb szélsõ rizsföld indexe.
 *
 * @return A szállítás költsége.
 */
long long Ar(long long tol, long long ig)
{
    long long hub = (tol + ig) / 2;
    long long ret = Balra[ig+1] - Balra[hub+1] - (Balra[hub+1] - Balra[tol]);
    if ((ig - tol) % 2 == 0 )
    {
        ret += X[hub];
    }
    return ret;
}

/// Bináris keresés
int Binkeres()
{
	int a = 2;
	int b = R + 1;
	int s;
	opt = 1;
	while (a < b)
	{
	    s = (b + a) / 2;
        minAr = maxosszeg;
	    for (int i=0;i<(R-s+1);i++)
	    {
	        minAr = min(minAr, Ar(i, i+s-1));
	    }
		if (minAr <= B)
		{
		    opt = s;
			a = s + 1;
		}
		else
		{
			b = s;
		}
	}
	return opt;
}

int main()
{
    Beolvas();

    cout << Binkeres() << endl;
    return 0;
}
