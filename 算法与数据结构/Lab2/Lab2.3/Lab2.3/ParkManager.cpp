#include "ParkManager.h"


ParkManager::ParkManager(): limit(2) {}

ParkManager::ParkManager(int limit) : limit(limit) {};



void ParkManager::inputRecv(LinkQueue<Request>& q) {

    std::cout << "���������е�ָ��: \n";
    while (1) {
        Request req;
        std::cin >> req.request >> req.plateNum >> req.time;

        if (req.request == 'E') {
            return;
        }
        //���������
        if (req.request != 'A' && req.request != 'D') {
            std::cout << "�������!\n";
            continue;
        }

        
        q.push(req);
    }
}

int ParkManager::costCalculate(Car car) {
    //�Ʒѹ���: ��0Ԫ��ʼ, ÿͣ��ͣ����1Сʱ, ����4Ԫ
    return 4 * (car.end - car.transform);
}

void ParkManager::execRequest(Request req) {
    if (req.request == 'A') {
        Car car;
        car.plate = req.plateNum;
        car.start = currentTime;
        car.transform = car.start;
        //car.isParking = false;

        std::cout << "��" << req.plateNum << "ʻ����ͣ����, ";

        if (limit <= parkinglot.getLength()) {
            //ͣ��������, �ѳ��ŵ������
            road.push(car);
            std::cout << "��ѽ, ͣ�����Ѿ�����, ������ֻ��ͣ�ڱ���ϡ�\n";
        }
        else {
            parkinglot.push(car);
            parkingcarset.insert(car.plate);
            car.transform = currentTime;
            // car.isParking = true;

            std::cout << "��˳����ͣ����ͣ������!\n";
        }
    }
    else if (req.request == 'D') {
        //���ҳ��Ƿ���ͣ������
        //��set�е���find()����, ����Ҳ���, ����end()

        std::cout << "��" << req.plateNum << "��Ҫ�뿪ͣ����, ";

        std::set<std::string>::iterator iter;
        if ((iter = parkingcarset.find(req.plateNum)) != parkingcarset.end()) {
            //Ҫ�ҵĳ�ͣ��ͣ������
            std::cout << "��ͣ����ͣ�����ڡ�\n";
            while (1) {
                //ִ�г��뿪�Ĳ���

                if (parkinglot.getTop().plate == req.plateNum) {
                    //��ʱҪ�뿪�ĳ�ǰ��û���������Ķ���, ׼���뿪
                    Car leavingcar = parkinglot.getTop();
                    leavingcar.end = currentTime;

                    //�Ʒ�
                    int cost = costCalculate(leavingcar);
                    std::cout << "������׼���뿪��, һ��������" << cost << "Ԫ, ��ӭ�ٴι���!\n";
                    //�뿪
                    parkinglot.pop();

                    break;
                }
                else {
                    tempparking.push(parkinglot.getTop());
                    std::cout << "��������ͣ������ǰ���ǳ�" << parkinglot.getTop().plate << ", ������Ҫ���������ط��ˡ�\n";
                    parkinglot.pop();
                }

            }

            //�������Ƴ�ͣ�����ĳ��Ż�ȥ
            while (!tempparking.isEmpty()) {
                //ǰ�滹�г�����, �����ŵ��ݴ�ĵط�(��һ��ջ)
                parkinglot.push(tempparking.getTop());
                std::cout << "��" << tempparking.getTop().plate << "�ص���ͣ�����ڡ�\n";
                tempparking.pop();
            }

            //��һ�����뿪��ͣ����, �����һ��������ͣ��ͣ������
            if (!road.isEmpty()) {
                Car newcar = road.getFront();
                std::cout << "����еĳ�" << newcar.plate << "��ʱ����ͣ�������ˡ�\n";
                newcar.transform = currentTime;
                parkinglot.push(newcar);
            }
        }
        else {
            //û�ҵ�, ˵���ڱ����
            std::cout << "��ͣ���˱���ϡ�\n";
            while (1) {
                //ִ�г��뿪�Ĳ���

                if (road.getFront().plate == req.plateNum) {
                    //��ʱҪ�뿪�ĳ�ǰ��û���������Ķ���, ׼���뿪
                    Car leavingcar = road.getFront();
                    leavingcar.end = leavingcar.transform = currentTime;
                      
                    //�Ʒ�(��ʵ��Ϊ������˼, ֻͣ�ڱ���еĳ����շ�), ����һ����0Ԫ
                    std::cout << "��" << leavingcar.plate << "׼���뿪��, ����������û�н���ͣ������, ���Բ���Ҫ��Ǯ, ��ӭ�ٴι���!\n";
                    //�뿪
                    road.pop();
                    break;
                }
                else {
                    //ǰ�滹�г�����, ����Ų����β
                    road.push(road.getFront());
                    std::cout << "�������ڱ������ǰ���ǳ�" << road.getFront().plate << ", ������Ҫ���������ˡ�\n";
                    road.pop();
                }

            }
        }
    }
}


void ParkManager::parkManage() {
    LinkQueue<Request> reqQueue;
    currentTime = 1;

    //�����û�����������
    inputRecv(reqQueue);
    std::cout << "\nͣ������ʼӪҵ��!";
    //��ʼģ��
    while (!reqQueue.isEmpty()) {
        bool isIdle = false;
        std::cout << "\n��" << currentTime << "Сʱ:\n";
        Request firstReq = reqQueue.getFront();
        if (currentTime == firstReq.time) {
            execRequest(firstReq);
            reqQueue.pop();
            isIdle = true;
        }
        if (!isIdle) {
            std::cout << "ʲô��û�з���...\n";
        }
        currentTime++;
    }

}