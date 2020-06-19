//
//  onlyinstance.hpp
//  hello world
//
//  Created by 須木 on 2020/6/10.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef onlyinstance_hpp
#define onlyinstance_hpp

#include <stdio.h>

class TheOnlyInstance
{
public:
    static TheOnlyInstance * GetTheOnlyInstance();
protected:
    TheOnlyInstance(){};
private:
    // private data
};

#endif /* onlyinstance_hpp */
