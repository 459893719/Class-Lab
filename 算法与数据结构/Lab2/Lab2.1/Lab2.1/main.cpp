//main.cpp

#include "LinkStack.h"
using namespace std;


int main() {
    
    while (1) {
        int num;
        int d;
        cout << "请输入要转换进制的十进制数(输入-1退出): ";
        cin >> num;
        if (num == -1) {
            break;
        }
        cout << "要转换成什么进制? ";
        cin >> d;

        cout << numSwitch(num, d) << endl << endl;
    }
    return 0;
}

