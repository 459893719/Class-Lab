#pragma once
#include <string>
#include <vector>


struct Location {
    double x;
    double y;
    Location(){}
    Location(double x, double y) : x(x), y(y) {};
};

struct City {
    std::string name;
    double x;
    double y;
    City(std::string name, double x, double y) :name(name), x(x), y(y) {}
    City(){}
};


struct ListNode {
    City data;
    ListNode* next;
    ListNode(std::string name, double x, double y): data(City(name, x, y)), next(0) {}
    ListNode() {}
};

class CityLinkList {
private:
    int length;
    ListNode* head;

    ListNode* searchByName(std::string name);
public:
    CityLinkList();

    //将该表内容删除
    ~CityLinkList();

    //将该表内容清空
    void clearList();

    //实现节点插入
    bool insertList(std::string name, double x, double y);

    //实现节点删除
    bool deleteByName(std::string name);

    //实现节点更新
    bool updateName(std::string name, std::string newName);
    bool updateLocation(std::string name, Location newLocation);

    //实现节点查找
    Location searchLocation(std::string cityname);
    std::vector<City> searchCityNearby(Location location, double distance);

    //打印链表内容
    void printList();

    //返回链表的长度
    int getLength() {
        return length;
    }
};