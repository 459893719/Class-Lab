#include "JosephLoop.h"
#include <iostream>
#include <cmath>



JosephLoop::JosephLoop() {
    element = new Node[MAXSIZE];
    length = 0;
    size = MAXSIZE;
}


bool JosephLoop::insertList(int code, int num) {

    //�ж�code��ֵ, ���Ϊ����, ��Ƿ�, ����ڵ�ʧ��
    if (code < 0) {

        std::cout << "Error: the code you input isn't legal.\n";

        return false;
    }

    if (length >= size) {
        //��ԭ�������鿽����һ�����������
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
//��node��������ɾ��
//����Ϊɾ���ڵ��ָ��
bool JosephLoop::deleteNode(ListNode* node) {

    //ɾ��˼·: ��node��һ���ڵ��ֵ������node��, ��ɾ��node����һ���ڵ�, ���ʵ��node��ɾ��


    //��Ϊ����deleteNode()����ʱ��֤���г��˱�ͷ�ڵ㻹�б�Ľڵ�, ��˲���Ҫ���д�����
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

    //���Ƚ���n m�ļ��, n>0 �� m>0
    if (!(n > 0 && m > 0)) {
        std::cout << "Error: Parameters are illegal.\n";
        return password;
    }

    std::cout << "Please input " << n << " numbers.\n";

    //�ڱ��в���n���ڵ�
    for (int i = 0; i < n; i++) {
        int input;

        //������벻��, ������һ��
        do {
            std::cout << i + 1 << ": ";
            std::cin >> input;
        } while (!this->insertList(input, i + 1));

    }

    int p = 0;
    int count = 1;

    //��lengthΪ0ʱ, ��ʾ����û�нڵ�, �˳�ѭ��
    while (length) {

        //��p�����Ѿ�����, ������
        if (element[p].isVisited) {
            p = (p + 1) % n;
            continue;
        }

        //�Ѿ����ﱨ������
        if (count == m) {
            //���õ��Ӧ����ŵ������, ��ɾ���õ�
            password.push_back(element[p].num);
            m = element[p].code;
            element[p].isVisited = true;
            count = 1;
            length--;
        }
        else {
            //�õ㲻ɾ���Ļ�, ��������
            count++;
            p = (p + 1) % n;
        }
    }

    return password;
}

JosephLoop::~JosephLoop() {
    delete[] element;
}