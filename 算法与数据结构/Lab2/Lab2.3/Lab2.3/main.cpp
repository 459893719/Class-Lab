#include "ParkManager.h"
#include <iostream>
using namespace std;



int main() {
    int n;
    cout << "ͣ����������: ";
    cin >> n;
    ParkManager pm(n);
    pm.parkManage();
    cin.get();
    cin.get();
    return 0;
}