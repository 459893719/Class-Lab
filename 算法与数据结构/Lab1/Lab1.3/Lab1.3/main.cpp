#include <iostream>
#include <cstdio>
#include "CityArray.h"
using namespace std;



int main() {
    CityArray clist;
    
    //���������ڵ㲢��ӡһ��
    clist.insertList("Beijing", 10.0, 10.0);
    clist.insertList("London", 100.0, -10.0);
    clist.insertList("Shanghai", 30.0, 30.0);
    clist.insertList("Chongqing", 15.0, 15.0);
    clist.insertList("Tokyo", -390.0, 400.0);
    clist.insertList("Yokohama", -400.0, 410.0);

    clist.printList();


    //�ĸ�ɾ�������ֱ���ɾ�����һ���ڵ�, ��β�ڵ�, һ��ڵ�, һ�������ڵĽڵ�, ����ӡһ��
    clist.deleteByName("Yokohama");
    clist.deleteByName("Beijing");
    clist.deleteByName("Tokyo");
    clist.deleteByName("Qingdao");

    clist.printList();

    clist.insertList("Yokohama", -400.0, 410.0);
    clist.insertList("Beijing", 10.0, 10.0);

    //��һ�����г��е�����, ����һ�������ڵĳ�������
    Location loc = clist.searchLocation("Beijing");
    cout << loc.x << " " << loc.y << "\n";
    Location loc1 = clist.searchLocation("Chengdu");
    cout << loc1.x << " " << loc1.y << "\n";


    //����������һ��ĳ��λ�ø����ĳ���, ����һ��λ�ø���û�г��е����
    vector<City> result = clist.searchCityNearby({ 0,0 }, 90);
    for (City i : result) {
        cout << "������: " << i.name << " λ��: (" << i.x << ", " << i.y << ")\n";
    }

    result = clist.searchCityNearby({ 0,0 }, 1);
    for (City i : result) {
        cout << "������: " << i.name << " λ��: (" << i.x << ", " << i.y << ")\n";
    }


    //���½ڵ�����: ����һ��Ľڵ� ����һ�������ڵĽڵ�
    clist.updateName("Beijing", "Peking");
    clist.updateName("Hongkong", "Xianggang");

    clist.printList();

    //���½ڵ�����: ����һ��Ľڵ� ����һ�������ڵĽڵ�
    clist.updateLocation("London", { 200.0, -10.0 });
    clist.updateLocation("Hongkong", { 1,1 });

    clist.printList();

    //������нڵ�, �ٴ�ӡһ��
    clist.clearList();
    clist.printList();


    //���Ų��볬�����鳤�ȵĽڵ�
    for (int i = 0; i < 1005; i++) {
        clist.insertList("Beijing", 10.0, 10.0);
    }

    cout << "Success!\n";
    cin.get();
    return 0;

}