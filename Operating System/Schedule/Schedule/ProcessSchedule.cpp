/*ProcessSchedule.cpp*/
#include "ProcessSchedule.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

/*
    vector<PCB> processlist;
    int timeslice;

    LinkQueue<PCB> ready;
    LinkQueue<PCB> finish;
    Node<PCB>* run;
*/

bool cmp1(PCB a, PCB b) {

    //排序规则: 先按照到达时间升序, 再按照优先级降序
    if (a.arrive_time != b.arrive_time) {
        return a.arrive_time < b.arrive_time;
    }
    else {
        return a.priority > b.priority;
    }
}

void ProcessSchedule::createProcess() {
    //让用户输入进程
    int num;
    cout << "请输入时间片长度: ";
    cin >> timeslice;
    cout << "请输入进程数: ";
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "请输入进程" << i + 1 << "的相关信息(进程名 优先级 到达时间 需要运行时间)\n";
        PCB pcb;
        cin >> pcb.name >> pcb.priority >> pcb.arrive_time >> pcb.need_time;
        pcb.use_time = 0;
        pcb.cpu_time = 0;
        processlist.push_back(pcb);
    }
}

void ProcessSchedule::printHeading() {
    cout << "进程名    优先级    到达时间  需要时间  已运行时间\n";
}
void ProcessSchedule::printProcess(PCB pcb) {
    printf("%-10s%-10d%-10d%-10d%-10d\n", pcb.name, pcb.priority, pcb.arrive_time, pcb.need_time, pcb.use_time);
}

void ProcessSchedule::printState() {
    //打印此时进程执行的状况
    //分别打印run, ready队列和finish队列的情况
    if (run == nullptr) {
        cout << "没有进程在执行.\n";
    }
    else {
        cout << "正在执行的进程:\n";
        printHeading();
        printProcess(run->data);
    }

    cout << endl;
    //ready
    if (ready.isEmpty()) {
        cout << "没有进程在就绪状态.\n";
    }
    else {
        cout << "正在就绪的进程:\n";
        printHeading();
        Node<PCB>* p = ready.front->next;
        while (p) {
            printProcess(p->data);
            p = p->next;
        }
    }

    cout << endl;
    //finish
    if (finish.isEmpty()) {
        cout << "没有进程完成.\n";
    }
    else {
        cout << "执行完成的进程:\n";
        printHeading();
        Node<PCB>* p = finish.front->next;
        while (p) {
            printProcess(p->data);
            p = p->next;
        }
    }
    cout << endl;
}

void ProcessSchedule::sched_FIFO() {
    //先将进程数组进行排序(按照到达时间和优先级)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive以后的进程是还未到达的进程
    while (counter < processlist.size()) {

        //先将到达的进程放到ready队列中
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //如果这个进程执行完成了, 就把这个进程放到finish队列, 删除ready相应进程
        //并选择一个ready队列新进程
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //这时候run指向的进程执行完成, 切换进程
            finish.push(run->data);
            ready.pop();
            counter++;
        }
            run = (ready.front)->next;

        //执行进程
        if (run != nullptr) {
            run->data.use_time++;
           
        }
        
        system("cls");
        cout << "系统时间: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "进程执行完成!\n";
    system("pause");
}

void ProcessSchedule::sched_RR() {

    //先将进程数组进行排序(按照到达时间和优先级)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive以后的进程是还未到达的进程
    while (counter < processlist.size()) {

        //先将到达的进程放到ready队列中
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //如果这个进程执行完成了, 就把这个进程放到finish队列, 删除ready相应进程
        //并选择一个ready队列新进程
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //这时候run指向的进程执行完成, 切换进程
            finish.push(run->data);
            ready.pop();
            counter++;
            run = (ready.front)->next;
        }
        else {
            //有两种情况: run为NULL, 或者run指向的进程还没有执行完

            //时间片结束, 如果run不是NULL, 就切换进程
            if (run!= nullptr && run->data.cpu_time == timeslice) {
               // if (run != nullptr) {
                    run->data.cpu_time = 0;
                    PCB temp;
                    temp = ready.getFront();
                    ready.pop();
                    ready.push(temp);
                //}
                run = (ready.front)->next;
            }
            else if (run == nullptr) {
                run = (ready.front)->next;
            }
        }

        //执行进程
        if (run != nullptr) {
            run->data.use_time++;
            run->data.cpu_time++;
        }
        system("cls");
        cout << "系统时间: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "进程执行完成!\n";
    system("pause");
}

void ProcessSchedule::sched_Other() {
    //先将进程数组进行排序(按照到达时间和优先级)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive以后的进程是还未到达的进程
    while (counter < processlist.size()) {

        //先将到达的进程放到ready队列中
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //当切换进程时, run指针指向优先级最高的进程

        //如果这个进程执行完成了, 就把这个进程放到finish队列, 删除ready相应进程
        //并选择一个ready队列新进程
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //这时候run指向的进程执行完成, 切换进程
            finish.push(run->data);
            
            Node<PCB>* p = ready.front;
            while (p) {
                if (p->next == run) {
                    break;
                }
                p = p->next;
            }

            p->next = run->next;
            delete run;

            counter++;
            run = mostPriority();
        }
        else {
            //有两种情况: run为NULL, 或者run指向的进程还没有执行完

            //时间片结束, 如果run不是NULL, 将该进程的优先数减2, 并切换进程
            if (run != nullptr && run->data.cpu_time == timeslice) {
                run->data.cpu_time = 0;
                run->data.priority -= 2;
                PCB temp;
                temp = ready.getFront();
                ready.pop();
                ready.push(temp);
                run = mostPriority();
            }
            else if (run == nullptr) {
                run = mostPriority();
            }
        }

        //执行进程
        if (run != nullptr) {
            run->data.use_time++;
            run->data.cpu_time++;
        }
        system("cls");
        cout << "系统时间: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "进程执行完成!\n";
    system("pause");
}

Node<PCB>* ProcessSchedule::mostPriority() {
    //寻找ready队列中优先级最高的进程

    Node<PCB>* p = ready.front->next;
    Node<PCB>* newrun = p;
    while (p) {
        if (p->data.priority >= newrun->data.priority) {
            newrun = p;
        }
        p = p->next;
    }
    return newrun;
}