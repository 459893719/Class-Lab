//main.cpp

#include "LinkStack.h"
using namespace std;


int main() {
    
    while (1) {
        int num;
        int d;
        cout << "������Ҫת�����Ƶ�ʮ������(����-1�˳�): ";
        cin >> num;
        if (num == -1) {
            break;
        }
        cout << "Ҫת����ʲô����? ";
        cin >> d;

        cout << numSwitch(num, d) << endl << endl;
    }
    return 0;
}

