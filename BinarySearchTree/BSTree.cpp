#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */

int BSTree::Depth(const string &key) const {

  BSTNode* currentNode = sentinel->right; // current node is the root of the tree
  int currentDepth = 0; // set the current depth counter to 0

  while (currentNode != sentinel) { // traverse the tree until the sentinel is found
    if (key == currentNode->key) {
      return currentDepth; // return the depth if the key is found
    }
    if (key < currentNode->key) {
      currentNode = currentNode->left; // point to the left side if current is less
    }
    else {
      currentNode = currentNode->right; // point to right otherwise
    }
    currentDepth++;
  }
  return -1;
}
           
int BSTree::Height() const {
  int height = recursive_find_height(sentinel->right);
  // calculates the height starting at the right
  return height;
}

vector <string> BSTree::Ordered_Keys() const {
  // declare vector to store keys
	vector<string> result;
	make_key_vector(sentinel->right, result); // makes the vector
	return result;
}
    
BSTree::BSTree(const BSTree &t) {
  sentinel = new BSTNode;
  sentinel->left = sentinel->right = sentinel->parent = sentinel;
  // initializes the sentinel node
  sentinel->key = "---SENTINEL---";
  sentinel->val = NULL;
  size = 0;

  if (!t.Empty()) { // if tree is not empty
	  vector <string> keys = t.Ordered_Keys();
	  vector <void *> values = t.Ordered_Vals();
	  sentinel->right = make_balanced_tree(keys, values, 0, keys.size());
    // makes the new tree
	  size = keys.size();
  }
}

BSTree& BSTree::operator= (const BSTree &t) {
	if (this != &t) {
		Clear(); // clears the current tree

    // ordered keys from the tree
		vector <string> keys = t.Ordered_Keys();
		vector <void *> values = t.Ordered_Vals();
    // making new tree and balacning it using the keys and values
		sentinel->right = make_balanced_tree(keys, values, 0, keys.size());
    // size of the tree is equal to the number of keys
		size = keys.size();
	}
	return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const {
  if (n == sentinel) {
    return 0; // base case
  }
  int leftHeight = recursive_find_height(n->left); // functions to find the height of left and right
  int rightHeight = recursive_find_height(n->right);

  return (leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const {
  if (n == sentinel) { // base case
    return;
  }
  make_key_vector(n->left, v); // recursive left
  v.push_back(n->key); // add nodes using push_back in vector
  make_key_vector(n->right, v); // recursive right
}
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, const vector<void *> &vals, size_t first_index, size_t num_indices) const {	
  if (num_indices <= 0) {
    return sentinel;
  }
  size_t middle = first_index + (num_indices >> 1); // Using bitwise shift for division by 2
  BSTNode *node = new BSTNode(); // new node
  node->key = sorted_keys[middle];
  node->val = vals[middle];

  int leftSize = middle - first_index;

  node->left = make_balanced_tree(sorted_keys, vals, first_index, leftSize); // left side
  node->right = make_balanced_tree(sorted_keys, vals, middle + 1, (num_indices - leftSize - 1)); // right side

  if (node->left != sentinel) {
    node->left->parent = node; // set parent of left child
  }
  if (node->right != sentinel) {
    node->right->parent = node; // set parent of right child
  }
  return node;
}
int BSTree::recursive_find_height(const BSTNode *n) const {
  if (n == sentinel) {
    return 0;
  }
  int leftHeight = recursive_find_height(n->left);
  int rightHeight = recursive_find_height(n->right);

  return (leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);
}
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const {
	if (n == sentinel) {
		return;
	}
	make_key_vector(n->left, v);
	v.push_back(n->key);
	make_key_vector(n->right, v);
}

