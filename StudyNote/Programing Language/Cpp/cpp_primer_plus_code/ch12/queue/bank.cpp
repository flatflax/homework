//
//  bank.cpp
//  hello world
//
//  Created by 須木 on 2020/6/9.
//  Copyright © 2020 須木. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "queue.hpp"

const int MIN_PER_HR = 60;

bool newcustomer(double x);

int ch12_queue_main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
    
    std::srand((unsigned)std::time(0));
    
    cout << "enter max size of queue: ";
    int qs;
    cin >> qs;
    Queue line(qs);
    
    cout << "enter the number of sim h: ";
    int hours;
    cin >> hours;
    long cyclelimit =  MIN_PER_HR * hours;
    
    cout << "enter the avg num of cumsters per hours: ";
    double perhour;
    cin >> perhour;
    double min_per_cust;
    min_per_cust = MIN_PER_HR / perhour;
    
    Item temp;
    long turnways = 0;
    long customers = 0;
    long served = 0;
    long sum_line = 0;
    int wait_time = 0;
    long line_wait = 0;
    
    for (int cycle=0; cycle < cyclelimit; cycle++)
    {
        // 如果有新顾客，加入队列
        if(newcustomer(min_per_cust))
        {
            if(line.isfull())
                turnways++;
            else{
                customers++;
                temp.set(cycle);
                line.enqueue(temp);
            }
        }
        // 等待时间归零，当前顾客处理结束，获取新顾客，设定等待时间
        if(wait_time <=0 && !line.isempty())
        {
            line.dequeue(temp);
            wait_time = temp.ptime();
            line_wait += cycle - temp.when();       // 用于计算平均等待时间
            served++;
        }
        if(wait_time > 0)
        {
            wait_time--;
        }
        // 用于计算平均队列长度
        sum_line += line.queuecount();
    }
    
    if(customers > 0)
    {
        cout << "customers accepted: " << customers << endl;
        cout << "    customers served: " << served << endl;
        cout << "    turnaways: " << turnways << endl;
        cout << "average queue size:" ;cout.precision(2);
        cout.setf( ios_base::fixed, ios_base::floatfield );
        cout.setf( ios_base::showpoint );
        cout << (double) sum_line / cyclelimit << endl;
        cout << "average wait time:" << (double) line_wait / served << " mins\n";
    }
    else
        cout << "No customers.\n";
    cout << "Doen.\n";
    return 0;
}


bool newcustomer(double x)
{
    return ( std::rand()*x / RAND_MAX < 1 );
}
