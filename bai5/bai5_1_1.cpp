#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void selection_sort(vector<int> &v) {
  int n = v.size();
  for (int i = 0; i < n - 1; i++) {
    int minPos = i;
    for (int j = i + 1; j < n; j++) {
      if (v[j] < v[minPos]) {
        minPos = j;
      }
    }
    swap(v[i], v[minPos]);
  }
}

void insertion_sort(vector<int> &v) {
  for (int i = 1; i < v.size(); i++) {
    int insPos = i - 1, insValue = v[i];
    while (insPos >= 0 && insValue < v[insPos]) {
      v[insPos + 1] = v[insPos];
      --insPos;
    }
    v[insPos + 1] = insValue;
  }
}

void bubble_sort(vector<int> &v) {
  for (int i = 0; i < v.size() - 1; i++) {
    for (int j = 0; j < v.size() - i - 1; j++) {
      if (v[j] > v[j + 1]) {
        swap(v[j], v[j + 1]);
      }
    }
  }
}

int main() {
  // freopen("test.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int &x : v)
    cin >> x;
  bubble_sort(v);
  for (int x : v)
    cout << x << "\n";
}
