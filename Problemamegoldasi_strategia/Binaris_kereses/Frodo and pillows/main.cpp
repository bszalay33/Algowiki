#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n, m, k, rk;
long long frodo, ki, opt;
long long osszeg;

/**
 * Frodo egyik oldal�n sz�ks�ges p�rn�k sz�m�t visszaad� f�ggv�ny.
 *
 * @param k Frodo egyik oldal�n l�v� �gyak sz�ma.
 * @param parnak A jelenleg Frodonak adott p�rn�k sz�ma.
 */
void ujOsszeg(long long k, long long parnak)
{
    if (k > parnak - 1)
	{
	    osszeg += (parnak - 1) * (parnak - 2) / 2 + k;
	}
	else
    {
        osszeg += (2 * parnak - k - 1) * k / 2;
    }
}

/// Bin�ris keres�s.
long long Binkeres()
{
	long long a = 1;
	long long b = m + 1;
	opt = 1;
	while (a < b)
	{
	    frodo = (b + a) / 2;
	    osszeg = frodo;
        ujOsszeg(k, frodo);
        ujOsszeg(rk, frodo);
		if (osszeg <= m)
		{
		    opt = frodo;
			a = frodo + 1;
		}
		else
		{
			b = frodo;
		}
	}
	return opt;
}

int main()
{
	cin >> n >> m >> k;

	rk = n - k; // Frodot�l jobbra l�v� �gyak
	--k;        // Frodot�l balra l�v� �gyak

	ki = Binkeres();

	cout << ki << endl;
	return 0;
}
