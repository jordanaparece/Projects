#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    int i;
    //https://academichelp.net/coding/cpp/how-to-square-a-number.html
    for (i = 2; pow(i, i) <= n; i++) { // only checks to the square root
        if (n % i == 0) { // n is divisble by any number other than 1 and itself
            return false;
        }
    }
    return true; // n is otherwise prime
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // program terminates if there are not 2 arguments in the command line
        return 1;
    }

    int max = stoi(argv[1]); // converting the value entered by the user to integer, which will be the max number
    int count = 0; // integer variable to keep track of 20 integers per line, per the write up

    for (int i = 2; i <= max; i++) {
        if (isPrime(i)) { // succeeding code runs if true
            cout << i << ", "; // print the integer and then increment
            count++; // increments the amount of numbers printed
            if (count % 20 == 0) { // arithmetic for 20 per line, per the write-up
                cout << endl;
            } 
        }
    }
    return 0;
}

