//
//  studentc.cpp
//  hello world
//
//  Created by 須木 on 2020/6/11.
//  Copyright © 2020 須木. All rights reserved.
//

#include "studentc.hpp"
using std::ostream;
using std::endl;
using std::istream;
using std::string;


// public method
double Student::Average() const
{
    if (ArrayDb::size() > 0)
        return ArrayDb::sum()/ArrayDb::size();
    else
        return 0;
}

const string & Student::Name() const
{
    return (const string &) *this;
}

double & Student::operator[](int i)
{
    return ArrayDb::operator[](i);
}

double Student::operator[](int i) const
{
    return ArrayDb::operator[](i);
}

// private method
ostream & Student::arr_out(std::ostream & os) const
{
    int i;
    int lim = (int)ArrayDb::size();
    if(lim > 0)
    {
        for(i=0;i<lim;i++)
        {
            os << ArrayDb::operator[](i) << " ";
            if(i % 5 == 4)
                os << endl;
        }
        if(i % 5 != 0)
            os << endl;
    }
    else
        os << "Empty array.";
    return os;
}

// friends
istream & operator>>(istream & is, Student & st)
{
    is >> (string &)st;
    return is;
}

istream & getline(istream & is, Student & st)
{
    getline(is, (string &)st);
    return is;
}

ostream & operator<<(ostream & os, Student & st)
{
    os << "Scores for " << (const string &)st << ":\n";
    st.arr_out(os);
    return os;
}
