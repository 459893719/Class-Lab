#include <Windows.h>
#include <queue>
#include "Customer.h"


 int NUM = 1;          //����
 int NUM_CUSTOM = 0;   //�ܹ˿���
 int NUM_DONE = 0;     //����ɵĹ˿���
 int Time = 0;         //��ǰʱ����
 int now_clone = 0;    //�����ж�a���������Ϣ

 HANDLE M_GET_NUM = CreateSemaphore(NULL, 1, 1, NULL);  //�˿�ȡ���ź���
 HANDLE M_CALL_NUM = CreateSemaphore(NULL, 1, 1, NULL); //��̨�к��ź���

 std::queue<Customer> customers_queue;  //Ԥ���ɹ˿Ͷ���
 std::queue<Customer*> a;               //�˿Ͷ��п�¡�����ڲ�����
 std::queue<Customer*> waitlist;        //�ȴ�����Ĺ˿Ͷ���