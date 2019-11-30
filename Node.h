#ifndef NODE_H
#define NODE_H

#include <QPoint>
#include "Block.h"
#include "Queue.h"


template <typename type>
class Node{
    type t;
    Node* next;

public:
    ~Node();
};

#endif // NODE_H
