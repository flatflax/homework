//
//  onlyinstance.cpp
//  hello world
//
//  Created by 須木 on 2020/6/10.
//  Copyright © 2020 須木. All rights reserved.
//

#include "onlyinstance.hpp"

TheOnlyInstance * TheOnlyInstance::GetTheOnlyInstance()
{
    static TheOnlyInstance objectTheOnlyInstace;
    return &objectTheOnlyInstace;
}
