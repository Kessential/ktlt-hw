#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void counting_sort(const vector<int> &v) {
    int k = *max_element(v.begin(), v.end());
    vector<int> count(k + 1, 0);
    for (int x : v) {
        count[x]++;
    }
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < count[i]; i++) {
            cout << i << "\n";
        }
    }
}

int main() {
    // freopen("test.txt", "r", stdin);
    // freopen("output.txt", "wa", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;
    counting_sort(v);
}