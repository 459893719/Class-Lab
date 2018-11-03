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

    //���ñ�����ɾ��
    ~CityLinkList();

    //���ñ��������
    void clearList();

    //ʵ�ֽڵ����
    bool insertList(std::string name, double x, double y);

    //ʵ�ֽڵ�ɾ��
    bool deleteByName(std::string name);

    //ʵ�ֽڵ����
    bool updateName(std::string name, std::string newName);
    bool updateLocation(std::string name, Location newLocation);

    //ʵ�ֽڵ����
    Location searchLocation(std::string cityname);
    std::vector<City> searchCityNearby(Location location, double distance);

    //��ӡ��������
    void printList();

    //��������ĳ���
    int getLength() {
        return length;
    }
};