#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

//first, extract all ints from input files and store in vector
vector<int> int_vector(string array){
  stringstream input;
  vector<int> vec;
  input << array;
  string temp; 
  int number; 
  while (!input.eof()){ 
    input >> temp;
    if (stringstream(temp) >> number){ 
      vec.push_back(number);
    }
    temp = "";
  }
  return vec;
}
