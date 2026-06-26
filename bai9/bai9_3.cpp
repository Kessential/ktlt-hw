// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 9 - Cau 3: file -> man hinh / file
 * Nhap mot hinh (tap hop cac diem) tu file.
 * Thuc hien cac phep bien hinh:
 *   1. Doi xung qua truc Ox
 *   2. Doi xung qua truc Oy
 *   3. Doi xung qua goc O (doi xung diem)
 *   4. Quay quanh goc O mot goc theta
 *   5. Phong to / Thu nho voi he so k
 *
 * Input file (shape.txt):
 *   Dong dau: so luong diem n
 *   n dong tiep theo: x y (toa do moi diem)
 *
 * Output file (shape_out.txt):
 *   Toa do cac diem sau bien hinh
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

const double PI = acos(-1.0);

// ==================== Diem 2D ====================
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// In mot diem
void printPoint(const Point& p, ostream& os) {
    os << fixed << setprecision(4) << "(" << p.x << ", " << p.y << ")";
}

// In tap hop diem
void printShape(const vector<Point>& pts, ostream& os, const string& title = "") {
    if (!title.empty()) os << title << "\n";
    for (int i = 0; i < (int)pts.size(); i++) {
        os << "  P" << i + 1 << " = ";
        printPoint(pts[i], os);
        os << "\n";
    }
}

// ==================== Cac phep bien hinh ====================

// 1. Doi xung qua truc Ox: (x, y) -> (x, -y)
vector<Point> reflectOx(const vector<Point>& pts) {
    vector<Point> res;
    for (const auto& p : pts) res.push_back({p.x, -p.y});
    return res;
}

// 2. Doi xung qua truc Oy: (x, y) -> (-x, y)
vector<Point> reflectOy(const vector<Point>& pts) {
    vector<Point> res;
    for (const auto& p : pts) res.push_back({-p.x, p.y});
    return res;
}

// 3. Doi xung qua goc O: (x, y) -> (-x, -y)
vector<Point> reflectOrigin(const vector<Point>& pts) {
    vector<Point> res;
    for (const auto& p : pts) res.push_back({-p.x, -p.y});
    return res;
}

// 4. Quay quanh goc O mot goc theta (do):
//    x' =  x*cos(t) - y*sin(t)
//    y' =  x*sin(t) + y*cos(t)
vector<Point> rotate(const vector<Point>& pts, double thetaDeg) {
    double t = thetaDeg * PI / 180.0;
    double cosT = cos(t), sinT = sin(t);
    vector<Point> res;
    for (const auto& p : pts) {
        double nx = p.x * cosT - p.y * sinT;
        double ny = p.x * sinT + p.y * cosT;
        res.push_back({nx, ny});
    }
    return res;
}

// 5. Phong to / Thu nho voi he so k (k > 1: phong to, 0 < k < 1: thu nho)
//    x' = k * x,  y' = k * y
vector<Point> scale(const vector<Point>& pts, double k) {
    vector<Point> res;
    for (const auto& p : pts) res.push_back({p.x * k, p.y * k});
    return res;
}

// ==================== Doc / Ghi file ====================
vector<Point> readShape(const string& filename) {
    vector<Point> pts;
    ifstream fin(filename);
    if (!fin.is_open()) {
        // Tao file mau neu chua co
        ofstream fout(filename);
        fout << "4\n";
        fout << "1.0 2.0\n";
        fout << "3.0 4.0\n";
        fout << "-2.0 1.5\n";
        fout << "0.0 -3.0\n";
        fout.close();
        cout << "[INFO] File '" << filename << "' chua ton tai. "
             << "Da tao file mau. Hay chay lai chuong trinh.\n";
        return pts; // tra ve rong
    }
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        double x, y;
        fin >> x >> y;
        pts.push_back({x, y});
    }
    fin.close();
    return pts;
}

void writeShape(const string& filename, const vector<Point>& pts,
                const string& header) {
    ofstream fout(filename, ios::app); // ghi them vao file
    if (!fout.is_open()) {
        cout << "[LOI] Khong mo duoc file: " << filename << "\n";
        return;
    }
    fout << header << "\n";
    for (int i = 0; i < (int)pts.size(); i++) {
        fout << "  P" << i + 1 << " = ";
        printPoint(pts[i], fout);
        fout << "\n";
    }
    fout << "\n";
}

// ==================== Hien thi menu ====================
void printMenu() {
    cout << "\n====== MENU BIEN HINH ======\n";
    cout << "  1. Doi xung qua truc Ox\n";
    cout << "  2. Doi xung qua truc Oy\n";
    cout << "  3. Doi xung qua goc O\n";
    cout << "  4. Quay quanh goc O\n";
    cout << "  5. Phong to / Thu nho\n";
    cout << "  6. Hien thi hinh hien tai\n";
    cout << "  7. Luu ket qua vao file\n";
    cout << "  0. Thoat\n";
    cout << "============================\n";
    cout << "Chon: ";
}

// ==================== Main ====================
int main() {
    string inputFile  = "shape.txt";
    string outputFile = "shape_out.txt";

    cout << "=== CHUONG TRINH BIEN HINH (file -> man hinh / file) ===\n";
    cout << "Doc hinh tu: " << inputFile << "\n\n";

    // Doc hinh ban dau
    vector<Point> shape = readShape(inputFile);
    if (shape.empty()) return 0;

    cout << "Hinh ban dau:\n";
    printShape(shape, cout);

    // Xoa file output cu
    ofstream clearOut(outputFile, ios::trunc);
    clearOut << "=== KET QUA BIEN HINH ===\n\n";
    clearOut.close();

    // Luu ban dau vao output
    writeShape(outputFile, shape, "Hinh ban dau:");

    vector<Point> current = shape;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                current = reflectOx(current);
                cout << "\n[Doi xung Ox] Ket qua:\n";
                printShape(current, cout);
                writeShape(outputFile, current, "[Doi xung Ox]:");
                break;
            }
            case 2: {
                current = reflectOy(current);
                cout << "\n[Doi xung Oy] Ket qua:\n";
                printShape(current, cout);
                writeShape(outputFile, current, "[Doi xung Oy]:");
                break;
            }
            case 3: {
                current = reflectOrigin(current);
                cout << "\n[Doi xung goc O] Ket qua:\n";
                printShape(current, cout);
                writeShape(outputFile, current, "[Doi xung goc O]:");
                break;
            }
            case 4: {
                double theta;
                cout << "Nhap goc quay (do, duong = nguoc chieu kim dong ho): ";
                cin >> theta;
                current = rotate(current, theta);
                cout << "\n[Quay " << theta << " do] Ket qua:\n";
                printShape(current, cout);
                writeShape(outputFile, current,
                           "[Quay " + to_string((int)theta) + " do]:");
                break;
            }
            case 5: {
                double k;
                cout << "Nhap he so phong to/thu nho (k > 0): ";
                cin >> k;
                if (k <= 0) {
                    cout << "[LOI] He so phai > 0!\n";
                    break;
                }
                current = scale(current, k);
                cout << "\n[Phong to/Thu nho x" << k << "] Ket qua:\n";
                printShape(current, cout);
                writeShape(outputFile, current,
                           "[Phong to/Thu nho x" + to_string(k) + "]:");
                break;
            }
            case 6: {
                cout << "\n[Hinh hien tai]:\n";
                printShape(current, cout);
                break;
            }
            case 7: {
                writeShape(outputFile, current, "[Luu thu cong]:");
                cout << "Da luu vao: " << outputFile << "\n";
                break;
            }
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "[LOI] Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    cout << "\nToan bo ket qua da duoc ghi vao: " << outputFile << "\n";
    return 0;
}
