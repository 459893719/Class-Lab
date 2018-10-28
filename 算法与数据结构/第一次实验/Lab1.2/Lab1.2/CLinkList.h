#pragma once
#include <string>
#include <vector>

struct ListNode {
    int code;
    int num;
    ListNode* next;
    ListNode(int code) : code(code), next(0) {}
    ListNode() {}
};

class CLinkList {
private:
    int length;
    ListNode* head;    //head��ʾ����ͷ���
    ListNode* tail;    //tail��ʾѭ���������һ���ڵ�, �����������Ԫ�صĲ���

public:
    CLinkList();

    //���ñ�����ɾ��
    ~CLinkList();

    //ʵ�ֽڵ����
    bool insertList(int code);

    //ʵ�ֽڵ�ɾ��
    bool deleteNode(ListNode* node);

    //ģ��Լɪ�򻷵Ĺ���
    std::vector<int> simulateJoseph(int n, int m);

};