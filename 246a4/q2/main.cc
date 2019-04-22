#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "a4q2.h"

using namespace std;

// You will need to make changes to this file
int main () {
  string s;
  std::vector<Expression *> v;
  Expression *e;

  // Read and construct expression object
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (ss >> n) {
      Expression *p = new Int(n);
      v.push_back(p);
    }
    else if (s == "NEG" || s == "ABS") {
      Expression *p;
      if (s == "NEG") {
        p = new Unary(true, v.back());
        v.pop_back();
      } else {
        p = new Unary(false, v.back());
        v.pop_back();
      }
      v.push_back(p);
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
      Expression *r = v.back();
      v.pop_back();
      Expression *l = v.back();
      v.pop_back();
      Expression *p = new Binary(s[0], l, r);
      v.push_back(p);
    }
    else if (s == "done") {
      e = v.back();
      v.pop_back();
      if (v.empty() == false) cout << "FAIL #1" << endl;
      e->prettyprint();
      cout << endl;
      break;
    }
    else {
      Expression *p = new Var(s);
      v.push_back(p);
    }
  }

  // Command interpreter
  while (cin >> s) {
    if (s == "eval") {
      int n;
      if (e->evaluate(&n)) 
        cout << n << endl;
    }
    else if (s == "set") {
      int n;
      string str;
      cin >> str >> n;
      if (e->set(str, n)) { }
        else cout << "FAIL #2" << endl;
    }
    else if (s == "unset") {
      string str;
      cin >> str;
      if (e->unset(str)) { }
        else cout << "FAIL #3" << endl;
    }
    else if (s == "print") {
      e->prettyprint();
      cout << endl;
    }
    else if (s == "copy") {
      Expression *cp = e->copy();
      cp->prettyprint();
      cout << endl;
      cp->set("x", 1);
      cp->prettyprint();
      cout << endl;
      int n;
      if (cp->evaluate(&n)) 
        cout << n << endl;
      delete cp;
    }
  }
  delete e;
}
