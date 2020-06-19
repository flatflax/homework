//
//  cpp_primer_plus.cpp
//  hello world
//
//  Created by 須木 on 2020/5/26.
//  Copyright © 2020 須木. All rights reserved.
//

#include "cpp_primer_plus.hpp"
#include <string>
#include <cstring>
#include <iostream>

struct inflatable{
    char name[20];
    float volume;
    double price;
    union id{
        std::string id_string;
        int id_num;
    };
};

void void_const_pt(){
    int age = 39;
    const int * pt = &age;
    std::cout << age << " " << &age << std::endl;
    std::cout << *pt << " " << pt << std::endl;
    age = 20;
    std::cout << age << " " << &age << std::endl;
    std::cout << *pt << " " << pt << std::endl;

}

void void_save(){
    // auto-save
    char * name = get_name();  // variable temp(recycle after func over)
    // static-save
    static double fee = 56.50;
    
    std::cout << name << fee << std::endl;
    // dynamic-save (with new & delete)
    int * i_array = new int[2];
    delete [] i_array;
}

char * get_name(){
    char temp[80];
    std::cout << "enter last name: ";
    std::cin >> temp;
    char * pn = new char[std::strlen(temp)+1];
    std::strcpy(pn, temp);
    return pn;
}

void void_address(){
    int i_num = 10;
    int * i_pointer = &i_num;
    std::cout << "address:" << i_pointer << "; value:" << *i_pointer << std::endl;
    
    int * i_array = new int[2];
    i_array[0] = 1;
    i_array[1] = 2;
    i_array[2] = 4;

    std::cout << "i_array[0]:" << *i_array << "; i_array[1]:" << *i_array+1 << std::endl;
    ++i_array;
    std::cout << "now i_array[0]:" << *i_array << std::endl;
    --i_array;
    delete [] i_array;  // new & delete
}

void void_enum(){
    enum spectrum{red, orange, yellow, green, blue, violet};
    spectrum band;
    band = blue;
    std::cout << band << "   ";
    int color = 1 + band;
    std::cout << color << std::endl;
    
    enum bits{one=1, two=2, four=4, eight=8};
    bits bit = two;
    std::cout << bit << std::endl;
}

void void_string(){
    using namespace std;
    string s1 = "string";
    std::cout<<s1<<std::endl;
}

void input_test(){
    char a[20];
    std::cout << "input sth" << std::endl;
    std::cin >> a;
    std::cout << "input a line" << std::endl;
    std::cin.getline(a,20);   // 会将上一cin的回车作为该行的输入值
    std::cout<<strlen(a)<<" "<<sizeof(a)<<std::endl;
}

void cal_sec(){
    const int count = 60;
    int second, min, hour;
    
    hour = 0;
    
    std::cout << "please input a sec number" << std::endl;
    std::cin >> second;

    min = second / count;
    hour = min / count;
    min = min % count;
    second = second % count;
    
    std::cout << hour << "h, " << min << "min, " << second << "sec" << std::endl;
}

