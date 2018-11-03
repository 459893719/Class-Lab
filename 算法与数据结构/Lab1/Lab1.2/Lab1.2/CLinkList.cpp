#include "CLinkList.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <new>

CLinkList::CLinkList() {
    head = new ListNode(0);
    tail = head;
    length = 0;
}

bool CLinkList::insertList(int code) {

    //判断code的值, 如果为负数, 则非法, 插入节点失败
    if (code < 0) {

        std::cout << "Error: the code you input isn't legal.\n";
        return false;
    }

    //如果创建节点失败时, 返回false
    ListNode* newnode = new (std::nothrow)ListNode(code);
    if (newnode == 0) {

        std::cout << "Error: allocation of the new node failed.\n";
        return false;
    }

    //进行新节点的插入操作
    tail->next = newnode;
    newnode->next = head->next;
    tail = newnode;
    length++;
    newnode->num = length;

    return true;
}



//将node从链表中删除
//参数为删除节点的指针
bool CLinkList::deleteNode(ListNode* node) {
    
    //删除思路: 将node下一个节点的值拷贝到node里, 并删除node的下一个节点, 间接实现node的删除


    //因为调用deleteNode()函数时保证表中除了表头节点还有别的节点, 因此不需要进行错误检测
    node->code = node->next->code;
    node->num = node->next->num;
    ListNode* pnode = node->next;

    node->next = pnode->next;
    delete pnode;
    length--;

    return true;
}

std::vector<int> CLinkList::simulateJoseph(int n, int m) {
    std::vector<int> password;
    
    //首先进行n m的检查, n>0 且 m>0
    if (!(n > 0 && m > 0)) {
        std::cout << "Error: Parameters are illegal.\n";
        return password;
    }

    std::cout << "Please input " << n << " numbers.\n";

    //在表中插入n个节点
    for (int i = 0; i < n; i++) {
        int input;

        //如果输入不对, 再输入一遍
        do {
            std::cout << i + 1 << ": ";
            std::cin >> input;
        } 
        while (!this->insertList(input));
        
    }

    ListNode* p = head->next;
    int count = 1;

    //当length为0时, 表示表中没有节点, 退出循环
    while (length) {

        if (count == m) {
            //报数为m, 将该点对应密码放到结果里, 并删除该点
            password.push_back(p->num);
            m = p->code;
            this->deleteNode(p);
            count = 1;
        }
        else {
            //该点不删除的话, 继续报数
            count++;
            p = p->next;
        }
    }

    head->next = 0;
    tail = head;

    return password;
}

CLinkList::~CLinkList() {
    delete head;
}