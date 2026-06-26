// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n; cin >> n;
    vector<int> v(n);
    for (int& x : v) cin >> x;
    ll max_sum = 0, cur_sum = 0;
    int start = 0, best_start = -1, best_end = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > 0) {
            if (cur_sum == 0) start = i;
            cur_sum += v[i];

            if (cur_sum > max_sum) {
                max_sum = cur_sum;
                best_start = start;
                best_end = i;
            }
        } else {
            cur_sum = 0;
        }

    }
    cout << "Tong lon nhat: " << max_sum << "\n";
    if (max_sum > 0) {
        cout << "Day con do la: ";
        for (int i = best_start; i <= best_end; i++) cout << v[i] << "\n";
    } else {
        cout << "Khong co day toan duong nao!\n";
    }
}
