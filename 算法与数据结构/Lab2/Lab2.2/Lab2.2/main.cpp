#include "LinkStack.h"
#include <iostream>
using namespace std;



int main() {

    while (1) {
        string braces;
        cout << "������һ����������(����quit�˳�): ";
        //Ϊ�˷�ֹ�ո�����, ʹ��getline
        getline(cin, braces);

        if (braces == "quit") {
            break;
        }

        try {
            if (braceMatch(braces)) {
                cout << "ƥ��ɹ�.\n\n";
            }
            else {
                cout << "����ƥ��ʧ��.\n\n";
            }
        }
        catch (int& e) {
            if (e == 1) {
                cout << "û��������ȷ����������.\n\n";
            }
            else if (e == 2) {
                cout << "���벻��Ϊ��.\n\n";
            }
        }
    }
    return 0;
}