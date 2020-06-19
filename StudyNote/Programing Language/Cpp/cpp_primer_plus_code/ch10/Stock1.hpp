//
//  Stock1.hpp
//  hello world
//
//  Created by 須木 on 2020/5/30.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef Stock1_hpp
#define Stock1_hpp

#include <iostream>
#include <cstring>

class Stock
{
private:
    std::string company;
    int shares;
    double share_val;
    double total_val;
    void set_tot() {total_val = shares * share_val;}
public:
    Stock(const char * co, int n, double pr);
    Stock();
    ~Stock();
    void acquire(const char * co, int n, double pr);
    void buy(int num, double price);
    void sell(int num, double price);
    void update(double price);
    void show();
    const Stock & topval(const Stock & s) const;
};

#endif /* Stock1_hpp */
