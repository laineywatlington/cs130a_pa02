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

#endif
