#pragma once
#include "PCB.h"
#include "LinkQueue.h"
/*ProcessSchedule.h*/
#include <vector>
#include <iostream>
using namespace std;


class ProcessSchedule {
private:
    vector<PCB> processlist;
    int timeslice;

    LinkQueue<PCB> ready;
    LinkQueue<PCB> finish;
    Node<PCB>* run;

public:
    ProcessSchedule() {}
    void createProcess();

    void printState();
    void printHeading();
    void printProcess(PCB pcb);


    void sched_RR();
    void sched_FIFO();
    void sched_Other();

    Node<PCB>* mostPriority();
};