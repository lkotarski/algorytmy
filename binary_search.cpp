#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

using namespace std;

void wyszukiwanie_lin(double *T, int n, int szukana);
void wyszukiwanie_bin(double *T, int n, int szukana);
void sortowanie(double *T, int n);

int main()
{
int n=0, x=0;
cout<<"Ile liczb mam wygenerowac?"<<endl;
cin>>n;
cout<<"Szukana liczba calkowita"<<endl;
cin>>x;
double* Tn = new double [n];
double* Pn = new double [n];
srand (time(NULL));

for(int i=0; i<n; i++){
Tn[i]= rand( ) % 100 + 1 ;
Pn[i]=Tn[i];
}

wyszukiwanie_lin(Tn, n, x);
sortowanie(Pn, n);
wyszukiwanie_bin(Pn, n, x);



delete [] Tn;
delete [] Pn;
    return 0;
}

void wyszukiwanie_lin(double *T, int n, int szukana){
int z;
int licznik=0;
for(int i=0; i<=n; i++){
    z=i;
    licznik++;
    if(T[i]==szukana){
        break;
    }
    else{
        z=-1;
    }
}

if(z==-1){
    cout<<"brak poszukiwanego elementu"<<endl;
}
else{
    cout<<"poszukiwany element kryje sie pod T["<<z<<"] = "<<szukana<<endl;
}

cout<<"liczba operacji (liniowy) = "<<licznik<<endl<<endl;
}

void wyszukiwanie_bin(double *T, int n, int szukana){
int p = n, l = 1, s;
int z=0;
int licznik=0;
while(l<=p)
{
    ceil(s=(l+p)/2);
    licznik++;
    if(szukana == T[s])
    {
        cout<<"poszukiwany element kryje sie pod T["<<s<<"] = "<<T[s]<<endl;
        z=1;
        break;
    }
    else if(T[s]<szukana)
    {
        l = s + 1;
    }
    else if(T[s]>szukana)
    {
        p = s - 1;
    }

}
if(z==0){cout<<"brak poszukiwanego elementu"<<endl;}
cout<<"liczba operacji (binarny) = "<<licznik<<endl;



}

void sortowanie(double *T, int n){
int x, j;
long long li1=0;

for(int i=1; i<n; i++){
    x=T[i];
    j=i-1;
    li1++;
    while(j>=0 && T[j]>x){
        T[j+1] = T[j];
        li1++;
        j--;
    }
    T[j+1] = x;
}
}

