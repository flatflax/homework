//
//  mytime0.cpp
//  hello world
//
//  Created by 須木 on 2020/6/1.
//  Copyright © 2020 須木. All rights reserved.
//

#include <iostream>
#include "mytime0.hpp"

Time::Time()
{
    hours=minutes=0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::Sum(const Time &t) const
{
    Time sum;
    sum.minutes = t.minutes + minutes;
    sum.hours = t.hours + hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = t.minutes + minutes;
    sum.hours = t.hours + hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

void Time::Show() const
{
    std::cout << hours << " hours. " << minutes << " minutes." << std::endl;
}

Time operator * (double m, const Time & t)
{
    Time result;
    long total_minutes = t.hours * m * 60 + t.minutes * m;
    result.hours = (int)total_minutes / 60;
    result.minutes = (int)total_minutes % 60;
    return result;
}
