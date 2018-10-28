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

    //�ж�code��ֵ, ���Ϊ����, ��Ƿ�, ����ڵ�ʧ��
    if (code < 0) {

        std::cout << "Error: the code you input isn't legal.\n";
        return false;
    }

    //��������ڵ�ʧ��ʱ, ����false
    ListNode* newnode = new (std::nothrow)ListNode(code);
    if (newnode == 0) {

        std::cout << "Error: allocation of the new node failed.\n";
        return false;
    }

    //�����½ڵ�Ĳ������
    tail->next = newnode;
    newnode->next = head->next;
    tail = newnode;
    length++;
    newnode->num = length;

    return true;
}



//��node��������ɾ��
//����Ϊɾ���ڵ��ָ��
bool CLinkList::deleteNode(ListNode* node) {
    
    //ɾ��˼·: ��node��һ���ڵ��ֵ������node��, ��ɾ��node����һ���ڵ�, ���ʵ��node��ɾ��


    //��Ϊ����deleteNode()����ʱ��֤���г��˱�ͷ�ڵ㻹�б�Ľڵ�, ��˲���Ҫ���д�����
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
        } 
        while (!this->insertList(input));
        
    }

    ListNode* p = head->next;
    int count = 1;

    //��lengthΪ0ʱ, ��ʾ����û�нڵ�, �˳�ѭ��
    while (length) {

        if (count == m) {
            //����Ϊm, ���õ��Ӧ����ŵ������, ��ɾ���õ�
            password.push_back(p->num);
            m = p->code;
            this->deleteNode(p);
            count = 1;
        }
        else {
            //�õ㲻ɾ���Ļ�, ��������
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