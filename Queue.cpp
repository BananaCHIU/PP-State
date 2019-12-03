#include "Queue.h"

template<typename type>
bool Queue<type>::isEmpty()
{
    return head == nullptr ? true : false;
}

template<typename type>
void Queue<type>::enqueue(const type *&data)
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
Queue<type>::~Queue(){
    // to be implemented
}
