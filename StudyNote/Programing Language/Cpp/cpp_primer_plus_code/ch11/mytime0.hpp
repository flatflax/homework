//
//  mytime0.hpp
//  hello world
//
//  Created by 須木 on 2020/6/1.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef mytime0_hpp
#define mytime0_hpp

#include <stdio.h>

class Time
{
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h, int m = 0);
    void AddMin(int m);
    void AddHr(int h);
    void Reset(int h = 0, int m = 0);
    Time Sum(const Time & t) const;
    Time operator +(const Time & t) const;      // reload func operation +
    void Show() const;
    friend Time operator * (double m, const Time & t);      // friend func opration *
};

#endif /* mytime0_hpp */
