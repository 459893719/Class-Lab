#include <Windows.h>
#include <queue>
#include "Customer.h"


 int NUM = 1;          //号码
 int NUM_CUSTOM = 0;   //总顾客数
 int NUM_DONE = 0;     //已完成的顾客数
 int Time = 0;         //当前时刻数
 int now_clone = 0;    //用于判断a队列相关信息

 HANDLE M_GET_NUM = CreateSemaphore(NULL, 1, 1, NULL);  //顾客取号信号量
 HANDLE M_CALL_NUM = CreateSemaphore(NULL, 1, 1, NULL); //柜台叫号信号量

 std::queue<Customer> customers_queue;  //预生成顾客队列
 std::queue<Customer*> a;               //顾客队列克隆（用于操作）
 std::queue<Customer*> waitlist;        //等待服务的顾客队列