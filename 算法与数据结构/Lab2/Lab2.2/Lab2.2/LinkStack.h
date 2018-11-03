#pragma once
#include <iostream>
#include <string>


//括号匹配函数, 输入为一个由括号组成的字符串, 返回匹配是否正确
bool braceMatch(std::string braces);

struct Node {
    char data;
    Node* next;
    Node() {}
    Node(char data) : data(data), next(0) {}
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
    char getTop();
    //push
    bool push(char ele);
    //pop
    bool pop(char* ele);
    //清空链表
    void clear();
    //析构函数
    ~LinkStack();

};


