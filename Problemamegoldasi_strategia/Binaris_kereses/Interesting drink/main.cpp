#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q, be, opt;
vector <int> X;
int M[100000];
int ki[100000];

void Beolvas()
{
	cin >> n;
	X.reserve(n);
	for (int i = 0; i < n; i++)
	{
		cin >> be;
		X.push_back(be);
	}
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		cin >> M[i];
	}
}

/// Napi költségvetés megkeresése
int Binkeres(int elem)
{
	int a = 0;
	int b = n;
	int s;
	opt = -1;
	while (a < b)
	{
	    s = (b + a) / 2;
		if (X[s] <= elem)
		{
		    opt = s;
			a = s + 1;
		}
		else
		{
			b = s;
		}
	}
	return opt + 1;
}

void Kiir()
{
	for (int i = 0; i < q; i++)
	{
		cout << ki[i] << endl;
	}
}

int main()
{
	Beolvas();

	/// Nyugodtan használjuk az algorithm header rendezését (O(n*lgn))
	sort(X.begin(), X.end());

	for (int i = 0; i < q; i++)
	{
		ki[i] = Binkeres(M[i]);
	}

	Kiir();
	return 0;
}
