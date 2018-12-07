/*main.cpp*/
#include "ProcessSchedule.h"
using namespace std;


int main() {
    ProcessSchedule ps;
    ps.createProcess();
    system("cls");
    printf("\
1 -------- �ȵ��ȷ���(FIFO)\n\
2 -------- ��ת����(RR)\n\
3 -------- ��ʱ����(��̬���ȼ�)\n");
    getchar();
    char ch = getchar();

    switch (ch) {
    case '1': {
        ps.sched_FIFO();
        break;
    }
    case '2': {
        ps.sched_RR();
        break;
    }
    case '3': {
        ps.sched_Other();
        break;
    }
    }

    return 0;
}