#include <iostream>

using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int a, b; cin >> a >> b;
    cout << "gcd(a, b) = " << gcd(a, b) << "\n"
        << "lcm(a, b) = " << lcm(a, b) << "\n";
}
