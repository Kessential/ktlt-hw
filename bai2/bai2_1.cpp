#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// hien thi du lieu tu file
// them du lieu vao file
// xoa du lieu tu file
// cap nhat du lieu tu file

void hienThi() {
  ifstream in("data.txt");
  if (in.is_open()) {
    cout << "Du lieu cua file data.txt:\n";
    string tmp;
    while (getline(in, tmp)) {
      cout << tmp << "\n";
    }
    in.close();
  } else {
    cout << "Khong the mo duoc file!\n";
  }
}

void themDL(string data) {
  ofstream ou("data.txt", ios::app);
  if (ou.is_open()) {
    ou << data << "\n";
    ou.close();
    cout << "Da them: " << data << "\n";
  } else {
    cout << "Khong tim thay file!\n";
  }
}

void xoaDL(string dlCanXoa) {
  ifstream in("data.txt");
  ofstream ou("tmp.txt");
  string line;
  bool found = false;
  if (in.is_open() && ou.is_open()) {
    while (getline(in, line)) {
      if (line == dlCanXoa) {
        found = true;
      } else {
        ou << line << endl;
      }
    }
    in.close();
    ou.close();
    remove("data.txt");
    rename("tmp.txt", "data.txt");
    if (found) {
      cout << "Da xoa thanh cong!" << endl;
    } else {
      cout << "Khong tim thay du lieu can xoa." << endl;
    }
  }
}
void updateDL(string dlCu, string dlMoi) {
  ifstream fileIn("data.txt");
  ofstream fileOut("tmp.txt");
  string line;
  bool found = false;
  if (fileIn.is_open() && fileOut.is_open()) {
    while (getline(fileIn, line)) {
      if (line == dlCu) {
        found = true;
        fileOut << dlMoi << endl;
      } else {
        fileOut << line << endl;
      }
    }
    fileIn.close();
    fileOut.close();
    remove("data.txt");
    rename("tmp.txt", "data.txt");
    if (found) {
      cout << "Da cap nhat thanh cong!" << endl;
    } else {
      cout << "Khong tim thay du lieu can cap nhat." << endl;
    }
  }
}

int main() {
  while (true) {
    cout << "1. Hien thi du lieu\n"
         << "2. Them du lieu vao cuoi file\n"
         << "3. Xoa du lieu can tim\n"
         << "4. Cap nhat du lieu\n"
         << "0. Ket thuc chuong trinh\n";
    cout << "Nhap tuy chon: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 0:
      return 0;
    case 1:
      hienThi();
      break;
    case 2: {
      cout << "Nhap du lieu ban can them\n";
      string data;
      getline(cin, data);
      themDL(data);
      break;
    }
    case 3: {
      cout << "Nhap du lieu ban can xoa\n";
      string data;
      getline(cin, data);
      xoaDL(data);
      break;
    }
    case 4: {
      string dlCu, dlMoi;
      cout << "Nhap du lieu ban can tim\n";
      getline(cin, dlCu);
      cout << "Nhap du lieu ban can cap nhat\n";
      getline(cin, dlMoi);
      updateDL(dlCu, dlMoi);
      break;
    }
    default: {
      cout << "Ban nhap lua chon sai, chuong trinh ket thuc\n";
      return 1;
    }
    }
  }
}
