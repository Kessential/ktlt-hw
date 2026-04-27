#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& v, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = v[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = v[m + 1 + i];
    }
    int idx = l, i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[idx++] = L[i++];
        }
        else {
            v[idx++] = R[j++];
        }
    }
    while (i < n1) {
        v[idx++] = L[i++];
    }
    while (j < n2) {
        v[idx++] = R[j++];
    }
}

void merge_sort(vector<int>& v, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(v, l, m);
        merge_sort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;
    merge_sort(v, 0, v.size() - 1);
    for (int x : v) cout << x << "\n";

}