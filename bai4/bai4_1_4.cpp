#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  map<int, int> mp;
  for (int &x : v) {
    cin >> x;
    mp[x]++;
  }
  pair<int, int> result{-1, -1e9};
  for (auto &[key, val] : mp) {
    if (val >= result.second) {
      result = {key, val};
    }
  }
  cout << result.first << " " << result.second << "\n";
}
