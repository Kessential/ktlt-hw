// Name: Pham Minh Khanh
// Student ID: 202418924
// Class: 763966
/*
 * Bai 2.1 - Mo phong hang doi (Queue) xu ly yeu cau den server
 * Moi yeu cau gom:
 *   - Ten yeu cau (request name)
 *   - Dia chi IP nguon (source IP)
 *   - Noi dung (content)
 *   - Thoi gian thuc hien (execution time, don vi: ms)
 *
 * Su dung queue (FIFO): yeu cau den truoc duoc xu ly truoc.
 * Server xu ly tung yeu cau mot, neu hang doi rong thi cho.
 */

#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// ==================== Cau truc Request ====================
struct Request {
    int    id;           // Ma yeu cau (tu dong tang)
    string name;         // Ten yeu cau
    string sourceIP;     // Dia chi IP nguon
    string content;      // Noi dung yeu cau
    int    execTimeMs;   // Thoi gian thuc hien (ms)

    void print() const {
        cout << "  +----------------------------------\n";
        cout << "  | ID      : " << id << "\n";
        cout << "  | Ten     : " << name << "\n";
        cout << "  | IP      : " << sourceIP << "\n";
        cout << "  | Noi dung: " << content << "\n";
        cout << "  | Time    : " << execTimeMs << " ms\n";
        cout << "  +----------------------------------\n";
    }
};

// ==================== Server Queue ====================
class ServerQueue {
private:
    queue<Request> requestQueue;   // Hang doi yeu cau
    int nextId = 1;                // ID tu dong tang
    int totalProcessed = 0;        // Tong so yeu cau da xu ly
    int totalTime = 0;             // Tong thoi gian xu ly (ms)

public:
    // Them yeu cau vao hang doi (Enqueue)
    void addRequest(const string& name, const string& ip,
                    const string& content, int timeMs) {
        Request req;
        req.id         = nextId++;
        req.name       = name;
        req.sourceIP   = ip;
        req.content    = content;
        req.execTimeMs = timeMs;
        requestQueue.push(req);

        cout << "\n[ENQUEUE] Them yeu cau #" << req.id
             << " (\"" << name << "\") vao hang doi.\n";
        cout << "  So yeu cau dang cho: " << requestQueue.size() << "\n";
    }

    // Server xu ly mot yeu cau (Dequeue)
    void processNext(bool simulate = true) {
        if (requestQueue.empty()) {
            cout << "\n[SERVER] Hang doi rong, khong co yeu cau can xu ly.\n";
            return;
        }

        Request req = requestQueue.front();
        requestQueue.pop();

        cout << "\n[SERVER] Dang xu ly yeu cau:\n";
        req.print();

        if (simulate) {
            cout << "  ... xu ly trong " << req.execTimeMs << " ms ...\n";
            this_thread::sleep_for(chrono::milliseconds(min(req.execTimeMs, 2000)));
        }

        totalProcessed++;
        totalTime += req.execTimeMs;
        cout << "  [DONE] Hoan thanh yeu cau #" << req.id << "!\n";
        cout << "  Con lai trong hang doi: " << requestQueue.size() << " yeu cau.\n";
    }

    // Xu ly tat ca yeu cau trong hang doi
    void processAll(bool simulate = true) {
        if (requestQueue.empty()) {
            cout << "\n[SERVER] Hang doi rong.\n";
            return;
        }
        cout << "\n[SERVER] Bat dau xu ly tat ca " << requestQueue.size()
             << " yeu cau...\n";
        while (!requestQueue.empty()) {
            processNext(simulate);
        }
        cout << "\n[SERVER] Da xu ly xong tat ca yeu cau!\n";
    }

    // Hien thi hang doi hien tai
    void displayQueue() const {
        if (requestQueue.empty()) {
            cout << "\n[QUEUE] Hang doi rong.\n";
            return;
        }

        queue<Request> tmp = requestQueue;  // Sao chep de hien thi
        cout << "\n[QUEUE] Danh sach yeu cau dang cho ("
             << requestQueue.size() << " yeu cau):\n";
        while (!tmp.empty()) {
            tmp.front().print();
            tmp.pop();
        }
    }

    // Hien thi thong ke
    void displayStats() const {
        cout << "\n[STATS] ================================\n";
        cout << "  Tong yeu cau da xu ly : " << totalProcessed << "\n";
        cout << "  Tong thoi gian xu ly  : " << totalTime << " ms\n";
        if (totalProcessed > 0)
            cout << "  TB thoi gian moi yeu cau: "
                 << totalTime / totalProcessed << " ms\n";
        cout << "  Yeu cau dang cho      : " << requestQueue.size() << "\n";
        cout << "========================================\n";
    }

    bool isEmpty() const { return requestQueue.empty(); }
    int  size()    const { return (int)requestQueue.size(); }
};

// ==================== Nhap hop le ====================
string inputNonEmpty(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "  [LOI] Khong duoc de trong!\n";
    }
}

int inputPositiveInt(const string& prompt) {
    int n;
    while (true) {
        cout << prompt;
        if (cin >> n && n > 0) {
            cin.ignore();
            return n;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  [LOI] Nhap so nguyen duong!\n";
    }
}

// ==================== Menu ====================
void printMenu() {
    cout << "\n======== MO PHONG SERVER QUEUE ========\n";
    cout << "  1. Them yeu cau vao hang doi\n";
    cout << "  2. Server xu ly yeu cau tiep theo\n";
    cout << "  3. Server xu ly tat ca yeu cau\n";
    cout << "  4. Xem danh sach hang doi\n";
    cout << "  5. Xem thong ke\n";
    cout << "  0. Thoat\n";
    cout << "=======================================\n";
    cout << "Chon: ";
}

// ==================== Main ====================
int main() {
    cout << "===== MO PHONG HANG DOI XU LY YEU CAU SERVER =====\n";
    cout << "(Queue - FIFO: yeu cau den truoc duoc xu ly truoc)\n\n";

    ServerQueue server;
    int choice;

    // Them san mot so yeu cau mau
    cout << "[INIT] Khoi tao mot so yeu cau mau...\n";
    server.addRequest("GET /index.html", "192.168.1.10", "Lay trang chu",       200);
    server.addRequest("POST /login",     "10.0.0.5",     "Dang nhap he thong",  350);
    server.addRequest("GET /api/users",  "172.16.0.20",  "Lay danh sach user",  150);

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
                cout << "\n--- Them yeu cau moi ---\n";
                string name    = inputNonEmpty("  Ten yeu cau  : ");
                string ip      = inputNonEmpty("  Dia chi IP   : ");
                string content = inputNonEmpty("  Noi dung     : ");
                int    time    = inputPositiveInt("  Thoi gian (ms): ");
                server.addRequest(name, ip, content, time);
                break;
            }
            case 2:
                server.processNext(false); // false = khong simulate sleep
                break;
            case 3:
                server.processAll(false);
                break;
            case 4:
                server.displayQueue();
                break;
            case 5:
                server.displayStats();
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
