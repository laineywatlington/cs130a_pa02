#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>
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

//prints a Pre-Order traversal of tree
void preOrder(Node* root){
  if(root != NULL){
    //visit root
    cout << root -> key << " ";
    //traverse left subtree
    preOrder(root -> leftchild);
    //traverse right subtree
    preOrder(root -> rightchild);
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

//rotations
Node* rotateRight(Node* c){
  //subtree rooted at c
  Node* b = c -> leftchild;
  Node* a = b -> rightchild;
  //rotate
  b -> rightchild = c;
  c -> leftchild = a;
  //heights
  c -> height = maximum(getHeight(c -> leftchild), getHeight(c -> rightchild)) + 1;
  b -> height = maximum(getHeight(b -> leftchild), getHeight(b -> rightchild)) + 1;
  //returns root of subtree
  return b;
}

Node* rotateLeft(Node* c){
  //subtree rooted at c
  Node* b = c -> rightchild;
  Node* a = b -> leftchild;
  //rotate
  b -> leftchild = c;
  c -> rightchild = a;
  //heights
  c -> height = maximum(getHeight(c -> leftchild), getHeight(c -> rightchild)) + 1;
  b -> height = maximum(getHeight(b -> leftchild), getHeight(b -> rightchild)) + 1;
  //returns root of subtree
  return b;
}

//get height difference for left and right subtrees of node
//we will use this to check if AVL height property is violated
int balanceFactor(Node* node){
  if(node == NULL){
    return 0;
  }
  else{
    int leftHeight = getHeight(node -> leftchild);
    int rightHeight = getHeight(node -> rightchild);
    int difference = leftHeight - rightHeight;
    return difference;
  }
}

//function to insert node into tree (recursively)
Node* insert(Node* node, int key, int* r, int* v){
  //if the node doesnt exist, create a new node
  if(node == NULL){
    return (newNode(key));
    *v += 1;
  }
  //if key to be inserted is less than nodes key
  //we recursively try to insert it at nodes left child
  if(key < node -> key){
    *v += 1;
    node -> leftchild = insert(node -> leftchild, key, r, v);
  }
  //similarly for the right child if key to be inserted is larger than nodes key
  else if(key > node -> key){
    *v += 1;
    node -> rightchild = insert(node -> rightchild, key, r, v);
  }
  //cant have two nodes with same key in tree
  else{
    *v += 1;
    return node;
  }
  //heights
  node -> height = 1 + maximum(getHeight(node -> leftchild), getHeight(node -> rightchild));
  //CHECK IF AVL PROPERTY IS VIOLATED
  int balanceCheck = balanceFactor(node);
  //if balance property violated, we fix with either a ll, lr, rr, rl rotation
  //single rotations first
  //left left
  if(balanceCheck > 1 && key < node -> leftchild -> key){
    *r = *r + 1;
    return rotateRight(node);
  }
  //right right
  if(balanceCheck < -1 && key > node -> rightchild -> key){
    *r = *r + 1;
    return rotateLeft(node);
  }
  //now double rotations
  //left right
  if(balanceCheck > 1 && key > node -> leftchild -> key){
    *r = *r + 2;
    node -> leftchild = rotateLeft(node -> leftchild);
    return rotateRight(node);
  }
  //right left
  if(balanceCheck < -1 && key < node -> rightchild -> key){
    *r = *r + 2;
    node -> rightchild = rotateRight(node -> rightchild);
    return rotateLeft(node);
  }
  return node; //pointer to node
}

int lookup(Node* root, int search, int *v){
  if(root != NULL){
    if(search == root -> key){
      *v = *v + 1;
      return search;
    }
    else if(search < root -> key){
      *v = *v + 1;
      return lookup(root -> leftchild, search, v);
    }
    else if(search > root -> key){
      *v = *v + 1;
      return lookup(root -> rightchild, search, v);
    }
    else{
      return -1;
    }
  }
  else{
    return -1;
  }
}

void printTree(Node* root, int* x){
    if(root != NULL){
      if (root -> leftchild != NULL || root -> rightchild != NULL){
        cout << string(*x*2, ' ' );
        cout << "Node(" << root -> key << ", h=" << root -> height - 1 << "):" << endl;
        int y = *x + 1;
        printTree(root -> leftchild, &y);
        printTree(root -> rightchild, &y);
      }
      if (root -> leftchild == NULL && root -> rightchild == NULL){
        cout << string(*x*2, ' ' );
        cout << "Leaf(" << root -> key << ")" << endl;
      }
    }
    else{
      cout << string(*x*2, ' ' );
      cout << "Null" << endl;
    }
}

void pll(Node* root, int *ubound, int *lbound, vector<pair <int,int>> *mem){
    if(root != NULL){
        int before = balanceFactor(root);
        if(before == -1){
          *lbound = root -> key + 1;
        }
        if(before == 1 && root -> leftchild != NULL && root -> leftchild -> leftchild == NULL){
          *ubound = root -> leftchild -> key - 1;
          mem -> push_back(make_pair(*lbound, *ubound));
            *ubound = 2147483647; //largest in that can be made w 32 bits
            *lbound = -2147483647; //smallest int that can be made w 32 bits
        }
        pll(root -> leftchild, ubound, lbound, mem);
        pll(root -> rightchild, ubound, lbound, mem);
    }
}

void prr(Node* root, int* ubound, int* lbound, vector<pair<int,int>> *mem){
  if (root != NULL){
    int before = balanceFactor(root);
    if(before == 1){
      *ubound = root -> key - 1;
    }
    if(before == -1 && root -> rightchild != NULL && root -> rightchild -> rightchild == NULL){
      *lbound = root -> rightchild -> key + 1;
      mem -> push_back(make_pair(*lbound, *ubound));
      *ubound = 2147483647;
      *lbound = -2147483647;
    }
    prr(root -> leftchild, ubound, lbound, mem);
    prr(root -> rightchild, ubound, lbound, mem);
  }
}

void plr(Node* root, int* ubound, int* lbound, vector<pair<int,int>> *mem){
  if (root != NULL){
    int before = balanceFactor(root);
    if(before == 1 && root -> leftchild != NULL && root -> leftchild -> rightchild == NULL){
      *ubound = root -> key - 1;
      *lbound = root -> leftchild -> key + 1;
      mem -> push_back(make_pair(*lbound, *ubound));
      *ubound = 2147483647;
      *lbound = -2147483647;
    }
    plr(root -> leftchild, ubound, lbound, mem);
    plr(root -> rightchild, ubound, lbound, mem);
  }
}

void prl(Node* root, int* ubound, int* lbound, vector<pair<int,int>> *mem){
  if (root != NULL){
    int before = balanceFactor(root);
    if(before == -1 && root -> rightchild != NULL && root -> rightchild -> leftchild == NULL){
      *lbound = root -> key + 1;
      *ubound = root -> rightchild -> key - 1;
      mem -> push_back(make_pair(*lbound, *ubound));
      *ubound = 2147483647;
      *lbound = -2147483647;
    }
    prl(root -> leftchild, ubound, lbound, mem);
    prl(root -> rightchild, ubound, lbound, mem);
  }
}
