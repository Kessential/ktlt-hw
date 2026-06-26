// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 3 - Mo phong Cay Nhi Phan Tim Kiem (Binary Search Tree - BST)
 * Cac thao tac:
 *   1. Them mot phan tu (Insert)
 *   2. Xoa mot phan tu (Delete)
 *   3. Kiem tra mot phan tu co trong cay (Search)
 *   4. Dem so phan tu cua cay (Count)
 *   5. Hien thi cay (Inorder / Preorder / Postorder)
 */

#include <iostream>
#include <queue>
#include <string>
#include <iomanip>

using namespace std;

// ==================== Node ====================
struct Node {
    int   data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ==================== BST Class ====================
class BST {
private:
    Node* root;
    int   nodeCount;   // So phan tu trong cay

    // ---- Ham noi bo de de quy ----

    // Them nut
    Node* insertRec(Node* node, int val, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            nodeCount++;
            return new Node(val);
        }
        if (val < node->data)
            node->left  = insertRec(node->left,  val, inserted);
        else if (val > node->data)
            node->right = insertRec(node->right, val, inserted);
        else
            inserted = false;   // Gia tri da ton tai
        return node;
    }

    // Tim nut co gia tri nho nhat trong cay con
    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Xoa nut
    Node* deleteRec(Node* node, int val, bool& deleted) {
        if (node == nullptr) {
            deleted = false;
            return nullptr;
        }
        if (val < node->data) {
            node->left  = deleteRec(node->left,  val, deleted);
        } else if (val > node->data) {
            node->right = deleteRec(node->right, val, deleted);
        } else {
            // Tim thay nut can xoa
            deleted = true;
            nodeCount--;

            if (node->left == nullptr && node->right == nullptr) {
                // Truong hop 1: la (leaf node)
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                // Truong hop 2: chi co con phai
                Node* tmp = node->right;
                delete node;
                return tmp;
            } else if (node->right == nullptr) {
                // Truong hop 2: chi co con trai
                Node* tmp = node->left;
                delete node;
                return tmp;
            } else {
                // Truong hop 3: co ca hai con
                // Tim nut nho nhat cay con phai (inorder successor)
                Node* successor = findMin(node->right);
                node->data  = successor->data;
                // Xoa inorder successor
                bool tmp = true;
                nodeCount++;  // Tang lai vi deleteRec se tru
                node->right = deleteRec(node->right, successor->data, tmp);
            }
        }
        return node;
    }

    // Tim kiem
    bool searchRec(Node* node, int val) const {
        if (node == nullptr) return false;
        if (val == node->data) return true;
        if (val < node->data)  return searchRec(node->left, val);
        return searchRec(node->right, val);
    }

    // Duyet Inorder (trai - goc - phai) -> cho ra danh sach tang dan
    void inorderRec(Node* node) const {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Duyet Preorder (goc - trai - phai)
    void preorderRec(Node* node) const {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    // Duyet Postorder (trai - phai - goc)
    void postorderRec(Node* node) const {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    // Xoa toan bo cay (giai phong bo nho)
    void clearRec(Node* node) {
        if (node == nullptr) return;
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    // Tinh chieu cao cay
    int heightRec(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + max(heightRec(node->left), heightRec(node->right));
    }

    // Ve cay (level-order, dang so do don gian)
    void printTreeRec(Node* node, int level, bool isLeft) const {
        if (node == nullptr) return;
        printTreeRec(node->right, level + 1, false);
        for (int i = 0; i < level; i++) cout << "    ";
        if (level > 0)
            cout << (isLeft ? "L-- " : "R-- ");
        cout << "[" << node->data << "]\n";
        printTreeRec(node->left,  level + 1, true);
    }

public:
    BST() : root(nullptr), nodeCount(0) {}
    ~BST() { clear(); }

    // Them phan tu
    void insert(int val) {
        bool inserted = false;
        root = insertRec(root, val, inserted);
        if (inserted)
            cout << "[INSERT] Them " << val << " thanh cong. So nut: " << nodeCount << "\n";
        else
            cout << "[INSERT] Gia tri " << val << " da ton tai trong cay!\n";
    }

    // Xoa phan tu
    void remove(int val) {
        bool deleted = false;
        root = deleteRec(root, val, deleted);
        if (deleted)
            cout << "[DELETE] Xoa " << val << " thanh cong. So nut: " << nodeCount << "\n";
        else
            cout << "[DELETE] Gia tri " << val << " khong ton tai trong cay!\n";
    }

    // Tim kiem
    void search(int val) const {
        bool found = searchRec(root, val);
        if (found)
            cout << "[SEARCH] Tim thay " << val << " trong cay.\n";
        else
            cout << "[SEARCH] Khong tim thay " << val << " trong cay.\n";
    }

    // Dem so phan tu
    void count() const {
        cout << "[COUNT] So phan tu trong cay: " << nodeCount << "\n";
    }

    // Chieu cao cay
    void height() const {
        cout << "[HEIGHT] Chieu cao cay: " << heightRec(root) << "\n";
    }

    // Hien thi duyet Inorder
    void inorder() const {
        cout << "[INORDER]   ";
        if (root == nullptr) cout << "(Cay rong)";
        else inorderRec(root);
        cout << "\n";
    }

    // Hien thi duyet Preorder
    void preorder() const {
        cout << "[PREORDER]  ";
        if (root == nullptr) cout << "(Cay rong)";
        else preorderRec(root);
        cout << "\n";
    }

    // Hien thi duyet Postorder
    void postorder() const {
        cout << "[POSTORDER] ";
        if (root == nullptr) cout << "(Cay rong)";
        else postorderRec(root);
        cout << "\n";
    }

    // Hien thi cay dang do thi
    void printTree() const {
        if (root == nullptr) {
            cout << "(Cay rong)\n";
            return;
        }
        cout << "\n--- So do cay (xoay 90 do, doc tu phai sang trai) ---\n";
        printTreeRec(root, 0, false);
        cout << "------------------------------------------------------\n";
    }

    // Xoa toan bo cay
    void clear() {
        clearRec(root);
        root = nullptr;
        nodeCount = 0;
    }

    bool isEmpty() const { return root == nullptr; }
};

// ==================== Nhap so nguyen ====================
int inputInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n) {
            cin.ignore();
            return n;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  [LOI] Nhap so nguyen!\n";
    }
}

// ==================== Menu ====================
void printMenu() {
    cout << "\n====== CAY NHI PHAN TIM KIEM (BST) ======\n";
    cout << "  1. Them phan tu\n";
    cout << "  2. Xoa phan tu\n";
    cout << "  3. Kiem tra phan tu\n";
    cout << "  4. Dem so phan tu\n";
    cout << "  5. Hien thi cay (so do)\n";
    cout << "  6. Duyet Inorder (tang dan)\n";
    cout << "  7. Duyet Preorder\n";
    cout << "  8. Duyet Postorder\n";
    cout << "  9. Chieu cao cay\n";
    cout << "  10. Xoa toan bo cay\n";
    cout << "  0. Thoat\n";
    cout << "==========================================\n";
    cout << "Chon: ";
}

// ==================== Main ====================
int main() {
    cout << "===== MO PHONG CAY NHI PHAN TIM KIEM =====\n";
    cout << "(Thao tac: Them, Xoa, Tim kiem, Dem)\n\n";

    BST tree;
    int choice;

    // Khoi tao cay mau
    cout << "[INIT] Khoi tao cay voi cac phan tu: 50 30 70 20 40 60 80\n";
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        tree.insert(v);
    tree.printTree();

    do {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        } else {
            cin.ignore();
        }

        switch (choice) {
            case 1: {
                int val = inputInt("Nhap gia tri can them: ");
                tree.insert(val);
                tree.printTree();
                break;
            }
            case 2: {
                int val = inputInt("Nhap gia tri can xoa: ");
                tree.remove(val);
                tree.printTree();
                break;
            }
            case 3: {
                int val = inputInt("Nhap gia tri can tim: ");
                tree.search(val);
                break;
            }
            case 4:
                tree.count();
                break;
            case 5:
                tree.printTree();
                break;
            case 6:
                tree.inorder();
                break;
            case 7:
                tree.preorder();
                break;
            case 8:
                tree.postorder();
                break;
            case 9:
                tree.height();
                break;
            case 10:
                tree.clear();
                cout << "[CLEAR] Da xoa toan bo cay.\n";
                break;
            case 0:
                cout << "\nThoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
