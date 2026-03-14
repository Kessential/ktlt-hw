#include <iostream>

using namespace std;

// c++ nhung su dung c-style string: char[]

int my_strlen(char s[]) {
    int cnt = 0;
    char* tmp = s;
    while (*tmp != '\0') {
        ++cnt;
        ++tmp;
    }
    return cnt;
}
int main() {
    char str[2048];
    cin.getline(str, 2048);
    cout << my_strlen(str) << "\n";
} 
