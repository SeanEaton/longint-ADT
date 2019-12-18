#include <iostream>
#include "longint.h"

using namespace std;

int main( ) {
  cout << "Testing constuctors: " << endl;
  LongInt aa;
  cout << "aa: " << aa << endl;
  LongInt a("000092bu3");
  cout << "a:" << a << endl;
  LongInt b("-w021");
  cout << "b:" << b << endl;
  LongInt c;
  cout << "Enter a value for c: ";
  cin >> c;
  cout << "c:" << c << endl;
  LongInt d(c);
  cout << "copy of c (d) via copy constructor: " << d << endl << endl;

  cout << "Testing assignment operator + additional operator>> test on filled longint: " << endl;
  LongInt e = a;
  cout << "copy of a (e) via assignment operator: " << e << endl;
  e = b;
  cout << "copy of b (e) via assignment operator: " << e << endl;
  cout << "Enter a value to overwrite e with: ";
  cin >> e;
  cout << "e:" << e << endl << endl;

  cout << "Testing comparison operators with a & c: " << endl;
  cout << a << " < " << c << " = " << (a < c) << endl;
  cout << a << " <= " << c << " = " << (a <= c) << endl;
  cout << a << " == " << c << " = " << (a == c) << endl;
  cout << a << " != " << c << " = " << (a != c) << endl;
  cout << a << " > " << c << " = " << (a > c) << endl;
  cout << a << " >= " << c << " = " << (a >= c) << endl << endl;;

  cout << "Testing arithmetic operators: " << endl;
  LongInt j;
  cout << "Enter a value for left operand (j): ";
  cin >> j;
  cout << "j:" << j << endl;
  LongInt k;
  cout << "Enter a value for right operand (k): ";
  cin >> k;
  cout << "k:" << k << endl;
  cout << j << " + " << k << " = " << (j + k) << endl;
  cout << j << " - " << k << " = " << (j - k) << endl << endl;
  return 0; 
}