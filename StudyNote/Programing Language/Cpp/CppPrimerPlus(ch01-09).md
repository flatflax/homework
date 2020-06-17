# CppPrimerPlus(ch01-ch09)

## ch01: Intro

结构化编程（引入循环和if-else判断），OOP， 多态（为函数创建多个定义，根据上下文选择使用的定义）， 通用编程(generic programing)

编译器：(2005ver)
- UNIX :C++编译器 CC命令编译
  CC spiffy.c [编译器]—> spiffy.o [系统链接程序]—>a.out

- Linux :GNU g++编译器
  g++ spiffy.c —> a.out

- Windows :Gpp编译器
  gpp great.cpp —> a.exe

- Wins IDE compiler: compile, build, make, link, run

## ch02:cpp程序基础结构
```cpp
#include (Header file 头文件, include file包含文件); 
using namespace <name>; 	//命名空间

int main(){
  return 0;
}		

```



## ch03: 常见数据类型

本节讲到的常见数据类型主要是整形和浮点数。

* **整型溢出**：重置点: 
  * 有符号整数(-32767 --> +32767) 2bytes (short or some int) ;
  * 无符号整数(+65535 --> 0) unsigned short/int/long

- long long / unsigned long: 64 bytes

```cpp
int a = 0x42;	// hex int 
int b = 042; 	// octal int
long c = 20L; 	// long
unsigned d = 20U; 	// unsigned int
unsigned long e = 20LU;	// unsigned long
```

Limits文件：记录各个整形的限制
Const 常量

## ch04:复合数据类型

本节讲到的复合数据类型：数据、结构(structure)、指针

- array： typeName arrayName[arraySize];
- C-风格字符串: ¥0结束
- Struct, struct array, 
- Union, anonymous union: 当数据项使用多种格式中的其中一种时，可以节省空间
- Enum 枚举
- 指针pointer和内存address
  声明、赋值、解除引用、区分指针和指针指向的值、指针算术、数组的动态联编和静态联编、数组表示法和指针表示法

```cpp
// 动态分配内存
int* i(address) = new int; 		// new分配
i = (int*) 0xB8000000;	//转型
int p = 34;
int* p_address = &p;
```

New和delete需要配对使用，否则会出现内存泄漏(被分配的内存无法再被使用)

指针算术：指针加一—>该类型字节数位移

## ch05:循环和关系表达式

for、while、if-else
数组变量/函数变量：对象，指向地址（数组变量指向第一个值的地址）

```cpp
int array[10];
int * pt;
pt = array;
pt = &array[0];
```

cctype 判断值类型（字母、数字等）

## ch06：分支语句和逻辑操作符

## ch07：函数

尽可能使用const 指针，防止指向的原始数据被修改；传递基本类型时，按值传递，函数使用副本，可以保护原始函数

使用一个函数的三个步骤：定义函数、提供原型、调用函数

## ch08：函数

- 内联函数 inline
  省略原型，函数定义写在程序中函数原型的位置。适合比较短的函数

- 按引用传递函数参数

```cpp
Int & rodents = rats    // int & ：int变量的引用
```


需要在声明引用时初始化。

若函数返回类型为引用类型，则不能返回在函数中定义的新对象（除非在函数中new分配内存）

临时变量: 传入函数的实参类型和函数定义不一样的情况下，或者类型一致，但没有对应变量名时，会生成临时变量。

- 默认参数
- 函数重载（多态）
- 函数模板

```cpp
// template
template<class Any>
void swap(Any a, Any b){}

// 显式实例化
template void Swap(int, int)
// 显式具体化
template<> void Swap(int &, int &);
template <> void Swap(int &, int &);
```

函数模板具体化

1. 隐式实例化
2. 显式实例化 【template没有<>】
3. 显式具体化 【template<>】



## ch09:内存模型和命名空间

1. 使用多文件的策略：头文件+源文件
2. cpp的存储方案，决定变量的储存持续性、作用域和链接性
3. namespace定义一个可以在其中声明标示符的命名区域，减少命名冲突

### 9.1 单独编译

头文件包含内容：

- 函数原型
- #define, const
- 结构声明、类声明、模板声明、内联函数

```cpp
#include <iostream>  // 在存储标准头文件的主机系统的文件系统中查找
#include “coordin.h”  // 在当前目录或源代码目录中寻找

// coordin.h
#ifndef COORDIN_H_
#define COORDIN_H_
```

make 跟踪依赖、文件最终修改时间

### 9.2 存储持续性、作用域和链接性（访问数据）

内存方案，作用域scope，链接性linkage

- 内存方案：自动存储持续性/静态存储持续性/动态存储持续性(new&delete, free store)
   - 作用域：变量在文件的可见范围：全局/局部
- 链接性：变量在不同单元间共享

### 9.2.1 自动存储持续性
```cpp
short waffles;		// auto variable by default
auto short pancakes;	// explicitly auto
register int muffins;	// register variable
```

**作用域**：局部(代码块); **链接性**：无

同名变量，在代码块中会被hide，代码块结束后重新可见（代码块中的变量经历allocated—>scope begins—>expires）

- 声明时初始化
- 1. 通过**堆栈(stack)**来管理内存
堆栈为FILO,后进先出。程序使用两个指针追踪堆栈。指针1指向栈底，即堆栈开始的位置；指针2指向栈尾，即下一个内存单位的地址。
函数开始时，将传入函数的新值压栈。函数结束时不将新值删除，而是将修改指针2位置为以前的位置，下个被压栈的值将覆盖存储之前所用的单元地址。
- 2. **register寄存器**变量，使用CPU寄存器处理特定变量
用于使用频率很高的变量。实际上不一定使用寄存器处理变量，可能因为寄存器已被占用，或者寄存器无法存储所请求的类型

### 9.2.2 静态持续变量
**作用域**：局部/全局；3种**链接性**：外部/内部/无

```cpp
// file1
int global = 1000;			// static duration, external linkage
static int one_file = 50;		// static duration, internal linkage

int main(){}
void functl(int n){
	static int count = 0;		// static duration, no linkage
	int llama = 0;
}
———
// file2
extern int global;
```

如上，count只能在functor()中使用。但和llama不同的是，即使functor()没有被调用，count也留在内存中。one_file可以在文件内各个函数中使用。global可以在本文件、其他文件中使用。外部文件使用该文件的变量，可以添加extern关键词。

未被初始化的静态变量，所有位设置为0；只能使用常量表达式来初始化静态变量。

### 存储说明符和cv-限定符

存储说明符: auto/ register/ static/ extern/ mutable
cv-限定符: const/ volatile

- mutable: const的结构变量中的部分成员可修改
- volatile: 使编译器不缓存值（可能是变化的硬件数据）

### 函数和链接性

函数的存储持续性都是静态，可以通过static/ extern 来决定其链接性（该文件夹内/其他文件夹）。但每个extern函数只能有一个定义。

动态内存由new&delete控制。可以使用存储方案概念来管理动态内存中的静态/自动指针变量。

### 9.3 布局（placement）new操作符（动态分配内存）

New操作符在**堆(heap)**中找到满足要求的内存块。布局(placement)new操作符可以指定使用的位置，多个变量保存到同一个buffer时，由程序员控制偏移量。delete不能删除布局new操作符分配的内存。

```cpp
struct chaff{
	char dross[20];
	int slag;
}
char buffer1[50];
char buffer2[500];

int main(){
	chaff *p1, *p2;
	int *p3, *p4;
  p1 = new chaff;	// place structure in heap
	p3 = new int[20];	// place int array in heap

	p2 = new (buffer1) chaff;	// place struct in buffer1
	p4 = new (buffer2) int[20];	// place int array in buffer2
  return 0
  }
```

### 9.4 名称空间

- 声明区域declaration region
- 潜在作用域potential scope
- 潜在作用域从声明点开始，到声明区域结束。作用域<潜在作用域<声明区域
- 变量可能在另一个嵌套声明区域中被隐藏

namespace: 
- 全局 or namespace中
- Default: extern linkage（除非引用常量）
- using声明：`using namespace::declaration;` 使名称可用
- using编译指令：`using namespace <name>;` 使所有名称可用

