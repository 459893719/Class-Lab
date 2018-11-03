#include "LinkStack.h"


//构造函数, 创建一个空栈(带头结点)
LinkStack::LinkStack() {
    length = 0;
    top = new Node(0);
}

//获得栈顶元素
//返回值为int
char LinkStack::getTop() {
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
bool LinkStack::push(char ele) {
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
bool LinkStack::pop(char* ele) {
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

//括号匹配函数, 输入为一个由括号组成的字符串, 返回匹配是否正确
bool braceMatch(std::string braces) {
    LinkStack stack;

    //输入为空时抛出异常
    if (braces.length() == 0) {
        throw 2;
    }

    for (int i = 0; i < braces.length(); i++) {
        //对字符进行遍历, 左括号入栈, 右括号判断是否与栈顶元素匹配成功
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
            //输入错误, 抛出一个异常
            throw 1;
        }
        }
    }


    //如果遍历完之后栈中还有元素, 证明匹配失败, 否则匹配成功
    if (!stack.isEmpty()) {
        return false;
    }
    else {
        return true;
    }
}