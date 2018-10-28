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

    //将该表内容删除
    ~JosephLoop();

    //实现节点插入
    bool insertList(int code, int num);

    

    //模拟约瑟夫环的过程
    std::vector<int> simulateJoseph(int n, int m);

};