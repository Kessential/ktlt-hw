#include <iostream>
#include <vector>

using namespace std;

bool binSearch(const vector<int> &v, int value) {
  int l = 0, r = v.size() - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (v[m] == value)
      return true;
    else if (v[m] < value) {
      l = m + 1;
    } else
      r = m - 1;
  }
  return false;
}

int main() {
  int n, value;
  cin >> n >> value;
  vector<int> v(n);
  for (int &x : v) {
    cin >> x;
  }
  cout << (binSearch(v, value) ? "YES\n" : "NO\n");
}
