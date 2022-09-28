#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <stdio.h>

using namespace std;



struct test {
	long* dane = new long[10000];
	int ilosc_danych;
};
void printArray(long arr[], int n)
{
	if (n == 1)return;
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

void heapify(long arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;


	if (l < n && arr[l] > arr[largest])
		largest = l;


	if (r < n && arr[r] > arr[largest])
		largest = r;


	if (largest != i) {
		swap(arr[i], arr[largest]);


		heapify(arr, n, largest);
	}
}


void heapSort(long arr[], int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);


	for (int i = n - 1; i > 0; i--) {

		swap(arr[0], arr[i]);


		heapify(arr, i, 0);
		printArray(arr, i);
	}
}




int main()
{
	int il_test;
	cout << "Podaj ilosc testow " << endl;
	cin >> il_test;
	test* testy = new test[il_test];
	for (int i = 0; i+1 <= il_test; i++)
	{
		cout << "Dane dla testu nr " << i << endl;
		cout << "Podaj ilosc danych";
		cin >> testy[i].ilosc_danych;
		for (int j = 0; j < testy[i].ilosc_danych; j++) {
			cout << "Podaj liczbe: ";
			cin >> testy[i].dane[j];
		}


	}

	for (int i = 0; i < il_test; i++) {
		int ilosc = testy[i].ilosc_danych;
		long *arr = new long[ilosc];
		for (int j = 0; j < ilosc; j++) {
			arr[j] = testy[i].dane[j];
		}
		printArray(arr, ilosc);
		heapSort(arr, ilosc);
		printArray(arr, ilosc);
	}


}
