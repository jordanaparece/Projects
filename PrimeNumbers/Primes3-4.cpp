#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {

    vector<int> primes; 
    int max_prime = 2; 

    int n;
    while (cin >> n) { 
        if (n > max_prime) { 
            for (int i = max_prime + 1; i <= n; i++) {
                bool isPrime = true;
                for (size_t j = 0; j < primes.size(); j++) {
                    int prime = primes[j];
                    if (prime > sqrt(i)) {
                        break;
                    }
                    if (i % prime == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) {
                    primes.push_back(i); 
                }
            }
            max_prime = n; 
        }

        if (binary_search(primes.begin(), primes.end(), n)) {
			// binary search is used for sorted array of elements
			// has two iterators and a value, n, to search for
            cout << "prime" << endl;
        } else {
            cout << "not prime" << endl;
        }
    }

    return 0;
}


