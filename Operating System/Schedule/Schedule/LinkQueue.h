/*LinkQueue.h*/
#pragma once
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(): next(0) {}
    Node(T data) : data(data), next(0) {}
};

template <typename T>
struct LinkQueue {

    Node<T>* front;
    Node<T>* rear;

	//����һ���ն���
    LinkQueue();

	//���е�push����
    bool push(T data);
	
	//���е�pop����
    bool pop();

	//���ض�ͷԪ��
    T getFront();

	//�ж϶����Ƿ�Ϊ�ն���
    bool isEmpty();

	//���ٶ���
    ~LinkQueue();
};

//����һ���ն���
template <typename T>
LinkQueue<T>::LinkQueue() {
    rear = new Node<T>();
    front = rear;
}

//�ж϶����Ƿ�Ϊ�ն���
template <typename T>
bool LinkQueue<T>::isEmpty() {
    if (front->next == nullptr) {
        return true;
    }
    return false;
}

//���ض�ͷԪ��
template <typename T>
T LinkQueue<T>::getFront() {
    if (isEmpty()) {
        std::cout << "Error: Queue is empty.\n";
        return T();
    }
    return front->next->data;
}

//���е�push����
template <typename T>
bool LinkQueue<T>::push(T data) {
    Node<T>* newnode = new (std::nothrow) Node<T>(data);
    if (!newnode) {
        //�����½ڵ�ʧ��, ����false
        std::cout << "Error: Fail to push a new element.\n";
        return false;
    }

    rear->next = newnode;
    rear = newnode;
    return true;
}

//���е�pop����
template <typename T>
bool LinkQueue<T>::pop() {
    if (isEmpty()) {
        std::cout << "Error: Queue is empty.\n";
        return 0;
    }
    Node<T>* deleteNode = front->next;
    front->next = deleteNode->next;
    delete deleteNode;

    if (isEmpty()) {
        rear = front;
    }

    return true;
}

//����һ������
template <typename T>
LinkQueue<T>::~LinkQueue() {
    while (front) {
        rear = front->next;
        delete front;
        front = rear;
    }
}