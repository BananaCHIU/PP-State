#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include "Block.h"
#include "Queue.h"


template <typename type>
class Node{
    type data;
    Node* next;

public:
    Node(const type& x) : data(x) { }
    ~Node();
};

#endif // NODE_H
