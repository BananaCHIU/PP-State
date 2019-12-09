#include<QPoint>
#include "Block.h"
#include "Node.h"

template<typename type>
Node<type>::Node(type* x) : data(x) {

}

template<typename type>
Node<type>::~Node()
{
<<<<<<< HEAD:Node.tpp
    delete data;

=======
    // to be implemented
>>>>>>> monster:Node.cpp
}
