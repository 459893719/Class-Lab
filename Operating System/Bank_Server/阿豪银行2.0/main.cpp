#include <iostream>
#include <cstdlib>
#include <mutex>
#include "Server.h"
#include "Customer.h"
#include "Anime.h"
#include "state.h"

#define N 4 //��̨��
#define T 1000 //ʱ������
#define random(x) (rand()%x)

int now;

void timeShow(char *s, int minutes) {
	int hour = (8 + minutes / 60) % 24;
	int min = minutes % 60;
    sprintf(s, "%2d:%d%d", hour, min/10, min%10);
}

void Message() {
	while (true) {
		char s[10];
		char s1[20];
		char s2[20];
        char s3[30];
        timeShow(s, Time);
		outtextxy(CELL * 12 + 10, 12 * CELL + 10, s);
		sprintf(s1, "�ȴ�������: %d", (int)waitlist.size());
		outtextxy(0, 0, s1);

		sprintf(s2, "%3d", NUM);
		outtextxy(CELL * 3 + 8, 12 * CELL + 10, s2);

        sprintf(s3, "����ɷ�������: %d", NUM_DONE);
        outtextxy(200, 0, s3);

		Sleep(500);
	}
}

void Clock() {
	while (true) {
		Sleep(1000);
		Time++;
	}
}

HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

void CustomerComing() {
	int i = 1;          //�˿����
	int n = 0;          //���������
	int t = Time;       //�˿͵��������ſ�ʱ��
	int d;              //�˿���Ҫ�ķ���ʱ��

	while (Time == 0);  //������ʱ��Ϊ0ʱ����˿�

	while (1) { //��ͣ����
		while (NUM_CUSTOM - NUM_DONE < 30) { //����Ԥ���ɹ˿����Ϊ30����
			
			srand(n++);
			t = t + random(10) + 1;
			srand(t);
			d = random(10) + 1;
			//����ʱ�������ʱ�����ȡ��

			customers_queue.push(Customer(i, t, d)); //ѹ��˿Ͷ���
			WaitForSingleObject(hMutex, INFINITE);   //P������ȡ��a���У��˿Ͷ��п�¡���ķ���Ȩ
			a.push(&customers_queue.back());         //���˿Ͷ����½����Ԫ��ȡ�ò�ѹ�롣
			ReleaseMutex(hMutex);                    //V�������ͷ�a���еķ���Ȩ��
			i++;                   //�˿��������
			NUM_CUSTOM++;          //�����˿�����
		}
	}
}



int main() {

    initgraph(800, 629);   // ������ͼ���ڣ���СΪ 800x629 ����
    setbkcolor(RGB(231, 220, 216));
    settextcolor(BLACK);
    cleardevice();
    IMAGE img;
    loadimage(&img, "./images/background.jpg");
    putimage(0, 0, &img);

	HANDLE clock_thread;
	DWORD clock_threadID;
	//clock_thread��ʱ���߳�
	clock_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Clock, NULL, 0, &clock_threadID);//��ʼʱ�Ӻ���

	HANDLE message_thread;
	DWORD message_threadID;
	//clock_thread��ʱ���߳�
	message_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Message, NULL, 0, &message_threadID);//��ʼʱ�Ӻ���

																								  //��̨�߳�����
	HANDLE server_thread[N];
	DWORD server_threadID[N];
	//servers�Ƕ�������
	Server **servers;
	servers = new Server*[N];
	for (int i = 0; i < N; i++)//�����й�̨��ʼ����
	{
		*(servers + i) = new Server(i+1);//��ʼ����̨
		Server* thisserver = *(servers + i);
		//һ����̨�̶߳�Ӧһ����̨����
		//��̨�߳�ִ��Call_num����, ���кź���
		server_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Call_num, *(servers + i), 0, &server_threadID[i]);
	}



	HANDLE Come_thread;
	DWORD Come_threadID;
	Come_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CustomerComing, 0, 0, &Come_threadID);//��ʼʱ�Ӻ���
	//��ʼ���ɹ˿�

	std::vector<HANDLE> custom_thread;   
	std::vector<DWORD*> custom_threadID;
	//�洢ÿһ���˿��̵߳���Ϣ
	int forID = 0;           //���ڷ���vector
	while (a.size() != 10);  //������ʮ���˿��ڶ�����ʱ����ʼ�����·�����
	while (1) {
		while (!customers_queue.empty()) {
			WaitForSingleObject(hMutex, INFINITE);        //P������ȡ�ö�a���еķ���Ȩ
			if (!a.empty()&&a.front()->Entered()) {       //��a���в��գ��ҵ�һ��Ԫ���ѵ��
				custom_threadID.push_back(new DWORD);      
				custom_thread.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_num, a.front(), 0, custom_threadID[forID]));
				//������Ӧ�˿��̣߳���ʼȡ�š�

				customers_queue.pop();  //�˿Ͷ��е���
				a.pop();                //��¡���е���
				forID++;
			}
			ReleaseMutex(hMutex);                         //V�������ͷŶ�a���еķ���Ȩ
		}
	}



	//system("pause");
	return 0;
}

