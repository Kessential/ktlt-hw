// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (n <= 0)
    return 1;
  vector<int> v(n);
  for (int &x : v)
    cin >> x;
  double avg = 0;
  for (int i = 0; i < v.size() - 1; i++) {
    avg += abs(v[i] - v[i + 1]);
  }
  if (n == 1) cout << 0 << "\n";
  else cout << avg / (n - 1) << "\n";
}
