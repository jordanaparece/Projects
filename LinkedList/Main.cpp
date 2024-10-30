#include "list.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        istringstream iss(s);
        string number1, number2;
        iss >> number1 >> number2;
        List L1, L2;

        // Reverse string to handle least significant digit first
        reverse(number1.begin(), number1.end());
        reverse(number2.begin(), number2.end());

        // Append digits in reverse order
        for (char digit : number1) {
            L1.appendNode(digit - '0');
        }
        for (char digit : number2) {
            L2.appendNode(digit - '0');
        }

        List sum = L1.addList(L2);
        sum.print(); // Should print in the correct order now
    }
    return 0;
}   
