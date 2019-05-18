#include <iostream>

using namespace std;

/// Enn�l a konstansn�l minden k�lts�g kisebb lesz (maxR * maxL).
const long long maxosszeg = 10000000000;

long long R, L, B;
long long X[100000];
long long Balra[100001]; // Prefix �sszegek t�mbje
long long minAr, opt;

/// Beolvas�s �s prefix �sszegek el��ll�t�sa.
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
 * Teljes k�lts�g kisz�m�t�s�ra szolg�l� f�ggv�ny.
 *
 * A f�ggv�ny k�t megadott rizsf�ld k�z�, a sorsz�mok k�l�nbs�g�nek
 * fel�n�l elhelyezett hub alapj�n sz�mol. Ehhez a kor�bban
 * kisz�molt prefix �sszegeket h�vja seg�ts�g�l.
 *
 * @param tol A bal sz�ls� rizsf�ld indexe.
 * @param ig A jobb sz�ls� rizsf�ld indexe.
 *
 * @return A sz�ll�t�s k�lts�ge.
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

/// Bin�ris keres�s
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
