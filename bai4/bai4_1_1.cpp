#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool linSearch(const vector<int> &v, int value) {
  for (const int &x : v) {
    if (x == value)
      return true;
  }
  return false;
}

int main() {
  int n, value;
  cin >> n >> value;
  vector<int> v(n);
  int maxVal = -1e9, minVal = 1e9;
  for (int &x : v) {
    cin >> x;
    maxVal = max(maxVal, x);
    minVal = min(minVal, x);
  }
  cout << (linSearch(v, value) ? "YES\n" : "NO\n");
  cout << minVal << " " << maxVal << "\n";
}
