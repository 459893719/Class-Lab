//LinkStack.h

#pragma once
#include <iostream>
#include <string>

//����ת������, ʵ��һ��ʮ������������ת��
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
    //���캯��, ����һ����ջ
    LinkStack();
    //�ж�ջ�Ƿ�Ϊ��
    bool isEmpty();
    //���ջ�ĳ���
    int getLength() {
        return length;
    }
    //���ջ��Ԫ��
    int getTop();
    //push
    bool push(int ele);
    //pop
    bool pop(int* ele);
    //�������
    void clear();
    //��������
    ~LinkStack();

};


