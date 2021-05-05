#include "doubly-linked-list.h"
#include <iostream>
#include <new>
using namespace std;

DoublyLinkedList::Node::Node(DataType data):
        value(data), next(NULL), prev(NULL)
{
}
DoublyLinkedList::DoublyLinkedList()
        :head_(NULL), tail_(NULL), size_(0)
{
}
/*DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& list)
:size_(list.size_)
{
	


}*/
DoublyLinkedList::~DoublyLinkedList()
{
    Node *temp = head_;
    for (int index = 0; index < size_; ++index) //Goes through each index of the list and deletes each node.
    {
        head_ = temp -> next;
        delete temp;   //frees up allocated memory.
        temp = head_;
    }
    size_ = 0;
}
bool DoublyLinkedList::empty() const
{
    if(size_ == 0)      //checks to see if the list is empty.
        return true;
    return false;

}
unsigned int DoublyLinkedList::size() const
{
    return size_;  //returns the size of the last.
}
void DoublyLinkedList::print() const
{
    Node *temp = head_;
    for (int index = 0; index < size_; ++index)  //prints the contents of the list to the console.
    {
        cout << temp -> value << " ";
        temp = temp -> next;
    }

}
bool DoublyLinkedList::insert_front(DataType value)
{
    return insert(value,0);  //inserts a value to the front of the list.
}
bool DoublyLinkedList::remove_front()
{
    return remove(0);  //removes the value at the front of the list.
}
bool DoublyLinkedList::insert_back(DataType value)
{
   return insert(value,size_);  //inserts a value to the back of the list.
}
bool DoublyLinkedList::remove_back()
{
    return remove(size_-1); //removes the value at the back of the list.
}
bool DoublyLinkedList::insert(DataType value, unsigned int index) //inputs a value at any point in the list
{
    if (!full() && index >= 0 && index <= size_)  //makes sure the index is within the list and not full
    {
        if (index == 0)
        {
            if (size_ == 0)
            {
                Node *node_ = new Node(value); //if there are no values in the list assign the node to the head and tail
                head_ = node_;
                tail_ = node_;
            }
            else
            {
                Node *node_ = new Node(value);
                node_->next = head_;
                head_->prev = node_; //transfers the previous heads info to the new node.
                head_ = node_;  // if input index is 0 and non-empty, make the new node the head.
            }
        }
        else if (index == size_)
        {
            Node *node_ = new Node(value);
            node_ ->prev = tail_; // assigns previous tails info to the new node.
            node_ ->next = NULL;
            tail_ -> next = node_;
            tail_ = node_;  // assigns the new node to be the tail.

        }
        else
        {
            Node *node_ = new Node(value);
            node_ -> next = getNode(index);
            node_ -> prev = getNode(index-1);

            Node *tempNodeAfter= getNode(index); //creates an temporary node of index.
            tempNodeAfter -> prev = node_; // assigns the previous node to the new node value being added.

            Node *tempNodeBefore = getNode(index-1); // creates temporary node of the node left of the index.
            tempNodeBefore -> next = node_; // assigns the next node to the new node value being added.
        }
        size_++;
        return true;
    }
    return false;
}
bool DoublyLinkedList::remove(unsigned int index)
{
    if (index >= 0 && index < size_)
    {
        if (index == 0)
        {
            if (size_ > 1)
            {
                Node *temp = getNode(index);
                head_ = temp->next;
                delete temp; // frees up allocated memory.
                head_ -> prev = NULL; // assigns the head node to second one in series.
            }
            else
            {
                head_ = NULL;
                tail_ = NULL;  //assigns the head and tail to NULL because the list is empty.
            }
        }
        else if (index == size_-1)
        {
            Node *temp = getNode(index);
            tail_ = temp->prev;
            delete temp;
            tail_ -> next= NULL;    // removes the final node and makes the second last one the new tail.
        }
        else
        {
            Node *temp = getNode(index);

            Node *tempNodeAfter = temp -> next; //creates temporary nodes to save info.
            Node *tempNodeBefore = temp -> prev;

            tempNodeAfter -> prev = tempNodeBefore;
            tempNodeBefore -> next = tempNodeAfter;  // nodes skip over the removed node.

            delete temp; //deletes the old node.
        }
        size_--;
        return true;
    }
    return false;
}
unsigned int DoublyLinkedList::search(DataType value) const //searches if the list contains a certain value.
{
    Node *temp = head_;
    for (int listIndex = 0; listIndex < size_; ++listIndex)
    {
        if (temp -> value == value)
        {
            return listIndex;
        }
        temp = temp->next;
    }
    return size_;
}
DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const //finds the value a index
{
    if(index >=0 && index < size_) // makes sure the index is valid.
    {
        Node *temp = getNode(index);
        return temp->value;
    }
    else
    {
        return tail_->value;
    }
}
bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index >= 0 && index <size_) {
        remove(index);      //removes the value at the certain index.
        insert(value,index); //adds the desired value back into the index.
        return true;
    }
    return false;
}
DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    if (index >=0 && index < size_) {
        Node *temp = head_;
        for (int listIndex = 0; (listIndex < index) && (temp->next != NULL); ++listIndex) {
            temp = temp->next; //goes to the desired node in the list given the index.
        }
        return temp; //returns the node at that index in the list.
    }
    else
    {
        return NULL;
    }
}
bool DoublyLinkedList::full() const // checks to see if the list is full.
{
    if (size_ >= CAPACITY)
        return true;
    return false;
}
