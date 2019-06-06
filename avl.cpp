#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

//first, extract all ints from input files and store in vector
vector<int> toint(string array){
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

//clear mem
void clear(Node* root){
  if(root != NULL){
    clear(root -> leftchild);
    clear(root -> rightchild);
    delete root;
  }
}

//insert tests
Node* insertTests(Node* root, vector<int> numArray){
	int r = 0;
	int v = 0;
	int temp;
	float toAdd = numArray.size();
	float totalAdded = 0;
	for (int i = 0; i < toAdd; i++) {  
		if (lookup(root, numArray[i], &temp) != numArray[i]){
			totalAdded += 1;
		}
        root = insert(root, numArray[i], &r, &v);
    }
    cout << "Added " << totalAdded << " of " << toAdd << " nodes." << endl;
    //amortized stats
    cout << "Visited " << v << " (" << v/toAdd << ") nodes and performed " << r << " (" << r/toAdd << ") rotations.\n" << endl;
    return root;
}

//lookup tests
void lookupTests(Node* root, vector<int> find){
  int v = 0;
  vector<int> found;
  float findSize = find.size();
  for (int i = 0; i < findSize; i++){
    int exists = lookup(root, find[i], &v);
    if(find[i] == exists){
      found.push_back(exists);
    }
  }
  int foundSize = found.size();
  cout << "Found " << foundSize << " of " << findSize << " nodes: [";
  for (int i = 0; i < foundSize; i++){
    cout << found[i];
    if(i < foundSize - 1){
      cout << ", ";
    }
  }
  //no rotations performed during lookup!
  cout << "]\nVisited " << v << " (" << v/findSize << ") nodes and performed 0 (0) rotations.\n";
}

//main 
int main(int argc, char* argv[]){
	if (argc > 1){
    //read test files
		string line;
		ifstream inFile;
		inFile.open(argv[1]);
    //new empty tree to add to
    Node *root = NULL;
    //error case
		if(!inFile){
			cout<<"unable to open file";
		}
		while(getline(inFile, line)){
			if(line.length() > 6){
        string name = line.substr(0,6);
				if (name.compare("insert") == 0){
          string array = line.substr(7, line.length());
          vector<int> numArray = toint(array);
					root = insertTests(root, numArray);
				}
        if (line.compare("print tree") == 0){
          int c = 0;
          printTree(root, &c);
          cout << endl;
        }
        if (name.compare("lookup") == 0){
          string array = line.substr(7, line.length());
          vector<int> find = toint(array);
          lookupTests(root, find);
          cout << endl;
        }
        //left left check
        if (line.compare("print left-left") == 0){
          int ubound = 2147483647;
          int lbound = -2147483647;
          vector<pair<int,int>> mem;
          pll(root, &ubound, &lbound, &mem);
          sort(mem.begin(), mem.end());
          int memSize = mem.size();
          if (memSize > 0){
            cout << "The following inserts would cause a left-left rotation:" << endl;
            for (int i = 0; i < memSize; i++){
              if(mem[i].first == mem[i].second){
                cout << mem[i].first;
              }
              else{
                cout << mem[i].first << " to " << mem[i].second;
              }
              if(i < memSize - 1){
                cout << ", ";
              }
            }
            cout << endl;
          }
          else{
            cout << "No inserts would cause a left-left rotation." << endl;
          }
          cout << endl;
        }
        //right right check
        if (line.compare("print right-right") == 0){
          int ubound = 2147483647;
          int lbound = -2147483648;
          vector<pair<int,int>> mem;
          prr(root, &ubound, &lbound, &mem);
          sort(mem.begin(), mem.end());
          int memSize = mem.size();
          if (memSize > 0){
            cout << "The following inserts would cause a right-right rotation:" << endl;
            for (int i = 0; i < memSize; i++){
              if(mem[i].first == mem[i].second){
                cout << mem[i].first;
              }
              else{
                cout << mem[i].first << " to " << mem[i].second;
              }
              if(i < memSize - 1){
                cout << ", ";
              }
            }
            cout << endl;
          }
          else{
            cout << "No inserts would cause a right-right rotation." << endl;
          }
          cout << endl;
        }
        //left right check
        if (line.compare("print left-right") == 0){
          int ubound = 2147483647;
          int lbound = -2147483648;
          vector<pair<int,int>> mem;
          plr(root, &ubound, &lbound, &mem);
          sort(mem.begin(), mem.end());
          int memSize = mem.size();
          if (memSize > 0){
            cout << "The following inserts would cause a left-right rotation:" << endl;
            for (int i = 0; i < memSize; i++){
              if(mem[i].first == mem[i].second){
                cout << mem[i].first;
              }
              else{
                cout << mem[i].first << " to " << mem[i].second;
              }
              if(i < memSize - 1){
                cout << ", ";
              }
            }
            cout << endl;
          }
          else{
            cout << "No inserts would cause a left-right rotation." << endl;
          }
          cout << endl;
        } 
        //right left check
        if (line.compare("print right-left") == 0){
          int ubound = 2147483647;
          int lbound = -2147483648;
          vector<pair<int,int>> mem;
          prl(root, &ubound, &lbound, &mem);
          sort(mem.begin(), mem.end());
          int memSize = mem.size();
          if (memSize > 0){
            cout << "The following inserts would cause a right-left rotation:" << endl;
            for (int i = 0; i < memSize; i++){
              if(mem[i].first == mem[i].second){
                cout << mem[i].first;
              }
              else{
                cout << mem[i].first << " to " << mem[i].second;
              }
              if(i < memSize - 1){
                cout << ", ";
              }
            }
            cout << endl;
          }
          else{
            cout << "No inserts would cause a right-left rotation." << endl;
          }
          cout << endl;
        }
			}
		}
    clear(root);
	}
	return 0;
}
