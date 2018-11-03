#include "CityArray.h"
#include <iostream>
#include <cmath>
#include <exception>


//���캯��, ����һ���յĳ�������
CityArray::CityArray() {

    element = new City[MAXSIZE];
    size = MAXSIZE;
    length = 0;
}


//��һ���ڵ���뵽��βλ��
//����Ϊ�½ڵ�����ּ�λ������
bool CityArray::insertList(std::string name, double x, double y) {
    if (length >= size) {
        //��ԭ�������鿽����һ�����������
        City* newelement = new (std::nothrow)City[size + MAXSIZE];

        if (newelement == 0) {
            std::cout << "Error: Overflow when inserting cities.\n";
            return false;
        }

        size += MAXSIZE;
        for (int i = 0; i < length; i++) {
            newelement[i] = element[i];
        }

        delete[] element;

        element = newelement;

        

    }

    element[length++] = City(name, x, y);
    return true;
}


//ͨ�����ֲ��ұ��иó��е�λ������
//����ֵΪλ��
//����Ϊ����
Location CityArray::searchLocation(std::string cityname) {
    int i = 0;

    while (i != length) {
        if (element[i].name == cityname) {
            return Location(element[i].x, element[i].y);
        }

        i++;
    }

    //û���ҵ��ڵ�, ����NULL
    std::cout << "Error: Cannot find the city " << cityname << " when searching the location.\n";
    return { 0,0 };
}


//����������֮��ľ���
inline double dis(Location loc1, Location loc2) {
    double x1 = loc1.x, x2 = loc2.x, y1 = loc1.y, y2 = loc2.y;
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//Ѱ����ĳλ�þ��벻����D�����г���
//����ֵΪ��������
//����Ϊλ��, ����
std::vector<City> CityArray::searchCityNearby(Location location, double distance) {

    //ʹ��vector������������ĳ���, �����������
    std::vector<City> result;
    int i = 0;
    while (i != length) {
        Location location1 = Location(element[i].x, element[i].y);
        double pdistance = dis(location, location1);
        if (pdistance <= distance) {
            result.push_back(element[i]);
        }

        i++;
    }

    if (result.size() == 0) {
        std::cout << "No cities found.\n";
    }
    else {
        std::cout << "You've found " << result.size() << " cities.\n";
    }


    return result;

}
bool CityArray::deleteByName(std::string name) {
    //���ҵ����ֶ�Ӧ�ĳ��е�ǰ���ڵ�

    int i = 0;

    while (i!= length) {
        if (element[i].name == name) {
            break;
        }
        i++;
    }

    //���p->nextΪNULL, ˵���Ҳ������ֶ�Ӧ�ĳ���, �׳��쳣
    if (i == length) {
        std::cout << "Error: Cannot find the city " << name << " when deleting the node.\n";
        return false;
    }

    //ɾ���ڵ�
    for (int j = i + 1; j < length; j++) {
        element[j - 1] = element[j];
    }


    length--;
    std::cout << "Successfully delete the city " << name << ".\n";
    return true;
}


//�������������ҽڵ�λ��
//����ֵΪ�ڵ�ָ��, ����Ҳ����ͷ���NULL
int CityArray::searchByName(std::string name) {
    int i = 0;

    while (i != length) {
        if (element[i].name == name) {
            return i;
        }
        i++;
    }

    return length;
}


//����һ���ڵ������
//����Ϊԭ�Ƚڵ�ĳ��������³�����
bool CityArray::updateName(std::string name, std::string newName) {

    int i = searchByName(name);

    if (i == length) {
        std::cout << "Error: Cannot find the city " << name << " when updating the node.\n";
        return false;
    }

    element[i].name = newName;
    std::cout << "Successfully update the name of " << name << ".\n";
    return true;
}



//����һ���ڵ��λ������
//����Ϊԭ�Ƚڵ�ĳ��������³���λ��
bool CityArray::updateLocation(std::string name, Location newLocation) {
    int i = searchByName(name);

    if (i == length) {
        std::cout << "Error: Cannot find the city " << name << " when updating the node.\n";
        return false;
    }

    element[i].x = newLocation.x;
    element[i].y = newLocation.y;
    std::cout << "Successfully update the location of " << name << ".\n";
    return true;
}



void CityArray::printList() {
    if (length == 0) {
        //����û��Ԫ��
        std::cout << "\n�ñ���û�нڵ�.\n\n";
        return;
    }
    std::cout << "\n����������" << length << "��Ԫ�ء�\n";
    int i = 0;
    while (i!=length) {
        std::cout << "������: " << element[i].name << " λ��: (" << element[i].x << ", " << element[i].y << ")\n";

        i++;
    }
    std::cout << "\n";
}


void CityArray::clearList() {
    
    length = 0;
    std::cout << "Successfully clear the citylist.\n";
}

//������ռ��ͷų���
CityArray::~CityArray() {

    delete[] element;

}