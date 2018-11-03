#pragma once
#include <iostream>


const int INIT_SIZE = 100;
const int INCRE_SIZE = 10;

template <typename T>
class ArrayStack {
protected:
    T* top;
    T* base;
    int size;

public:
    ArrayStack();

    bool isEmpty();

    int getLength() {
        return top - base;
    }

    T getTop();

    bool push(T data);

    bool pop();

    ~ArrayStack();
};

template <typename T>
ArrayStack<T>::ArrayStack() {
    base = new T[INIT_SIZE];
    size = INIT_SIZE;
    top = base;
}

template <typename T>
bool ArrayStack<T>::isEmpty() {
    if (top - base == 0) {
        return true;
    }
    return false;
}

template <typename T>
T ArrayStack<T>::getTop() {
    if (top - base == 0) {
        std::cout << "Error: Stack is empty.\n";
        return T();
    }
    return *(top - 1);
}

template <typename T>
bool ArrayStack<T>::push(T data) {
    if (top - base >= size) {
        Car* newbase = new (std::nothrow) Car[INIT_SIZE + INCRE_SIZE];
        if (newbase == nullptr) {
            std::cout << "Error: Fail to push a new element.\n";
            return false;
        }
        for (int i = 0; i < size; i++) {
            newbase[i] = base[i];
        }
        base = newbase;
        delete base;
        size += INCRE_SIZE;
    }
    *top = data;
    top++;
    return true;
}

template <typename T>
bool ArrayStack<T>::pop() {
    if (top == base) {
        std::cout << "Error: Stack is empty.\n";
        return false;
    }
    top--;
    return true;
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] base;
}