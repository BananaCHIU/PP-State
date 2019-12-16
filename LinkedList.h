#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <typename type>
class Linkedlist{
    Node<type> *head {nullptr};
    Node<type> *tail {nullptr};
    int size {0};

public:
    Linkedlist();
    Linkedlist(type* x);
    ~Linkedlist();

    void print();
    bool isEmpty();
    void append(type* data);
    type* removehead();
    bool deleteNode(type*);

    Node<type>* getHead();
    Node<type>* getTail();
    int getSize();
};

#include "LinkedList.tpp"
#endif // LINKEDLIST_H
