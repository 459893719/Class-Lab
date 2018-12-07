/*PCB.h*/
#pragma once
#include <string>
using namespace std;


struct PCB {
    char name[20]; //进程名
    int arrive_time;  //进程到达时间
    int priority;     //优先级
    int need_time;    //进程需要运行的时间
    int use_time;     //进程已运行的总时间
    int cpu_time;     //进程在CPU的时间
};