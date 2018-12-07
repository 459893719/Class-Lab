#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
using namespace std;

#define INS_NUM 320     //指令执行总数
#define MAX_PAGES 32    //页的数量, 以及内存最大的帧数
#define INVALID -1      
#define INF 5000

//指令的抽象结构
typedef struct ins {
    int addr;
    int pagenumber;
    int offset;
}ins;

//页面的抽象结构
typedef struct page_struct {
    int frame;
    int usetime;
    int freq;
    int nextusetime;
}ps;

ins CPUSeq[INS_NUM];
//数组下标表示CPU执行的顺序, addr表示这个指令的虚拟地址

ps pagetable[MAX_PAGES];
int frames[MAX_PAGES];


//生成指令执行的随机序列, 并产生页地址流
void generatePages() {
    int i, addr, m;
    srand((int)time(NULL));

    //把生成的随机序列放到CPUSeq的addr中
    for (i = 0; i < INS_NUM; i += 4) {
        m = rand() % INS_NUM;
        m++;
        CPUSeq[i].addr = m;
        m = rand() % (m + 2);
        CPUSeq[i + 1].addr = m;
        CPUSeq[i + 2].addr = m + 1;
        m = rand() % (INS_NUM - m - 2) + m + 2;
        CPUSeq[i + 3].addr = m;
    }

    //生成页地址流
    for (i = 0; i < INS_NUM; i++) {
        CPUSeq[i].pagenumber = CPUSeq[i].addr / 10;
        CPUSeq[i].offset = CPUSeq[i].addr % 10;
    }


}

double FIFO(int total_pages) {
    //创建一个队列, 记录页面进入内存的先后顺序
    queue<int> q;
    int i, j;
    int misspages = 0, pn;
    int oldestpage;

    //初始化页表, 将所有页的帧号置为INVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //开始进行页面调度
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //发生page fault, 记录失页数
            misspages++;

            //查看是否有空的帧, 有的话加进去, 并将这个页加到队列中
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    q.push(pn);
                    break;
                }
            }

            //如果内存满了, 就将队头对应的页换出, 并将这个页换进
            if (pagetable[pn].frame == INVALID) {
                oldestpage = q.front();
                pagetable[pn] = pagetable[oldestpage];
                pagetable[oldestpage].frame = INVALID;
                q.pop();
                q.push(pn);
            }
        }
    }
    return 1.0 - (double)misspages / INS_NUM;

    
}
double LRU(int total_pages) {
    int i, j;
    int misspages = 0, pn;
    int time = 0;
    int oldestpage, oldesttime = 500;

    //初始化页表, 将所有页的帧号和最近使用时间置为INVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //开始进行页面调度
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //发生page fault, 记录失页数
            misspages++;

            //查看是否有空的帧, 有的话加进去, 并将这个页加到队列中
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    //改变usetime
                    pagetable[pn].usetime = ++time;
                    break;
                }
            }

            //如果内存满了, 就将usetime最小的页换出, 并将新的页换进
            if (pagetable[pn].frame == INVALID) {
                oldesttime = INF;
                for (j = 0; j < MAX_PAGES; j++) {
                    if (pagetable[j].frame != INVALID && pagetable[j].usetime < oldesttime) {
                        oldestpage = j;
                        oldesttime = pagetable[j].usetime;
                    }
                }
                pagetable[pn] = pagetable[oldestpage];
                pagetable[pn].usetime = ++time;
                pagetable[oldestpage].frame = INVALID;
                pagetable[oldestpage].usetime = INVALID;
            }
        }
        else {
            pagetable[pn].usetime = ++time;
        }
    }
    return 1.0 - (double)misspages / INS_NUM;
}
double LFR(int total_pages) {
    int i, j;
    int misspages = 0, pn;
    int time = 0;
    int oldestpage, leastfreq = INF;

    //初始化页表, 将所有页的帧号和最近使用时间置为INVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //开始进行页面调度
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //发生page fault, 记录失页数
            misspages++;

            //查看是否有空的帧, 有的话加进去, 并将这个页加到队列中
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    //改变freq
                    pagetable[pn].freq++;
                    break;
                }
            }

            //如果内存满了, 就将freq最小的页换出, 并将这个页换进
            if (pagetable[pn].frame == INVALID) {
                leastfreq = INF;
                for (j = 0; j < MAX_PAGES; j++) {
                    if (pagetable[j].frame != INVALID && pagetable[j].freq < leastfreq) {
                        oldestpage = j;
                        leastfreq = pagetable[j].freq;
                    }
                }
                pagetable[pn] = pagetable[oldestpage];
                pagetable[pn].freq++;
                pagetable[oldestpage].frame = INVALID;
                pagetable[oldestpage].freq = INVALID;
            }
        }
        else {
            pagetable[pn].freq++;
        }
    }
    return 1.0 - (double)misspages / INS_NUM;
}
double OPT(int total_pages) {
    int i, j, k;
    int misspages = 0, pn;
    int time = 0;
    int latestpage, latesttime = 0;

    //初始化页表, 将所有页的帧号和最近使用时间置为INVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //开始进行页面调度
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //发生page fault, 记录失页数
            misspages++;

            //查看是否有空的帧, 有的话加进去, 并将这个页加到队列中
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    break;
                }
            }

            //如果内存满了, 先将所有在内存中页的下一次使用时间找出来, 找到最大的
            if (pagetable[pn].frame == INVALID) {
                for (j = 0; j < MAX_PAGES; j++) {
                    if (pagetable[j].frame != INVALID) {
                        //遍历之后的指令序列, 找到最后的使用时间, 用指令序列的下标表示
                        for (k = i + 1; k < INS_NUM; k++) {
                            if (CPUSeq[k].pagenumber == j) {
                                break;
                            }
                        }
                        if (k > latesttime) {
                            latesttime = k;
                            latestpage = j;
                        }
                    }
                }
                //将最近使用时间最长的页换出, 将新的页换进
                pagetable[pn] = pagetable[latestpage];
                pagetable[latestpage].frame = INVALID;
                pagetable[latestpage].nextusetime = INF;
            }
        }
    }
    return 1.0 - (double)misspages / INS_NUM;
}

int main() {
    int i;
    for (i = 4; i <= 32; i++) {
        generatePages();
        printf("-----------\n");
        printf("内存容量为%3d时:\n", i);
        printf("FIFO------%f\n", FIFO(i));
        printf("LRU-------%f\n", LRU(i));
        printf("LFR-------%f\n", LFR(i));
        printf("OPT-------%f\n", OPT(i));
        printf("\n");
    }
    system("pause");
    return 0;
}