//
//  stringbad.hpp
//  hello world
//
//  Created by 須木 on 2020/6/3.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef stringbad_hpp
#define stringbad_hpp

#include <stdio.h>
#include <iostream>

using std::ostream;
using std::istream;

class StringBad
{
private:
    char * str;
    int len;
    static int num_string;
    static const int CINLIM = 80;   // cin input limit
public:
    // constructors
    StringBad(const char * s);
    StringBad(const StringBad & st);    // deep copy constructor 重复构造函数
    StringBad();
    ~StringBad();
    int length() const { return len; }
    // overload oprator methods
    StringBad & operator= (const StringBad & st);   // 赋值操作符
    StringBad & operator= (const char *);   // 赋值操作符
    char & operator[](int i);
    const char & operator[](int i) const;
    // overload operator friends
    friend ostream & operator<< (ostream & os,
                                      const StringBad & st);
    friend istream & operator>> (istream & is, StringBad & st);
    friend bool operator< (const StringBad & st1, const StringBad & st2);
    friend bool operator> (const StringBad & st1, const StringBad & st2);
    friend bool operator== (const StringBad & st1, const StringBad & st2);
    // static func
    static int HowMany();
    };

#endif /* stringbad_hpp */
