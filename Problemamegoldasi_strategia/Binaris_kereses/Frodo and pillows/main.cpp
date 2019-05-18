#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long n, m, k, rk;
long long frodo, ki, opt;
long long osszeg;

/**
 * Frodo egyik oldalán szükséges párnák számát visszaadó függvény.
 *
 * @param k Frodo egyik oldalán lévõ ágyak száma.
 * @param parnak A jelenleg Frodonak adott párnák száma.
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

/// Bináris keresés.
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

	rk = n - k; // Frodotól jobbra lévõ ágyak
	--k;        // Frodotól balra lévõ ágyak

	ki = Binkeres();

	cout << ki << endl;
	return 0;
}
