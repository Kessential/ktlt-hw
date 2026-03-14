#include <iostream>

// Name: Pham Minh Khanh
// Student ID: 202418924
// Date: 12/3/2026

using namespace std;

// c++ nhung su dung c-style string: char[]

int my_strlen(char s[]) {
  int cnt = 0;
  char *tmp = s;
  while (*tmp != '\0') {
    ++cnt;
    ++tmp;
  }
  return cnt;
}
int main() {
  char str[2048];
  cin.getline(str, 2048);
  cout << my_strlen(str) << "\n";
}
