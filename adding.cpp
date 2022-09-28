#include <iostream>
using namespace std;



int reverse(int n)
{
    int x = 0, y;
    while (n != 0) {
        y = n % 10;
        x = x * 10 + y;
        n /= 10;
        
    }
    return x;
}
int main() {

    unsigned  long int num1, num2, sum;
    cin >> num1 >> num2;
    cerr << reverse(num1) << " + " << reverse(num2) << endl;
    sum = reverse(num1) + reverse(num2);
    cout << reverse(sum) << endl;
    return 0;

    return 0;
}