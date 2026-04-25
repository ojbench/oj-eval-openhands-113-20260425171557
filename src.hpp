#ifndef SRC_HPP
#define SRC_HPP

#include <cstdio>
#include <iostream>

template <typename T>
class LinkedList {
protected:
    struct Node {
        T val;
        Node* prev;
        Node* next;
        Node(const T& v) : val(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int len;

    void clear_nodes() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        len = 0;
    }

public:
    // 默认构造函数：构造一个空链表
    LinkedList() : head(nullptr), tail(nullptr), len(0) {}

    // 拷贝构造函数：构造一个与给定链表相同的链表
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), len(0) {
        for (Node* cur = other.head; cur != nullptr; cur = cur->next) {
            pushBack(cur->val);
        }
    }

    // 析构函数：释放所有节点，防止内存泄漏
    virtual ~LinkedList() {
        clear_nodes();
    }

    // 在链表头插入一个元素
    void pushFront(const T& v) {
        Node* n = new Node(v);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        ++len;
    }

    // 在链表尾插入一个元素
    void pushBack(const T& v) {
        Node* n = new Node(v);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        ++len;
    }

    // 在链表头删除一个元素，返回被删除元素的值；若空则返回T默认值
    T popFront() {
        if (!head) return T();
        Node* n = head;
        T ret = n->val;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete n;
        --len;
        return ret;
    }

    // 在链表尾删除一个元素，返回被删除元素的值；若空则返回T默认值
    T popBack() {
        if (!tail) return T();
        Node* n = tail;
        T ret = n->val;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete n;
        --len;
        return ret;
    }

    // 返回链表长度
    int size() const { return len; }

    // 输出链表，元素间空格，结尾换行（使用cout）
    void print() const {
        for (Node* cur = head; cur != nullptr; cur = cur->next) {
            std::cout << cur->val << ' ';
        }
        std::cout << '\n';
    }

    // 虚函数声明与基类默认实现（保证不会直接调用基类版本）
    virtual const char* name() { return "LinkedList"; }
    virtual T peak() { return tail ? tail->val : T(); }
    virtual T pop() { return popBack(); }
    virtual void push(T val) { pushBack(val); }
};

// 栈：不能在类内定义变量，复用基类存储
// 实现虚函数：name/peak/pop/push

template <typename T>
class Stack : public LinkedList<T> {
public:
    const char* name() { return "Stack"; }
    T peak() { return this->tail ? this->tail->val : T(); }
    T pop() { return this->popBack(); }
    void push(T val) { this->pushBack(val); }
};

// 队列：不能在类内定义变量，复用基类存储
// 实现虚函数：name/peak/pop/push

template <typename T>
class Queue : public LinkedList<T> {
public:
    const char* name() { return "Queue"; }
    T peak() { return this->head ? this->head->val : T(); }
    T pop() { return this->popFront(); }
    void push(T val) { this->pushBack(val); }
};

#endif // SRC_HPP
