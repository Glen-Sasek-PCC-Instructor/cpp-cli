#include <cstdlib> /* srand, rand */
#include <ctime>   /* time */
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "gs_utils.h"

using namespace std;

enum { LEFT_LIGHT, EVEN, LEFT_HEAVY };

class Selections {
public:
  vector<int> left;
  vector<int> right;
};

class Secret {
public:
  int secret_number = rand() % 12 + 1;
  bool secret_is_lighter = rand() % 2 == 1;

  int compare(Selections selections){
    if(selections.left.size() != selections.right.size()) {
      return selections.left.size() < selections.right.size() ? LEFT_LIGHT : LEFT_HEAVY;
    }
    
    if(contains(selections.left, secret_number)) {
      return secret_is_lighter ? LEFT_LIGHT : LEFT_HEAVY;
    } else if(contains(selections.right, secret_number)) {
      return secret_is_lighter ? LEFT_HEAVY : LEFT_LIGHT;
    } else {
      return EVEN;
    }    
  } 
};

void display_menu();

bool play();

Selections get_selections();

string to_display_string(vector<int> v);

void display_even(Selections selections);

void display_left_light(Selections selections);

void display_left_heavy(Selections selections);

void display_result(Selections selections, int result);

bool enter_solution(Secret secret);

void give_up(Secret secret);

int main() {
  srand(time(NULL));
  
  while(play()){
    char c = 0;
    cout << "Play Again [Y/y:N/n] ";
    cin >> c;
    eatline(cin);
    if('n' == tolower(c)) {
      break;
    } else {
      system("clear");
    }
  }
  return 0;
}


bool play() {
  Secret secret;
  display_menu();

  while (true) {
    cout << "? ";
    char c = '\0';
    cin.clear();
    cin >> c;
    if (isdigit(c)) {
      cin.putback(c);
      Selections selections = get_selections();
      int result = secret.compare(selections);
      display_result(selections, result);
      continue;
    }

    switch (tolower(c)) {
      case 'm':
        display_menu();
        break;
      case 's':
        if(enter_solution(secret)){
          return true;
        } 
        break;
      case 'g':
        give_up(secret);
        return true;
      case 'q':
        return false;
      default:
        cout << "OPTION NOT RECOGNIZED;(\n";
        eatline(cin);
        display_menu();
    }
  }
}

Selections get_selections() {
  Selections selections;
  istringstream sin;
  string s;
  getline(cin,s,'-');
  sin.str(s);
  int n = 0;
  while(sin && sin >> n){
    selections.left.push_back(n);
    n = 0;
  }
  sin.clear();
  getline(cin,s);
  sin.str(s);
  while(sin && sin >> n){
    selections.right.push_back(n);
    n = 0;
  }
   
  return selections;
}

void give_up(Secret secret) {
  cout << "GIVE UP :(\n";
  cout << secret.secret_number << " is " << (secret.secret_is_lighter ? "Lighter" : "Heavier") << '\n';
}

bool enter_solution(Secret secret) {
  bool win = false;
  cout << "NUMBER: ";
  int n = 0;
  cin >> n ;
  cout << "LIGHTER or HEAVIER [L/l:H/h] ";
  char c;
  cin >> c;
 eatline(cin);
  bool guess_lighter = false;
  switch (tolower(c)) {
    case 'l':
      guess_lighter = true;
      break;
    case 'h':
      guess_lighter = false;
      break;
    default:
      cout << "OPTION NOT RECOGNIZED\n";
      eatline(cin);
      display_menu();
      return false;
  }
  win = n == secret.secret_number && guess_lighter == secret.secret_is_lighter;
  if(win){
    cout << "CORRECT\n";
  } else {
    cout << "WRONG\n";
  }
  return win;
}

void display_menu() {
  cout << "*****************************************\n";
  cout << "* 1  2  3  4  5  6  7  8  9  10  11  12 *\n";
  cout << "*****************************************\n\n";
    
  cout << "There are 12 balls, one is either\n\n";
  cout <<           "         " << underline("LIGHTER") << '\n';
  cout <<           "     OR /\n";
  cout << underline("HEAVIER") << "/\n\n";
  cout << "than the others.\n";
  cout << "You have a balance scale.\n";
  cout << "Use space separated numbers with a '-'\n";
  cout << "character between to compare.\n";
  cout << "Example: 1 2 3 - 4 5 6 will compare\n"; 
  cout << "1,2,3 with 4,5,6.\n\n";
  cout << "Find the odd ball and determine if it is heavier or lighter.\n\n";
  cout << "[M/m] Display this menu.\n";
  cout << "[S/s] Enter Solution.\n";
  cout << "[G/g] Give Up (See Solution).\n";
  cout << "[Q/q] Quit\n";
  cout << "GOOD LUCK!\n";
}

void display_result(Selections selections, int result) {
  cout << cursor_up(1) << erase_line;
  if(LEFT_LIGHT == result) {
    display_left_light(selections);
  } else if(LEFT_HEAVY == result) {
    display_left_heavy(selections);
  } else {
    display_even(selections);
  }
  cout << endl;
}

string to_display_string(vector<int> v) {
  string s = "";
  for(int n : v) {
    s += to_string(n) + ' ';
  }
  return s.substr(0, s.size()-1);
}

void display_even(Selections selections) {
  string l = to_display_string(selections.left);
  string r = to_display_string(selections.right);
  cout << underline(l);
  cout << " == ";
  cout << underline(r) << endl;
}

void display_left_light(Selections selections) {
  string l = to_display_string(selections.left);
  string r = to_display_string(selections.right);
  cout << underline(l) << endl;
  cout << setw(l.size() + 1) << '\\' << endl; 
  cout << setw(l.size() + 2) << '\\' <<  underline(r) << endl; 
}

void display_left_heavy(Selections selections) {
  string l = to_display_string(selections.left);
  string r = underline(to_display_string(selections.right));
  cout << setw(l.size() + 3 + r.size()) << r << endl;
  cout << setw(l.size() + 2) << '/' << endl; 
  cout << underline(l) << '/' << endl; 
}

