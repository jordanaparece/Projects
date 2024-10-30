#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {

    vector<int> v; // vector of primes
    int start = 2; // essentially a start number, which is the smallest prime number 

    int n;
    while (cin >> n) {  // standard input
        if (n > start) { // checks to see if the curent is larger than 2
            for (int i = start + 1; i <= n; i++) {
				// iterates through integers, from one + the current max
				// adds number to the vector if it is prime
                bool isPrime = true; // number is prime, testing otherwise
                for (size_t j = 0; j < v.size(); j++) {
					// traverse through the vector of primes
                    int prime = v[j];
					// assigns the element j of the prime vector to the variable prime
                    if (prime > sqrt(i)) {
                        break;
                    }
                    if (i % prime == 0) {
                        isPrime = false;
                        break;
                    }
					// if the number is divisble by a prime, it is not prime
                }
                if (isPrime) {
                    v.push_back(i);
					// if prime is found, add it to the vector using push_back(i)
                }
            }
            start = n; 
			// used to update the largest prime
        }

        if (find(v.begin(), v.end(), n) != v.end()) {
            cout << "prime" << endl;
        }
		// checks if the iterator is not equal to the end of the vector
		// if it is not, then it is prime
        else {
            cout << "not prime" << endl;
        }
    }

    return 0;
}


