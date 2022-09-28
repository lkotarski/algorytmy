#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <fstream>


const int r = 256;   
const int q = 9551;  

using namespace std;

struct testCase {
	string fileName;
	string pattern;
};

string wczytaj_plik(string fileName) {
	fstream plik;
	plik.open(fileName);
	string linia;
	getline(plik, linia);
	return linia;
}

vector<testCase> entry() {
	vector<testCase> V;
	
	int count;
	cin >> count;
	for (int i = 0; i < count; i++) {
		testCase tc = testCase();
		cin >> tc.fileName;
		cin >> tc.pattern;
		V.push_back(tc);
	}
	return V;

}


int power_modulo_fast(int a, int b, int m)
{
	int i;
	int result = 1;
	long int x = a % m;

	for (i = 1; i <= b; i <<= 1)
	{
		x %= m;
		if ((b & i) != 0)
		{
			result *= x;
			result %= m;
		}
		x *= x;
	}

	return result % m;
}

char wzorzec[1000000];
char tekst[10000000];



int main()
{
	vector<testCase> v = entry();

	for (const auto& value : v) {
		string tekst = wczytaj_plik(value.fileName);
		string wzorzec = value.pattern;
		



		int m, n, i, j, h1, h2, rm;

		

		n = tekst.length();
		m = wzorzec.length();
		h2 = 0;
		h1 = 0;
		


		
		for (i = 0; i < m; i++)
		{
			h2 = ((h2 * r) + tekst[i]);
			h2 %= q;
		}
		
		for (i = 0; i < m; i++)
		{
			h1 = ((h1 * r) + wzorzec[i]);
			h1 %= q;
		}

		rm = power_modulo_fast(r, m - 1, q);
		i = 0;


		while (i < n - m)
		{
			j = 0;
			if (h1 == h2) while ((j < m) && (wzorzec[j] == tekst[i + j])) j++;
			if (j == m) cout << i << " ";
			h2 = ((h2 - tekst[i] * rm) * r + tekst[i + m]);
			h2 %= q;
			if (h2 < 0) h2 += q;
			i++;
		}
		j = 0;
		if (h1 == h2) while ((j < m) && (wzorzec[j] == tekst[i + j])) j++;
		if (j == m) cout << i;
		cout << endl;

	}

	return 0;
}

