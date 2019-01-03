#include "Server.h"
#include "state.h"



Server::Server(int server_num){
	this->server_num = server_num;
}

void Server::serve(int duration) {
	Sleep(duration * 1000);
	custom->End_serve();
	Call_num(this);
}

void Call_num(Server* this_server) {
	while (1) {
		while (NUM_DONE < NUM_CUSTOM) {
			if (WaitForSingleObject(M_CALL_NUM, INFINITE) == WAIT_OBJECT_0) { //P������ȡ�ýк�������ֹ������̨ͬʱ�кţ�
				if (waitlist.size() != 0) {                                   //��û�еȴ��˿���������
					this_server->custom = waitlist.front(); 
					waitlist.pop();
					//ȡ���ȴ����е�һ�����з���
					ReleaseSemaphore(M_CALL_NUM, 1, NULL); //V����������������������̨�к�
                    char s[20];
					sprintf(s, "%3d", this_server->custom->getNum());
					outtextxy(CELL * (6 * this_server->server_num - 2), CELL + 9, s);
                    anime3(this_server->custom->img3, this_server->server_num, this_server->custom->clothes);
                    
					int duration;
					duration = this_server->custom->Get_serve(this_server->server_num, Time);//�ù˿ͷ����̨Ϊ��ǰ��̨
                    Sleep(duration * 1000);
					//ִ�з���
                    sprintf(s, "      ");
                    outtextxy(CELL * (6 * this_server->server_num - 2), CELL + 9, s);
                    this_server->custom->End_serve();
                    anime4(this_server->custom->img4, this_server->server_num, this_server->custom->clothes);                }
				else {
					ReleaseSemaphore(M_CALL_NUM, 1, NULL);
				}
			}
		}
	}
}