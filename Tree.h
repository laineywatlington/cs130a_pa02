#ifndef TREE_H
#define TREE_H

using namespace std;

//create node class, this is what we will insert into tree
class Node{
  public:
  int key;
  int height;
  Node* leftchild;
  Node* rightchild;
};

//now define functions here
int maximum(int x, int y);
int minimum(int x, int y);
int getHeight(Node* node);
void preOrder(Node* root);
//building tree and tree functions
Node* newNode(int key);
Node* rotateRight(Node* node);
Node* rotateLeft(Node* node);
int balanceFactor(Node* node);
Node* insert(Node* node, int key, int* r, int* v);
int lookup(Node* root, int search, int* v);
//printing/parsing
/*void printTree(Node* root, int* c);
void printLL(Node* root, int* ub, int* lb, vector<pair<int, int>> *store);
void printRR
void printLR
void printRL*/
#endif
