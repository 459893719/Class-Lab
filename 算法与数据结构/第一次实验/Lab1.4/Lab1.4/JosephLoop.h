#pragma once
#include <string>
#include <vector>

const int MAXSIZE = 100;


struct Node {
    int code;
    bool isVisited;
    int num;
    Node(){}
    Node(int code, int num) : code(code), isVisited(false), num(num) {}
};

class JosephLoop {
private:
    int length;
    Node* element;
    int size;
public:
    JosephLoop();

    //���ñ�����ɾ��
    ~JosephLoop();

    //ʵ�ֽڵ����
    bool insertList(int code, int num);

    

    //ģ��Լɪ�򻷵Ĺ���
    std::vector<int> simulateJoseph(int n, int m);

};