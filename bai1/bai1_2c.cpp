#include <cmath>
#include <iostream>

using namespace std;

void solve(double a, double b, double c) {
  if (a == 0) {
    if (b == 0) {
      if (c == 0) {
        cout << "Phuong trinh co vo so nghiem\n";
      } else {
        cout << "Phuong trinh vo nghiem\n";
      }
    } else {
      if (c == 0) {
        cout << "x = 0\n";
      } else {
        cout << "x = " << -c / b << "\n";
      }
    }
  } else {
    double delta = b * b - 4 * a * c;
    double sqrtDelta = sqrt(abs(delta));
    if (delta == 0) {
      cout << "x1 = x2 = " << -b / (2 * a) << "\n";
    } else if (delta > 0) {
      cout << "x1 = " << (-b + sqrtDelta) / (2 * a) << "\n"
           << "x2 = " << (-b - sqrtDelta) / (2 * a) << "\n";
    } else {
      cout << "x1 = " << -b / (2 * a) << " + " << sqrtDelta / (2 * a) << "i\n"
           << "x2 = " << -b / (2 * a) << " - " << sqrtDelta / (2 * a) << "i\n";
    }
  }
}

int main() {
  double a, b, c;
  cout << "Nhap lan luot gia tri cua a, b va c: ";
  cin >> a >> b >> c;
  solve(a, b, c);
}
