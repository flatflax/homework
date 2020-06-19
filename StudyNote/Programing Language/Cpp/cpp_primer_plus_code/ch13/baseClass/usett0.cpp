//
//  usett0.cpp
//  hello world
//
//  Created by 須木 on 2020/6/9.
//  Copyright © 2020 須木. All rights reserved.
//

#include <iostream>
#include "tabtenn0.hpp"

int ch13_base_class_main(void)
{
    using std::cout;
    using std::endl;
    TableTennisPlayer player1("Chuck", "B", true);
    RatedPlayer rplayer1(1140, "Mallory", "D", false);
    
    rplayer1.Name();
    if(rplayer1.HasTable())
    {
        cout << ": has a table.\n";
    }
    else
        cout << ": has not a table.\n";
    
    player1.Name();
    if(player1.HasTable())
    {
        cout << ": has a table.\n";
    }
    else
        cout << ": has not a table.\n";
    
    rplayer1.Name();
    cout << "; rating: " << rplayer1.Rating() << endl;
    
    RatedPlayer rplayer2(1212, player1);
    rplayer2.Name();
    cout << "; rating: " << rplayer2.Rating() << endl;
    
    return 0;
}
