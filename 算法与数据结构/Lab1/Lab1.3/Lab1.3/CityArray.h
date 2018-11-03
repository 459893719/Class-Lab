#pragma once
#include <string>
#include <vector>

//�������͵Ķ���

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

    //���ñ�����ɾ��
    ~CityArray();

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