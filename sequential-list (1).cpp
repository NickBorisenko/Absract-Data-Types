#include "sequential-list.h"
#include <iostream>
using namespace std;

SequentialList::SequentialList(unsigned int cap)
{
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType[capacity_]; // creates DataType array
}

SequentialList::~SequentialList()
{
   delete []data_; // deletes the data_ array
   size_ = 0;
   capacity_ = 0;
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if (size_ == 0)
        return true;
    else
        return false;
}

bool SequentialList::full() const
{
    if (capacity_ == size_)
        return true;
    else
        return false;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
   return data_[index];
}

unsigned int SequentialList::search(DataType val) const
{
    for (int index = 0; index < capacity_-1; ++index) // goes through every index searching if the value matches.
    {
        if (data_[index]==val)
        {
            return index; // returns the index of the value if found.
        }
    }
    return size_; // returns the size of the list if value is not found.
}

void SequentialList::print() const
{
    for (int index = 0; index < size_; ++index)
    {
        cout << data_[index] << "  "; //prints the list elements to the console.
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (!full() && index >= 0 && index <=size_) //check to see if the list is full and if the input index is valid.
    {
        for (unsigned int count=size_; count > index; --count)
        {
            data_[count] = data_[count - 1]; //shifts the contents of the list right, starting from the index.
        }
        data_[index] = val; // assigns the value to the index.
        size_++;
        return true;
    }
    return false;
}

bool SequentialList::insert_front(DataType val)
{
    return insert(val,0); // shifts all list contents to the right and inserts the value to the front.
}

bool SequentialList::insert_back(DataType val)
{
    return insert(val, size_); // inserts the value to the back of the list.
}

bool SequentialList::remove(unsigned int index)
{
    if (!empty() && index >= 0 && index < size_) //checks if the list is empty and if input index is valid.
    {
        for (unsigned int count = index ; count < size_-1; ++count)
        {
            data_[count] = data_[count+1]; //shifts the list contents to the left from the end to the index.
        }
        data_[size_-1] = 0; // removes the duplicated value at the end of the list.
        size_--;
        return true;
    }
    return false;
}

bool SequentialList::remove_front()
{
    return remove(0); // removes the front list value and shifts the list contents to the left.
}

bool SequentialList::remove_back()
{
   return remove(size_-1); // removes the last value in the list
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (size_ > 0 && index >= 0 && index < size_) // checks if the list is empty and if the index input is valid.
    {
        data_[index] = val; // replaces a index of the list to another value.
        return true;
    }
    return false;
}

