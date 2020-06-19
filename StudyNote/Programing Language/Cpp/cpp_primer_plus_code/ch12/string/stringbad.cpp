//
//  stringbad.cpp
//  hello world
//
//  Created by 須木 on 2020/6/3.
//  Copyright © 2020 須木. All rights reserved.
//

#include "stringbad.hpp"
#include <cstring>
using std::cout;
using std::cin;

int StringBad::num_string = 0;      // 初始化静态成员,使用作用域操作符指定类

// static method
int StringBad::HowMany()
{
    return num_string;
}

// class method
StringBad::StringBad(const char * s)
{
    len = (int)std::strlen(s);
    str = new char[len+1];
    std::strcpy(str, s);
    num_string++;
//    cout << num_string << ":\"" << str << "\" object create \n";
}

StringBad::StringBad(const StringBad & st)
{
    num_string++;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str, st.str);
//    cout << num_string << ":\"" << str << "\" object create \n";
}

StringBad::StringBad()
{
    len = 0;
    str = new char[1];      // 和析构函数兼容
    str[0] = '\0';
    num_string++;
//    cout << num_string << ":\"" << str << "\" object create \n";
}

StringBad::~StringBad()
{
//    cout << "\"" << str << "\" object deleted, ";
    --num_string;
//    cout << num_string << " left\n";
    delete [] str;      // 释放构造函数中由new分配的内存
}


// overload oprator methods
StringBad & StringBad::operator= (const StringBad & st)
{
    if (this == & st)       // 判断地址
        return *this;
    delete [] str;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str, st.str);
    return *this;
}

StringBad & StringBad::operator= (const char * s)
{
    delete [] str;
    len = (int)std::strlen(s);
    str = new char[len+1];
    std::strcpy(str, s);
    return *this;
}

// read-write char access for non-const String
char & StringBad::operator[](int i)
{
    return str[i];
}

// read-onlu char access for const String
const char & StringBad::operator[](int i) const
{
    return str[i];
}

ostream & operator<< (ostream & os, const StringBad & st)
{
    os << st.str;
    return os;
}

istream & operator>> (istream & is, StringBad & st)
{
    char temp[StringBad::CINLIM];
    is.get(temp, StringBad::CINLIM);
    if(is)
    {
//        st.str = temp;
        delete [] st.str;
        int len = (int)std::strlen(temp);
        st.str = new char[len+1];
        st.len = len;
        std::strcpy(st.str, temp);
    }
    while(is && is.get()!='\n')
        continue;
    return is;
}

bool operator< (const StringBad & st1, const StringBad & st2)
{
    if(std::strcmp(st1.str, st2.str)>0)
        return true;
    else
        return false;
}

bool operator> (const StringBad & st1, const StringBad & st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator== (const StringBad & st1, const StringBad & st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}
