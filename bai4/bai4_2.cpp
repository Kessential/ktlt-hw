#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int a[n];
  for (int &x : a)
    cin >> x;
  for (int *it = a + n - 1; it >= a; it--) {
    cout << *it << " ";
  }
  cout << "\n";
}
