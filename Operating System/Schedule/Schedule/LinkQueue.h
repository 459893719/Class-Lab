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

	//创建一个空队列
    LinkQueue();

	//队列的push操作
    bool push(T data);
	
	//队列的pop操作
    bool pop();

	//返回队头元素
    T getFront();

	//判断队列是否为空队列
    bool isEmpty();

	//销毁队列
    ~LinkQueue();
};

//创建一个空队列
template <typename T>
LinkQueue<T>::LinkQueue() {
    rear = new Node<T>();
    front = rear;
}

//判断队列是否为空队列
template <typename T>
bool LinkQueue<T>::isEmpty() {
    if (front->next == nullptr) {
        return true;
    }
    return false;
}

//返回队头元素
template <typename T>
T LinkQueue<T>::getFront() {
    if (isEmpty()) {
        std::cout << "Error: Queue is empty.\n";
        return T();
    }
    return front->next->data;
}

//队列的push操作
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

//队列的pop操作
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

//销毁一个队列
template <typename T>
LinkQueue<T>::~LinkQueue() {
    while (front) {
        rear = front->next;
        delete front;
        front = rear;
    }
}