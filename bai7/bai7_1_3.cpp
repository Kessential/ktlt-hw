// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, M; cin >> n >> M;
    vector<int> v(n);
    for (int& x : v) cin >> x;
    int left = 0, right = 0;
    int sum = 0;
    for (right = 0; right < n; right++) {
        sum += v[right];
        while (sum > M && left <= right) {
            sum -= v[left];
            ++left;
        }
        if (sum == M) {
            cout << "Mang con co tong bang M bat dau tu [" << left << ", " << right << "]\n";
            break;
        }
    }
}
