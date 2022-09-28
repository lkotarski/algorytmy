#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class edge;


void droga(int d, vector<edge>& k);


void z_wagi(vector<edge>& k);


bool porownanie(edge k1, edge k2);


int z_miasto(int x, int* miasta);


void kruskalmst(int m, vector<edge>& k, vector<edge>& mst);


void dfs(bool visited[], vector<vector<int>>& sasiedzi, vector<int>& trasa, int s, int e);


void sasiad(vector<edge>& mst, int m, vector<vector<int>>& sasiedzi);


void fill(bool visited[], int m);


int liczba_pasazerow(vector<edge>& mst, vector<int>& trasa);


int liczba_przejazdow(int t, int p);

int main()
{
    vector <edge> k;
    vector <edge> mst;

    int m, d, f = -1, h = -1, p, t;
    cin >> m;
    cin >> d;
    vector<vector<int>> sasiedzi(m + 1);

    droga(d, k);
    z_wagi(k);
    sort(k.begin(), k.end(), porownanie);
    kruskalmst(m, k, mst);
    z_wagi(mst);
    sasiad(mst, m, sasiedzi);


    while (f != 0 && h != 0)
    {
        cin >> f;
        cin >> h;
        if (f == 0 && h == 0)
            break;
        cin >> t;
        vector<int> trasa;
        trasa.push_back(0);
        bool* visited = new bool[m + 1];
        fill(visited, m);
        dfs(visited, sasiedzi, trasa, f, h);

        for (size_t i = 1; i < trasa.size(); i++)
        {
            cout << trasa[i] << " ";
        }
        cout << endl;
        delete[]visited;
        trasa.clear();
    }
}

class edge
{
public:
    int g1,g2,p;
    
    edge(int nc1, int nc2, int np)
    {
        g1 = nc1;
        g2 = nc2;
        p = np;
    }
   
    void odwrocenie()
    {
        int x;
        x = this->p;
        x = -x;
        this->p = x;
    }
};


void droga(int d, vector<edge>& k)
{
    int c1, c2, p;
    for (int i = 0; i < d; i++)
    {
        cin >> c1 >> c2 >> p;
        k.push_back(edge(c1, c2, p));
    }
}

void z_wagi(vector<edge>& k)
{
    for (size_t i = 0; i < k.size(); i++)
    {
        k[i].odwrocenie();
    }
}

bool porownanie(edge k1, edge k2)
{
    return k1.p < k2.p;
}

int z_miasto(int x, int* miasta)
{
    if (miasta[x] == x)
        return x;
    return z_miasto(miasta[x], miasta);
}

void kruskalmst(int m, vector<edge>& k, vector<edge>& mst)
{
    
    int* miasta = new int[m];
    
    for (int i = 0; i < m; i++)
        miasta[i] = i;
    
    int licznik = 0;
    int i = 0;
    
    while (licznik < m - 1)
    {
        if (i == k.size())
            break;
        int miastoPoczatkowe = z_miasto(k[i].g1 - 1, miasta);
        int miastoDocelowe = z_miasto(k[i].g2 - 1, miasta);
        if (miastoDocelowe != miastoPoczatkowe)
        {
            int tym;
            if (k[i].g1 > k[i].g2)
            {
                tym = k[i].g2;
                k[i].g2 = k[i].g1;
                k[i].g1 = tym;
            }
            mst.push_back(k[i]);
            tym = k[i].g1;
            k[i].g1 = k[i].g2;
            k[i].g2 = tym;
            mst.push_back(k[i]);
            licznik++;
            miasta[miastoPoczatkowe] = miastoDocelowe;
        }
        i++;
    }
    delete[]miasta;
    k.clear();
}


void dfs(bool visited[], vector<vector<int>>& sasiedzi, vector<int>& trasa, int s, int e)
{
    visited[s] = true;
    vector<int>::iterator i;
    for (i = sasiedzi[s].begin(); i != sasiedzi[s].end(); i++)
    {
        if (!visited[*i])
        {
            if (trasa.back() == s)
            {
                trasa.pop_back();
            }
            trasa.push_back(s);
            if (*i == e)
            {
                trasa.push_back(e);
                break;
            }
            dfs(visited, sasiedzi, trasa, *i, e);
        }
    }
}

void sasiad(vector<edge>& mst, int m, vector<vector<int>>& sasiedzi)
{

    for (size_t i = 0; i < mst.size(); i++)
    {
        sasiedzi[mst[i].g1].push_back(mst[i].g2);
    }


}

int liczba_pasazerow(vector<edge>& mst, vector<int>& trasa)
{
    int p = 1000000;
    for (size_t i = 1; i < trasa.size() - 1; i++)
    {
        for (size_t j = 0; j < mst.size(); j++)
        {
            if (mst[j].g1 == trasa[i] && mst[j].g2 == trasa[i + 1])
            {
                if (p > mst[j].p)
                    p = mst[j].p;
            }
        }
    }
    return p;
}

void fill(bool visited[], int m)
{
    for (int i = 0; i <= m; i++)
    {
        visited[i] = false;
    }
}

int liczba_przejazdow(int t, int p)
{
    int suma = 0;
    while (t > 0)
    {
        t -= p;
        suma++;
    }
    return suma;
}