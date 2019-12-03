#include "Node.h"
#include "Queue.h"
#include <iostream>
using namespace std;

template<typename type>
Queue<type>::Queue() : head(nullptr), tail(nullptr){}

template<typename type>
Queue<type>::Queue(type* x) {
    Node<type>* n = new Node<type>(x);
    head = n;
    tail = n;
}

Queue<Block>::Queue(Block* x) {
    Node<Block>* n = new Node<Block>(x);
    head = n;
    tail = n;
}

template<typename type>
Queue<type>::~Queue()
{

}

template<typename type>
bool Queue<type>::isEmpty()
{
    return head == nullptr ? true : false;
}

template<typename type>
void Queue<type>::enqueue(type* data)
{
    Node<type> * new_node = new Node<type>(data);
    if (isEmpty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

template<typename type>
type *Queue<type>::dequeue()
{
    if (isEmpty()) return nullptr;
    type* result = head->data;
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        delete head;
        head = head->next;
    }
    return result;
}

template<typename type>
void Queue<type>::print(){
    for(const Node<type>* p = head; p; p = p->next){
        cout << p->data << endl;
    }
}

void Queue<Block>::print(){
    for(const Node<Block>* p = head; p; p = p->next){
        cout << p->data << endl;
    }
}
