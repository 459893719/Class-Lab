#pragma once
#include <stack>
#include <queue>
#include <set>
#include "ArrayStack.h"
#include "LinkQueue.h"
#include "Car.h"

struct Request {
    char request;
    std::string plateNum;
    int time;
    Request() {}
};

template<typename T>
class ArrayStack;
template<typename T>
class LinkQueue;

class ParkManager {
private:
    ArrayStack<Car> parkinglot;
    LinkQueue<Car> road;
    ArrayStack<Car> tempparking;
    std::set<std::string> parkingcarset;   //存储在停车场中的车辆车牌号, 用于之后的查找
    int currentTime;
    int limit;

public:
    ParkManager();
    ParkManager(int limit);

    void parkManage();

    void inputRecv(LinkQueue<Request>& q);

    void execRequest(Request req);

    int costCalculate(Car car);
};