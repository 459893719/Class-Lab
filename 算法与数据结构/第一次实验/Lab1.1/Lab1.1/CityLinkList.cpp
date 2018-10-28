#include "CityLinkList.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <new>


//���캯��, ����һ���յĳ�������
CityLinkList::CityLinkList() {
    head = new ListNode("", 0, 0);
    length = 0;
}


//��һ���ڵ���뵽�����ͷλ��
//����Ϊ�½ڵ�����ּ�λ������
bool CityLinkList::insertList(std::string name, double x, double y) {
    ListNode* newnode = new (std::nothrow)ListNode(name, x, y);
    if (newnode == 0) {
        return false;
    }
    newnode->next = head->next;
    head->next = newnode;

    length++;
    return true;
}


//ͨ�����ֲ��ұ��иó��е�λ������
//����ֵΪλ��
//����Ϊ����
Location CityLinkList::searchLocation(std::string cityname) {
    ListNode* p = head->next;

    while (p) {
        if (p->data.name == cityname) {
            return Location(p->data.x, p->data.y);
        }

        p = p->next;
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
std::vector<City> CityLinkList::searchCityNearby(Location location, double distance) {

    //ʹ��vector������������ĳ���, �����������
    std::vector<City> result;
    ListNode* p = head->next;
    while (p) {
        Location location1 = Location(p->data.x, p->data.y);
        double pdistance = dis(location, location1);
        if (pdistance <= distance) {
            result.push_back(p->data);
        }

        p = p->next;
    }

    if (result.size() == 0) {
        std::cout << "No cities found.\n";
    }
    else {
        std::cout << "You've found " << result.size() << " cities.\n";
    }
        

    return result;

}
bool CityLinkList::deleteByName(std::string name) {
    //���ҵ����ֶ�Ӧ�ĳ��е�ǰ���ڵ�

    ListNode* p = head;

    while (p->next) {
        if (p->next->data.name == name) {
            break;
        }
        p = p->next;
    }

    //���p->nextΪNULL, ˵���Ҳ������ֶ�Ӧ�ĳ���, �׳��쳣
    if (p->next == 0) {
        std::cout << "Error: Cannot find the city " << name << " when deleting the node.\n";
        return false;
    }

    //ɾ���ڵ�
    ListNode* deletenode = p->next;
    p->next = deletenode->next;
    delete deletenode;


    length--;
    std::cout << "Successfully delete the city " << name << ".\n";
    return true;
}


//�������������ҽڵ�λ��
//����ֵΪ�ڵ�ָ��, ����Ҳ����ͷ���NULL
ListNode* CityLinkList::searchByName(std::string name) {
    ListNode* p = head->next;

    while (p) {
        if (p->data.name == name) {
            return p;
        }

        p = p->next;
    }

    return 0;
}


//����һ���ڵ������
//����Ϊԭ�Ƚڵ�ĳ��������³�����
bool CityLinkList::updateName(std::string name, std::string newName) {

    ListNode* updateNode = searchByName(name);

    if (updateNode == 0) {
        std::cout << "Error: Cannot find the city " << name << " when updating the node.\n";
        return false;
    }

    updateNode->data.name = newName;
    std::cout << "Successfully update the name of " << name << ".\n";
    return true;
}



//����һ���ڵ��λ������
//����Ϊԭ�Ƚڵ�ĳ��������³���λ��
bool CityLinkList::updateLocation(std::string name, Location newLocation) {
    ListNode* updateNode = searchByName(name);

    if (updateNode == 0) {
        std::cout << "Error: Cannot find the city " << name << " when updating the node.\n";
        return false;
    }

    updateNode->data.x = newLocation.x;
    updateNode->data.y = newLocation.y;
    std::cout << "Successfully update the location of " << name << ".\n";
    return true;
}



void CityLinkList::printList() {
    if (head->next == 0) {
        //����û��Ԫ��
        std::cout << "\n�ñ���û�нڵ�.\n\n";
        return;
    }
    std::cout << "\n����������" << length << "��Ԫ�ء�\n";
    ListNode* p = head->next;
    while (p) {
        std::cout << "������: " << p->data.name << " λ��: (" << p->data.x << ", " << p->data.y << ")\n";

        p = p->next;
    }
    std::cout << "\n";
}


void CityLinkList::clearList() {
    ListNode *p1, *p2;

    p1 = head->next;

    while (p1) {
        p2 = p1->next;
        delete p1;
        p1 = p2;
    }

    head->next = 0;
    length = 0;
    std::cout << "Successfully clear the citylist.\n";
}

//������ռ��ͷų���
CityLinkList::~CityLinkList() {

    ListNode *p1, *p2;

    p1 = head;

    while (p1) {
        p2 = p1->next;
        delete p1;
        p1 = p2;
    }

}