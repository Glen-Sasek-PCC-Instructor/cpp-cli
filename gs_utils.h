#ifndef GS_UTILS
#define GS_UTILS

#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

string underline(string s) { 
  return "\e[4m" + s + "\e[0m"; 
}

string cursor_up(int n) {
  return "\e[" + to_string(n) + "A"; 
}

const string erase_line = "\e[2K"; 

void eatline(istream& is){ \
  is.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

bool contains(vector<int> v, int n) {
  return find(v.begin(), v.end(), n) != v.end();
}

#endif
