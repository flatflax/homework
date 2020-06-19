//
//  stack.hpp
//  hello world
//
//  Created by 須木 on 2020/5/31.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef stack_hpp
#define stack_hpp

#include <stdio.h>

typedef unsigned long Item;

class Stack
{
private:
    enum { MAX=10 };
    Item items[MAX];
    int top;
public:
    Stack();
    bool isEmpty() const;
    bool isFull() const;
    bool push(const Item & item);
    bool pop(Item & item);
};

#endif /* stack_hpp */
