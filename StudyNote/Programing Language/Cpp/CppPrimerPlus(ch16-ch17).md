# CppPrimerPlus(ch16-ch17)

## ch16 string类和STL

string类、`auto-ptr`模板、标准模板库(STL)(容器类、迭代器、函数对象、算法)

#### string类

##### string输入

```cpp
string stuff;
cin >> stuff;		// a word
getline(cin, stuff);		// a line, 自动调整string对象的大小
```

string类对象的最大允许长度由`string::npos`指定。`getline()`读取字符存储到string对象时：

- 到达文件尾，设置输入流的`eofbit`。`fail()==eof()==true`
- 遇到分界符`\n`，分界符从输入流删除但不存储。
- 到达字符数最大允许值，设置输入流的`failbit`。`fail()==true`
- 出现无法识别的故障，设置输入流的`badbit`。
- 一切顺利，设置输入流的`goodbit`。

##### 使用字符串

```cpp
// 如果找到相应的str/s/ch，返回首次出现的位置，否则返回string::npos
size_type find(const string & str, size_type pos = 0) const
size_type find(const char * s, size_type pos = 0) const
size_type find(const char * s, size_type pos = 0, size_type n)
size_type find(char ch, size_type pos = 0) const
```

##### 其他功能

删除、替换、插入、比较、提取、复制、交换

自动调整大小：如果字符串增大，超过分配内存块大小，程序将分配大小为原有两倍的内存块，以提供空间。`capacity()`返回分配给字符串的内存块大小，`reverse()`请求内存块的最小长度。

#### `auto_ptr`类

`auto_ptr`类是一个模板类，用于管理内存动态分配的用法。需要使用头文件`memory`。`auto_ptr`模板类定义了类似指针的对象，使用`new`获取，当对象过期时，析构函数使用`delete`回收内存。

```cpp
#include <memory>

auto_ptr<string> ps(new string("str"));
```

可以使用`auto_ptr`执行接触引用操作(`* ps`)，递增操作（`++ps`），访问结构成员（`ps->puffIndex`），赋给同类型常规指针，赋给同类型`auto_ptr`。

##### 注意事项

###### `new[]`问题

`auto_ptr`模板类的析构函数使用的是`delete`释放内存，因此不能和`new[]`一起使用，不能适用于动态数组。但可以通过复制头文件`memory`中的`auto_ptr`模板，对其修改，使之使用`delete[]`来匹配`new[]`

###### 赋值操作符和复制构造函数

当使用赋值操作符将一个`auto_ptr`指针的值赋给另一个`auto_ptr`指针时，可能会出现两个指针指向同一个对象的问题。解决方法如下：

- 定义赋值操作符，进行深拷贝
- 创建所有权概念，对特定对象，只能有一个智能指针拥有他。智能指针的析构函数只能删除该指针拥有的对象。同时使赋值操作转让所有权。这是用于`auto_ptr`的策略。
- 使用智能更高的指针，跟踪引用特定对象的智能指针数。即引用计数。当引用计数归零时，`delete`才被调用。

#### STL

STL提供一组表示容器、迭代器、函数对象和算法的模板。其中，容器是同质的，存储相同类型的值；迭代器用于遍历容器的对象，是广义指针；函数对象可以是类对象或函数指针。

##### vector模板类

在计算中，vector对应array。`vector`模板在头文件`vector`中定义，使用动态内存分配。

```cpp
// 如果初始化时，没有指定分配器，默认使用allocator<T>作为分配器管理内存
template <class T, class Allocator = allocator<T> > 
class vector {...}

// do with vectors
vector<string> title(10);
title.size();			// 等价于title.end()-title.begin()
title.begin();		// 指向第一个元素的迭代器
title.end();			// 指向超过容器尾的迭代器
title.push_back("new item");		// 添加元素到矢量尾
title.swap(new_title);		// 替换
title.erease(title.begin(), title.begin()+2);
title.insert(title_position_iterator, new_vector_begin_iterator, new_vector_end_iterator);		// 向title指定位置插入参数容器指定区间的元素

vector<double>::iterator pd;		// 迭代器
vector<double> scores;
pd = scores.begin();

for_each(title.begin(), title.end(), func());	// 避免显示使用迭代器变量
random_shuffle(title.begin(), title.end());		// 随机排列指定区间的元素
sort(title.begin, title.end(), sort_func());		// sort_func()默认使用内置的operator<()
```

#### 泛型编程 generic programming

#### 迭代器

迭代器的**特征**：

- 能够对迭代器解除引用，以访问它引用的值。`p`是迭代器，对`*p`进行定义
- 能将迭代器赋给另一个迭代器
- 迭代器间可以进行比较
- 能够使用迭代器遍历容器的所有元素

迭代器**类型**：输入迭代器、输出迭代器、正向迭代器、双向迭代器、随机迭代器（input iterator, output iterator, forward iterator, bidi-rectional iterator, and random access iterator）

- 输入迭代器：(read-only)输入：容器的信息传输给程序。程序使用输入迭代器访问容器的信息。

- 输出迭代器：(write-only)输出：程序的信息传输给容器。程序使用输出迭代器修改容器值。
- 正向迭代器：只使用`operator++`遍历容器
- 双向迭代器：拥有正向迭代器所有特性，支持`operator++`和`operator--` 
- 随机访问迭代器：拥有双向迭代器所有特性，支持随机访问操作`ps+n/ps-n`和排序操作

##### 概念concept、改进refinement和模型model

概念用于描述一系列要求，改进是概念的继承，模型是概念的具体实现。例如：存在正向迭代器概念，双向迭代器是正向迭代器概念的改进，指向int的指针是正向迭代器模型。

- 用指针作为迭代器

迭代器是广义指针，指针能够实现迭代器的所有需求。程序可以使用指针来对非STL容器调用STL算法。

```cpp
int casts[10] = {6, 7, 2, 9 ,4 , 11, 8, 7, 10, 5};
vector<int> dice[10];
copy(casts, casts + 10, dice.begin());

ostream_iterator<int, char> out_iter(cout, " ");		// adaptor转换接口
copy(dice.begin(), dice.end(), ostream_iterator<int, char>(cout, “ “) );		// 输出流转换
copy(istream_iterator<int, char>(cin), istream_iterator<int, char>(), dice.begin())		// 输入流转换
```

- 其他迭代器

`reverse_iterator`, `back_insert_iterator`, `front_insert_iterator`, `insert_iterator`

#### 容器

容器概念：容器、序列容器、联合容器等。

容器类型：`deque, list, queue, priority_queue, stack, vector, map, multimap, set, multiset, bitset` 

##### 容器概念

- 存储其他对象的对象。被存储的对象必须是同一类型的。当容器过期，被存储的数据也将过期（如果存储的是指针，则指向数据不一定过期）。
- 被存储对象的类型必须是可复制构造和可赋值的。
- 不保证元素按特定顺序存储、也不能保证顺序不变。（改进后可以添加保证）

##### 改进

###### 序列sequence

STL序列容器：`deque, list, queue, priority_queue,stack, vector`

其中，`deque=double-ended queue`为双端队列，`priority_queue`最大的元素被移到队首。

序列概念：

- 迭代器至少是正向迭代器。保证元素按特定顺序排列。
- 元素按严格的线性顺序排列。可以对序列进行插入特定位置、删除特定区间等操作

###### 联合容器

联合容器为`key-value`形式。STL联合容器：`set, multiset, map, multimap`

其中，`set`和`multiset`的`key-value`类型一致，`map`和`multimap`的类型可以不同。`set`和`map`的关键词唯一，`multiset`和`multimap`关键词不唯一。

`set`和`multiset`的`value`同时也是`key`。

`map`和`multimap`使用`typedef pair<const Key, T> value_type;`来定义存储的`key-value`对。

联合容器特点：

- 可以快速访问元素
- 不能指定元素的插入位置（因为联合容器通常包含确定数据放置位置的算法，以便快速检索）

#### 函数对象 Function Objects

函数对象也称为函数符(functor)。函数符是函数方式与`()`结合的任意对象。

##### 函数符概念

- generator 生成器，不用参数可以调用
- Unary function 一元函数，一个参数可以调用
- binary function 二元函数，两个参数可以调用

###### 改进

- 返回`bool`的一元函数：断言(predicate)
- 返回`bool`的二院函数：二元断言(binary predicate)

###### 预定义的函数符

预定义的基本函数符：操作符相应的函数符等

###### 自适应函数符(adaptable)

自适应的函数符携带标识参数类型和返回类型的`typedef`成员（`result_type, first_argument_type, second_argument_type`）。因为函数适配(function adaptor)对象在使用函数对象时，认为存在`typedef`成员，因此具有自适应性的函数符可以被函数适配对象使用。

#### 算法

- 使用模板提供通用类型
- 使用迭代器访问容器数据

分类：

- 非修改序列操作：`find()`, `for_each()`
- 修改序列操作
- 排序和相关操作
- 数字运算

##### 算法通用特征

- 就地算法和复制算法
  - 就地算法(in-place aplgorithm)：结果存放在原始数据的位置上
  - 复制算法(copy algorithm)：结果发送到其他位置

- 根据函数作用于容器元素的结果进行操作

### 其他库

valarray类模板：面向数组的数值运算

complex类模板：面向复述的数值运算



## Ch17 输入、输出和文件

缓冲区, `iostream`(`ostream`, `istream`), 文件I/O(`ifstream`, `ofstream`, `fstream`)

