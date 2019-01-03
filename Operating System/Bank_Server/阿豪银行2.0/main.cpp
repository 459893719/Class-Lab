#include <iostream>
#include <cstdlib>
#include <mutex>
#include "Server.h"
#include "Customer.h"
#include "Anime.h"
#include "state.h"

#define N 4 //柜台数
#define T 1000 //时钟周期
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
		sprintf(s1, "等待室人数: %d", (int)waitlist.size());
		outtextxy(0, 0, s1);

		sprintf(s2, "%3d", NUM);
		outtextxy(CELL * 3 + 8, 12 * CELL + 10, s2);

        sprintf(s3, "已完成服务人数: %d", NUM_DONE);
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
	int i = 1;          //顾客序号
	int n = 0;          //随机种子用
	int t = Time;       //顾客到达银行门口时间
	int d;              //顾客需要的服务时间

	while (Time == 0);  //避免在时间为0时进入顾客

	while (1) { //不停生成
		while (NUM_CUSTOM - NUM_DONE < 30) { //限制预生成顾客最大为30名。
			
			srand(n++);
			t = t + random(10) + 1;
			srand(t);
			d = random(10) + 1;
			//到达时间与服务时间随机取得

			customers_queue.push(Customer(i, t, d)); //压入顾客队列
			WaitForSingleObject(hMutex, INFINITE);   //P操作，取得a队列（顾客队列克隆）的访问权
			a.push(&customers_queue.back());         //将顾客队列新进入的元素取得并压入。
			ReleaseMutex(hMutex);                    //V操作，释放a队列的访问权。
			i++;                   //顾客序号自增
			NUM_CUSTOM++;          //已来顾客自增
		}
	}
}



int main() {

    initgraph(800, 629);   // 创建绘图窗口，大小为 800x629 像素
    setbkcolor(RGB(231, 220, 216));
    settextcolor(BLACK);
    cleardevice();
    IMAGE img;
    loadimage(&img, "./images/background.jpg");
    putimage(0, 0, &img);

	HANDLE clock_thread;
	DWORD clock_threadID;
	//clock_thread是时钟线程
	clock_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Clock, NULL, 0, &clock_threadID);//开始时钟函数

	HANDLE message_thread;
	DWORD message_threadID;
	//clock_thread是时钟线程
	message_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Message, NULL, 0, &message_threadID);//开始时钟函数

																								  //柜台线程数组
	HANDLE server_thread[N];
	DWORD server_threadID[N];
	//servers是对象数组
	Server **servers;
	servers = new Server*[N];
	for (int i = 0; i < N; i++)//令所有柜台开始服务
	{
		*(servers + i) = new Server(i+1);//初始化柜台
		Server* thisserver = *(servers + i);
		//一个柜台线程对应一个柜台对象
		//柜台线程执行Call_num函数, 即叫号函数
		server_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Call_num, *(servers + i), 0, &server_threadID[i]);
	}



	HANDLE Come_thread;
	DWORD Come_threadID;
	Come_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CustomerComing, 0, 0, &Come_threadID);//开始时钟函数
	//开始生成顾客

	std::vector<HANDLE> custom_thread;   
	std::vector<DWORD*> custom_threadID;
	//存储每一个顾客线程的信息
	int forID = 0;           //用于访问vector
	while (a.size() != 10);  //在已有十个顾客在队列中时，开始进行下方处理。
	while (1) {
		while (!customers_queue.empty()) {
			WaitForSingleObject(hMutex, INFINITE);        //P操作，取得对a队列的访问权
			if (!a.empty()&&a.front()->Entered()) {       //若a队列不空，且第一个元素已到达。
				custom_threadID.push_back(new DWORD);      
				custom_thread.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Get_num, a.front(), 0, custom_threadID[forID]));
				//创建对应顾客线程，开始取号。

				customers_queue.pop();  //顾客队列弹出
				a.pop();                //克隆队列弹出
				forID++;
			}
			ReleaseMutex(hMutex);                         //V操作，释放对a队列的访问权
		}
	}



	//system("pause");
	return 0;
}

