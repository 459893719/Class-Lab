#pragma once
#include <iostream>
#include <string>


//����ƥ�亯��, ����Ϊһ����������ɵ��ַ���, ����ƥ���Ƿ���ȷ
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
    //���캯��, ����һ����ջ
    LinkStack();
    //�ж�ջ�Ƿ�Ϊ��
    bool isEmpty();
    //���ջ�ĳ���
    int getLength() {
        return length;
    }
    //���ջ��Ԫ��
    char getTop();
    //push
    bool push(char ele);
    //pop
    bool pop(char* ele);
    //�������
    void clear();
    //��������
    ~LinkStack();

};


