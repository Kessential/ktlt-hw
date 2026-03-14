#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

int main() {
  int n;
  cout << "Nhap chieu cao cua cay noel, toi thieu 3: ";
  cin >> n;
  if (n < 3) {
    cout << "Dau vao ko hop le\n";
    return 1;
  }
  n -= 2;
  for (int i = 0; i < n; i++) {
    for (int j = n - i - 1; j > 0; j--)
      cout << " ";
    for (int j = 0; j < 2 * i + 1; j++)
      cout << "x";
    cout << "\n";
  }
  for (int x : {0, 1}) {
    for (int i = 0; i < n; i++) {
      cout << (i != n - 1 ? " " : "x");
    }
    cout << "\n";
  }
}
