/*PCB.h*/
#pragma once
#include <string>
using namespace std;


struct PCB {
    char name[20]; //������
    int arrive_time;  //���̵���ʱ��
    int priority;     //���ȼ�
    int need_time;    //������Ҫ���е�ʱ��
    int use_time;     //���������е���ʱ��
    int cpu_time;     //������CPU��ʱ��
};