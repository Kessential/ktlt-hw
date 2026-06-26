// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 1.2 - Tinh gia tri bieu thuc toan hoc
 * Thuat toan Shunting-yard (Dijkstra):
 *   - Dung 2 stack: mot cho so (operands), mot cho toan tu (operators)
 *   - Ho tro: +, -, *, /, ^ va ngoac don ()
 *   - Uu tien toan tu: ^ > *, / > +, -
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cctype>

using namespace std;

// Tra ve do uu tien cua toan tu
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Kiem tra toan tu la ket hop phai (right-associative)
bool isRightAssoc(char op) {
    return op == '^';
}

// Thuc hien phep tinh
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Loi: Chia cho 0!");
            return a / b;
        case '^': return pow(a, b);
        default: throw runtime_error("Toan tu khong hop le!");
    }
}

// Lay toan tu tren dinh stack va tinh toan
void processTop(stack<double>& nums, stack<char>& ops) {
    if (nums.size() < 2) throw runtime_error("Bieu thuc khong hop le!");
    double b = nums.top(); nums.pop();
    double a = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();
    nums.push(applyOp(a, b, op));
}

// Ham chinh tinh gia tri bieu thuc
double evaluate(const string& expr) {
    stack<double> nums;   // Stack chua so
    stack<char>   ops;    // Stack chua toan tu

    int i = 0;
    int len = (int)expr.size();

    while (i < len) {
        char c = expr[i];

        // Bo qua khoang trang
        if (c == ' ' || c == '\t') {
            i++;
            continue;
        }

        // Doc so (co the la so thap phan, va so am o dau)
        if (isdigit(c) || c == '.' ||
            (c == '-' && (i == 0 || expr[i-1] == '('))) {
            string numStr;
            if (c == '-') {
                numStr += '-';
                i++;
            }
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                numStr += expr[i++];
            }
            if (numStr.empty() || numStr == "-")
                throw runtime_error("Bieu thuc khong hop le: so rong!");
            nums.push(stod(numStr));
            continue;
        }

        // Mo ngoac
        if (c == '(') {
            ops.push(c);
            i++;
            continue;
        }

        // Dong ngoac: giai phong toan tu cho den khi gap mo ngoac
        if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                processTop(nums, ops);
            }
            if (ops.empty()) throw runtime_error("Ngoac don khong can bang!");
            ops.pop(); // Bo mo ngoac '('
            i++;
            continue;
        }

        // Toan tu
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            while (!ops.empty() && ops.top() != '(' &&
                   (precedence(ops.top()) > precedence(c) ||
                   (precedence(ops.top()) == precedence(c) && !isRightAssoc(c)))) {
                processTop(nums, ops);
            }
            ops.push(c);
            i++;
            continue;
        }

        // Ky tu khong hop le
        throw runtime_error(string("Ky tu khong hop le: ") + c);
    }

    // Xu ly cac toan tu con lai
    while (!ops.empty()) {
        if (ops.top() == '(') throw runtime_error("Ngoac don khong can bang!");
        processTop(nums, ops);
    }

    if (nums.size() != 1) throw runtime_error("Bieu thuc khong hop le!");
    return nums.top();
}

// ==================== Main ====================
int main() {
    cout << "===== TINH GIA TRI BIEU THUC TOAN HOC =====\n";
    cout << "(Ho tro: +, -, *, /, ^ va ngoac don ())\n";
    cout << "Nhap 'exit' de thoat.\n\n";

    string expr;
    while (true) {
        cout << "Nhap bieu thuc: ";
        getline(cin, expr);

        if (expr == "exit" || expr == "EXIT") {
            cout << "Thoat chuong trinh.\n";
            break;
        }

        if (expr.empty()) continue;

        try {
            double result = evaluate(expr);
            // In ket qua: neu la so nguyen thi in nguyen, nguoc lai in thap phan
            if (result == (long long)result)
                cout << "Ket qua: " << (long long)result << "\n\n";
            else
                cout << "Ket qua: " << result << "\n\n";
        } catch (const exception& e) {
            cout << "[LOI] " << e.what() << "\n\n";
        }
    }

    return 0;
}
