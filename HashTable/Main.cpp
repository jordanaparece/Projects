#include "hash_202.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

int XOR(string key) {
    int j = 0; // initializing the value to 0
    size_t size = 7; // size is equal to 7
    for (size_t i = 0; i < key.length(); i += size) { // traverse the length of the string
        string valueAsLine = key.substr(i, size);
        int value;
        istringstream(valueAsLine) >> hex >> value; // convert to a integer
        j ^= value; // XOR operation
    }
    return j;
}
int Last7(const string &key) {
    int i = key.length() - 7; // arithmetic that calculates the starting index for the string
    if (i < 0) { // if the starting index is a negative value, reset it to 0
        i = 0;
    }
    istringstream iss(key.substr(i)); // extract substring from the start of the index
    int j;
    iss >> hex >> j; // converting the integer value to hex value
    return j;
}
string Hash_202::Set_Up(size_t table_size, const string &fxn, const string &collision) {
    Nkeys = 0;

    if (!Keys.empty() || !Vals.empty()) {
        return "Hash table already set up";
    }
    if (table_size == 0) {
        return "Bad table size";
    }
    if (fxn == "Last7") {
        Fxn = 'L';
    } else if (fxn == "XOR") {
        Fxn = 'X';
    } else {
        return "Bad hash function";
    }
    if (collision == "Linear") {
        Coll = 'L';
    } else if (collision == "Double") {
        Coll = 'D';
    } else {
        return "Bad collision resolution strategy";
    }

    Keys.resize(table_size);
    Vals.resize(table_size);
    return "";
}
string Hash_202::Add(const string &key, const string &val) {

    size_t hashValue = 0;
    size_t start = 0;
    size_t hash = 0;
    size_t currentVal = 0;

    if (Keys.size() == 0) {
        return "Hash table not set up";
    }
    if (key.size() == 0) {
        return "Empty key";
    }
    for (size_t i = 0; i < key.size(); i++) { // https://cplusplus.com/reference/cctype/isxdigit/
        if (!isxdigit(key[i])) {
            return "Bad key (not all hex digits)";
        }
    }
    if (val == "") {
        return "Empty val";
    }
    if (Nkeys == Keys.size()) {
        return "Hash table full";
    }
    if (Fxn == 'L') { // checks to see if the function is Last7
        hashValue = Last7(key); // if the above is true, this calculates the hash using Last7
        if (Coll == 'L') { // collision resolution: linear probing
            start = (hashValue) % Keys.size(); // this calculates the starting position
            do { // linear probing continually traverse through the table, searching for an open slot, hence the do/while
                currentVal = (hashValue + hash) % Keys.size(); // current position given the hash
                if (Keys[currentVal].size() == 0) { // checks to see if the slot at the current value is empty (0)
                    Keys[currentVal] = key; // inserts the key and value if it is empty
                    Vals[currentVal] = val;
                    Nkeys++; // increment by 1 (linearly)
                    return "";
                }
                else {
                    //if (key == Keys[currentVal]) { // checks to see if the key is already inserted at the desire position
					if(Find(key) != ""){
                        return "Key already in the table";
                    }
                    hash++;
                }

            } while (start != currentVal || hash <= 1);
            // continues unless it is back at the beginning or the second probe
        }
        else {
            // double hash function
            size_t h2 = 0;
            size_t currentVal = 0;
            size_t temp = 0;

            h2 = XOR(key); // calculates 2nd hash function
            if (h2 % Keys.size() == 0) { // checks to see if h2 is within the table
                h2 = 1;
            }
            else {
                h2 = h2 % Keys.size();
            }
            temp = (hashValue + hash * h2) % Keys.size(); // initial position arithmetic
            if (Keys[temp].size() == 0) { // if the slot is empty, insert pair
                Keys[temp] = key;
                Vals[temp] = val;
                Nkeys++;
                return "";
            }
            else {
                //if (key == Keys[currentVal]) {
				if(Find(key) != ""){
                    return "Key already in the table";
                }
                hash++;
            }

            do { // same logic as previous loop
                currentVal = (hashValue + hash * h2) % Keys.size();
                if (Keys[currentVal].size() == 0) {
                    Keys[currentVal] = key;
                    Vals[currentVal] = val;
                    Nkeys++;
                    return "";
                }
                else {
                    //if (key == Keys[currentVal]) {
					if(Find(key) != ""){
                        return "Key already in the table";
                    }
                    hash++;
                }
            } while (temp != currentVal);

			return "Cannot insert key";
        }
    }
    else {
        hashValue = XOR(key); // XOR function
        if (Coll == 'L') {
            start = (hashValue) % Keys.size(); // starting position
            do {
                currentVal = (hashValue + hash) % Keys.size(); // arithmetic to find current position
                if (Keys[currentVal].size() == 0) {
                    Keys[currentVal] = key; // insert pair if the slot is empty
                    Vals[currentVal] = val;
                    Nkeys++;
                    return "";
                }
                else {
                    //if (key == Keys[currentVal]) {
					if(Find(key) != ""){
                        return "Key already in the table";
                    }
                    hash++;
                }

            } while (start != currentVal || hash <= 1); // continue until the function traverse back to the beginning or it is at the second probe
        }
        else {
            size_t hash2 = 0;
            size_t currentVal = 0;
            size_t temp = 0;
            size_t h = 0;
            hash = XOR(key);
            hash2 = Last7(key);
            if (hash2 % Keys.size() == 0) { // checking bounds
                hash2 = 1;
            }
            else {
                hash2 = hash2 % Keys.size();
            }
            temp = (hash + (h * hash2)) % Keys.size();
            // initial position of the pair
            if (Keys[temp].size() == 0) {
                Keys[temp] = key; // insert pair if slot is empty
                Vals[temp] = val;
                Nkeys++;
                return "";
            }
            else {
                // error check messages
                //if (key == Keys[currentVal]) {
				if(Find(key) != ""){
                    return "Key already in the table";
                }
                if (h == Keys.size()) {
                    return "Hash table full";
                }
                /*if (h == Keys.size()) { //this wont ever get hit!!!
                    return "Cannot insert key";
                }*/
                h++;
            }
            do {
                // case: probe until slot is found or at initial position
                currentVal = (hash + (h * hash2)) % Keys.size();
                if (Keys[currentVal].size() == 0) {
                    Keys[currentVal] = key; // same logic as previous cases
                    Vals[currentVal] = val;
                    Nkeys++;
                    return "";
                }
                else {
                    if (key == Keys[currentVal]) {
                        return "Key already in the table";
                    }
                    if (h == Keys.size()) {
                        return "Hash table full";
                    }
                    h++;
                }
            } while (temp != currentVal); // continues until it traverse back to the beginning position
			
			return "Cannot insert key";
		}
    }
    return "";
}
string Hash_202::Find(const string &key) {
    size_t hashValue = 0;
    size_t h = 0;
    Nprobes = 0;
    if (Fxn == 'L') {
        hashValue = Last7(key); //Calling Last7 function
        if (Coll == 'L') { // collision resolution
            size_t start = (hashValue) % Keys.size(); // calculates the starting position
            size_t currentVal = start;
            do {
                if (key == Keys[currentVal]) {
                    return Vals[currentVal]; // return the key if the key is found
                }
                else {
                    Nprobes++; // increment probes
                    h++;
                }
                currentVal = (start + h) % Keys.size();
            } while (start != currentVal && h < Keys.size());
        }
        else {
            size_t hash2 = XOR(key);
            size_t start = (hashValue + h * hash2) % Keys.size(); // calculates the current position in the table
            size_t currentVal = start;
            do {
                if (key == Keys[currentVal]) {
                    return Vals[currentVal]; // return key if it is found
                }
                else {
                    Nprobes++;
                    h++;
                }
                currentVal = (start + h * hash2) % Keys.size();
            } while (start != currentVal && h < Keys.size());
        }
    }
    else {
        hashValue = XOR(key); // XOR function
        if (Coll == 'L') { // collision resolution
            size_t start = (hashValue) % Keys.size(); // starting position
            size_t currentVal = start;
            do {
                if (key == Keys[currentVal]) {
                    return Vals[currentVal]; // returns key if found
                }
                else {
                    Nprobes++;
                    h++;
                }
                currentVal = (start + h) % Keys.size(); // finds the current position by adding h to the start
            } while (start != currentVal && h < Keys.size());
            // probes until it is back at the start
        }
        else {
            size_t hash2 = Last7(key); // Last7 function
            if (hash2 % Keys.size() == 0) {
                hash2 = 1;
            }
            else {
                hash2 = hash2 % Keys.size();
            }
            size_t start = (hashValue + h * hash2) % Keys.size(); // new start position
            size_t currentVal = start;
            do {
                if (key == Keys[currentVal]) {
                    return Vals[currentVal];
                }
                else {
                    Nprobes++;
                    h++;
                }
                currentVal = (start + h * hash2) % Keys.size();
            } while (start != currentVal && h < Keys.size());
            // same logic as above
        }
    }
    return "";
}
void Hash_202::Print() const {
    for (size_t i = 0; i < Keys.size(); i++) {
        if (Keys[i] != "") {
            // if the key at index i is not empty, the following is printed
            cout << setw(5) << i << " " << Keys[i].c_str() << " " << Vals[i].c_str() << endl;
        }
    }
}

size_t Hash_202::Total_Probes() {
    size_t nprobes = 0;

    if (Keys.empty()) { // if the table is empty, return 0
        return 0;
    }
    for (size_t i=0; i < Keys.size(); i++) { // traverse through the table
        if (Keys[i].size() != 0) {
            Find(Keys[i]); // Find the key if the slot in the table is not empty
            nprobes += Nprobes; // running counter of probes
        }
    }
    return nprobes;
}
