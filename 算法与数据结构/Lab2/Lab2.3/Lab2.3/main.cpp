#include "ParkManager.h"
#include <iostream>
using namespace std;



int main() {
    int n;
    cout << "停车场的容量: ";
    cin >> n;
    ParkManager pm(n);
    pm.parkManage();
    cin.get();
    cin.get();
    return 0;
}