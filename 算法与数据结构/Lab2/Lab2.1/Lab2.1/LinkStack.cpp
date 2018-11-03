//LinkStack.cpp

#include "LinkStack.h"

//构造函数, 创建一个空栈(带头结点)
LinkStack::LinkStack() {
    length = 0;
    top = new Node(-1);
}

//获得栈顶元素
//返回值为int
 int LinkStack::getTop() {
    if (length == 0) {
        std::cout << "Error: Stack is empty.\n";
        return -1;
    }
    return top->data;
}

//判断栈是否为空栈
 //是的话, 返回true
bool LinkStack::isEmpty() {
    if (length == 0) {
        return true;
    }
    return false;
}

//栈的push操作, 如果失败, 返回false
bool LinkStack::push(int ele) {
    Node* newnode = new (std::nothrow) Node(ele);
    if (!newnode) {
        //创建新节点失败, 返回false
        std::cout << "Error: Fail to push a new element.\n";
        return false;
    }   

    newnode->next = top->next;
    top->next = newnode;
    length++;
    return true;
}

//栈的pop操作, 如果失败, 返回false
bool LinkStack::pop(int* ele) {
    //空栈的时候不能删除元素
    if (isEmpty()) {
        std::cout << "Error: Stack is empty.\n";
        return false;
    }
    //进行节点的删除操作
    Node* deleteNode = top->next;
    *ele = deleteNode->data;
    top->next = deleteNode->next;
    delete deleteNode;
    length--;
    return true;
}


//清空栈的节点
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

//将栈的所有内容回收
LinkStack::~LinkStack() {
    clear();
    delete top;
}
//数制转换函数, 实现一个十进制数的数制转换
//参数为一个十进制数num和转换进制类型d
//该函数只实现十进制转换成二进制到三十五进制
std::string numSwitch(int num, int d) {

    //输入判断, num为负数时报错, 返回空串
    if (num < 0) {
        std::cout << "Error: 不能转换负数.\n";
        return "";
    }
    //d不在2和35之间时, 报错, 返回空串
    if (!(d >= 2 && d <= 35)) {
        std::cout << "Error: 不能转换成" << d << "进制.\n";
        return "";
    }



    //num为0的时候直接返回0
    if (num == 0) {
        return "0";
    }


    //创建一个字符数组, 通过下标与字符对应, 建立了一个映射关系, 进制数的每一位都对应着一个字符
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