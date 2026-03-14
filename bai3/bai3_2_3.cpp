#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

int main() {
  int n;
  cin >> n;
  int a[n];
  for (int &x : a)
    cin >> x;
  long long sum = 0;
  for (int *ptr = a; ptr != a + n; ++ptr) {
    sum += *ptr;
  }
  cout << sum << "\n";
}
