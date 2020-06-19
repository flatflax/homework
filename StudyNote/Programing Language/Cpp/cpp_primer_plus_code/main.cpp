//
//  main.cpp
//  hello world
//
//  Created by 須木 on 2020/5/23.
//  Copyright © 2020 須木. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>

#include "ch01-09/cpp_primer_plus.hpp"
#include "ch10/Stock1.hpp"
#include "ch11/mytime0.hpp"

void ch10_class(void);
void ch11_class(void);

//int main(int argc, const char * argv[]) {
//    ch11_class();
//    return 0;
//}

void ch10_class(){
    Stock stock1("NanoSmart", 12, 20.0);
    stock1.show();
    Stock stock2;
    stock2.show();
    
    stock1 = Stock("NanoSmaer1", 12, 20.0);
    stock1.show();
}

void ch11_class()
{
    Time planning;
    Time coding(2, 40);
    Time fixing(5, 55);
    Time total;
    Time total2;
    Time result;
    
    planning.Show();
    coding.Show();
    fixing.Show();
    total = coding.Sum(fixing);
    total.Show();
    total2 = coding + fixing;       // reload func operation +
    total2.Show();
    result = operator*(2, coding);    // friend func opration *
    result.Show();
}
