//LinkStack.cpp

#include "LinkStack.h"

//���캯��, ����һ����ջ(��ͷ���)
LinkStack::LinkStack() {
    length = 0;
    top = new Node(-1);
}

//���ջ��Ԫ��
//����ֵΪint
 int LinkStack::getTop() {
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
bool LinkStack::push(int ele) {
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
bool LinkStack::pop(int* ele) {
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
//����ת������, ʵ��һ��ʮ������������ת��
//����Ϊһ��ʮ������num��ת����������d
//�ú���ֻʵ��ʮ����ת���ɶ����Ƶ���ʮ�����
std::string numSwitch(int num, int d) {

    //�����ж�, numΪ����ʱ����, ���ؿմ�
    if (num < 0) {
        std::cout << "Error: ����ת������.\n";
        return "";
    }
    //d����2��35֮��ʱ, ����, ���ؿմ�
    if (!(d >= 2 && d <= 35)) {
        std::cout << "Error: ����ת����" << d << "����.\n";
        return "";
    }



    //numΪ0��ʱ��ֱ�ӷ���0
    if (num == 0) {
        return "0";
    }


    //����һ���ַ�����, ͨ���±����ַ���Ӧ, ������һ��ӳ���ϵ, ��������ÿһλ����Ӧ��һ���ַ�
    char charmap[50];
    for (int i = 0; i < 10; i++) {
        charmap[i] = i + '0';
    }
    for (int i = 10; i < 36; i++) {
        charmap[i] = i - 10 + 'A';
    }

    LinkStack stack;

    while (num) {
        stack.push(num % d);
        num /= d;
    }

    std::string newnum;
    int* element = new int(0);
    newnum.resize(stack.getLength());
    for (int i = 0; i < newnum.length(); i++) {
        stack.pop(element);
        newnum[i] = charmap[*element];
    }
    delete element;
    return newnum;
}