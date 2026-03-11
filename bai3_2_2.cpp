#include <iostream>

using namespace std;

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int a, b;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "Hoan doi gia tri cua a va b!\n";
    swap(&a, &b);
    cout << "a = " << a << "\n"
        << "b = " << b << "\n";
}
