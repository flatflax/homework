//
//  queue.hpp
//  hello world
//
//  Created by 須木 on 2020/6/9.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>

class Customer
{
private:
    long arrive;
    int processtime;
public:
    Customer(){ arrive=processtime=0; }
    void set(long when);
    long when() const { return arrive; }
    int ptime() const { return processtime; }
};

typedef Customer Item;

class Queue
{
private:
    // class scope definitions
    struct Node { Item item; struct Node * next; };
    enum { Q_SIZE=10 };
    // private class members
    Node * front;
    Node * rear;
    int items;          // current num
    const int qsize;    // max num
    // preemptive difinitions to prevent public copy
    Queue (const Queue & q): qsize(0) { };
    Queue & operator= (const Queue & q ) { return *this; };
public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &item);
    bool dequeue(Item &item);
};

#endif /* queue_hpp */
