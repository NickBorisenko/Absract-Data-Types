#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    init_capacity_ = 16;
    items_ = new StackItem[init_capacity_]; //creates the stack array given the base 16 size.
    size_ = 0;
    capacity_ = init_capacity_;
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    items_ = new StackItem[capacity]; // creates stack array of desired size.
    size_ = 0;
    init_capacity_ = capacity;
    capacity_ = capacity;
}

DynamicStack::~DynamicStack()
{
    delete []items_; // deallocates the memory of the array when it's asked to be deleted.
    size_ = 0;
    capacity_ = 0;
    init_capacity_ = 0;
}

bool DynamicStack::empty() const
{
    if (size_ == 0) //checks to see if the stack is empty.
        return true;
    return false;
}

int DynamicStack::size() const
{
    return size_; //returns the size/number of elements in the stack.
}

void DynamicStack::push(StackItem value) //pushes a value at the top of the stack.
{
    if (size_ < capacity_) // checks to see if the stack has reached the capacity.
    {
        items_[size_] = value; // places desired value at the end of the array/top of the stack.
    }
    else if(size_ >= capacity_)
    {
        capacity_ = capacity_*2;
        StackItem* tempList;
        tempList = new StackItem[capacity_]; //creates a larger temporary array to store stack contents.

        for (int itemIndex = 0; itemIndex < size_; ++itemIndex)
        {
            tempList[itemIndex] = items_[itemIndex]; // transfers item data from the shorter array to the larger one.
        }
        items_ = tempList; // assigns the new array to the main item stack.
        items_ [size_] = value; // adds the desired value at the top of the stack.
    }
    size_++;

}

DynamicStack::StackItem DynamicStack::pop()
{
    double fillPercent = ((size_-1)*1.0)/(capacity_*1.0); //Calculates how full the stack is if one item is removed.
    if (empty())
    {
        return EMPTY_STACK;
    }
    else if (fillPercent <= 0.25 && (capacity_/2)>=init_capacity_)//checks to see if a quarter of the stack is required.
    {                                                  //checks if halving the stack size is more then the initial size.
        StackItem top = items_[size_-1]; //saves the value of the item being removed
        items_[size_-1] = NULL; // removes the item at the top of the stack.
        size_--;
        capacity_ = capacity_/2; //halving the capacity.
        StackItem* tempList;  //creates a smaller temporary array to store the larger stack data.
        tempList = new StackItem[capacity_];
        for (int itemIndex = 0; itemIndex < size_; ++itemIndex)
        {
            tempList[itemIndex] = items_[itemIndex]; // copies data from the larger stack to the smaller one.
        }
        items_ = tempList; //makes the new smaller array the main item stack.
        return top;
    }
    else
    {
        StackItem top = items_[size_-1];
        items_[size_-1] = NULL; // removes the item at the top of the stack.
        size_--;
        return top;
    }
}
DynamicStack::StackItem DynamicStack::peek() const
{
    if (!empty())
        return items_[size_-1]; //returns the item at the top of the stack.
    else
        return EMPTY_STACK;
}

void DynamicStack::print() const //prints the contents of the stack from top to bottom.
{
    for (int itemIndex = size_-1; itemIndex >= 0; itemIndex--)
    {
        cout << items_[itemIndex] << endl;
    }
}
