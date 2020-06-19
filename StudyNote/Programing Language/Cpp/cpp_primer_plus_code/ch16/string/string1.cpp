//
//  string1.cpp
//  cpp_primer_plus
//
//  Created by 須木 on 2020/6/17.
//  Copyright © 2020 須木. All rights reserved.
//


// str1.cpp -- introducing the string
#include <iostream>
#include <string>
// using string constructors

int ch16_string1_main() {
    using namespace std;
    string one("Lottery Winner!");
    cout << one << endl;
    
    string two(20, '$');
    cout << two << endl;
    
    string three(one);
    cout << three << endl;
    
    one += " Oops!";
    cout << one << endl;
    
    two = "Sorry! That was ";
    three[0] = 'P';
    string four;
    four = two + three;
    cout << four << endl;
    
    char alls[] = "All's well that ends well";
    string five(alls,20);
    cout << five << "!\n";
    
    string six(alls+6, alls + 10); // ctor #6
    cout<<six <<",";
    
    string seven(&five[6], &five[10]);// ctor #6 again
    cout << seven << "...\n";
    return 0;
    
}
