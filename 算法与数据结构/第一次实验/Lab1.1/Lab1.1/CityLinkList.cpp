#include "CityLinkList.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <new>


//构造函数, 建立一个空的城市链表
CityLinkList::CityLinkList() {
    head = new ListNode("", 0, 0);
    length = 0;
}


//将一个节点插入到链表表头位置
//参数为新节点的名字及位置坐标
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


//通过名字查找表中该城市的位置坐标
//返回值为位置
//参数为姓名
Location CityLinkList::searchLocation(std::string cityname) {
    ListNode* p = head->next;

    while (p) {
        if (p->data.name == cityname) {
            return Location(p->data.x, p->data.y);
        }

        p = p->next;
    }

    //没有找到节点, 返回NULL
    std::cout << "Error: Cannot find the city " << cityname << " when searching the location.\n";
    return { 0,0 };
}


//返回两个点之间的距离
inline double dis(Location loc1, Location loc2) {
    double x1 = loc1.x, x2 = loc2.x, y1 = loc1.y, y2 = loc2.y;
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

//寻找与某位置距离不大于D的所有城市
//返回值为城市数组
//参数为位置, 距离
std::vector<City> CityLinkList::searchCityNearby(Location location, double distance) {

    //使用vector存放满足条件的城市, 相比数组更灵活
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
    //先找到名字对应的城市的前驱节点

    ListNode* p = head;

    while (p->next) {
        if (p->next->data.name == name) {
            break;
        }
        p = p->next;
    }

    //如果p->next为NULL, 说明找不到名字对应的城市, 抛出异常
    if (p->next == 0) {
        std::cout << "Error: Cannot find the city " << name << " when deleting the node.\n";
        return false;
    }

    //删除节点
    ListNode* deletenode = p->next;
    p->next = deletenode->next;
    delete deletenode;


    length--;
    std::cout << "Successfully delete the city " << name << ".\n";
    return true;
}


//根据名字来查找节点位置
//返回值为节点指针, 如果找不到就返回NULL
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


//更新一个节点的名字
//参数为原先节点的城市名和新城市名
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



//更新一个节点的位置坐标
//参数为原先节点的城市名和新城市位置
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
        //表中没有元素
        std::cout << "\n该表中没有节点.\n\n";
        return;
    }
    std::cout << "\n该链表中有" << length << "个元素。\n";
    ListNode* p = head->next;
    while (p) {
        std::cout << "城市名: " << p->data.name << " 位置: (" << p->data.x << ", " << p->data.y << ")\n";

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

//将链表空间释放出来
CityLinkList::~CityLinkList() {

    ListNode *p1, *p2;

    p1 = head;

    while (p1) {
        p2 = p1->next;
        delete p1;
        p1 = p2;
    }

}