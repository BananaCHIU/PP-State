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
    ++size;
}

template<typename type>
Queue<type>::~Queue()
{
    while(!isEmpty())
    {
        dequeue();
    }
}

template<typename type>
bool Queue<type>::isEmpty()
{
    return size == 0 ? true : false;
}

template<typename type>
void Queue<type>::enqueue(type* data)
{
    Node<type>* new_node = new Node<type>(data);
    if (isEmpty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

template<typename type>
type* Queue<type>::dequeue()
{
    if (isEmpty()) return nullptr;
    Node<type>* temp = head;
    type* result = temp->data;
    if (head == tail) {
        delete temp;
        head = tail = nullptr;
    } else {
        head = head->next;
        delete temp;
    }
    cout << "dequeue" << endl;
    return result;
}

template<typename type>
void Queue<type>::print(){
    if(isEmpty()) { cout << "empty queue!!" << endl; }
    for(const Node<type>* p = head; p != nullptr; p = p->next){
        cout << p->data << endl;
    }
}

template<typename type>
Node<type>* Queue<type>::getHead(){
    return head;
}

template<typename type>
Node<type>* Queue<type>::getTail(){
    return tail;
}

template<typename type>
int Queue<type>::getSize(){
    return size;
}
