#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include "Block.h"

template <typename type>
class Node{
public:
    type data;
    Node* next {nullptr};

    Node(type x);
    ~Node();
};

template <>
class Node <Block>{
public:
    Block* data;
    Node* next {nullptr};

    Node(Block* x);
    ~Node();
};
#endif // NODE_H
