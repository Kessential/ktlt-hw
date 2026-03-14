#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

int gcd(int a, int b) {
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int lcm(int a, int b) { return a / gcd(a, b) * b; }

int main() {
  int a, b;
  cin >> a >> b;
  cout << "gcd(a, b) = " << gcd(a, b) << "\n"
       << "lcm(a, b) = " << lcm(a, b) << "\n";
}
