//
//  sayings2.cpp
//  hello world
//
//  Created by 須木 on 2020/6/6.
//  Copyright © 2020 須木. All rights reserved.
//
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "stringbad.hpp"


const int ArSize = 10;
const int MaxLen = 81;

int cp12_string_main()
{
    using namespace std;
    StringBad name;
    cout << "input your name\n";
    cin >> name;

    cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quit. \n";
    StringBad sayings[ArSize];
    char temp[MaxLen];
    int i;
    for(i = 0; i < ArSize; i++)
    {
        cout << i+1 << ":";
        cin.get(temp, MaxLen);
        while(cin && cin.get()!= '\n')
            continue;
        
        if(!cin || temp[0] == '\0')
            break;
        else
            sayings[i] = temp;
    }
    
    int total = i;
    if(total > 0)
    {
        cout << "your sayings:\n";
        for(i=0; i<total; i++)
            cout << sayings[i] << "\n";
        
        
        // get shorest saying and first saying with pt
        StringBad * shortest = &sayings[0];
        StringBad * first = &sayings[0];
        for(i=1; i<total; i++)
        {
            if(sayings[i].length() < shortest->length())
                shortest = &sayings[i];
            if(sayings[i] < *first)
                first = &sayings[i];
        }
        
        cout << "shortest saying:\n" << * shortest << endl;
        cout << "first saying:\n" << *first << endl;
        
        // get favorite saying with pt
        srand((unsigned int)time(0));
        int choice = rand()%total;
        StringBad * favorite = new StringBad(sayings[choice]);
        cout << "my favorite saying:\n" << * favorite << endl;
        delete favorite;
    }
    else
    {
        cout << "no much to say?\n";
    }
    cout << "bye.\n";
    return 0;
    
}
