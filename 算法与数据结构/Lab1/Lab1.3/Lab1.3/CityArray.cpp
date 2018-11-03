#include "CityArray.h"
#include <iostream>
#include <cmath>
#include <exception>


//构造函数, 建立一个空的城市链表
CityArray::CityArray() {

    element = new City[MAXSIZE];
    size = MAXSIZE;
    length = 0;
}


//将一个节点插入到表尾位置
//参数为新节点的名字及位置坐标
bool CityArray::insertList(std::string name, double x, double y) {
    if (length >= size) {
        //将原来的数组拷贝到一个更大的数组
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


//通过名字查找表中该城市的位置坐标
//返回值为位置
//参数为姓名
Location CityArray::searchLocation(std::string cityname) {
    int i = 0;

    while (i != length) {
        if (element[i].name == cityname) {
            return Location(element[i].x, element[i].y);
        }

        i++;
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
std::vector<City> CityArray::searchCityNearby(Location location, double distance) {

    //使用vector存放满足条件的城市, 相比数组更灵活
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
    //先找到名字对应的城市的前驱节点

    int i = 0;

    while (i!= length) {
        if (element[i].name == name) {
            break;
        }
        i++;
    }

    //如果p->next为NULL, 说明找不到名字对应的城市, 抛出异常
    if (i == length) {
        std::cout << "Error: Cannot find the city " << name << " when deleting the node.\n";
        return false;
    }

    //删除节点
    for (int j = i + 1; j < length; j++) {
        element[j - 1] = element[j];
    }


    length--;
    std::cout << "Successfully delete the city " << name << ".\n";
    return true;
}


//根据名字来查找节点位置
//返回值为节点指针, 如果找不到就返回NULL
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


//更新一个节点的名字
//参数为原先节点的城市名和新城市名
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



//更新一个节点的位置坐标
//参数为原先节点的城市名和新城市位置
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
        //表中没有元素
        std::cout << "\n该表中没有节点.\n\n";
        return;
    }
    std::cout << "\n该链表中有" << length << "个元素。\n";
    int i = 0;
    while (i!=length) {
        std::cout << "城市名: " << element[i].name << " 位置: (" << element[i].x << ", " << element[i].y << ")\n";

        i++;
    }
    std::cout << "\n";
}


void CityArray::clearList() {
    
    length = 0;
    std::cout << "Successfully clear the citylist.\n";
}

//将链表空间释放出来
CityArray::~CityArray() {

    delete[] element;

}