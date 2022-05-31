#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

bool isPrime(int n) {
  if (n == 0 || n == 1 || n == 4) return false;
  for (int x = 2; x < n / 2; x++) {
    if (n % x == 0) return false;
  }
  return true;
}

int main(int argc, char const *argv[])
{
    int n = 50000, sum = 0;
    bool IsPrime = false;

    //Secuencial
    auto start = chrono::high_resolution_clock::now();
    for (int i = n; i > 0; i--)
    {
        IsPrime = isPrime(i);
        if(IsPrime) sum += i; 
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Suma = " << sum << endl;
    cout << "Duración: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;

    //Paralelo
    

    return 0;
}
