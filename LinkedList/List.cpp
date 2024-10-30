#include "list.h"

using namespace std;

List::List() {
	head = nullptr;
}
List::~List() {
	if (!empty()) { // clobbering
		Node* p = head; // the first node
		while (p != NULL) { // if the node is not null, then retrieve the next node
			Node* next = p->next;
			delete p;
			p = next;
		}
	}
}
bool List::empty() {
	return (head == nullptr);
}
void List::print() {
	Node* p = head;
	if (!p) {
		cout << "0";
	}
	while (p != nullptr) {
		cout << p->data;
		p = p->next;
	}
	cout << endl;
}
void List::reverse() {

	// https:://youtube.com/watch?v=XgABnoJLtG4&t=594s
	
	Node* current = head; // 3 pointers, one set to the first node and the others set to null
	Node* prev = NULL;
	Node* next = NULL;
	
	while (current != NULL) { // interates over each node of the list and continues until the current node is null
		next = current->next; // stores the next node in the pointer "next"
		current->next = prev; // points to the previous node
		prev = current; // moves the pointer to the current node
		current = next; // moves the pointer to the next node
	}
	head = prev;

}
int List::nodeCount() {
	int n = 0;
	for (Node* p = head; p != nullptr; p = p->next) {
		n++;
	}
	return n;
}
void List::appendNode(const int& data) {
	Node *nn = newNode(data);
	if (empty()) { // make a new node
		head = nn;
	}
	else {
		Node* p = head;
		while (p->next != NULL) { // end of the list
			p = p->next;
		}
		p->next = nn;
	}
	nn->next = nullptr;
}
Node* List::newNode(const int& data) {
	Node* nn = new Node;
	nn->data = data; 
	nn->next = nullptr; 
	return nn;
}
List List::addList(const List& l2) {
	List result;
	Node *p1 = head, *p2 = l2.head;
	int carry = 0;
	while (p1 != NULL || p2 != NULL || carry != 0) {
		int sum = carry;
		if (p1 != NULL) {
			sum += p1->data;
			p1 = p1->next;
		}
		if (p2 != NULL) {
			sum += p2->data;
			p2 = p2->next;
		}
		carry = sum / 10;
		result.appendNode(sum % 10);
	}
	return result;
}
