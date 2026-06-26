// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 1.1 - Chuong trinh soan thao co Undo va Redo
 * Su dung hai stack:
 *   - undoStack: luu cac trang thai truoc do (de Undo)
 *   - redoStack: luu cac trang thai bi hoan tac (de Redo)
 */

#include <iostream>
#include <stack>
#include <string>

using namespace std;

// ==================== Editor Class ====================
class TextEditor {
private:
    string currentText;          // Van ban hien tai
    stack<string> undoStack;     // Stack luu trang thai truoc do
    stack<string> redoStack;     // Stack luu trang thai sau khi undo

public:
    TextEditor() : currentText("") {}

    // Them van ban vao cuoi
    void insert(const string& text) {
        undoStack.push(currentText);   // Luu trang thai hien tai vao undoStack
        while (!redoStack.empty())     // Xoa redoStack khi co thay doi moi
            redoStack.pop();
        currentText += text;
        cout << "[INSERT] Text: \"" << currentText << "\"\n";
    }

    // Xoa n ky tu cuoi cung
    void deleteChars(int n) {
        if (n <= 0) {
            cout << "[ERROR] So ky tu xoa phai > 0\n";
            return;
        }
        undoStack.push(currentText);
        while (!redoStack.empty())
            redoStack.pop();

        int len = (int)currentText.size();
        if (n >= len) {
            currentText = "";
        } else {
            currentText = currentText.substr(0, len - n);
        }
        cout << "[DELETE] Text: \"" << currentText << "\"\n";
    }

    // Hoan tac hanh dong cuoi cung
    void undo() {
        if (undoStack.empty()) {
            cout << "[UNDO] Khong co gi de hoan tac!\n";
            return;
        }
        redoStack.push(currentText);   // Luu trang thai hien tai vao redoStack
        currentText = undoStack.top();
        undoStack.pop();
        cout << "[UNDO] Text: \"" << currentText << "\"\n";
    }

    // Lam lai hanh dong vua hoan tac
    void redo() {
        if (redoStack.empty()) {
            cout << "[REDO] Khong co gi de lam lai!\n";
            return;
        }
        undoStack.push(currentText);
        currentText = redoStack.top();
        redoStack.pop();
        cout << "[REDO] Text: \"" << currentText << "\"\n";
    }

    // Hien thi van ban hien tai
    void display() const {
        cout << "[TEXT] \"" << currentText << "\"\n";
    }

    // Hien thi menu
    void printMenu() const {
        cout << "\n========== TEXT EDITOR ==========\n";
        cout << "  1. Insert text\n";
        cout << "  2. Delete N ky tu cuoi\n";
        cout << "  3. Undo\n";
        cout << "  4. Redo\n";
        cout << "  5. Hien thi van ban hien tai\n";
        cout << "  0. Thoat\n";
        cout << "=================================\n";
        cout << "Chon: ";
    }
};

// ==================== Main ====================
int main() {
    TextEditor editor;
    int choice;

    cout << "===== CHUONG TRINH SOAN THAO CO UNDO/REDO =====\n";
    cout << "(Su dung Stack de quan ly lich su thao tac)\n";

    do {
        editor.printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Nhap van ban them vao: ";
                string text;
                getline(cin, text);
                editor.insert(text);
                break;
            }
            case 2: {
                cout << "Nhap so ky tu can xoa: ";
                int n;
                cin >> n;
                cin.ignore();
                editor.deleteChars(n);
                break;
            }
            case 3:
                editor.undo();
                break;
            case 4:
                editor.redo();
                break;
            case 5:
                editor.display();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
