//
//  use_tv.cpp
//  hello world
//
//  Created by 須木 on 2020/6/15.
//  Copyright © 2020 須木. All rights reserved.
//

#include <iostream>
// #include "tv.hpp"    // friend class
#include "tvfm.h"       // friend member func


int ch15_friend_class_main() {
    using std::cout;
    Tv s27;
    cout << "Initial settings for 27\" TV:\n";
    s27.settings();
    s27.onoff();
    s27.chanup();
    cout << "\nAdjusted settings for 27\" TV:\n";
    s27.settings();
    
    Remote grey;
    
    grey.set_chan(s27, 10);
    grey.volup(s27);
    grey.volup(s27);
    cout << "\n27\" settings after using remote:\n";
    s27.settings();
    
    Tv s32(Tv::On);
    s32.set_mode();
    grey.set_chan(s32, 28);
    cout << "\n32\" settings:\n";
    s32.settings();
    
    return 0;
}
