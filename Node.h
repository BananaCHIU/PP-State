#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include "Block.h"

template <typename type>
class Node{
public:
    type* data;
    Node* next {nullptr};

    Node(type* x);
    ~Node();
};

#include "Node.tpp"
#endif // NODE_H
