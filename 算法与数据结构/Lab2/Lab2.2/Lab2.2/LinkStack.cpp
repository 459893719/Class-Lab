#include "LinkStack.h"


//���캯��, ����һ����ջ(��ͷ���)
LinkStack::LinkStack() {
    length = 0;
    top = new Node(0);
}

//���ջ��Ԫ��
//����ֵΪint
char LinkStack::getTop() {
    if (length == 0) {
        std::cout << "Error: Stack is empty.\n";
        return -1;
    }
    return top->data;
}

//�ж�ջ�Ƿ�Ϊ��ջ
//�ǵĻ�, ����true
bool LinkStack::isEmpty() {
    if (length == 0) {
        return true;
    }
    return false;
}

//ջ��push����, ���ʧ��, ����false
bool LinkStack::push(char ele) {
    Node* newnode = new (std::nothrow) Node(ele);
    if (!newnode) {
        //�����½ڵ�ʧ��, ����false
        std::cout << "Error: Fail to push a new element.\n";
        return false;
    }

    newnode->next = top->next;
    top->next = newnode;
    length++;
    return true;
}

//ջ��pop����, ���ʧ��, ����false
bool LinkStack::pop(char* ele) {
    //��ջ��ʱ����ɾ��Ԫ��
    if (isEmpty()) {
        std::cout << "Error: Stack is empty.\n";
        return false;
    }
    //���нڵ��ɾ������
    Node* deleteNode = top->next;
    *ele = deleteNode->data;
    top->next = deleteNode->next;
    delete deleteNode;
    length--;
    return true;
}


//���ջ�Ľڵ�
void LinkStack::clear() {
    Node* p1 = top->next;
    Node* p2 = p1;
    while (p1) {
        p2 = p1->next;
        delete p1;
        p1 = p2;
    }
    top = nullptr;
}

//��ջ���������ݻ���
LinkStack::~LinkStack() {
    clear();
    delete top;
}

//����ƥ�亯��, ����Ϊһ����������ɵ��ַ���, ����ƥ���Ƿ���ȷ
bool braceMatch(std::string braces) {
    LinkStack stack;

    //����Ϊ��ʱ�׳��쳣
    if (braces.length() == 0) {
        throw 2;
    }

    for (int i = 0; i < braces.length(); i++) {
        //���ַ����б���, ��������ջ, �������ж��Ƿ���ջ��Ԫ��ƥ��ɹ�
        switch (braces[i]) {
        case '(':
        case '[':{
            stack.push(braces[i]);
            break;
        }
        case ')': {
            if (stack.isEmpty()) {
                return false;
            }
            else {
                char* topchar = new char(0);
                stack.pop(topchar);
                if (*topchar != '(') {
                    return false;
                }
            }
            break;
        }
        case ']': {
            if (stack.isEmpty()) {
                return false;
            }
            else {
                char* topchar = new char(0);
                stack.pop(topchar);
                if (*topchar != '[') {
                    return false;
                }
            }
            break;
        }
        default: {
            //�������, �׳�һ���쳣
            throw 1;
        }
        }
    }


    //���������֮��ջ�л���Ԫ��, ֤��ƥ��ʧ��, ����ƥ��ɹ�
    if (!stack.isEmpty()) {
        return false;
    }
    else {
        return true;
    }
}