#include <iostream>
#include <fstream>

using namespace std;

struct SinhVien {
    string maSV, ten, lop;
    double gpa;
};

// hien thi du lieu tu file
// them du lieu vao file
// xoa du lieu tu file
// cap nhat du lieu tu file

int main() {
    fstream ofile("file.txt");
    if (!ofile.is_open()) {
        cout << "Cannot open file!";
        return 1;
    }
    
}
