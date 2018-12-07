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

    //�������: �Ȱ��յ���ʱ������, �ٰ������ȼ�����
    if (a.arrive_time != b.arrive_time) {
        return a.arrive_time < b.arrive_time;
    }
    else {
        return a.priority > b.priority;
    }
}

void ProcessSchedule::createProcess() {
    //���û��������
    int num;
    cout << "������ʱ��Ƭ����: ";
    cin >> timeslice;
    cout << "�����������: ";
    cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "���������" << i + 1 << "�������Ϣ(������ ���ȼ� ����ʱ�� ��Ҫ����ʱ��)\n";
        PCB pcb;
        cin >> pcb.name >> pcb.priority >> pcb.arrive_time >> pcb.need_time;
        pcb.use_time = 0;
        pcb.cpu_time = 0;
        processlist.push_back(pcb);
    }
}

void ProcessSchedule::printHeading() {
    cout << "������    ���ȼ�    ����ʱ��  ��Ҫʱ��  ������ʱ��\n";
}
void ProcessSchedule::printProcess(PCB pcb) {
    printf("%-10s%-10d%-10d%-10d%-10d\n", pcb.name, pcb.priority, pcb.arrive_time, pcb.need_time, pcb.use_time);
}

void ProcessSchedule::printState() {
    //��ӡ��ʱ����ִ�е�״��
    //�ֱ��ӡrun, ready���к�finish���е����
    if (run == nullptr) {
        cout << "û�н�����ִ��.\n";
    }
    else {
        cout << "����ִ�еĽ���:\n";
        printHeading();
        printProcess(run->data);
    }

    cout << endl;
    //ready
    if (ready.isEmpty()) {
        cout << "û�н����ھ���״̬.\n";
    }
    else {
        cout << "���ھ����Ľ���:\n";
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
        cout << "û�н������.\n";
    }
    else {
        cout << "ִ����ɵĽ���:\n";
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
    //�Ƚ����������������(���յ���ʱ������ȼ�)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive�Ժ�Ľ����ǻ�δ����Ľ���
    while (counter < processlist.size()) {

        //�Ƚ�����Ľ��̷ŵ�ready������
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //����������ִ�������, �Ͱ�������̷ŵ�finish����, ɾ��ready��Ӧ����
        //��ѡ��һ��ready�����½���
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //��ʱ��runָ��Ľ���ִ�����, �л�����
            finish.push(run->data);
            ready.pop();
            counter++;
        }
            run = (ready.front)->next;

        //ִ�н���
        if (run != nullptr) {
            run->data.use_time++;
           
        }
        
        system("cls");
        cout << "ϵͳʱ��: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "����ִ�����!\n";
    system("pause");
}

void ProcessSchedule::sched_RR() {

    //�Ƚ����������������(���յ���ʱ������ȼ�)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive�Ժ�Ľ����ǻ�δ����Ľ���
    while (counter < processlist.size()) {

        //�Ƚ�����Ľ��̷ŵ�ready������
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //����������ִ�������, �Ͱ�������̷ŵ�finish����, ɾ��ready��Ӧ����
        //��ѡ��һ��ready�����½���
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //��ʱ��runָ��Ľ���ִ�����, �л�����
            finish.push(run->data);
            ready.pop();
            counter++;
            run = (ready.front)->next;
        }
        else {
            //���������: runΪNULL, ����runָ��Ľ��̻�û��ִ����

            //ʱ��Ƭ����, ���run����NULL, ���л�����
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

        //ִ�н���
        if (run != nullptr) {
            run->data.use_time++;
            run->data.cpu_time++;
        }
        system("cls");
        cout << "ϵͳʱ��: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "����ִ�����!\n";
    system("pause");
}

void ProcessSchedule::sched_Other() {
    //�Ƚ����������������(���յ���ʱ������ȼ�)
    sort(processlist.begin(), processlist.end(), cmp1);
    int time = 0;
    run = nullptr;
    int counter = 0;
    int not_arrive = 0; //not_arrive�Ժ�Ľ����ǻ�δ����Ľ���
    while (counter < processlist.size()) {

        //�Ƚ�����Ľ��̷ŵ�ready������
        while (not_arrive < processlist.size()) {
            if (processlist[not_arrive].arrive_time == time) {
                ready.push(processlist[not_arrive]);
                not_arrive++;
            }
            else {
                break;
            }
        }

        //���л�����ʱ, runָ��ָ�����ȼ���ߵĽ���

        //����������ִ�������, �Ͱ�������̷ŵ�finish����, ɾ��ready��Ӧ����
        //��ѡ��һ��ready�����½���
        if (run != NULL  &&  run->data.need_time == run->data.use_time) {
            //��ʱ��runָ��Ľ���ִ�����, �л�����
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
            //���������: runΪNULL, ����runָ��Ľ��̻�û��ִ����

            //ʱ��Ƭ����, ���run����NULL, ���ý��̵���������2, ���л�����
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

        //ִ�н���
        if (run != nullptr) {
            run->data.use_time++;
            run->data.cpu_time++;
        }
        system("cls");
        cout << "ϵͳʱ��: " << time << endl;
        printState();
        time++;
        system("pause");
    }
    cout << "����ִ�����!\n";
    system("pause");
}

Node<PCB>* ProcessSchedule::mostPriority() {
    //Ѱ��ready���������ȼ���ߵĽ���

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