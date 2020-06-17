# CppPrimerPlus(ch13-ch15)

## ch13 类继承

`is-a`关系的继承，公有方式派生类，保护访问，构造函数成员初始化列表，向上和向下的强制转换，虚拟成员函数，联编，抽象基类，纯虚函数，何时/如何使用公有继承

类继承(class inheritance)从已有的类派生出新的类。可以在已有类上添加新方法、新数据，也可以修改类方法的行为。原始类称为基类，继承类称为派生类。

##### 基类和派生类

创建派生类对象时，先调用基类构造函数，然后再调用派生类构造函数。派生类构造函数总是调用一个基类构造函数，如果没有使用初始化器列表句法指定，则使用默认的基类构造函数。

```cpp
//声明
class derived_class_name: public base_class_name{...};

// 派生类构造函数，使用初始化列表机制，将至传给基类构造函数
derived::derived(type1 x, type2 y):base(x, y){...}		// initializer list

// 假如省略成员初始化列表，不调用基类构造函数，则使用默认基类构造函数。
// 因此应调用对应的基类构造函数
derived::derived(type1 x, type2 y){...}
derived::derived(type1 x, type2 y):base(){...}
```

基类和派生类间的关系：

- 派生类可以调用基类的非私有方法
- 基类的引用、指针可以在不显式转换的情况下引用、指向派生类对象。但此时，基类引用、指针只能用于调用基类方法。【反之不成功，派生类引用、指针不能指向基类对象】
- 派生类不能直接访问基类的私有数据成员，需要通过基类的公有方法访问

c++有三种继承方式：公有继承、私有继承、保护继承。公有继承建立一种`is-a`关系。

##### 虚方法

###### 多态公有继承

1. 在派生类中重新定义基类的方法
2. 使用虚方法(virtual method)
   - 使用引用/指针调用虚方法，程序使用对象类型定义的方法（而不是引用/指针类型定义的方法）【动态联编】
   - 基类中，需要在派生类中重新定义的方法声音为虚拟`virtual`
   - 基类中，构造函数不能为虚函数；析构函数应当是虚函数；友元不能是虚函数；

多态性：假如要同时管理基类和派生类，可以选择创建**指向基类的指针数组**，基类指针可以指向基类对象，也可以指向公有继承类型的派生类。虚构方法根据指向的对象，调用对应类型的方法。

###### 函数名联编

**函数名连编**：(源码)函数的调用-->特定函数代码块的执行。在cpp中，由于函数重载的缘故，编译器需要根据函数名和传入参数来确定使用哪个函数。

在编译过程中完成的联编被称为**静态联编**(static binding)/ 早期联编(early binding)。但像虚函数等在编译时无法确定选择类型的函数，编译器需要生成在程序运行时选择正确虚方法的代码，称为**动态联编**(dynamic binding)/ 晚期联编(late binding)。

效率：假如使用动态联编，即需要在程序运行阶段进行决策，则需要采取方法跟踪基类指针/引用指向的对象类型，增加额外开销。因此在程序中，如果该类非基类，或者派生类没有重写基类方法，则使用静态联编，提高效率。

概念模型：在基类的设计中，将需要重新定义的成员函数设置为虚函数，其他的不做修改，一是可以区分是否重新定义该函数，二是可以提高效率。

###### 指针和引用类型兼容性

向上强制转换(upcasting)：将派生类引用/指针，转换为基类引用/指针。不需要进行显式类型转换，需要动态联编和虚函数来满足该需求。

向下强制转换(downcasting)：将基类引用/指针，转换为派生类引用/指针。需要进行显式类型转换。

```cpp
// base_class:employee   derived_class:singer
Employee veep;
Singer trals;
Emoloyee * ps = trals;
Singer * pt = (Singer *)&veep;
```

###### 虚函数的工作原理

编译器为每个对象添加一个隐藏成员。隐藏成员中保存虚函数表(virtual function table, vtbl)，虚函数表中存储为类对象进行声明的虚函数的地址。

例：基类对象包含一个指针，指向基类所有虚函数的地址表。派生类对象包含一个指向独立地址表的指针。假如派生类没有重新定义虚函数，则vtbl保存函数原始版本的地址；如果定义了新的虚函数，则将该虚函数的地址添加到vtbl中。调用虚函数时，程序查看对象中的vtbl地址，转向相应的函数地址表。

**效率**：使用虚函数时，内存和执行速度都有一定成本。每个对象都需要增大存储地址的空间；对每个类，编译器都创建一个虚函数地址表；每个虚函数调用时，都需要到表中查找地址。

##### 访问控制 protected

派生类成员可以直接访问基类的`protected`类成员。对外部世界来说，`private`和`protected`成员相似。

##### 抽象基类 abstract base class

`抽象基类`需要含有至少1个`纯虚函数`(pure virtual function)，使用`func_name()=0`，代表未实现的函数，通过派生类重新定义。纯虚函数用于定义派生类的通用接口。因为抽象基类含有`纯虚函数`，因此不适合创建该类的对象。抽象基类的派生类被称为`具体类`(concrete class)。

###### 使用动态内存和友元的继承

派生类根据是否有新的需要使用动态内存的数据成员，来确定是否需要重写和动态内存相关的`析构函数`、`复制构造函数`、`重载赋值操作符`。对于派生类对象调用基类的`友元函数`来操作基类的`private`数据成员，因为不能用作用域解析符来确定需要调用的函数，因此可以使用**强制类型转换**，匹配需要调用的基类友元函数。

## Ch14 代码重用

`has-a`关系，包含成员对象的类（包含），私有和保护继承，多重继承，类模板

##### 包含成员对象的类 class with object members / containment

当成员对象满足的关系是`has-a`关系，比如学生类和分数类，显然学生有分数，所以分数类可以作为学生类的成员对象。

构造函数初始化顺序和声明顺序有关，和初始化列表的顺序无关。

##### 私有继承

```CPP
// private inheritance
class derived_class_name: private base_class_name1, private base_class_name2{...};
```

**私有继承**使用`private`关键词来定义派生类所继承的类。基类的`public`成员和`protected`成员会成为派生类的`private`成员，基类方法不会成为派生对象共有接口的一部分，但可以在派生类的成员函数中使用。

###### 使用包含还是私有继承？

包含(containment)可以通过类声明，直观地根据成员名称区分对象；使用继承则使得从属关系变得抽象。

当派生类继承多个基类的时候，可能会出现不同基类拥有同名方法、不同基类来源于同样的祖先基类等问题。包含也可以包括多个同类的子对象，但继承只能使用一个该类对象。

然而，包含关系中，包含类不能访问被包含类的`protected`成员，但在派生类上可以使用。当需要重新定义虚函数的时候，也需要使用私用继承实现。

##### 保护继承

```cpp
// protectd inheritance
class derived_class_name: protected base_class_name1, protect_class_name2{...};
```

保护继承是私有继承的变体。使用保护继承时，基类的`public`成员和`protected`成员都会成为派生类的`protected`成员。基类的接口在派生类中可用，但在继承结构之外不可用。保护继承和私有继承的不同之处在于多代派生类，使用私有继承时，第三代派生类不能使用基类的公有方法；使用保护继承时，第三代派生类可以使用其基类接口（保护类型）。

|                  | 共有继承             | 保护继承             | 私有继承             |
| ---------------- | -------------------- | -------------------- | -------------------- |
| (基类的)公有成员 | 派生类的公有成员     | 派生类的保护成员     | 派生类的私有成员     |
| (基类的)保护成员 | 派生类的保护成员     | 派生类的保护成员     | 派生类的私有成员     |
| (基类的)私有成员 | 只能通过基类接口访问 | 只能通过基类接口访问 | 只能通过基类接口访问 |
| 能否隐式向上转换 | 能                   | 能（派生类中）       | 不能                 |

##### 使用`using`重新定义访问权限

使用保护继承和私有继承时，将无法在派生类外使用基类的公有方法。此时可以定义使用该基类方法的派生类方法；也可以使用`using`声明，将函数调用包装在另一个函数调用中，使得派生类可以使用特定的基类成员（即使是私有继承）。使用`using`声明的方法只适用于继承，不适用于包含。

```cpp
class Student: private std::string, private std::valarray<double>
{
public:
  	using std::valarray<double>::min;
  	using std::valarray<double>::max;
  	...
};
```

##### 多重继承

使用多个基类的继承被称为**多重继承**(multiple inheritance, MI)。多重继承不使用关键词限定的情况下，默认为`private`私有继承。

###### 多重继承的一些问题

```cpp
class Worker{...};

class Singer: public Worker{...};
class Waiter: public Worker{...};

class SingingWaiter: public Singer, public Waiter{...};

// problem 1
SingingWaiter ed;
ed.Show();		// 歧义
ed.Singer::Show();	// singer ver
ed.Waiter::Show();	// waiter ver

// problem 2
Worker * pw = &ed;	// 歧义
Worker * pw = (Singer *)&ed;		// worker of singer
Worker * pw = (Worker *)&ed;		// worker of waiter
```

如上述代码，`SingingWaiter`类多重继承`Singer`,`Waiter`类，而这两个类都继承自`Worker`类。

针对第一个问题，基类都定义了`Show()`方法。假如在`SingingWaiter`类中没有重新定义该方法，则在调用时就会产生歧义。此时可以使用**作用域操作符**来明确需要调用的方法。同时应该将基类函数设计为`protected`类型的模块化方法，在派生类重新组合。

针对第二个问题，假如将三代派生类对象的地址赋给基类指针时，将会出现二义性。因为`ed`中包含两个`Worker`对象，有两个地址可供选择，所以应使用类型转换来指定对象。但包含两个`Worker`对象拷贝还会导致其他问题，因此应该避免这样的问题。C++引入了虚基类来解决多重继承的问题。

##### 虚基类 virtual base class

```cpp
class Worker{...};

class Singer: virtual public Worker{...};
class Waiter: virtual public Worker{...};

class SingingWaiter: public Singer, public Waiter{...};
```

如上述代码，此时`SingingWaiter`类对象中只包含一个`Worker`对象的拷贝，继承的`Singer`,`Waiter`对象共享一个`Worker`对象。

###### 为什么使用`virtual`关键词？

虚基类和虚函数虽然都是用`virtual`关键词，但是不存在明显联系。只是关键词重载。

###### 为什么不直接将基类声明为`virtual`，使`virtual`的基类成为多重继承的准则？

某些情况下，可能需要基类的多个拷贝。将基类作为虚拟类会要求程序完成额外的计算（添加虚拟表等）。这样的操作还会存在一些缺点。【tbc】

###### 虚基类需要做的额外操作

除了在类继承声明时需要添加`virtual`关键词，在构造函数等也需要进行修改。如下面代码所示，如果类有间接虚基类，除非使用虚基类的默认构造函数，否则需要显式调用该虚基类的构造函数。

```cpp
// normal bass class
SingingWaiter(const Work & wk, int p = 0, int v = Singer::other)
  					: Waiter(wk,p), Singer(wk, v){}

// virtual base class
SingingWaiter(const Work & wk, int p = 0, int v = Singer::other)
  					: Worker(wk), Waiter(wk,p), Singer(wk, v){}
```

###### 优先度 dominance

对于类的同名成员（数据成员/函数成员）的优先度，派生类 > 祖先基类（间接/直接）。没有继承关系的类的同名成员间不具有优先度，假如不使用**作用域操作符**限定成员，将出现二义性。

##### 类模板 class template

```cpp
// original
bool Stack::push(const Item & item){...}

// template class
template <typename Type>	// 类型参数Type
bool Stack<Type>::push(const Type & item){...}

// 非类型参数
template <typename T, int n>	// 非类型参数n
bool ArrayTP<T, n>::push(const Type & item){...}

ArrayTP<double, 12> eggweights;	//	表达式参数
ArrayTP< ArrayTP<int, 5>, 10> toodee;		// 递归使用模板

// 默认类型参数,多个类型参数
template<class T1, class T2=int> class Topo{...};
```

使用表达式参数方法的优点是可以根据非类型参数的值维护内存栈，提高执行效率。但是缺点是，在同类型参数值的情况下，会根据非类型参数的值生成不同的模板，生成独立的声明。

###### 模版具体化specialization

- 隐式实例化 Implicit Instantiations

```cpp
ArrayTP<double ,30> * pt;
pt = new ArrayTP<double, 30>;		// 生成
```

编译器在需要对象前，不会生成该类的隐式实例化。

- 显式实例化 Explicit Instantiations

```cpp
template class ArrayTP<string, 100>; // generate ArrayTP<string, 100> class
```

- 显式具现化 Explicit Specializations

用于特定类型（对应模板的通用类型）的定义。

* 部分具体化 Partial Specializations

```cpp
// general template
template <class T1, class T2> class Pair {...};

// specialization with T2 set to int
template <class T1> class Pair<T1, int> {...};		// 部分具体化
// specialization with T1 and T2 set to int 
template <> class Pair<int, int> {...};						// 显式具体化
```

用于限制模板的通用性。如果有多个模板可供选择，编译器则使用具体化程度最高的模板。

```cpp
Pair<double, double> p1; // use general Pair template
Pair<double, int> p2; // Pair<T1, int> 部分具体化 
Pair<int, int> p3; // Pair<int, int> 显式具体化
```

###### 成员模板

模板还可以作为结构、类、模板类的成员。

###### 友元

```cpp
template <class T> class HasFriend
{
		friend void reports(HasFriend<T> &);	// 1. template parameter
  	template <typename T> void report(T &); // 2. Bound Template Friend
  	template <typename C, typename D> friend void show2(C &, D &);	// 3. Unbound Template Friend
  	...
};

// 1. non-template friend to the HasFriend<int> class 
void reports(HasFriend<int> & hf)
{		cout <<”HasFriend<int>: “ << hf.item << endl; }

// 2. 
template <typename T> 
void reports(T & hf)
{  	cout << hf.item << endl; }

// 3.
template <typename C, typename D> 
void show2(C & c, D & d) 
{		cout << c.item << “, “ << d.item << endl; }
```

- 模板类的非模板友元函数

友元函数会成为模板类所有实例的友元。但该类型的友元函数不是模板函数，只是使用模板作为参数，因此需要为使用的友元定义显式具体化（对特定的参数类型作函数定义）。

- 模板类的约束模板友元函数

需要满足三个条件：1) 类定义为模板类；2) 类中有模板友元函数声明；3) 为友元提供模板定义。在这种情况下，对每个类型，都有自己的友元函数`reports`。

- 模板类的非约束模板友元函数

通过在类内部声明模板，可以创建非约束友元函数，即每个函数具体化，都是每个类具体化的友元。

## ch15 友元、异常及其他

友元类、友元类方法、嵌套类。异常、异常类。RTTI。

##### 友元

###### 友元类

用于实现不满足`is-a`,`has-a`的其他关系。可以定义两个类间的友元关系。友元声明在类声明中的位置不影响其作用。

```cpp
class Tv
{ 	friend class Remote;...	};		// friend class

class Remote{...}
```

###### 友元成员函数

假如只想将特定的类成员成为友元，需要使用**前向声明**(forward declaration)。如下代码所示，因为当编译器处理友元成员函数`Reomote::set_chan`时，需要知道友元成员函数所属类`Remote`的定义，而该类函数定义又提及了`Tv`类对象，又需要知道`Tv`类定义。为了解决这种循环依赖，需要使用前向声明。但使用友元类，不需要使用前向声明。

```cpp
class Tv;		// forward declaration

class Remote{...};
class Tv{friend void Remote::set_chan(Tv & t, int c);...};	// friend member func
```

使用友元函数可以控制能够修改目标类的私有成员的函数数量。

###### 其他友好关系

- 互相作为友元类

当两个类需要相互影响时，可以通过让类彼此成为对方的友元来实现。

- 共同的友元

当函数需要访问多个类的私有数据，可以将该函数作为两个类的友元函数。

##### 嵌套类

在另一个类中声明的类，被称为嵌套类。嵌套类和包含的区别在于：包含意味着将类对象作为另一个类的成员；而对类进行嵌套不创建成员，而是定义了一种类型，该类型在包含嵌套类声明的类中有效。通常用于避免名称混乱的问题。

|           | 包含的类 | 包含的类的派生类 | outside        |
| --------- | -------- | ---------------- | -------------- |
| Private   | y        | n                | n              |
| Protected | y        | y                | n              |
| Public    | y        | y                | y,通过类限定符 |

##### 异常

###### `abort()`

`abort()`向标准错误流(同`cerr`)发送错误消息`abnormal program termination`，然后终止程序，根据实现，会返回错误代码至操作系统或父进程，或者刷新文件缓冲区。

```cpp
#include <stdlib.h>			// cstdlib or stdlib.h
#include <cstdlib>

std::abort();
```

###### 返回错误码

函数返回`bool`值来判断是否运行成功，同时修改传入的用于存储结果的引用参数。

###### `try-catch`

使用`throw`抛出异常，由`try-catch`捕获异常。可以使用不同的异常类型，通过`throw`抛出和`catch`捕获不同类型的对象，来进行不同的处理。

```cpp
try { func(); }
catch(excep_func & ef){...}

void func(){ ... throw excep_func(args); ...}
```

###### 堆栈解退 unwinding the stack

正常函数运行时，堆栈存储子函数地址和自动变量地址，随着函数的运行会继续添加子函数的自动变量即子函数等地址，在函数结束`return`时回到父函数地址，释放相关自动变量。

堆栈解退是指，当函数运行因异常而终止时，程序将释放堆栈的内存，直到找到位于`try`块的返回地址，处理从`try`到`throw`之间的内存。对于堆栈内的自动类对象，会调用类的析构函数。

###### 其他异常特性

正常运行的函数，返回语句将控制权返回到调用该函数的父函数中。而使用`try-catch`组合，`thorw`语句将控制权返回到包含可以捕获该异常的`try-catch`组合所在的函数。

除此之外，引发异常时，编译器会创建临时拷贝，因为目标函数执行完之后，异常对象的内存将被回收。但`catch`块中依然使用引用的原因是，基类引用可以执行派生类对象，该`catch`块可以对异常类的派生类对象进行匹配。

由于引发的异常对象将被第一个匹配的`catch`块捕获，因此，当存在多层次继承的异常派生类时，`catch`块的排列顺序应该和派生顺序相反。

当异常未知时，可以使用`catch(...){ // statements };`来捕获任意异常。

###### `exception类`

使用`#include <exception>`中定义的`exception类`作为基类，定义派生异常类。c++库中也定义了很多常见的异常类型。

###### 未捕获异常

如果异常没有被捕获（没有`try`块或没有匹配的`catch`块），默认情况下，会导致程序异常停止：函数调用`terminate()`，默认情况下`terminate()`会调用`abort()`。可以使用`exception`头文件中的`set_terminate()`函数来修改`terminate()`的行为。

假如引发了异常规范中没有的异常，程序将调用`unexpected()`函数：默认调用`terminate()`，然后`terminate()`调用`abort()`。可以通过`set_unexpeted()`修改行为。主要为以下两种方式：

- 通过调用`terminate()`、`abort()`/`exit()`来终止程序
- 引发新异常
  - 新异常和原有异常规范匹配：被`catch()`捕获
  - 不匹配原来的异常规范，异常规范中不包含`std::bad_exception`类型：调用`terminate()`
  - 不匹配原来的异常规范，异常规范中包含`std::bad_exception`类型：被`std::bad_exception`替代

##### RTTI

RTTI是运行阶段类型识别(runtime type identification)的缩写。当想要调用派生类对象的非继承方法，或者出于调试目的，想要跟踪生成的对象类型时，可以使用RTTI确定对象的类型。

支持RTTI的3个元素：

- `dynamic_cast`操作符：使用基类指针生成派生类指针，或空指针。
- `typeid`操作符：生成一个指出对象类型的值。
- `type_info`结构：存储特定类型的信息。

###### `dynamic_cast`操作符

```cpp
// 指针pt的类型是否可以安全转换为Type类型
// 如果可以，返回pt地址，如果不可以，返回空指针
dynamic_cast<Type *>(pt)
```

###### `type_id`操作符和`type_info`类

```cpp
type_id(Type) == type_id(*pt)		// return bool
```

##### 类型转换操作符

为了使得类型转换过程更规范，c++添加了4个类型转换操作符：`dynamic_cast`, `const_cast`, `static_cast`, `reinterpret_cast`

```cpp
// type_name是expression所属类型的基类
// 父子类下行转换有类型检查，消耗高
dynamic_cast <type_name> (expression)	
  
// 改变值为const或volatile
const_cast <type_name> (expression)	
  
// 基本类型间、父子类上下行、空指针->目标类型指针、任意->void
// 不能转换掉expression的const、volatile、或者__unaligned属性
static_cast <type_name> (expression)	

// 不能：指针->整型/浮点型、函数指针<->数据指针
reinterpret_cast <type_name> (expression)
```



