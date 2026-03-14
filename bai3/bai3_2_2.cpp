#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main() {
  int a, b;
  cin >> a >> b;
  swap(&a, &b);
  cout << a << " " << b << "\n";
}
