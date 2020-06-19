//
//  cpp_primer_plus.hpp
//  hello world
//
//  Created by 須木 on 2020/5/26.
//  Copyright © 2020 須木. All rights reserved.
//

#ifndef cpp_primer_plus_hpp
#define cpp_primer_plus_hpp

void void_enum(void);
void void_string(void);
void input_test(void);
void cal_sec(void);
void void_address(void);
char * get_name(void);
void void_const_pt(void);
void void_save(void);

template <class Any>
void void_swap(Any &a, Any &b){
    Any temp;
    temp = a;
    a = b;
    b = temp;
}

#endif /* cpp_primer_plus_hpp */
