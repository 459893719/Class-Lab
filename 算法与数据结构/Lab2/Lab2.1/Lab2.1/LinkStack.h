//LinkStack.h

#pragma once
#include <iostream>
#include <string>

//数制转换函数, 实现一个十进制数的数制转换
std::string numSwitch(int num, int d);

struct Node {
    int data;
    Node* next;
    Node() {}
    Node(int data) : data(data), next(0) {}
};

class LinkStack {
private:
    Node* top;
    int length;
public:
    //构造函数, 创建一个空栈
    LinkStack();
    //判断栈是否为空
    bool isEmpty();
    //获得栈的长度
    int getLength() {
        return length;
    }
    //获得栈顶元素
    int getTop();
    //push
    bool push(int ele);
    //pop
    bool pop(int* ele);
    //清空链表
    void clear();
    //析构函数
    ~LinkStack();

};


