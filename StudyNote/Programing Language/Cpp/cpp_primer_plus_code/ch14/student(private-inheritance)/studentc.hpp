//
//  studentc.hpp
//  hello world
//
//  Created by 須木 on 2020/6/11.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef studentc_hpp
#define studentc_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <valarray>

class Student: private std::string, private std::valarray<double>       // private inheritance
{
private:
    typedef std::valarray<double> ArrayDb;
    std::ostream & arr_out(std::ostream & os) const;
public:
    Student(): std::string("Null Student"), ArrayDb() {}
    Student(const std::string &s): std::string(s), ArrayDb(){}
    explicit Student(int n): std::string("Null Student"), ArrayDb(n){}
    Student(const std::string &s, int n): std::string(s), ArrayDb(n){}
    Student(const std::string &s, const double * pd, int n): std::string(s), ArrayDb(pd,n){}
    ~Student(){}
    double Average() const;
    const std::string & Name() const;
    double & operator[](int i);
    double operator[](int i) const;
    //friends
    friend std::istream & operator>>(std::istream & is, Student & st);
    friend std::istream & getline(std::istream & is, Student & st);
    friend std::ostream & operator<<(std::ostream & os, Student & st);
};

#endif /* studentc_hpp */
