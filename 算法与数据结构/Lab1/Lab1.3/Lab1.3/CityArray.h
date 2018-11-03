#pragma once
#include <string>
#include <vector>

//错误类型的定义

const int MAXSIZE = 1000;

struct Location {
    double x;
    double y;
    Location() {}
    Location(double x, double y) : x(x), y(y) {};
};

struct City {
    std::string name;
    double x;
    double y;
    City(std::string name, double x, double y) :name(name), x(x), y(y) {}
    City() {}
};


class CityArray {
private:
    int length;
    City* element;
    int size;

    int searchByName(std::string name);
public:
    CityArray();

    //将该表内容删除
    ~CityArray();

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