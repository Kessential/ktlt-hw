#include <iostream>
#include <vector>

using namespace std;

using vvi = vector<vector<int>>;
using vi = vector<int>;

void inp(vvi &a) {
  cout << "Nhap kich thuoc ma tran: ";
  int n, m;
  cin >> n >> m;
  a.resize(n, vi(m));
  cout << "Nhap ma tran:\n";
  for (vi &tmp : a) {
    for (int &x : tmp)
      cin >> x;
  }
}

void printMat(const vvi &a) {
  cout << "-----------------------------\n";
  for (const vi &tmp : a) {
    for (const int &x : tmp) {
      cout << x << " ";
    }
    cout << "\n";
  }
  cout << "-----------------------------\n";
}

void addMat(vvi a, vvi b) {
  int n = a.size(), m = a[0].size();
  int p = b.size(), q = b[0].size();
  if (n != p || m != q) {
    cout << "Kich thuoc ma tran ko hop le!\n";
    return;
  }
  vvi result(n, vi(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      result[i][j] = a[i][j] + b[i][j];
    }
  }
  printMat(result);
}

void subMat(vvi a, vvi b) {
  int n = a.size(), m = a[0].size();
  int p = b.size(), q = b[0].size();
  if (n != p || m != q) {
    cout << "Kich thuoc ma tran ko hop le!\n";
    return;
  }
  vvi result(n, vi(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      result[i][j] = a[i][j] - b[i][j];
    }
  }
  printMat(result);
}

void mulMat(vvi a, vvi b) {
  int n = a.size(), m = a[0].size();
  int p = b.size(), q = b[0].size();
  if (m != p) {
    cout << "Kich thuoc ma tran ko hop le!\n";
    return;
  }
  vvi result(n, vi(q, 0));
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < m; k++) {
      int tmp = a[i][k];
      for (int j = 0; j < q; j++) {
        result[i][j] += tmp * b[k][j];
      }
    }
  }
  printMat(result);
}
int main() {
  vvi a, b;
  inp(a);
  inp(b);
  cout << "1. Cong ma tran\n"
       << "2. Tru ma tran\n"
       << "3. Nhan ma tran\n"
       << "0. Thoat\n"
       << "Nhap thao tac: ";
  int choice;
  cin >> choice;
  switch (choice) {
  case 1:
    addMat(a, b);
    break;
  case 2:
    subMat(a, b);
    break;
  case 3:
    mulMat(a, b);
    break;
  case 0:
    return 0;
  default:
    cout << "Thao tac ko hop le!\n";
    return 1;
  }
}
