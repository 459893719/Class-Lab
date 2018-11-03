#include "JosephLoop.h"
#include <iostream>
#include <cmath>



JosephLoop::JosephLoop() {
    element = new Node[MAXSIZE];
    length = 0;
    size = MAXSIZE;
}


bool JosephLoop::insertList(int code, int num) {

    //判断code的值, 如果为负数, 则非法, 插入节点失败
    if (code < 0) {

        std::cout << "Error: the code you input isn't legal.\n";

        return false;
    }

    if (length >= size) {
        //将原来的数组拷贝到一个更大的数组
        Node* newelement = new (std::nothrow)Node[size + MAXSIZE];

        if (newelement == 0) {
            std::cout << "Error: Overflow when inserting cities.\n";
            return false;
        }

        size += MAXSIZE;
        for (int i = 0; i < length; i++) {
            newelement[i] = element[i];
        }

        delete[] element;

        element = newelement;



    }

    element[length++] = Node(code, num);
    return true;


}


/*
//将node从链表中删除
//参数为删除节点的指针
bool JosephLoop::deleteNode(ListNode* node) {

    //删除思路: 将node下一个节点的值拷贝到node里, 并删除node的下一个节点, 间接实现node的删除


    //因为调用deleteNode()函数时保证表中除了表头节点还有别的节点, 因此不需要进行错误检测
    node->code = node->next->code;
    node->num = node->next->num;
    ListNode* pnode = node->next;

    node->next = pnode->next;
    delete pnode;
    length--;

    return true;
}*/

std::vector<int> JosephLoop::simulateJoseph(int n, int m) {
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
        } while (!this->insertList(input, i + 1));

    }

    int p = 0;
    int count = 1;

    //当length为0时, 表示表中没有节点, 退出循环
    while (length) {

        //第p个人已经走了, 跳过他
        if (element[p].isVisited) {
            p = (p + 1) % n;
            continue;
        }

        //已经到达报数上限
        if (count == m) {
            //将该点对应密码放到结果里, 并删除该点
            password.push_back(element[p].num);
            m = element[p].code;
            element[p].isVisited = true;
            count = 1;
            length--;
        }
        else {
            //该点不删除的话, 继续报数
            count++;
            p = (p + 1) % n;
        }
    }

    return password;
}

JosephLoop::~JosephLoop() {
    delete[] element;
}