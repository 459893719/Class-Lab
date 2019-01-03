#include "Customer.h"
#include <iostream>
#include <cstdlib>
#include "state.h"


Customer::Customer(int customer_num, int enter_time, int duration_time){
	this->customer_num = customer_num;
	this->enter_time = enter_time;
	this->duration_time = duration_time;
	this->got_num = false;  //初始化时是未取号状态
    this->clothes = rand() % CLOTHES_NUM;
	this->img1 = new IMAGE();
	this->img2 = new IMAGE();
	this->img3 = new IMAGE();
	this->img4 = new IMAGE();
	WaitForSingleObject(this->M_CUSTOM, INFINITE);//P操作，抬起以保护用户将要使用的数据
}

bool Customer::Entered() {
	return (enter_time <= Time);
}

int Customer::Get_serve(int server_num, int start_time) {
	//在顾客开始接受服务时，记录为他服务的柜台号及开始服务的时间。
	this->server_num = server_num;
	this->start_time = start_time;
	return this->duration_time;
}

void Customer::End_serve() {
	//结束服务时，记录结束服务的时间。
	this->end_time = Time;
	NUM_DONE++;
	now_clone--;
	ReleaseSemaphore(this->M_CUSTOM, 1, NULL);//V操作，用户相关数据使用结束，同步结束
}


void Get_num(Customer *this_customer)//取号过程
{ 
	if (WaitForSingleObject(M_GET_NUM, INFINITE) == WAIT_OBJECT_0)//P操作
	{
        anime1(this_customer->img1, this_customer->clothes); //取号动画
		this_customer->num = NUM;             //取号
		this_customer->got_num = true;        //是否取到号的标志设为true
		NUM++;								  //“下一个即将取到的号”自增
        ReleaseSemaphore(M_GET_NUM, 1, NULL); //V操作
	}
	anime2(this_customer->img2, this_customer->clothes);
	waitlist.push(this_customer);             //加入等待柜台服务队列，等待叫号
}

