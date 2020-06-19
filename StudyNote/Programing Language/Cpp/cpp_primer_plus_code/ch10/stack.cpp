//
//  stack.cpp
//  hello world
//
//  Created by 須木 on 2020/5/31.
//  Copyright © 2020 須木. All rights reserved.
//

#include "stack.hpp"

Stack::Stack()
{
    top = 0;
}

bool Stack::isEmpty() const
{
    return top == 0;
}

bool Stack::isFull() const
{
    return top == MAX;
}

bool Stack::push(const Item &item)
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else return false;
}

bool Stack::pop(Item &item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}
