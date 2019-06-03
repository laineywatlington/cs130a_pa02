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
  if(node == NULL){
    return 0;
  }
  else{
    return (node->height);
  }
}
