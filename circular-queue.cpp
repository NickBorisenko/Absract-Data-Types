#include "circular-queue.h"
#include <iostream>
using namespace std;
const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    capacity_ = 16;
    items_ = new QueueItem[capacity_]; //creates the queue array given the base 16 size.
    head_ =0;
    tail_ = 0;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    items_ = new QueueItem[capacity]; // creates queue array of desired size.
    size_ = 0;
    head_ =0;
    tail_ = 0;
    capacity_ = capacity;
}

CircularQueue::~CircularQueue()
{
    delete []items_; // deallocates the memory of the array when it's asked to be deleted.
    size_ = 0;
    head_ =0;
    tail_ = 0;
    capacity_ = 0;
}

bool CircularQueue::empty() const
{
    if (size_ == 0) //checks to see if the queue is empty.
        return true;
    return false;
}

bool CircularQueue::full() const
{
    if (size_==capacity_) //checks to see if the queue is full.
        return true;
    return false;
}

int CircularQueue::size() const
{
    return size_; //returns the size/number of elements in the queue.
}

bool CircularQueue::enqueue(QueueItem value)
{
    if (full())
        return false;
    else
    {
        items_[tail_]= value; // inputs value data at the tail spot opening.
        tail_ = (tail_+1)%capacity_; // moves the tail down to the next free spot.
        size_++;
        return true;
    }
}
CircularQueue::QueueItem CircularQueue::dequeue()
{
    if (empty())
        return EMPTY_QUEUE;
    else
    {
        QueueItem temp_Item = items_[head_]; // saves the head value as a temporary variable.
        items_[head_]=NULL;
        head_ = (head_+1)%capacity_; // moves the head down to the next item in the queue.
        size_--;
        return temp_Item;
    }
}

CircularQueue::QueueItem CircularQueue::peek() const
{
    if (empty())
        return EMPTY_QUEUE;
    else
        return items_[head_]; //returns the item at the head of the queue.
}

void CircularQueue::print() const
{

    for(int indexItems = 0; indexItems < size_; ++indexItems) //prints out the queue items in order(first in/first out).
    {
        cout << items_[(head_+indexItems)%capacity_] << endl;
    }
}
