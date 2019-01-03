#pragma once
#include <Windows.h>
#include <queue>
#include "Customer.h"
extern int NUM;         //“下一个将被取到的”号码
extern int NUM_CUSTOM;  //总顾客数
extern int NUM_DONE;    //已完成的顾客数
extern int Time;        //当前时刻数
extern int now_clone;   //用于判断a队列相关信息

extern HANDLE M_GET_NUM;  //顾客取号信号量
extern HANDLE M_CALL_NUM; //柜台叫号信号量

extern std::queue<Customer> customers_queue;  //预生成顾客队列
extern std::queue<Customer*> a;               //顾客队列克隆（用于操作）
extern std::queue<Customer*> waitlist;        //等待服务的顾客队列

