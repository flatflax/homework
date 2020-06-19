//
//  queue.cpp
//  hello world
//
//  Created by 須木 on 2020/6/9.
//  Copyright © 2020 須木. All rights reserved.
//

#include "queue.hpp"
#include <cstdlib>

Queue::Queue(int qs): qsize(qs)     // 成员初始化列表
{
    front = rear = NULL;
    items = 0;
}

Queue::~Queue()
{
    Node * temp;
    while(front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

bool Queue::isempty()const
{
    return items==0;
}

bool Queue::isfull()const
{
    return items==qsize;
}

int Queue::queuecount()const
{
    return items;
}

bool Queue::enqueue(const Item &item)
{
    if(isfull())
        return false;
    Node * add = new Node;
    if (add==NULL)
        return false;
    add->item = item;
    add->next = NULL;
    items++;
    if(front==NULL)
        front = add;
    else
        rear->next = add;
    rear = add;
    return true;
}

bool Queue::dequeue(Item &item)
{
    if(front==NULL)
        return false;
    item = front->item;
    items--;
    Node * temp = front;
    front = front->next;
    delete temp;
    if(items==0)
        rear = NULL;
    return true;
}

// customer method
void Customer::set(long when)
{
    processtime = std::rand() % 3 + 1;
    arrive = when;
}
