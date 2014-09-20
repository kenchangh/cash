#include <iostream>
using namespace std;


int *start_ptr = new int[5000];

int make_hash(string key) {
  int hash = 0;
  for (char &c: key) {
    int ascii = c;
    ascii -= 31; // removes weird symbols
    hash += ascii;
  }
  cout << hash << endl;
  return hash;
}

void set(string key, int value) {
  int hash = make_hash(key);
  *(start_ptr + hash) = value;
  return;
}

int get(string key) {
  int hash = make_hash(key);
  return *(start_ptr + hash);
}

void remove(string key) {
  int hash = make_hash(key);
  *(start_ptr + hash) = 0;
  return;
}

int main() {
  set("yo", 50);
  cout << get("y") << endl;
  delete[] start_ptr;
  return 0;
}
