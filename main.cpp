#include <iostream>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <omp.h>

using namespace std;

bool isPrime(int n) {
  if (n == 0 || n == 1 || n == 4) return false;
  for (int x = 2; x < n / 2; x++) {
    if (n % x == 0) return false;
  }
  return true;
}

int test(int first, int last)
{
  int sumat = 0;

  #pragma omp for schedule(static) ordered
  for(int i=first; i < last; i++){
    //Do something here
    int aux = 0;
    for(int j=1; j<=i; j++)
    if(i%j==0 && i%1==0)
    aux++;
    if(aux==2)
    {
      #pragma omp ordered
      // cout<<i<<endl;
      sumat=sumat+i;
    }
  }

  // cout << "Sum2 = "<<sumat<<endl;
  return sumat;
}

int main(int argc, char const *argv[])
{
    int n = 5000, sum = 0, sum2 = 0;
    bool IsPrime = false;
    float T1 = 0, TP = 0;

    //Secuencial
    auto start = chrono::high_resolution_clock::now();
    for (int i=1; i<n; i++)
    {
        int aux = 0;
        for(int j=1; j<=i; j++)
        if(i%j==0 && i%1==0)
        aux++;
        if(aux==2)
        {
          // cout<<i<<endl;
          sum=sum+i;
        }
        // IsPrime = isPrime(i);
        // if(IsPrime) sum += i; 
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Secuencial" << endl;
    cout << "Suma = " << sum << endl;
    T1 = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Duracion: " << T1 << " microseconds\n" << endl;

    //Paralelo
    auto start2 = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
      sum2 = test(1,n);
    }
    auto end2 = chrono::high_resolution_clock::now();

    cout << "Paralelo" << endl;
    cout << "Suma = " << sum2 << endl;
    TP = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "Duracion: " << TP << " microseconds\n" << endl;

    cout << "Speedup: " << T1/TP << endl;

    return 0;
}
