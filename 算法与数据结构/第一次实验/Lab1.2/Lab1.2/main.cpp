#include <iostream>
#include <cstdio>
#include "CLinkList.h"
#include <cstdlib>
using namespace std;



int main() {
    CLinkList jlist;
    int n, m;

    int num = 5;
    while (num--) {
        cout << "请输入报数人数以及初始的报数上限值:\n";
        cin >> n >> m;

        vector<int> password = jlist.simulateJoseph(n, m);

        for (int i = 0; i < password.size(); i++) {
            if (i) { cout << ", "; }
            cout << password[i];
        }
        cout << "\n\n";
    }
    system("pause");
    return 0;
}