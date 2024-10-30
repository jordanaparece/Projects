#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    vector<int> primes;
    int max_prime = 2; // initialized to 2 because 2 is the smallest prime number
    double totalPrimes = 0.0;

    int n;
    while (cin >> n) { // reading in standard input
        if (n >= primes.size()) {
            primes.resize(n + 1); // resize if necessary
            // https://cplusplus.com/reference/vector/vector/resize/#google_vignette
        }
        if (n > max_prime) {
            for (int i = max_prime + 1; i <= n; i++) {
                bool isPrime = true;
                for (int j = 2; j <= sqrt(i); j++) {
                    if (i % j == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) {
                    primes[i] = 1;
                    totalPrimes++;
                }
                else {
                    primes[i] = 0;
                }
            }
            max_prime = n;
        }
        if (primes[n] == 1) {
            cout << "prime" << endl;
        } 
        else {
            cout << "not prime" << endl;
        }
    }

    double loadFactor = (totalPrimes) / 2000000;
    cout << "Load factor: " << loadFactor;
    return 0;
}

