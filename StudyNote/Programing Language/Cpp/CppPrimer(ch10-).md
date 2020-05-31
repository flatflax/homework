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

操作符重载，友元函数，状态成员，类转换（自动转换和强制转换）

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

友元函数、友元类、友元成员函数。通过让函数成为类的友元，使该函数有和类的成员函数相同的访问权限，可以访问类的对象的私有部分。使用关键词`friend`声明和定义非成员函数作为友元函数。

```cpp
friend Time oprator*(double m, const Time & t);
```

