#include "CardDeck.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

CardDeck::CardDeck(int n) {
	size = (n > 0 ? n : 10); //validate array size (n)
	deck = new int[size]; // create space for pointer-based array
	for (int i = 0; i < size; i++) {
		deck[i] = i; // set array element to 0
	}
}
CardDeck::~CardDeck() {
	delete[] deck; // release pointer-based array space
}
CardDeck::CardDeck(const CardDeck &right) { 
	size = right.size;
	deck = new int[size]; // create space for pointer-based array
	for (int i = 0; i < size; ++i) {
		deck[i] = right.deck[i];
	}
}
CardDeck &CardDeck::operator=(const CardDeck &right) { // Dr. Emrich's note
	if (&right != this) { // avoid self-assignment
		if (size != right.size) {
			delete[] deck; // release space
			size = right.size; // resize the object
			deck = new int[size]; // declaring space for the copy array
		}
		for (int i = 0; i < size; i++) {
			deck[i] = right.deck[i];
		}
	}
	return *this;
}
int CardDeck::getSize() const {
	return size; //return the number of elements in the deck
}
void CardDeck::shuffle() { // lab help video

	srand(0);
	random_shuffle(&deck[0], &deck[size]); // TA help - Maggie

}
void CardDeck::printDeck() const {
	for (int i = 0; i < size; i++) {
		cout << deck[i] << " ";
	}
	cout << endl;
}
