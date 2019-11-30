#include<QPoint>
#include "Block.h"
#include "Node.h"

template <>
class Node <Block> {

    Block b;

public:

};

template <>
class Node <Queue*> {

    Queue* q;

public:

};
