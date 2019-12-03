#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include "Block.h"


template <typename type>
class Node{
    type* data;
    Node* next {nullptr};

public:
    Node(const type& x);
    ~Node();
};

#endif // NODE_H
