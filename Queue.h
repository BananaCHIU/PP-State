#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename type>
class Queue{
    Node<type> *head {nullptr};
    Node<type> *tail {nullptr};

public:
    Queue();
    Queue(type* x);
    ~Queue();

    void print();
    bool isEmpty();
    void enqueue(type* data);
    type* dequeue();
};

template <>
class Queue<Block>{
    Node<Block> *head {nullptr};
    Node<Block> *tail {nullptr};

public:
    Queue();
    Queue(Block* x);
    ~Queue();

    void print();
    bool isEmpty();
    void enqueue(Block* data);
    Block* dequeue();
};
#endif // QUEUE_H
