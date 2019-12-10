#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename type>
class Queue{
    Node<type> *head {nullptr};
    Node<type> *tail {nullptr};
    int size {0};
public:
    Queue();
    Queue(type* x);
    ~Queue();

    void print();
    bool isEmpty();
    void enqueue(type* data);
    type* dequeue();

    Node<type>* getHead();
    Node<type>* getTail();
    int getSize();
};

#include "Queue.tpp"
#endif // QUEUE_H
