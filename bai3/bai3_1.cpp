#include <fstream>
#include <iostream>
#include <string>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

int main() {
  ifstream input("inp.txt");
  if (!input.is_open()) {
    cout << "Khong the mo file nay!\n";
    return 1;
  }
  ofstream output("out.txt");
  string tmp;
  while (getline(input, tmp)) {
    for (char x : tmp) {
      if (x == '1') {
        output << "X ";
      } else if (x == '0') {
        output << "  ";
      }
    }
    output << "\n";
  }
  input.close();
  output.close();
}
