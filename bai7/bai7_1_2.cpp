// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  // freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int &x : v)
    cin >> x;
  set<int> seen;
  vector<int> new_v;
  for (int x : v) {
    if (seen.find(x) == seen.end()) {
      seen.insert(x);
      new_v.push_back(x);
    }
  }
  for (int x : new_v)
    cout << x << "\n";
}
