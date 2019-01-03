#include "Customer.h"
#include <iostream>
#include <cstdlib>
#include "state.h"


Customer::Customer(int customer_num, int enter_time, int duration_time){
	this->customer_num = customer_num;
	this->enter_time = enter_time;
	this->duration_time = duration_time;
	this->got_num = false;  //��ʼ��ʱ��δȡ��״̬
    this->clothes = rand() % CLOTHES_NUM;
	this->img1 = new IMAGE();
	this->img2 = new IMAGE();
	this->img3 = new IMAGE();
	this->img4 = new IMAGE();
	WaitForSingleObject(this->M_CUSTOM, INFINITE);//P������̧���Ա����û���Ҫʹ�õ�����
}

bool Customer::Entered() {
	return (enter_time <= Time);
}

int Customer::Get_serve(int server_num, int start_time) {
	//�ڹ˿Ϳ�ʼ���ܷ���ʱ����¼Ϊ������Ĺ�̨�ż���ʼ�����ʱ�䡣
	this->server_num = server_num;
	this->start_time = start_time;
	return this->duration_time;
}

void Customer::End_serve() {
	//��������ʱ����¼���������ʱ�䡣
	this->end_time = Time;
	NUM_DONE++;
	now_clone--;
	ReleaseSemaphore(this->M_CUSTOM, 1, NULL);//V�������û��������ʹ�ý�����ͬ������
}


void Get_num(Customer *this_customer)//ȡ�Ź���
{ 
	if (WaitForSingleObject(M_GET_NUM, INFINITE) == WAIT_OBJECT_0)//P����
	{
        anime1(this_customer->img1, this_customer->clothes); //ȡ�Ŷ���
		this_customer->num = NUM;             //ȡ��
		this_customer->got_num = true;        //�Ƿ�ȡ���ŵı�־��Ϊtrue
		NUM++;								  //����һ������ȡ���ĺš�����
        ReleaseSemaphore(M_GET_NUM, 1, NULL); //V����
	}
	anime2(this_customer->img2, this_customer->clothes);
	waitlist.push(this_customer);             //����ȴ���̨������У��ȴ��к�
}

