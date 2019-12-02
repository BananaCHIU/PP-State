#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"


template <typename type>
class Queue{
    Node<type> *head {nullptr};
    Node<type> *tail {nullptr};

public:
    Queue(const type& x);
    ~Queue();

    bool isEmpty();
    void enqueue(const type *&data);
    type* dequeue();
};

#endif // QUEUE_H
