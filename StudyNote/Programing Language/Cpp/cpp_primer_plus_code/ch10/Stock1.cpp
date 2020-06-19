//
//  Stock1.cpp
//  hello world
//
//  Created by 須木 on 2020/5/30.
//  Copyright © 2020 須木. All rights reserved.
//

#include <iostream>
#include "Stock1.hpp"

using namespace std;

void Stock::acquire(const char * co, int n, double pr)
{
    company = co;
    if (n < 0){
        shares=0;
    }
    else
        shares=n;
    share_val=pr;
    set_tot();
}

void Stock::buy(int num, double price)
{
    if (num < 0)
    {
        std::cerr << "number invalid.¥n";
    }
    else{
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(int num, double price)
{
    if (num < 0)
    {
        std::cerr << "number invalid.¥n";
    }
    else{
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show()
{
    std::cout << "company: " << company
            << " shares: " << shares << std::endl
            << " share price: $" << share_val
            << " total worth: $" << total_val << std::endl;
}

Stock::Stock(const char * co, int n, double pr)
{
    company = co;
    if (n < 0){
        shares=0;
    }
    else
        shares=n;
    share_val=pr;
    set_tot();
}

Stock::Stock(){
    company = "no name";
    shares = 0;
    share_val = 0;
    total_val = 0;
}

Stock::~Stock(){
    std::cout << "stock class " << company << " has been destructor."<< std::endl;
}

const Stock & Stock::topval(const Stock & s) const{
    if (s.total_val > total_val){
        return s;
    }
    else{
        return *this;
    }
}
