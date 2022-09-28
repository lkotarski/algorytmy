#include <iostream>
#include <cmath> 

struct lamp
{
	double x; 
	double y;
};

using namespace std;
bool operator==(lamp a, lamp b);
lamp znajdz_najnizszy(lamp tab[], int ilosc);
int nastepny_indeks(int indeks, lamp tab[], lamp granica[], int ile_w_otoczce, int ilosc);
bool w_srodku(lamp a, lamp b, lamp sprawdzany);

int bud_otoczka(lamp tab[], lamp hull[], int ilosc);
bool zegar(lamp a, lamp b, lamp c);

int main()
{
	int ile_d; 
	int ile_m; 
	int a, b; 
	cin >> ile_d;
	if (ile_d < 3) { ile_d = 3; } 
	lamp* duze = new lamp[ile_d];
	for (a = 0; a < ile_d; a++)
	{
		cin >> duze[a].x;
		cin >> duze[a].y;
	}
	
	cin >> ile_m;
	lamp* male = new lamp[ile_m];
	for (a = 0; a < ile_m; a++)
	{
		cin >> male[a].x;

		cin >> male[a].y;
	}
	lamp najnizszy = znajdz_najnizszy(duze, ile_d);
	for (a = 0; a < ile_d; a++)
	{
		duze[a].x -= najnizszy.x;
		duze[a].y -= najnizszy.y;
	}
	for (a = 0; a < ile_m; a++)
	{
		male[a].x -= najnizszy.x;
		male[a].y -= najnizszy.y;
	}
	lamp* otoczka = new lamp[ile_d];
	otoczka[0].x = 0;
	otoczka[0].y = 0;
	int i = 1;
	int nr_nastepnego = nastepny_indeks(0, duze, otoczka, i, ile_d);
	bool juz_wpisany = false;
	otoczka[1] = duze[nr_nastepnego];
	i++;
	int ile_elementow_otoczki = 1; 
	ile_elementow_otoczki = bud_otoczka(duze, otoczka, ile_d);
	bool* srodkowe = new bool[ile_m]; 
	for (a = 0; a < ile_m; a++)
	{
		srodkowe[a] = true; 
	}
	for (a = 0; a < ile_elementow_otoczki - 1; a++)
	{
		for (b = 0; b < ile_m; b++)
		{
			if (!w_srodku(otoczka[a], otoczka[a + 1], male[b]))
			{
				if (srodkowe[b]) { srodkowe[b] = false; } 
			}
		}
	}
	for (b = 0; b < ile_m; b++)
	{
		if (!w_srodku(otoczka[ile_elementow_otoczki - 1], otoczka[0], male[b]))
		{
			if (srodkowe[b]) { srodkowe[b] = false; }
		}
	}
	int ile_wewnatrz = 0;
	for (a = 0; a < ile_m; a++)
	{
		if (srodkowe[a]) { ile_wewnatrz++; }
	}
	cout << ile_wewnatrz << std::endl;
	delete[] duze;
	delete[] male;
	delete[] otoczka;
	delete[] srodkowe;
	return 0;
}
bool operator==(lamp a, lamp b)
{
	if ((a.x == b.x) && (a.y == b.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
lamp znajdz_najnizszy(lamp tab[], int ilosc)
{
	lamp najnizszy = tab[0];
	int a;
	for (a = 1; a < ilosc; a++)
	{
		if (tab[a].y < najnizszy.y)
		{
			najnizszy = tab[a];
		}
	}
	for (a = 0; a < ilosc; a++)
	{
		if ((tab[a].y == najnizszy.y) && (tab[a].x < najnizszy.x))
		{
			najnizszy = tab[a];
		}
	}
	return najnizszy;
}
int nastepny_indeks(int indeks, lamp tab[], lamp granica[], int ile_w_otoczce, int ilosc)
{
	lamp tenteraz = tab[indeks];
	int a;
	int jegoindeks;
	double roznica_x, roznica_y;
	double kat, kat_poprzedniego;
	double najwiekszy_kat;
	double liczbapi = 2 * asin(1); 
	if (ile_w_otoczce > 1)
	{
		double jego_y = granica[ile_w_otoczce - 1].y;
		double jego_x = granica[ile_w_otoczce - 1].x;
		kat_poprzedniego = atan(jego_y / jego_x);
	}
	else
	{
		kat_poprzedniego = (double)0;
	}
	jegoindeks = 0;
	najwiekszy_kat = 0;
	for (a = 0; a < ilosc; a++)
	{
		roznica_x = tenteraz.x - tab[a].x;
		roznica_y = tenteraz.y - tab[a].y;
		kat = atan((double)(-1) * roznica_y / roznica_x); 
		kat += kat_poprzedniego;
		while (kat >= 2 * liczbapi)
		{
			kat -= 2 * liczbapi;
		}
		if (kat > najwiekszy_kat)
		{
			jegoindeks = a;
			najwiekszy_kat = kat;
		}
	}
	return jegoindeks; 
}
bool w_srodku(lamp a, lamp b, lamp sprawdzany)
{
	lamp wektorAB;
	wektorAB.x = b.x - a.x;
	wektorAB.y = b.y - a.y;
	lamp wektorSPR;
	wektorSPR.x = sprawdzany.x - a.x;
	wektorSPR.y = sprawdzany.y - a.y;
	long long iloczyn;
	iloczyn = (long long)(wektorAB.x * wektorSPR.y) - (long long)(wektorSPR.x * wektorAB.y);
	if (iloczyn < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
int bud_otoczka(lamp tab[], lamp hull[], int ilosc)
{
	int ile_w_otoczce = 1;
	int a, indeks = 0, xyz;
	for (a = 0; a < ilosc; a++)
	{
		if (tab[a] == hull[0])
		{
			indeks = a;
			break;
		}
	}
	xyz = (indeks + 1) % ilosc; 
	for (a = 0; a < ilosc; a++)
	{
		if (zegar(tab[indeks], tab[a], tab[xyz]))
		{
			xyz = a;
		}
	}
	indeks = xyz;
	do {
		hull[ile_w_otoczce] = tab[indeks];
		ile_w_otoczce++;
		xyz = (indeks + 1) % ilosc; 
		for (a = 0; a < ilosc; a++)
		{
			if (zegar(tab[indeks], tab[a], tab[xyz]))
			{
				xyz = a;
			}
		}
		indeks = xyz;
	} while (!(tab[indeks] == hull[0]));
	return ile_w_otoczce;
}

bool zegar(lamp a, lamp b, lamp c)
{
	long long iloczyn_wektorowy = 0;
	iloczyn_wektorowy = (long long)(b.y - a.y) * (long long)(c.x - b.x) - (long long)(b.x - a.x) * (long long)(c.y - b.y);
	if (iloczyn_wektorowy < 0) { return true; }
	else { return false; }
}