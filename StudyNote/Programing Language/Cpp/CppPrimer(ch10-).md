# CppPrimer(ch10-)

## ch10 **面对对象编程和类设计**

重要的OOP特性：抽象；封装和数据隐藏；多态；继承；代码的可重用性

类规范：

1. 类声明：类的蓝图，成员函数方式描述公有接口
2. 类方法定义： 细节，描述如何实现类成员函数

```cpp
//类声明
class className
{
  private:		
  	data member declarations
  public:			// 公有接口
  	member function prototypes
    void func_name();
}

//类方法定义
void className::func_name(){}
```

类设计需要将公有接口和实现细节分开封装。所谓的数据隐藏（将数据放在类的私有部分），属于封装的一种，将实现细节封装在类的私有部分中。数据隐藏可以防止类的用户直接访问数据。

类对象的默认访问控制为private。

#### 实现类成员函数

1. 定义成员函数，例：`void Stock::update(double price)`
2. 类方法可以访问类的private组件
3. 函数定义位于类声明中的函数为隐性内联函数，也可以在外部使用`inline`显式定义。

#### 类的构造函数和析构函数

类构造函数，用于构造新对象、赋值数据成员。没有返回值，但没有被声明为void类型。

默认构造函数，用于未提供显式初始化值时，用来创建对象的构造函数。

折构函数，类对象过期时，程序调用折构函数，完成清理动作。

```cpp
// structor
Stock::Stock(const char * co, int n, double pr){}
Stock::Stock(){}

// destructor
Stock::~Stock(){}
```

#### this指针

```cpp
// 函数topval返回total_val更大的Stock类对象
const Stock & Stock::topval(const Stock & s) const{
    if (s.total_val > total_val){
        return s;
    }
    else{
        return *this;
    }
}
// this为对象的地址，*this作为调用对象的别名（返回调用对象本身，而不是拷贝），函数括号后的const限定符将this限定为const，使得无法使用this来修改对象的值。
```

#### 类作用域

`.`直接成员操作符		`->`间接成员操作符		`::`作用域解析操作符

```cpp
Ik * pik = new Ik;
Ik ee = Ik();

ee.ViewIk();		// 类对象调用成员函数
pik->ViewIk();			// 类指针调用成员函数
```

在类中定义的名称（类数据成员名和类成员函数名）的作用域为整个类。因此，可以在类声明或类成员函数中，使用未修饰的成员名称。

创建作用域为整个类的常量：1. 声明一个枚举；2. 使用关键字static创建一个常量。第一个方法，枚举的作用域为整个类，但枚举不会创建类数据成员，类中的代码遇到枚举中的符号名称(如`Len1`)时，编译器使用声明的值(`30`)来代替它。第二个方法，创建一个静态常量，将于其他静态变量存储在一起，而不是存储在对象中，因此该常量与所有同类对象共享。

```cpp
// 创建一个由所有类共享的常量
// error
class Stock{
private:
  	const int Len=30;	// 声明类只描述对象的形式，不真正创建对象。因此在类创建前没有用于存储值的空间
  	...
}
// right
class Stock{
private:
		enum {Len1 = 30};		// 1.enum
  	static const int Len2 = 30;		// 2.static(only enum or interger)
  	char company[Len1];
    ...
}
```

#### 抽象数据类型 abstract data type

ADT以通用方式描述数据类型，但没有引入语言或实现细节。可以通过类来描述抽象数据类型，其中公有成员函数接口提供ADT描述的服务，类的私有部分和类方法的代码提供了实现。



## ch11 类的使用

友元函数，操作符重载(类成员函数或友元函数)，状态成员，类转换（自动转换和强制转换）

#### 操作符重载

```cpp
operator op(argument-list)
  
//exp
class Salesperson{
  ...
public:
  Salesperson operator+ (const Salesperson & s) const;
};

Salesperson district, sid, sara;
district = sid + sara;
district = sid.+(sara);	// 隐式使用sid，显式使用sara
```

重载限制p357

#### 友元

友元函数、友元类、友元成员函数。通过让函数成为类的友元，使该函数有和类的成员函数相同的访问权限，可以访问类的对象的私有部分(通过传入对象作为参数的形式)。使用关键词`friend`声明和定义非成员函数作为友元函数。友元函数不是类的组成部分。

```cpp
// hpp
class Time{
public:
	friend Time oprator*(double m, const Time & t);		// friend
  ...
};

// cpp
Time oprator*(double m, const Time & t){}		// 没有friend
```



```cpp
// 声明
Time oprator+ (const Time & t) const;		// member-version;
friend Time oprator+ (const Time & t1, const Time & t2);		//non-member-version

T1 = T2 + T3;
T1 = T2.oprator+(T3);		// member func
T2 = oprator(T2, T3);		// non-member func
```

举例: 

1. `std::ostream & oprator<< (std::ostream & os, const Time &t)`; 定义`<<`操作符，和cout一起使用，显示对象内容
2. 矢量(vector)

* 大小（长度）和方向（角度）描述矢量
* 水平分量`x`和垂直分量`y`描述矢量

#### 类型转换

给标准型变量赋值另一标准型值时，假如两种类型兼容，cpp会自动进行转换，例：`long count = 8; int side = 3.3;`。但cpp不自动转换不兼容的类型，例：`int * p = 10; // type clash`。无法自动转换时可以进行强制类型转换。

可以将构造函数用作自动类型转换函数。假如需要关闭该自动特性，可以在声明构造函数时使用关键字`explicit`

```cpp
// 声明
Stonewt();
explicit Stonewt(double lbs);		// no implicit conversions allowed
Stonewt(int stn, double lbs);

// 实例化
Stonewt myCat;
myCat = 19.6;		// invalid
myCat = Stonewt(19.6);	// explicit conversion
myCat = (Stonewt) 19.6;		// explicit typecast

Stonewt Jumbo(7000); 		// convert int to double
```

**转换函数**是用户定义的强制类型转换。转换函数必须是类方法，不能指定返回类型，不能有参数。关键字`explict`不能用于转换函数。应该尽量使用显式转换，避免隐式转换。

```cpp
Stonewt woife(285.7);
double host = double(woife);
double thinker = (double) woife;
double stats = woife;		// implicit

// 转换函数 conversion functions
operator typeName();
//	exp
operator int(); operator double();
```

转换函数、友元函数、成员函数的使用考量：如上，需要`Stonewt`量和`double`量相加，可以考虑以下两种方法：

1. 定义友元函数`operator+(const Stonewt &, const Stonewt &)`，借助构造函数将`double`类参数转换为`Stonewt`类参数。优点：定义的函数少；缺点：转换时需要调用转换构造函数，增加时间和内存开销。

2. 将加法操作符重载为显式使用`double`类型参数的函数。优点：运行速度较快；缺点：增加开发消耗。

   ```cpp
   Stonewt operator+(double x);		// 2.1
   friend Stonewt oprator+(double x, Stonewt &);		// 2.2
   
   double kennyD = 3.5;
   Stonewt total;
   Stonewt jennySt(16.9);
   
   total = jennySt + kennyD;		// 2.1	jennySt.oprator+(kennyD)
   total = kenny + jennySt;		// 2.2	oprator+(kenny, jennySt)
   ```

   

## ch12 类和动态内存分配

对类使用`new`和`delete`；动态内存对构造函数、折构函数、操作符重载的影响。

