#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int lomuto_partition(vector<int>& v, int l, int r) {
    int i = l - 1, pivot = v[r];
    for (int j = l; j < r; j++) {
        if (v[j] <= pivot) {
            ++i;
            swap(v[i], v[j]);
        }
    }
    ++i;
    swap(v[i], v[r]);
    return i;
}

void quick_sort(vector<int>& v, int l, int r) {
    if (l < r) {
        int partition = lomuto_partition(v, l, r);
        quick_sort(v, l, partition - 1);
        quick_sort(v, partition + 1, r);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;
    quick_sort(v, 0, v.size() - 1);
    for (int x : v) cout << x << "\n";
}