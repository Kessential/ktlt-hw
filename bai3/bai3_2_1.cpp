#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int *pa = &a, *pb = &b;
  cout << "a + b = " << *pa + *pb << "\n";
}
