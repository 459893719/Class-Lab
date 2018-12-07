#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
using namespace std;

#define INS_NUM 320     //ָ��ִ������
#define MAX_PAGES 32    //ҳ������, �Լ��ڴ�����֡��
#define INVALID -1      
#define INF 5000

//ָ��ĳ���ṹ
typedef struct ins {
    int addr;
    int pagenumber;
    int offset;
}ins;

//ҳ��ĳ���ṹ
typedef struct page_struct {
    int frame;
    int usetime;
    int freq;
    int nextusetime;
}ps;

ins CPUSeq[INS_NUM];
//�����±��ʾCPUִ�е�˳��, addr��ʾ���ָ��������ַ

ps pagetable[MAX_PAGES];
int frames[MAX_PAGES];


//����ָ��ִ�е��������, ������ҳ��ַ��
void generatePages() {
    int i, addr, m;
    srand((int)time(NULL));

    //�����ɵ�������зŵ�CPUSeq��addr��
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

    //����ҳ��ַ��
    for (i = 0; i < INS_NUM; i++) {
        CPUSeq[i].pagenumber = CPUSeq[i].addr / 10;
        CPUSeq[i].offset = CPUSeq[i].addr % 10;
    }


}

double FIFO(int total_pages) {
    //����һ������, ��¼ҳ������ڴ���Ⱥ�˳��
    queue<int> q;
    int i, j;
    int misspages = 0, pn;
    int oldestpage;

    //��ʼ��ҳ��, ������ҳ��֡����ΪINVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //��ʼ����ҳ�����
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //����page fault, ��¼ʧҳ��
            misspages++;

            //�鿴�Ƿ��пյ�֡, �еĻ��ӽ�ȥ, �������ҳ�ӵ�������
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    q.push(pn);
                    break;
                }
            }

            //����ڴ�����, �ͽ���ͷ��Ӧ��ҳ����, �������ҳ����
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

    //��ʼ��ҳ��, ������ҳ��֡�ź����ʹ��ʱ����ΪINVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //��ʼ����ҳ�����
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //����page fault, ��¼ʧҳ��
            misspages++;

            //�鿴�Ƿ��пյ�֡, �еĻ��ӽ�ȥ, �������ҳ�ӵ�������
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    //�ı�usetime
                    pagetable[pn].usetime = ++time;
                    break;
                }
            }

            //����ڴ�����, �ͽ�usetime��С��ҳ����, �����µ�ҳ����
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

    //��ʼ��ҳ��, ������ҳ��֡�ź����ʹ��ʱ����ΪINVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //��ʼ����ҳ�����
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //����page fault, ��¼ʧҳ��
            misspages++;

            //�鿴�Ƿ��пյ�֡, �еĻ��ӽ�ȥ, �������ҳ�ӵ�������
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    //�ı�freq
                    pagetable[pn].freq++;
                    break;
                }
            }

            //����ڴ�����, �ͽ�freq��С��ҳ����, �������ҳ����
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

    //��ʼ��ҳ��, ������ҳ��֡�ź����ʹ��ʱ����ΪINVALID
    for (i = 0; i < MAX_PAGES; i++) {
        pagetable[i].frame = INVALID;
        pagetable[i].usetime = INVALID;
        pagetable[i].freq = 0;
        pagetable[i].nextusetime = INF;
        frames[i] = 0;
    }

    //��ʼ����ҳ�����
    for (i = 0; i < INS_NUM; i++) {
        pn = CPUSeq[i].pagenumber;
        if (pagetable[pn].frame == INVALID) {
            //����page fault, ��¼ʧҳ��
            misspages++;

            //�鿴�Ƿ��пյ�֡, �еĻ��ӽ�ȥ, �������ҳ�ӵ�������
            for (j = 0; j < total_pages; j++) {
                if (frames[j] == 0) {
                    pagetable[pn].frame = j;
                    frames[j] = 1;
                    break;
                }
            }

            //����ڴ�����, �Ƚ��������ڴ���ҳ����һ��ʹ��ʱ���ҳ���, �ҵ�����
            if (pagetable[pn].frame == INVALID) {
                for (j = 0; j < MAX_PAGES; j++) {
                    if (pagetable[j].frame != INVALID) {
                        //����֮���ָ������, �ҵ�����ʹ��ʱ��, ��ָ�����е��±��ʾ
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
                //�����ʹ��ʱ�����ҳ����, ���µ�ҳ����
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
        printf("�ڴ�����Ϊ%3dʱ:\n", i);
        printf("FIFO------%f\n", FIFO(i));
        printf("LRU-------%f\n", LRU(i));
        printf("LFR-------%f\n", LFR(i));
        printf("OPT-------%f\n", OPT(i));
        printf("\n");
    }
    system("pause");
    return 0;
}