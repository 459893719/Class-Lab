#include "ParkManager.h"


ParkManager::ParkManager(): limit(2) {}

ParkManager::ParkManager(int limit) : limit(limit) {};



void ParkManager::inputRecv(LinkQueue<Request>& q) {

    std::cout << "请输入所有的指令: \n";
    while (1) {
        Request req;
        std::cin >> req.request >> req.plateNum >> req.time;

        if (req.request == 'E') {
            return;
        }
        //输入错误检测
        if (req.request != 'A' && req.request != 'D') {
            std::cout << "输入错误!\n";
            continue;
        }

        
        q.push(req);
    }
}

int ParkManager::costCalculate(Car car) {
    //计费规则: 从0元开始, 每停在停车场1小时, 增加4元
    return 4 * (car.end - car.transform);
}

void ParkManager::execRequest(Request req) {
    if (req.request == 'A') {
        Car car;
        car.plate = req.plateNum;
        car.start = currentTime;
        car.transform = car.start;
        //car.isParking = false;

        std::cout << "车" << req.plateNum << "驶入了停车场, ";

        if (limit <= parkinglot.getLength()) {
            //停车场已满, 把车放到便道中
            road.push(car);
            std::cout << "哎呀, 停车场已经满了, 所以它只能停在便道上。\n";
        }
        else {
            parkinglot.push(car);
            parkingcarset.insert(car.plate);
            car.transform = currentTime;
            // car.isParking = true;

            std::cout << "它顺利地停在了停车场内!\n";
        }
    }
    else if (req.request == 'D') {
        //查找车是否在停车场中
        //在set中调用find()函数, 如果找不到, 返回end()

        std::cout << "车" << req.plateNum << "想要离开停车场, ";

        std::set<std::string>::iterator iter;
        if ((iter = parkingcarset.find(req.plateNum)) != parkingcarset.end()) {
            //要找的车停在停车场中
            std::cout << "它停在了停车场内。\n";
            while (1) {
                //执行车离开的操作

                if (parkinglot.getTop().plate == req.plateNum) {
                    //此时要离开的车前面没有其他车的堵塞, 准备离开
                    Car leavingcar = parkinglot.getTop();
                    leavingcar.end = currentTime;

                    //计费
                    int cost = costCalculate(leavingcar);
                    std::cout << "这辆车准备离开了, 一共花费了" << cost << "元, 欢迎再次光临!\n";
                    //离开
                    parkinglot.pop();

                    break;
                }
                else {
                    tempparking.push(parkinglot.getTop());
                    std::cout << "但是现在停车场门前的是车" << parkinglot.getTop().plate << ", 这辆车要开到其他地方了。\n";
                    parkinglot.pop();
                }

            }

            //将其他移出停车场的车放回去
            while (!tempparking.isEmpty()) {
                //前面还有车挡着, 把它放到暂存的地方(另一个栈)
                parkinglot.push(tempparking.getTop());
                std::cout << "车" << tempparking.getTop().plate << "回到了停车场内。\n";
                tempparking.pop();
            }

            //有一辆车离开了停车场, 便道的一辆车可以停到停车场中
            if (!road.isEmpty()) {
                Car newcar = road.getFront();
                std::cout << "便道中的车" << newcar.plate << "此时进入停车场内了。\n";
                newcar.transform = currentTime;
                parkinglot.push(newcar);
            }
        }
        else {
            //没找到, 说明在便道中
            std::cout << "它停在了便道上。\n";
            while (1) {
                //执行车离开的操作

                if (road.getFront().plate == req.plateNum) {
                    //此时要离开的车前面没有其他车的堵塞, 准备离开
                    Car leavingcar = road.getFront();
                    leavingcar.end = leavingcar.transform = currentTime;
                      
                    //计费(其实因为题中意思, 只停在便道中的车不收费), 所以一定是0元
                    std::cout << "车" << leavingcar.plate << "准备离开了, 但由于它并没有进入停车场内, 所以不需要花钱, 欢迎再次光临!\n";
                    //离开
                    road.pop();
                    break;
                }
                else {
                    //前面还有车挡着, 把它挪到队尾
                    road.push(road.getFront());
                    std::cout << "但是现在便道的最前面是车" << road.getFront().plate << ", 这辆车要到便道最后了。\n";
                    road.pop();
                }

            }
        }
    }
}


void ParkManager::parkManage() {
    LinkQueue<Request> reqQueue;
    currentTime = 1;

    //接收用户的所有输入
    inputRecv(reqQueue);
    std::cout << "\n停车场开始营业啦!";
    //开始模拟
    while (!reqQueue.isEmpty()) {
        bool isIdle = false;
        std::cout << "\n第" << currentTime << "小时:\n";
        Request firstReq = reqQueue.getFront();
        if (currentTime == firstReq.time) {
            execRequest(firstReq);
            reqQueue.pop();
            isIdle = true;
        }
        if (!isIdle) {
            std::cout << "什么都没有发生...\n";
        }
        currentTime++;
    }

}