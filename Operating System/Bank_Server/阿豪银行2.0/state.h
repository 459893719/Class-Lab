#pragma once
#include <Windows.h>
#include <queue>
#include "Customer.h"
extern int NUM;         //����һ������ȡ���ġ�����
extern int NUM_CUSTOM;  //�ܹ˿���
extern int NUM_DONE;    //����ɵĹ˿���
extern int Time;        //��ǰʱ����
extern int now_clone;   //�����ж�a���������Ϣ

extern HANDLE M_GET_NUM;  //�˿�ȡ���ź���
extern HANDLE M_CALL_NUM; //��̨�к��ź���

extern std::queue<Customer> customers_queue;  //Ԥ���ɹ˿Ͷ���
extern std::queue<Customer*> a;               //�˿Ͷ��п�¡�����ڲ�����
extern std::queue<Customer*> waitlist;        //�ȴ�����Ĺ˿Ͷ���

