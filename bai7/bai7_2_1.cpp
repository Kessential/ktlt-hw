// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
#include <iostream>
#include <string>

using namespace std;

struct SinhVien {
    string MSSV;
    string Ten;
    string HocPhan;
    double Diem;
};

struct Node {
    SinhVien data;
    Node* next;
};

struct LinkedList {
    Node* head = nullptr;
    void addNodeToFirst(SinhVien data) {
        Node* tmp = new Node {data, head};
        head = tmp;
    }
    void addNodeToLast(SinhVien data) {
        if (head == nullptr) {
            addNodeToFirst(data);
            return;
        }
        Node* tmp = head;
        while (tmp->next != nullptr) tmp = tmp->next;
        Node* newNode = new Node {data, nullptr};
        tmp->next = newNode;
    }
    void addNode(string mssv, SinhVien data) {
        if (head == nullptr) return;
        Node* tmp = head;
        while (tmp != nullptr) {
            if (tmp->data.MSSV == mssv) {
                Node* newNode = new Node {data, tmp->next};
                tmp->next = newNode;
                return;
            }
            tmp = tmp->next;
        }
    }
    bool changeSVData(string mssv, double diem) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data.MSSV == mssv) {
                curr->data.Diem = diem;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    bool findMSSV(string mssv) {
        if (head == nullptr) return false;
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->data.MSSV == mssv) return true;
            curr = curr->next;
        }
        return false;
    }
    void deleteFirstNode() {
        if (head == nullptr) return;
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
    void deleteLastNode() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* curr = head;
        while (curr->next->next != nullptr) curr = curr->next;
        delete curr->next;
        curr->next = nullptr;
    }
    void deleteNode(string mssv) {
        if (head == nullptr) return;
        if (head->data.MSSV == mssv) {
            deleteFirstNode();
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            if (curr->next->data.MSSV == mssv) {
                Node* tmp = curr->next;
                curr->next = curr->next->next;
                delete tmp;
                return;
            }
            curr = curr->next;
        }
    }
    void printList() {
        if (head == nullptr) {
            cout << "(Danh sach rong)\n";
            return;
        }
        Node* tmp = head;
        while (tmp != nullptr) {
            cout << "[" << tmp->data.MSSV << " | " << tmp->data.Diem << "] -> ";
            tmp = tmp->next;
        }
        cout << "NULL\n";
    }

};

int main() {
    LinkedList list;
    SinhVien sv1{"20240001", "Nguyen Van A", "Tin dai cuong", 8.5};
    SinhVien sv2{"20240002", "Tran Thi B", "Kinh te chinh tri", 4.0};
    SinhVien sv3{"20240003", "Le Van C", "Giai tich 1", 9.0};

    cout << "--- BAT DAU TEST CASE DAC BIET ---\n\n";

    // ==========================================
    // NHÓM 1: TEST TRÊN DANH SÁCH RỖNG (Empty List)
    // ==========================================
    cout << "1. Thao tac tren danh sach rong:\n";
    list.deleteFirstNode(); // Không crash
    list.deleteLastNode();  // Không crash
    list.deleteNode("20240001"); // Không crash
    list.addNode("20240001", sv1); // Không chèn được vì làm gì có ai để chèn phía sau
    cout << "-> Trang thai list sau khi pha hoai luc rong: ";
    list.printList(); 

    // Chèn phần tử đầu tiên bằng addNodeToLast xem có tự động chuyển thành chèn đầu không
    list.addNodeToLast(sv1);
    cout << "-> List sau khi addNodeToLast vao list rong: ";
    list.printList(); // Kết quả kỳ vọng: sv1 -> NULL
    cout << "----------------------------------------\n";

    // ==========================================
    // NHÓM 2: TEST TRÊN DANH SÁCH CHỈ CÓ 1 NODE (Single Element)
    // ==========================================
    cout << "2. Thao tac tren danh sach chi co 1 phan tu:\n";
    list.addNode("20240001", sv2); // Chèn sv2 vào sau sv1 (Đang tìm phần tử duy nhất)
    cout << "-> List sau khi chen vao sau phan tu duy nhat: ";
    list.printList(); // Kỳ vọng: sv1 -> sv2 -> NULL

    // Reset lại list về 1 phần tử để test tiếp
    list.deleteLastNode(); 
    
    // Test xóa node duy nhất bằng hàm deleteNode chung
    list.deleteNode("20240001");
    cout << "-> List sau khi dung deleteNode xoa di nut duy nhat: ";
    list.printList(); // Kỳ vọng: (Danh sach rong)
    cout << "----------------------------------------\n";

    // ==========================================
    // NHÓM 3: TEST XÓA CÁC VỊ TRÍ ĐẶC BIỆT TRÊN LIST NHIỀU NODE
    // ==========================================
    cout << "3. Thao tac xoa cac vi tri nhạy cam:\n";
    // Chuẩn bị lại list: sv1 -> sv2 -> sv3
    list.addNodeToLast(sv1);
    list.addNodeToLast(sv2);
    list.addNodeToLast(sv3);
    cout << "-> List goc ban dau: ";
    list.printList();

    // Kịch bản A: Xóa phần tử nằm ở chính HEAD khi danh sách đang dài
    list.deleteNode("20240001"); 
    cout << "-> Sau khi xoa HEAD (sv1): ";
    list.printList(); // Kỳ vọng còn lại: sv2 -> sv3 -> NULL

    // Kịch bản B: Xóa phần tử nằm ở chính TAIL (Cuối danh sách) bằng hàm deleteNode chung
    list.deleteNode("20240003");
    cout << "-> Sau khi xoa TAIL (sv3): ";
    list.printList(); // Kỳ vọng còn lại: sv2 -> NULL
    cout << "----------------------------------------\n";

    // ==========================================
    // NHÓM 4: TEST DỮ LIỆU KHÔNG TỒN TẠI
    // ==========================================
    cout << "4. Thao tac voi thong tin KHONG co trong list:\n";
    bool checkSua = list.changeSVData("99999999", 10.0);
    cout << "-> Ket qua sua sinh vien khong ton tai: " << (checkSua ? "Thanh cong" : "That bai (Chuan)") << "\n";
    
    list.deleteNode("99999999"); // Không tìm thấy thì không được lỗi, list giữ nguyên
    cout << "-> List sau khi yeu cau xoa ma ma khong ton tai: ";
    list.printList(); // Kỳ vọng còn nguyên sv2
    cout << "----------------------------------------\n";

    cout << "--- TEST CASE HOAN THANH - MOI THU ON DINH ---\n";
    return 0;
}
