#include <cmath>
#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

bool isPrime(int n) {
  if (n < 2)
    return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0)
      return false;
  }
  return true;
}
int main() {
  int n;
  cin >> n;
  cout << (isPrime(n) ? "YES\n" : "NO\n");
}
