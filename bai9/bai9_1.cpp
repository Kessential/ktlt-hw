// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 9 - Cau 1: file -> file
 * Thuc hien phep toan (+, -, *, /) voi so lon nhap tu file
 *
 * Input file (input.txt):
 *   Dong 1: so thu nhat (so nguyen lon)
 *   Dong 2: phep toan (+, -, *, /)
 *   Dong 3: so thu hai (so nguyen lon)
 *
 * Output file (output.txt):
 *   Ket qua phep toan
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ==================== BigInteger Class ====================
// Luu so nguyen lon bang vector cac chu so (little-endian, digits[0] = hang don vi)
// Ho tro: so am, phep +, -, *, /
class BigInteger {
public:
    vector<int> digits; // digits[0] la hang don vi, little-endian
    bool negative;

    BigInteger() : negative(false) {}

    BigInteger(string s) : negative(false) {
        if (s.empty()) { digits.push_back(0); return; }
        if (s[0] == '-') { negative = true; s = s.substr(1); }
        else if (s[0] == '+') { s = s.substr(1); }
        // Xoa so 0 o dau
        int start = 0;
        while (start < (int)s.size() - 1 && s[start] == '0') start++;
        for (int i = (int)s.size() - 1; i >= start; i--)
            digits.push_back(s[i] - '0');
        // Neu la 0, dam bao khong am
        if (isZero()) negative = false;
    }

    bool isZero() const {
        return digits.size() == 1 && digits[0] == 0;
    }

    // So sanh gia tri tuyet doi: -1 < 0 > 1
    static int cmpAbs(const BigInteger& a, const BigInteger& b) {
        if (a.digits.size() != b.digits.size())
            return (a.digits.size() < b.digits.size()) ? -1 : 1;
        for (int i = (int)a.digits.size() - 1; i >= 0; i--) {
            if (a.digits[i] != b.digits[i])
                return (a.digits[i] < b.digits[i]) ? -1 : 1;
        }
        return 0;
    }

    // Cong hai gia tri tuyet doi
    static BigInteger addAbs(const BigInteger& a, const BigInteger& b) {
        BigInteger res;
        int carry = 0;
        int n = max(a.digits.size(), b.digits.size());
        for (int i = 0; i < n || carry; i++) {
            int sum = carry;
            if (i < (int)a.digits.size()) sum += a.digits[i];
            if (i < (int)b.digits.size()) sum += b.digits[i];
            res.digits.push_back(sum % 10);
            carry = sum / 10;
        }
        return res;
    }

    // Tru |a| - |b| (gia su |a| >= |b|)
    static BigInteger subAbs(const BigInteger& a, const BigInteger& b) {
        BigInteger res;
        int borrow = 0;
        for (int i = 0; i < (int)a.digits.size(); i++) {
            int diff = a.digits[i] - borrow;
            if (i < (int)b.digits.size()) diff -= b.digits[i];
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            res.digits.push_back(diff);
        }
        // Xoa so 0 thua o dau (dang little-endian)
        while (res.digits.size() > 1 && res.digits.back() == 0)
            res.digits.pop_back();
        return res;
    }

    // Phep cong
    BigInteger operator+(const BigInteger& other) const {
        if (negative == other.negative) {
            BigInteger res = addAbs(*this, other);
            res.negative = negative;
            if (res.isZero()) res.negative = false;
            return res;
        }
        // Khac dau
        int c = cmpAbs(*this, other);
        if (c == 0) return BigInteger("0");
        BigInteger res;
        if (c > 0) { res = subAbs(*this, other); res.negative = negative; }
        else        { res = subAbs(other, *this); res.negative = other.negative; }
        if (res.isZero()) res.negative = false;
        return res;
    }

    // Phep tru
    BigInteger operator-(const BigInteger& other) const {
        BigInteger neg = other;
        neg.negative = !other.negative;
        if (neg.isZero()) neg.negative = false;
        return *this + neg;
    }

    // Phep nhan
    BigInteger operator*(const BigInteger& other) const {
        BigInteger res;
        res.digits.assign(digits.size() + other.digits.size(), 0);
        for (int i = 0; i < (int)digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < (int)other.digits.size() || carry; j++) {
                long long cur = (long long)res.digits[i + j] + carry;
                if (j < (int)other.digits.size())
                    cur += (long long)digits[i] * other.digits[j];
                res.digits[i + j] = cur % 10;
                carry = cur / 10;
            }
        }
        while (res.digits.size() > 1 && res.digits.back() == 0)
            res.digits.pop_back();
        res.negative = (negative != other.negative);
        if (res.isZero()) res.negative = false;
        return res;
    }

    // Phep chia nguyen (thuong so)
    BigInteger operator/(const BigInteger& divisor) const {
        if (divisor.isZero()) {
            cout << "[LOI] Chia cho 0!\n";
            return BigInteger("0");
        }
        BigInteger absA = *this;  absA.negative = false;
        BigInteger absB = divisor; absB.negative = false;

        if (cmpAbs(absA, absB) < 0) return BigInteger("0");

        // Long division theo tung chu so (big-endian)
        BigInteger quotient, current;
        current.digits = {0};
        int n = (int)absA.digits.size();
        for (int i = n - 1; i >= 0; i--) {
            // current = current * 10 + absA.digits[i]
            current.digits.insert(current.digits.begin(), absA.digits[i]);
            while (current.digits.size() > 1 && current.digits.back() == 0)
                current.digits.pop_back();

            // Tim so lon nhat q sao cho q * absB <= current
            int lo = 0, hi = 9, q = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                BigInteger tmp;
                tmp.digits = {mid};
                BigInteger prod = tmp * absB;
                if (cmpAbs(prod, current) <= 0) { q = mid; lo = mid + 1; }
                else hi = mid - 1;
            }
            quotient.digits.insert(quotient.digits.begin(), q);
            BigInteger qtmp; qtmp.digits = {q};
            current = current - qtmp * absB;
        }
        while (quotient.digits.size() > 1 && quotient.digits.back() == 0)
            quotient.digits.pop_back();
        quotient.negative = (negative != divisor.negative);
        if (quotient.isZero()) quotient.negative = false;
        return quotient;
    }

    // Chuyen thanh chuoi
    string toString() const {
        string s = "";
        if (negative) s = "-";
        for (int i = (int)digits.size() - 1; i >= 0; i--)
            s += (char)('0' + digits[i]);
        return s;
    }
};

// ==================== Main ====================
int main() {
    string inputFile  = "input.txt";
    string outputFile = "output.txt";

    // --- Doc file dau vao ---
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        // Neu chua co file, tao file mau
        ofstream fout(inputFile);
        fout << "12345678901234567890\n";
        fout << "+\n";
        fout << "98765432109876543210\n";
        fout.close();
        cout << "[INFO] File '" << inputFile << "' chua ton tai. "
             << "Da tao file mau. Hay chay lai chuong trinh.\n";
        return 0;
    }

    string numA, op, numB;
    fin >> numA >> op >> numB;
    fin.close();

    cout << "=== PHEP TOAN SO LON (file -> file) ===\n";
    cout << "Doc tu: " << inputFile << "\n";
    cout << "A   = " << numA << "\n";
    cout << "Toan tu = " << op  << "\n";
    cout << "B   = " << numB << "\n";

    // Kiem tra hop le
    if (op != "+" && op != "-" && op != "*" && op != "/") {
        cout << "[LOI] Phep toan khong hop le: " << op << "\n";
        cout << "Chi ho tro: +, -, *, /\n";
        return 1;
    }

    BigInteger a(numA), b(numB);
    BigInteger result;
    string opName;

    if      (op == "+") { result = a + b; opName = "Cong"; }
    else if (op == "-") { result = a - b; opName = "Tru"; }
    else if (op == "*") { result = a * b; opName = "Nhan"; }
    else {
        if (b.isZero()) {
            cout << "[LOI] Khong the chia cho 0!\n";
            return 1;
        }
        result = a / b;
        opName = "Chia nguyen";
    }

    string resultStr = result.toString();
    cout << "Ket qua = " << resultStr << "\n";

    // --- Ghi file dau ra ---
    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cout << "[LOI] Khong mo duoc file: " << outputFile << "\n";
        return 1;
    }
    fout << "=== KET QUA PHEP TOAN SO LON ===\n";
    fout << "A          = " << numA << "\n";
    fout << "Toan tu    = " << op  << "\n";
    fout << "B          = " << numB << "\n";
    fout << "Ket qua    = " << resultStr << "\n";
    fout.close();

    cout << "Da ghi ket qua vao: " << outputFile << "\n";
    return 0;
}
