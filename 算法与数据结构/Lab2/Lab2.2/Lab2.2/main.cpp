#include "LinkStack.h"
#include <iostream>
using namespace std;



int main() {

    while (1) {
        string braces;
        cout << "请输入一个括号序列(输入quit退出): ";
        //为了防止空格输入, 使用getline
        getline(cin, braces);

        if (braces == "quit") {
            break;
        }

        try {
            if (braceMatch(braces)) {
                cout << "匹配成功.\n\n";
            }
            else {
                cout << "括号匹配失败.\n\n";
            }
        }
        catch (int& e) {
            if (e == 1) {
                cout << "没有输入正确的括号序列.\n\n";
            }
            else if (e == 2) {
                cout << "输入不能为空.\n\n";
            }
        }
    }
    return 0;
}