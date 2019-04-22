#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct IntArray {
  int size;
  int capacity;
  int *contents;
};

IntArray readIntArray() {
    IntArray ans;
    ans.size = 0;
    ans.capacity = 5;
    ans.contents = new int[ans.capacity];
    int n;
    string s;
    while (cin >> s) {
        if (s[0] > '9' || s[0] < '0') {
            cin.ignore();
            break;
        } else {
            stringstream st;
            st << s;
            st >> n;
            ans.contents[ans.size] = n;
            ans.size++;
            if (ans.size == ans.capacity) {
                int b[ans.capacity];
                for (int i = 0; i < ans.size; ++i)
                    b[i] = ans.contents[i];
                delete [] ans.contents;
                ans.capacity *= 2;
                ans.contents = new int[ans.capacity];
                for (int i = 0; i < ans.size; ++i)
                    ans.contents[i] = b[i];
            }
        }
    }
    return ans;
}

void addToIntArray(IntArray& ia) {
    int n;
    string s;
    while (cin >> s) {
        if (s[0] > '9' || s[0] < '0') {
            cin.ignore();
            break;
        } else {
            stringstream st;
            st << s;
            st >> n;
            ia.contents[ia.size] = n;
            ia.size++;
            if (ia.size == ia.capacity) {
                int b[ia.capacity];
                for (int i = 0; i < ia.size; ++i)
                    b[i] = ia.contents[i];
                delete [] ia.contents;
                ia.capacity *= 2;
                ia.contents = new int[ia.capacity];
                for (int i = 0; i < ia.size; ++i)
                    ia.contents[i] = b[i];
            }
        }
    }
}

void printIntArray(const IntArray& ia) {
    for (int i = 0; i < ia.size; ++i) 
        cout << ia.contents[i] << " ";
    cout << endl;
}


// Do not change this function!

int main() {  // Test harness for IntArray functions.
  bool done = false;
  IntArray a[4];
  a[0].contents = a[1].contents = a[2].contents = a[3].contents = 0;

  while(!done) {
    char c;
    char which;

    // Note:  prompt prints to stderr, so it should not occur in .out files
    cerr << "Command?" << endl;  // Valid commands:  ra, rb, rc, rd,
                                 //                  +a, +b, +c, +d,
                                 //                  pa, pb, pc, pd, q
    cin >> c;  // Reads r, +, p, or q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
        cin >> which;  // Reads a, b, c, or d
        delete [] a[which-'a'].contents;
        a[which-'a'].contents = 0;
        a[which-'a'] = readIntArray();
        break;
      case '+':
        cin >> which;  // Reads a, b, c, or d
        addToIntArray(a[which-'a']);
        break;
      case 'p':
        cin >> which;  // Reads a, b, c, or d
        printIntArray(a[which-'a']);
        cout << "Capacity: " << a[which-'a'].capacity << endl;
        break;
      case 'q':
        done = true;
    }
  }

  for (int i = 0; i < 4; ++i) delete [] a[i].contents;
}
