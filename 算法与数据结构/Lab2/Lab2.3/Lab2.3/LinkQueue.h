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
class LinkQueue {
private:
    Node<T>* front;
    Node<T>* rear;
public:
    LinkQueue();

    bool push(T data);
    bool pop();

    T getFront();

    bool isEmpty();

    ~LinkQueue();
};

template <typename T>
LinkQueue<T>::LinkQueue() {
    rear = new Node<T>();
    front = rear;
}

template <typename T>
bool LinkQueue<T>::isEmpty() {
    if (front->next == nullptr) {
        return true;
    }
    return false;
}

template <typename T>
T LinkQueue<T>::getFront() {
    if (isEmpty()) {
        std::cout << "Error: Queue is empty.\n";
        return T();
    }
    return front->next->data;
}

template <typename T>
bool LinkQueue<T>::push(T data) {
    Node<T>* newnode = new (std::nothrow) Node<T>(data);
    if (!newnode) {
        //创建新节点失败, 返回false
        std::cout << "Error: Fail to push a new element.\n";
        return false;
    }

    rear->next = newnode;
    rear = newnode;
    return true;
}

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

template <typename T>
LinkQueue<T>::~LinkQueue() {
    while (front) {
        rear = front->next;
        delete front;
        front = rear;
    }
}