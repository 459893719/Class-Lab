#include <iostream>
#include <cstdio>
#include "CityArray.h"
using namespace std;



int main() {
    CityArray clist;
    
    //插入六个节点并打印一次
    clist.insertList("Beijing", 10.0, 10.0);
    clist.insertList("London", 100.0, -10.0);
    clist.insertList("Shanghai", 30.0, 30.0);
    clist.insertList("Chongqing", 15.0, 15.0);
    clist.insertList("Tokyo", -390.0, 400.0);
    clist.insertList("Yokohama", -400.0, 410.0);

    clist.printList();


    //四个删除操作分别是删除表第一个节点, 表尾节点, 一般节点, 一个不存在的节点, 最后打印一次
    clist.deleteByName("Yokohama");
    clist.deleteByName("Beijing");
    clist.deleteByName("Tokyo");
    clist.deleteByName("Qingdao");

    clist.printList();

    clist.insertList("Yokohama", -400.0, 410.0);
    clist.insertList("Beijing", 10.0, 10.0);

    //找一个表中城市的坐标, 再找一个不存在的城市坐标
    Location loc = clist.searchLocation("Beijing");
    cout << loc.x << " " << loc.y << "\n";
    Location loc1 = clist.searchLocation("Chengdu");
    cout << loc1.x << " " << loc1.y << "\n";


    //先正常地找一下某个位置附近的城市, 再找一个位置附近没有城市的情况
    vector<City> result = clist.searchCityNearby({ 0,0 }, 90);
    for (City i : result) {
        cout << "城市名: " << i.name << " 位置: (" << i.x << ", " << i.y << ")\n";
    }

    result = clist.searchCityNearby({ 0,0 }, 1);
    for (City i : result) {
        cout << "城市名: " << i.name << " 位置: (" << i.x << ", " << i.y << ")\n";
    }


    //更新节点名字: 更新一般的节点 更新一个不存在的节点
    clist.updateName("Beijing", "Peking");
    clist.updateName("Hongkong", "Xianggang");

    clist.printList();

    //更新节点名字: 更新一般的节点 更新一个不存在的节点
    clist.updateLocation("London", { 200.0, -10.0 });
    clist.updateLocation("Hongkong", { 1,1 });

    clist.printList();

    //清空所有节点, 再打印一遍
    clist.clearList();
    clist.printList();


    //试着插入超过数组长度的节点
    for (int i = 0; i < 1005; i++) {
        clist.insertList("Beijing", 10.0, 10.0);
    }

    cout << "Success!\n";
    cin.get();
    return 0;

}