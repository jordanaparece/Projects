#include <iostream>

struct Node {
	int data;
	Node *next;
};
class List {
	private:
		Node *head;
		Node* newNode(const int &);
	public:
		List();
		~List();
		bool empty();
		void print();
		int nodeCount();
		void appendNode(const int &);
		List addList(const List &l2);
		void reverse();
};
