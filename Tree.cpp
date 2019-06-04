#include "Tree.h"
#include <iostream>

//finds max of two ints
int maximum(int x, int y){
  if(x < y){
    return y;
  }
  else{
    return x;
  }
}

//finds min of two ints
int minimum(int x, int y){
  if(x < y){
    return x;
  }
  else{
    return y;
  }
}

//get height of tree rooted at node
int getHeight(Node* node){
  //if node doesnt exist
  if(node == NULL){
    return 0;
  }
  else{
    return (node->height);
  }
}

//create a new node with desired key 
//node will be a leaf
Node* newNode(int key){
  Node* node = new Node;
  node -> key = key;
  node -> leftchild = NULL;
  node -> rightchild = NULL;
  node -> height = 1;
  return node;
}

//get height difference for left and right subtrees of node
int balanceFactor(Node* node){
  if(node == NULL){
    return 0;
  }
  else{
    int leftHeight = height(node -> leftchild);
    int rightHeight = height(node -> rightchild);
    int difference = leftHeight - rightHeight;
    return difference;
  }
}
