#include <iostream>

using namespace std;

void hanoiTower(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoiTower(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    hanoiTower(n - 1, aux, to, from);
}

int main() {
    int n; cin >> n;
    hanoiTower(n, 'A', 'B', 'C');
}