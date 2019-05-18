#include <iostream>

using namespace std;

/// Ennél a konstansnál minden költség kisebb lesz (maxR * maxL).
const long long maxosszeg = 10000000000;

long long R, L, B;
long long X[100000];
long long Balra[100001]; // Prefix összegek tömbje
long long minAr;

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

/// Two pointers iteráció
int Twopts()
{
	int a = 0;
	int b = 0;
	int s = 0;
    int hossz;
	while (b < R)
	{
	    hossz = b - a + 1;
		if (Ar(a, b) <= B)
		{
		    s = max(s, hossz);
			++b;
		}
		else
		{
			++a;
		}
	}
	return s;
}

int main()
{
    Beolvas();

    cout << Twopts() << endl;
    return 0;
}
