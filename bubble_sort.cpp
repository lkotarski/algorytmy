#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstddef>

using namespace std;

int sortowanie_bombelkowe(int tab[], int n)
{
    int ile_op=0;
int p;
int i;
int pmin = 0; int pmax = n - 1;
  do
  {
    p = -1;
    for(i = pmin; i < pmax; i++){
         ile_op++;
      if(tab[i] > tab[i+1])
      {
        swap(tab[i], tab[i+1]);
        if(p < 0) pmin = i;
        p = i;

      }
    }

    if(pmin) pmin--;
    pmax = p;
  } while(p >= 0);
  return ile_op;
}

int sortowanie_przez_wstawianie(int* tab, int n)
{

    int k, temp;
    long int ile_op=0;
    for (int i = 0; i < (n - 1); i++) {
            ile_op++;
        if (tab[i + 1] < tab[i]) {
            k = i;
            while (k >= 0 && tab[i + 1] < tab[k]) {
                k--;
                ile_op++;

            }

            if (k == i - 1) {
                swap(tab[i], tab[i + 1]);

            }
            else {
                temp = tab[i + 1];

                for (int l = i + 1; l > k + 1; l--) {
                    tab[l] = tab[l - 1];

                }

                tab[k + 1] = temp;
            }
        }

    }
    return ile_op;
}

int main()
{
    srand(time(NULL));
    int n;
    cout <<"Podaj ilosc liczb ";
    cin >> n;
    int* tab = new int[n];
    for (int i = 0; i < n; i++) {
        tab[i] = rand() % 100 + 1;
    }
    int* tab1 = new int[n];
    int ile_opbombel, ile_opwstawianie;
    std::copy(tab, tab + n, tab1); //kopia danych wejsciowych do drugiego sortowania
cout <<"Wylosowane liczby: "<<endl;
    for (int i = 0; i < n; i++) {
        cout << tab1[i] << " ";
    }
    cout<<endl;
    cout<<endl;
    ile_opbombel = sortowanie_bombelkowe(tab, n);
    cout << "sortowanie_bombelkowe ";
    for (int i = 0; i < n; i++) {
        cout << tab[i] << " ";
    }

    cout<<endl;
    cout<<endl;

    cout << "sortowanie_przez_wstawianie ";
    ile_opwstawianie = sortowanie_przez_wstawianie(tab1, n);

    for (int i = 0; i < n; i++) {
        cout <<tab1[i] << " ";
    }

    delete[] tab;
    delete[] tab1;
    cout << endl;
    cout << endl;

    cout <<"Suma operacji porownan dla sortowania bombelkowego: "<< ile_opbombel << endl;
    cout << "Suma operacji porownan dla sortowania przez wstawianie: "<<ile_opwstawianie << endl;

    return 0;
}
