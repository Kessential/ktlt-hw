#include <iostream>

using namespace std;

int main() {
  string msv, ten;
  cout << "Nhap ho ten: ";
  getline(cin, ten);
  cout << "Nhap mssv: ";
  getline(cin, msv);
  cout << "Chao ban " << ten << " " << msv
       << ", minh den voi the gioi lap trinh\n";
}
