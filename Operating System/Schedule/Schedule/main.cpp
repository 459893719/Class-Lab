/*main.cpp*/
#include "ProcessSchedule.h"
using namespace std;


int main() {
    ProcessSchedule ps;
    ps.createProcess();
    system("cls");
    printf("\
1 -------- 先到先服务(FIFO)\n\
2 -------- 轮转调度(RR)\n\
3 -------- 分时调度(动态优先级)\n");
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