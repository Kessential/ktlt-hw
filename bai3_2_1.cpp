#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int *pa = &a, *pb = &b;
    cout << "Tong 2 so a = " << *pa << " va b = " << *pb << " cong boi 2 con tro la: " << *pa + *pb << "\n"; 
}
