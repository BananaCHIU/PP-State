#include<QPoint>
#include "Block.h"
#include "Node.h"

template<typename type>
Node<type>::Node(type* x) : data(x) {

}

Node<Block>::Node(Block* x) : data(x){

}

template<typename type>
Node<type>::~Node()
{
    delete data;
}

Node<Block>::~Node()
{
    delete data;
}

