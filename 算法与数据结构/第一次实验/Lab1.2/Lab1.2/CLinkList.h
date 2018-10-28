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
    ListNode* head;    //head表示链表头结点
    ListNode* tail;    //tail表示循环链表最后一个节点, 方便进行链表元素的插入

public:
    CLinkList();

    //将该表内容删除
    ~CLinkList();

    //实现节点插入
    bool insertList(int code);

    //实现节点删除
    bool deleteNode(ListNode* node);

    //模拟约瑟夫环的过程
    std::vector<int> simulateJoseph(int n, int m);

};