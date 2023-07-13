# C++基础

## 1.变量和基本类型

### 1.1算术类型

|    类型     |     含义     |   最小尺寸   |
| :---------: | :----------: | :----------: |
|    bool     |   布尔类型   |    1字节     |
|    char     |     字符     |     8位      |
|    short    |    短整型    |     16位     |
|     int     |     整形     |     16位     |
|    long     |    长整型    |     32位     |
|  long long  |    长整型    |     64位     |
|    float    |  单精度浮点  | 6位有效数字  |
|   double    |  双精度浮点  | 10位有效数字 |
| long double | 扩展精度浮点 | 10位有效数字 |
|   wchar_t   |    宽字符    |     16位     |
|  char16_t   | Unicode字符  |     16位     |
|  char32_t   | Unicode字符  |     32位     |

* 可寻址最小内存：字节（byte)
* 存储基本单元：字（word)

### 1.2带符号和无符号

```
unsigned int <==> unsigned
```

`char` 在有些机器是有符号的，有些没有，因此在算数运算中不使用`char`，如需使用，应指明`signed char`或`unsigned char`。

### 1.3类型转换

* 当赋给无符号整型一个超出其范围的数时，结果为初始值对可表示最大值取余。
* 带符号类型与无符号类型混用的表达式中，带符号会自动转化为无符号类型。

#### 1.3.1强制类型转换

`static_cast`

用于良性转换，如：

* 基本数据类型的转换，`short`转`int`,`int`转`double`
* `void`指针和具体指针的转换

```c++
void *p = &d;
double *dp = static_cast<double*> (p);//将p转换为double*类型
```

`const_cast`

用来去掉表达式的 `const` 修饰或 `volatile` 修饰，换句话说，`const_cast` 就是用来将 `const/volatile` 类型转换为非` const/volatile `类型。**`const_cast`类型转换对象必须为指针或引用**

**`const_cast`只能改变运算对象的底层`const`**

```c++
const char *pc;
char *p = const_cast<char*>(pc);
```

使用场景：

① 常量指针转换为非常量指针，并且仍然指向原来的对象；

②常量引用转换为非常量引用，并且仍然指向原来的对象；

volatile(易变的) 提醒编译器它后面所定义的变量随时都有可能改变，因此编译后的程序每次需要存储或读取这个变量的时候，都会**直接从变量地址中读取数据**。（告诉编译器对该变量不做优化）

`dynamic_cast` 只能用于类间转换，可以是类对象的指针、引用。

* 专用于将多态基类指针或引用强制转换为派生类的指针或引用，并且能够检查转换的安全性，对于不安全的指针转换，结果返回NULL指针。
* 通过“运行时检查”来保证安全性
* 基类必须有虚函数，因为`dynamic_cast`是运行时类型检查，需要运行时类型信息，而这个信息存储在虚函数表中，只有定义了虚函数，才有虚函数表。

* 上行转换和`static_cast`效果一样；

* 下行转化时具有类型检查功能，比`static_cast`更安全。若对指针转换，失败返回`nullptr`,若对引用转换，失败抛出异常。

`reinterpret_cast`

两个具体指针之间的转换，int转指针。

转换过程仅为比特位拷贝。

### 1.4字面值常量

* 十进制字面值默认为int\long\long long类型

* 浮点型字面值默认为double类型

* ```c++
  'a' //字符型字面值
  "Hello World" //字符串型字面值
  ```

* `nullptr`: 指针字面值

#### 1.4.1指定字面值类型

通过添加前缀和后缀的方式

整形字面值

| 后缀       | 类型        |
|:--------:|:---------:|
| u or U   | unsigned  |
| l or L   | long      |
| ll or LL | long long |

浮点型字面值

| 后缀     | 类型          |
|:------:|:-----------:|
| f or F | float       |
| l or L | long double |

### 1.5变量

#### 1.5.1对象

一块能存储数据并具有某种类型的内存空间。

#### 1.5.2初始化

```c++
int a = 0;
int a = {0};//列表初始化
int a{0};//列表初始化
int a(0);
```

* 函数体之外的未初始化的变量将被初始化为0.
* 使用列表初始化时，若存在数据丢失风险，程序将会报错，如：`int a{3.14}`

#### 1.5.3声明与定义

**声明**：在变量前加extern并且不要显式地初始化变量，显式地初始化将成为定义。

```c++
extern int i;//声明i而非定义i
extern int j = 0;//定义
```

**变量只能被定义一次，但可以多次声明。**

### 1.6引用

**引用** ：为对象起了另一个名字,对引用进行的操作均是在其所绑定地对象上进行，引用本身并非对象，因此**不能定义引用的引用**。

```c++
int ival = 1024;
int &refVal = ival;//refVal指向ival
```

### 1.7指针

```c++
int ival = 12;
int *p = &ival;
int *p2 = p;
cout << *p << endl;//使用解引用运算符*来访问指针所指对象
```

```c++
int i = 0;
(a) double* dp = &i;//非法，类型不一致
(b) int *ip = i;//非法，不能将int型赋给指针型
(c) int *p = &i;//合法
```

#### 1.7.1空指针

```c++
int *p1 = nullptr;//定义空指针
int *p2 = 0;
int *p3 = NULL;
```

* 尽可能初始化所有指针，即使只是初始化为空指针。

#### 1.7.2 void *指针

可存放任意对象的地址。

#### 1.7.3指针的指针

```c++
int ival = 1024;
int *pi = &ival;
int **ppi = &pi;
*pi--->ival
*ppi--->pi
**ppi --->*pi<==>ival
```

#### 1.7.4指向指针的引用

```c++
int i = 42;
int *p;
int *&r = p;//r指向指针p
r = &i;//给r赋值&i，即给p赋值&r
```

### 1.8 const限定符

* const对象仅在文件内有效，多个文件出现同名const变量时，将被认为是不同的变量。
* 如需在多个文件间共享const变量，则须在定义与声明时均加`extern`.

#### 1.8.1对const常量的引用

不能通过引用来改变所指对象的值，但引用所指对象可以是非常量

```c++
const int ci = 1024;
const int &r = ci;
```

#### 1.8.2指向const的指针（常量指针）

不能通过指针改变所指对象的值，但指针所指对象可以是非常量。

```c++
const int ival = 12;
const int *p = &ival;
```

#### 1.8.3指针常量（指针本身是常量）

```c++
int ival = 12;
int *const p = &ival;
```

#### 1.8.4顶层与底层const

**顶层const**：表示指针本身是一个常量，顶层`const`作用于对象本身。

**底层const**: 表示指针所指对象是一个常量

#### 1.8.5常量表达式

**值不会改变**，并且在编译阶段就能得到计算结果的表达式。字面值属于常量表达式。

#### 1.8.6 constexpr变量

### 1.9处理类型

#### 1.9.1 类型别名

```c++
typedef double wages;//wages是double的别名
typedef wages base, *p;//base是double的别名，p是double*的别名
```

```c++
using wages = double;
```

#### 1.9.2 auto

由编译器通过**初始值**来确定变量类型，一般会忽略掉顶层const

* auto定义的变量必须有初始值

```c++
int i = 12;
auto *p = &i;//p为整型指针
```

#### 1.9.3 decltype

希望从表达式的类型推断出要定义的变量类型，但**不希望用该表达式的值初始化变量**。

```c++
decltype(f()) sum = x;//sum的类型即f()的返回值类型
```

`decltype`一般会保留顶层`const`

* 如果表达式的内容是解引用操作，则`decltype`会得到引用类型

```c++
int i = 42, *p = &i, j = 20;
decltype(*p) c = j;//c为int&类型
```

* `decltype`加双层括号得到引用类型，赋值表达式得也到引用类型

```c++
int i = 12， j;
decltype((i))//得到int&类型
decltype(j=i)//得到int&类型
```

### 预处理器

在编译之前执行的一段程序如`#include`

#### 头文件保护符

防止头文件的重复包含

`#ifndef`由C/C++支持

```c++
#ifndef SALES_DATA_H
#define SALES_DATA_H//定义预处理变量，若SALES_DATA_H已被定义，则忽略#ifndef和#endif之间的代码
#include<string>
头文件内容
#endif
```

`#pragma once`由编译器支持

## 2.字符串、向量和数组

### 2.1命名空间的using声明

```c++
using std::cin;
using std::cout;
using namespace std;
```

### 2.2 string 容器

可变长字符序列

#### 2.2.1 初始化string

```c++
#include<string>
string s1;//默认初始化，空串
string s2(s1);//直接初始化 '()'
string s2 = s1;//拷贝初始化 ‘=’
string s3("value");
string s4(n, 'c');//n个c
```

#### 2.2.2 string对象操作

```c++
os<<s;//将s写入到输出流os中，返回os
is>>s;//从输入流is中读取字符串赋给s，字符串以空白（空格、回车）分隔，返回is
getline(is, s);//从is中读取一行赋给s,返回is，读取一整行，包含了字符串中的空白，直到遇到换行符停止
s.empty();
s.size();
s[n];//返回字符中第n个字符的引用
s1+s2;//s1、s2连接
s1 = s2;//s2代替s1
s1 == s2;//判断所含字符是否相等
<, >, >=, <=;//返回第一对相异字符的比较结果
```

读取未知数量的`string`对象

```c++
string word;
while(cin>>word)//反复读取直到文件结束标记
    cout << word << endl;//逐个输出
```

**`string::size_type`类型**

`s.size()`返回的是`string::size_type`类型，无符号整型，避免与`int`型混用

#### 2.2.3处理字符

```c++
isalnum(c) //是否字母或数字
isalpha(c)//是否字母
iscntrl(c)//是否控制字符
isdigit(c)//是否数字
islower(c)//是否小写字母
isupper(c)//是否大写
tolower(c)//转化为小写
toupper(c)//转化为大写
```

#### 范围for语句

```c++
string str("some string");
for(auto c:str)//遍历字符串
    cout << c << endl;

string s("Hello World");
for(auto &c : s)// 定义为引用类型可以直接改变字符串s
    c = toupper(c);
cout << s << endl;
```

### 2.3 vector容器

#### 2.3.1初始化vector对象

```c++
vector<T> v1;//空vector,默认初始化
vector<T> v2(v1);//v2中包含v1的副本
vector<T> v2 = v1;
vector<T> v3(n, val);//包含n个重复元素val
vector<T> v4(n);//包含n个执行默认初始化的对象
vector<T> v5{a, b, c, ...}
vector<T> v5 = {a, b, c, ...}//列表初始化
```

#### 向vector中添加元素

```c++
vector<int> v2;
for(int i=0; i!=100;++i)
    v2.push_back(i);//使用成员函数push_back()
```

下标运算符用于访问已存在的元素，不能用于添加元素

### 2.4迭代器

`begin`返回指向第一个元素的迭代器

`end`返回容器尾元素的下一位置的迭代器（尾后迭代器）

若容器为空，则`begin`和`end`返回同一个迭代器，都是尾后迭代器

```c++
string s("Hello World");
for(auto it = s.begin();it != s.end()&&!isspace(*it); ++it)
    *it = toupper(*it);
```

#### 2.4.1迭代器类型

```c++
vector<int>::iterator it; //it能读写vector<int>的元素
string::iterator it;//it能读写string对象中的字符
vector<int>::const_iterator it;//it只读
string::const_iterator it;//it只读
```

`it->mem <==> (*it).mem`

### 2.5数组

**数组大小固定**

使用字符串字面值初始化字符数组时，会在末尾自动添加空字符。

**不允许使用一个数组初始化或直接赋值给另一个数组。**

#### 2.5.1 数组、指针、引用

```c++
int *ptrs[10];//定义一个含有10个整型指针的数组
int (*parray)[10] = &arr;//parray指向含有10个整型元素的数组arr
int (&arrRef)[10] = arr;//arrRef引用一个含有10个元素的数组arr
```

数组名可作为指向数组首元素的指针

* 使用`auto`推断出的数组名类型为指针类型。

* 使用`decltype`推断出为数组类型。

#### 2.5.2 begin(), end()

可使用标准库函数`begin()`和`end()`获取数组的首元素指针和尾后指针。

```c++
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int *beg = begin(ia);
int *last = end(ia);
```

### 2.6 stack容器

容器声明

```c
#include<stack>

stack<int> s;
stack<char> s1;
stack<数据类型> S;
```

容器方法

```c
s.top();//返回栈顶元素
s.push();//入栈
s.pop();//出栈
s.empty();//判断是否为空，为空返回1
```

## 3. try语句块和异常处理...

## 4.函数

函数的返回类型不可以是数组、函数，但可以是指向数组和函数的指针。

**引用形参**：如果函数无需改变引用形参的值，最好将其声明为常量引用。

### 4.1 数组形参

实际传递的是数组的首地址。

```c++
//三条语句等价
void print(const int*);
void print(const int[]);
void print(const int[10]);
```

数组形参传递给函数时，须使函数知道数组的大小，以免发生越界。

**数组引用形参**

```c++
void print(int (&arr[10]))
{
    for (auto elem:arr)
        cout << elem << endl;
}
```

**传递多维数组**

```c++
void print(int (*matrix)[10], int rowSize);
```

**多维数组** 

可视为数组的数组，即外层数组的元素分别为内层数组的数组名（首元素地址）

### 4.2 main命令行

```c++
int main(int argc, char *argv[])
//argc表示数组中形参的数量
//argv数组元素是指向字符串的指针，argv的第一个元素指向程序的名字或空字符串。
//当使用argv中的实参时，须从argv[1]开始，argv[0]保存程序的名字，而非用户输入。
```

### 4.3 返回数组指针的函数

* 使用类型别名
  
  ```c++
  typedef int arrT[10];
  using arrT = int[10];//arrT是一个类型别名，表示含有10个整数的数组。
  arrT* func(int i);//函数返回一个指向10个整数的数组的指针。
  ```

* 标准声明

```c++
int (*func(int i))[10];
```

* 使用尾置返回类型

```c++
auto func(int i) -> int(*)[10];
```

### 4.4 函数重载

重载函数：同一作用域内几个函数名字相同但形参列表不同，调用时编译器根据传递的实参类型来推断使用哪个函数。

### 4.5 默认实参

```c++
typedef string::size_type sz;
string screen(sz ht=24, sz wid=80, char background = '');
```

**默认实参负责填补函数调用缺少的尾部实参。**即，要给后面的形参赋值时必须给前面的形参也传入值；只给前面的形参赋值时可以省略后面的形参。

### 4.6 内联函数

### 4.7 assert预处理宏

### 4.8 函数指针

函数指针指向的是函数而非对象。

```c++
bool lengthCompare(const string &, const string &);
bool (*pf)(const string &, const string &);//*pf指向函数  （*pf)括号必不可少，表示定义的是一个指针，指针指向函数。
```

函数名作为值使用时，自动转化为指针

```
pf = lengthCompare;//pf指向lengthCompare
bool b1 = pf("hello", "goodbye");//调用函数
bool b1 = (*pf)("hello", "goodbye");//同上
```

#### 4.8.1 函数指针做形参

```c++
void useBigger(const string&s1, const string &s2, bool pf(const string&, const string&));//第三个形参为函数类型，自动转换为指针
void void useBigger(const string&s1, const string &s2, bool (*pf)(const string&, const string&));//显式地将第三个形参定义为指向函数的指针。
```

#### 4.8.2 返回指向函数的指针

```c++
auto f1(int) -> int(*)(int*, int);
```

## 5 内存分区

C++代码运行后，内存的四个分区：

* 代码区：存放函数体的二进制代码，由操作系统管理。
* 全局区：存放全局变量、静态变量以及常量。
* 栈区：由编译器自动分配释放，存放函数的参数值、局部变量等
* 堆区：由程序员分配和释放、若程序员不释放，则程序结束时由操作系统回收。

### 5.1 程序编译后运行前

分为两个区域

* 代码区

存放CPU机器指令，代码区是共享的、只读的。

* 全局区
  
  全局变量、静态变量、常量。

### 5.2 程序运行后

栈区：由编译器自动释放。

堆区：由程序员分配释放

### 5.3 new操作符

在堆区开辟数据，返回数据的指针

```c++
int *a = new int(10);//初始化为10
delete a;//释放数据
```

开辟数组

```c++
int *arr = new int[10];
delete[] arr;
```

### 5.4 智能指针

智能指针的行为类似于常规指针，区别在于它负责自动释放所指向的对象。标准库提供了两种智能指针：

`shared_ptr`:允许多个指针指向同一个对象。

`unique_ptr`：独占所指向的对象。

```c++
shared_ptr<string> p1;   //指向string
shared_ptr<list<int>> p2;  //指向list
```

默认初始化的智能指针中保存着一个空指针。

支持的操作：

* `shared_ptr<T> sp`:空智能指针，指向类型为T的对象
* `p.get()`:返回`p`中保存的指针。
* `swap(p, q), p.swap(q)`：交换`p`、`q`中的指针。

`shared_ptr`独有的操作：

* `make_shared<T>(args)`：返回一个`shared_ptr`,指向一个动态分配的类型为`T`的对象，使用`args`初始化该对象。
* `shared_ptr<T>p(q)`：`p`是`q`的拷贝，此操作会递增`q`中的计数器。`q`中的指针必须能转换为`T*`。
* `p = q`：此操作会递减`p`的引用计数，递增`q`的引用计数，若`p`的引用计数变为0，则将其管理的原内存释放。
* `p.unique()`：若`p.use_count()`为`1`，返回`true`;否则返回`false`。
* `p.use_count()`：返回`p`共享对象的智能指针数量，主要用于调试。

最安全的分配和使用动态内存的方法是调用`make_shared`标准库函数，此函数在动态内存中分配一个对象并初始化它，返回指向此对象的`shared_ptr`。

```c++
shared_ptr<int> p = make_shared<int>();
auto p = make_shared<int>();
```

每个`shared_ptr`都有一个关联的引用计数器，无论何时拷贝一个`shared_ptr`时，引用计数都会递增。当给`shared_ptr`赋予一个新值或是`shared_ptr`被销毁，计数器就会递减。一旦一`shared_ptr`的计数器变为0，它就会自动释放所管理的对象。

`unique_ptr`独有的操作

`unique_ptr<T> u1,  unique_ptr<T, D> u2`：`u1`会使用`delete`来释放它的指针，`u2`会使用一个类型为`D`的可调用对象来释放指针。

`u = nullptr`：释放`u`指向的对象，将`u`置为空。

`u.release()`：`u`放弃对指针的控制权，返回指针，并将`u`置为空。

`u.reset()`：释放`u`所指向的对象。

## 6 类和对象

面向对象三大特征：封装、继承、多态

封装：将属性和行为作为一个整体

### 6.1**访问权限**：

1、`public`  :类内外都可访问

2、`protected`：类内可访问，类外不可访问

3、`private`：类内可访问，类外不可访问

**`struct`与`class`唯一区别**:

`struct`默认权限为公共

`class`默认权限为私有

### 6.2 构造函数和析构函数

由编译器自动调用，完成对象的初始化和清理工作。

若程序员不提供构造和析构函数，则编译器会提供空实现的构造和析构函数。

#### 6.2.3 **构造函数**

1、主要用于在创建对象时，为对象的成员属性初始化、赋值。

2、构造函数无返回值

3、函数名与类名相同

4、无需手动调用，在对象被创建时自动调用。

5、可以有参数，可发生重载

```c++
//有参构造函数
Sales_data(const std::string &S, unsigned n, double p ):bookNo(s), units_sold(n), revenue(p*n){}//构造函数初始值列表，用于为数据成员赋值
```

```c++
//拷贝构造函数
Sales_data(const Sales_data &S);
```

默认情况下，编译器会给一个类添加3个函数：

1、默认构造函数（无参、函数体为空）

2、默认析构函数（无参、函数体为空）

3、默认拷贝构造函数，对属性进行值拷贝

**构造函数调用规则：**

* 若用户定义有参构造，则编译器不提供默认构造函数，但会提供默认拷贝构造函数。

* 若用户定义拷贝构造函数，则编译器不再提供其他构造函数
  
  也就是说：
  
  ```c++
  class Person
  {
  public:
      Person(int a)//有参构造
      {
          age = a;
      }
      int age;
  };
  void main()
  {
      Person p;//报错，因用户定义了有参构造，编译器不再提供默认无参构造函数。
      Person p1(10);//正确
      Person p1 = 10;//正确
      Person p2(p1);//正确，编译器提供了默认拷贝构造函数，执行浅拷贝
  }
  ```

#### 6.2.4**析构函数**

1、无返回值

2、函数名为`~`+类名

3、无参数，因此不可发生重载

4、程序在对象销毁前会自动调用析构函数

#### 6.2.5 深拷贝与浅拷贝

浅拷贝：简单的赋值拷贝操作

深拷贝：在堆区重新申请空间，进行拷贝操作

* 若属性中有在堆区开辟的，必须自己提供深拷贝构造函数，避免默认拷贝构造函数的浅拷贝带来的堆区重复释放问题。（拷贝得到的新对象属性在析构函数中释放时）

```c++
class Person
{
public:
    Person(int age)
    {
        m_Age = new int(age);//在堆区开辟了内存
    }
    Person(const Person &p)//须定义拷贝构造函数执行深拷贝
    {
        m_Age = new int(*p.m_Age);
    }
    int *m_Age;
    ~Person()
    {
        if (m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
    }
};
```

### 6.3 类成员

#### 6.3.1 类对象作为类成员

```c++
class A{};
class B
{
    A a;
};
```

* 创建B对象时，先调用A的构造函数，再调用B的构造函数，B对象生命周期结束时，先调用A的析构函数，再调用B的析构函数。

#### 6.3.2 静态成员

在成员变量或成员函数前加`static`

静态成员变量不属于类的对象，只有非静态成员变量才属于类的对象，静态成员函数也不占用类的对象空间。

* 静态成员变量
  * 所有对象共享一份数据
  * 在编译阶段分配内存
  * 类内声明，只能在类外初始化
  * 静态存储
* 静态成员函数
  * 所有对象共享同一个函数
  * 静态成员函数只能访问静态成员变量。

```c++
class Person
{
public:
    static int m_A;
    const int m_B = 1;//常量的声明式而非定义式  
};
int Person::m_A = 10;//静态成员只能在类外初始化，可以通过对象赋值，不可以通过对象初始化。
const int Person::m_B;//若编译器需要提供定义式，则在类外进行定义。

void main()
{
    Person p1;
    //两种访问方式
    cout << p1.m_A << endl;
    cout << Person::m_A << endl;
}
```

### 6.4 this 指针

`this`指针是隐含于每一个非静态成员函数内的一种指针，**指向被调用的成员函数所属的对象。**

用途：

* 当形参和变量名相同时，用`this`指针加以区分。
* 在类的非静态成员函数中返回对象本身。

```c++
class Person
{
public:
    Person(int m_A, int m_B)
    {
        this->m_A = m_A;
        this->m_B = m_B;
    }
    Person& AddPerson(Person p)
    {
        this->m_A += p.m_A;
        this->m_B += p.m_B;
        return *this;//返回对象本身
    }
    int m_A;
    int m_B;
};
void main()
{
    Person p1(12, 13);
    Person p2(p1);
    p2.AddPerson(p1).AddPerson(p1).AddPerson(p1);
    cout << p2.m_A << endl;
}
```

### 6.5 const修饰成员函数

* 类定义中，函数后面加`const`表明该函数不会对类的成员做出改变，除了用`mutable`修饰的成员。（表明该成员函数传入的隐形参数this指向的对象为常对象。）
* 声明对象前加const称该对象为常对象，常对象只能调用常函数。
* 一个类中有名称相同的常函数和非常函数，则非常对象调用非常函数，常对象调用常函数。 

```c++
class Person
{
public:
    Person(int age)
    {
        m_age = age;
    }
    void test()const//常函数，无法修改成员变量，除了用mutable修饰的变量
    {
        m_age += 1;//错误
        m_birth += 1;//正确
    }
    int m_age;
    mutable int m_birth;//可以被常函数修改
};
```

### 6.6 友元

让一个函数或一个类访问另一个类中的私有成员。

* 全局函数做友元

```c++
class Building
{
friend void grilFriend(Building *biulding);//告诉编译器grilFriend函数为友元
public:
    Building()
    {
        drawingrRoom = "客厅";
        bedroom = "卧室";
    }
    string drawingrRoom;
private:
    string bedroom;
};
void grilFriend(Building *biulding)
{
   cout << biulding->bedroom << endl;
}
```

* 类做友元

```c++
class Building
{
    friend class GrilFriend;//告诉编译器grilFriend类为友元
public:
    Building()
    {
        drawingrRoom = "客厅";
        bedroom = "卧室";
    }
    string drawingrRoom;
private:
    string bedroom;
};
class GrilFriend
{
public:
    void visit()
    {
        cout << building.bedroom << endl;
    }
private:
    Building building;
};
void main()
{
    GrilFriend g;
    g.visit();

}
```

* 成员函数做友元

让某类中的某成员函数作为另一个类的友元，以访问其中的私有内容。

### 6.7 运算符重载

对已有运算符进行重新定义。

#### 6.7.1 加号运算符重载

实现两个自定义数据类型的相加。

```c++
class Person
{
 public:
    //成员函数实现+运算符重载
    Person operator+(const Person &p)
    {
        Person temp;
        temp.m_A = this->m_A + p.m_A;
        temp.m_B = this->m_B + p.m_B;
        return temp;
    }
    int m_A;
    int m_B;
};
//全局函数实现+运算符重载，运算符重载函数可以发生函数重载
Person operator+(const Person &p1, int val)
{
     Person temp;
     temp.m_A = p1.m_A + val;
     temp.m_B = p1.m_B + val;
     return temp;
}
void test()
{
    Person p1;
    p1.m_A = 1;
    p1.m_B = 2;
    Person p2;
    p2.m_A = 3;
    p2.m_B = 4;
    Person p3 = p1 + p2;//本质：Person p3 = p1.operator+(p2);
    Person p4 = p1 + 3;//本质：Person p4 = operator+(p1, 3)
}
```

#### 6.7.2 左移运算符重载

输出自定义数据类型

```c++
class Person
{
friend ostream& operator<<(ostream& out, Person &p);//可以访问私有成员
public:
    Person(int a, int b)
    {
        m_A = a;
        m_B = b;
    }
    private:
    int m_A;
    int m_B;
}
ostream& operator<<(ostream& out, Person &p)//不能以成员函数方式实现，因为p << out不是想要的效果。
{
    out << p.m_A << p.m_B << endl;
    return out;//返回out是为了实现链式编程 cout << p1 << p2 << p3...
}
void test()
{
    Person p(10, 9);
    cout << p;//等效于operator<<(cout, p);
}
```

#### 6.7.3 递增运算符重载

用于实现自定义数据类型递增

```c++
class MyInteger()
{
    friend ostream& operator<<(ostream &out, MyInteger mi);
public:
    MyInteger(int i)
    {
        m_i = i;
    }
    MyInteger& operator++()//前置递增，返回引用类型是为了满足链式递增:++(++mi)
    {
        m_i++;
        return *this;
    }
    MyInteger operator++(int)//后置递增，int为占位参数，用于提醒编译器此为后置递增
    {
        MyInteger temp(m_i);
        m_i++;
        return temp;
    }
private:
    int m_i;
};
ostream& operator<<(ostream &out, MyInteger mi)
{
    out << mi.m_i << endl;
    return out;
}
```

#### 6.7.4 赋值运算符重载

c++编译器一般会给一个类添加4个函数

1. 默认构造函数(无参，函数体为空)
2. 默认析构函数(无参，函数体为空)
3. 默认拷贝构造函数，对属性进行值拷贝
4. 赋值运算符 operator=, 对属性进行值拷贝

**当类中有属性指向堆区时，做赋值操作会产生深浅拷贝问题。**

```c++
class Person
{
public:
    Person(int age)
    {
        m_Age = new int(age);//在堆区开辟内存，须手动释放
    }
    Person(const Person &p)//因有属性指向堆区，须定义拷贝构造函数执行深拷贝
    {
        m_Age = new int(*p.m_Age);
    }
    int* m_Age;
    ~Person()
    {
        if(m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
    }
    Person& operator=(Person &p)//传入p
    {
        //此时本对象已经存在堆区的属性，须先释放掉
        if(m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
        //执行深拷贝
        m_Age = new int(*p.m_Age);
        return *this;//返回对象本身
    }
};

void test()
{
    Person p1(10);
    Person p2(20);
    p2 = p1;//默认执行值拷贝，即p2.m_Age = p1.m_Age;此时p1和p2的m_Age指向同一块堆区地址，因此在p1和p2的析构中会存在重复释放内存的问题，必须添加深拷贝操作
}
```

#### 6.7.5 关系运算符重载

实现自定义数据类型的比较

```c++
class Person
{
public:
    Person(int age, string name)
    {
        mAge = age;
        mName = name;
    }
    bool operator==(const Person& p)
    {
        if (mAge == p.mAge && mName == p.mName)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int mAge;
    string mName;
};
void main()
{
    Person p1(10, "qin");
    Person p2(11, "qin");
    cout << (p1 == p2) << endl;
}
```

#### 6.7.6 函数调用运算符重载

函数调用运算符()

也称为仿函数

```c++
class Myprint
{
    void operator()(string text)
    {
        cout << text << endl;
    }
};

void main()
{
    Myprint myp;
    myp("abc");
}
```

### 6.8 继承

继承语法：`class 子类: 继承方式 父类`

继承方式：

* 公共继承  `class B : public A`    可访问父类`public`成员和`protected`成员
* 保护继承  `class B : protected A`   可访问父类`public`成员和`protected`成员
* 私有继承  `class B : private A`   

父类中的私有成员也被继承下去了，只是被隐藏了，访问不到。

#### 6.8.1 继承中的构造与析构

先调用父类构造函数，再调用子类构造函数，先调用子类析构函数，再调用父类析构函数。

#### 6.8.2 继承同名成员

* 访问子类同名成员 直接访问
* 访问父类同名成员 需要加作用域

```c++
class Base
{
  public:
    int m_A;
};
class Son:public Base
{
    public:
    int m_A;
};

void main()
{
    Son s;
    s.m_A = 10;//子类中的m_A
    s.Base::m_A = 11;//父类中的m_A
}
```

#### 6.8.3 多继承语法

C++允许一个类继承多个类

`class 子类：继承方式 父类1， 继承方式 父类2 ...`

#### 6.8.4 菱形继承

两个子类继承了同一个基类，又有一个子子类同时继承了这两个子类，导致继承自基类的数据继承了两份。存在数据冗余和访问时二义性问题。

![菱形继承](C:\Users\QMJ\Desktop\菱形继承.jpg)

```c++
class Animal
{
    public:
    int mAge;
};
class Sheep: public Animal
{};
class Tuo:public Animal
{};
class SheepTuo:public Sheep, public Tuo
{};

void main()
{
    SheepTuo st;
    st.Sheep::mAge = 10;
    st.Tuo::mAge = 11;//有两份mAge，只需要一份即可
    st.mAge = 11;//报错，不明确
}
```

使用虚继承来解决菱形继承

```c++
class Sheep: virtual public Animal
{};//虚继承继承了一个虚基类指针，指针指向虚基类表
class Tuo: virtual public Animal
{};//虚继承继承了一个虚基类指针，指针指向虚基类表
//两个虚基类指针指向同一个mAge
class SheepTuo:public Sheep, public Tuo
{};
void main()
{
    SheepTuo st;
    st.mAge = 11;//只剩一份
}
```

### 6.9 多态

* 静态多态：函数重载和运算符重载  
  
  静态多态的函数地址早绑定，编译阶段确定函数地址

* 动态多态：**派生类**和**虚函数**实现运行时多态
  
  动态多态的函数地址晚绑定，运行阶段确定函数地址

满足动态多态：

* 有继承关系
* 子类重写父类的虚函数

多态使用：

* 父类类型的指针或引用指向子类对象
  
  ```c++
  class Animal
  {
      public:
      virtual void speak()//父类虚函数
      {
          cout << "动物在说话" << endl;
      }
  };
  class Cat:public Animal
  {
      public:
      void speak()//子类重写父类虚函数
      {
          cout << "小猫在说话" << endl;
      }
  };
  class Dog:public Animal
  {
      public:
      void speak()//子类重写父类虚函数
      {
          cout << "小狗在说话" << endl;
      }
  };
  
  void DoSpeak(Animal &animal)
  {
      animal.speaK();
  }
  
  void main()
  {
      Cat cat;
      DoSpeak(cat);//使用父类类型的引用指向子类对象，实现运行时绑定
      Dog dog;
      DoSpeak(dog);
  }
  ```
  
  多态底层：

添加了虚函数的基类内部存放了虚函数表指针`vfptr`

`vfptr`指向虚函数表，表内部记录虚函数地址，

当子类中没有重写父类虚函数时，子类继承了父类中的`vfptr`,

当子类重写了父类虚函数，此时子类中的`vfptr`会替换成子类的虚函数地址。

#### 6.9.1 纯虚函数与抽象类

在多态中，可以将基类的虚函数写为**纯虚函数**

`virtual 返回值类型 函数名（参数列表） = 0;`

含有纯虚函数的类称为**抽象类**

抽象类：

* 无法实例化对象，负责定义接口
* 子类必须重写抽象类中的虚函数，否则也属于抽象类

```c++
class Base
{
    public:
    virtual void func() = 0;//纯虚函数
};
class Son:public Base
{
    public:
    void func()
    {
        cout << "重写纯虚函数" << endl;
    }
};

void main()
{
    Base *base = NULL;
    base = new Son;
    base->func();
    delete base;
}
```

#### 6.9.2 虚析构和纯虚析构

**多态使用时，如果子类有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码。**：

```c++
class Animal
{
public:
    Animal()
    {
        cout << "父类构造函数调用" << endl;
    }
    virtual void speak() = 0;
    ~Animal()
    {
        cout << "父类析构函数调用" << endl;
    }
};

class Cat:public Animal
{
 public:
    Cat(string name)
    {
      m_name = new string(name); //子类在堆区创建了数据
    }
    void speak()
    {
        cout << m_name << "小猫在说话" << endl;
    }
    ~Cat()
    {
        if(m_name!=NULL)
        {
            cout << "子类析构调用" << endl;
            delete m_name;
            m_name = NULL;
        }
    }
    string* m_name;
};


void main()
{
    Animal *animal = new Cat("TOM");//父类指针指向子类对象
    animal->speak();
    delete animal;//销毁父类指针时，只调用了父类析构，不会走到子类析构，导致内存泄漏
}
```

解决办法：

将父类析构改为**虚析构**：

```c++
virtual ~Animal()
{
   cout << "父类析构调用" << endl;
}
```

**也就是说，当子类有数据开辟到堆区时，父类析构应写为虚析构，以解决父类指针释放子类对象时无法走到子类析构的问题。**

**纯虚析构**

也是为了解决上述问题。

```c++
virtual ~Animal() = 0;//类内声明
Animal::~Animal()//纯虚析构必须写类外实现，否则报错
{
    cout << "Animal 纯虚析构函数调用！" << endl;
}
```

* 拥有纯虚析构的类也是抽象类，不能实例化对象。

## 7 文件操作

文件操作头文件`<fstream>`

文件类型：

文本文件

二进制文件

操作文件三大类

* `ofstream`:写操作

* `ifstream`写操作

* `fstream`:读写操作

**文件打开方式**：

| 打开方式          | 解释             |
| ------------- | -------------- |
| `ios::in`     | 读文件            |
| `ios::out`    | 写文件，文件不存在时将创建  |
| `ios::ate`    | 初始位置：文件尾       |
| `ios::app`    | 追加方式写文件        |
| `ios::trunc`  | 如果文件存在，先删除，再创建 |
| `ios::binary` | 二进制方式          |

注意：文件打开方式可以配合使用

如：用二进制方式写文件`ios::binary|ios::out`

```c++
#include <fstream>

void write()
{
    ofstream ofs;//创建流对象
    ofs.open("test.txt", ios::out);
    ofs << "姓名：张三" << endl;//写入
    ofs << "性别：男" << endl;
    ofs.close();//关闭文件
}
void read()
{
    ifstream ifs;
    ifs.open("test.txt", ios::in);
    if(!ids.is_open())//判断文件是否打开成功
    {
        cout << "打开失败" << endl;
        return;
    }
    //第一种
    char buf[1024] = {0};
    while(ifs >> buf)//以空白为间隔，读到文件尾结束
    {
        cout << buf << endl;
    }
    //第二种
    char buf[1024] = {0};
    while(ifs.getline(buf, sizeof(buf)))//以换行符为间隔
    {
        cout << buf << endl;
    }
    //第三种
    string buf;
    while(getline(ifs, buf))
    {
        cout << buf << endl;
    }
    //第四种
    char c;
    while((c=ifs.get()) != EOF)
    {
        cout << c;
    }
    ifs.close();
}
```

**二进制方式**

写文件：`ostream& write(const char * buffer, int len)`

读文件：`istream& read(char *buffer, int len)`

```c++
#include <fstream>
#include <string>
class Person
{
    public:
    char m_Name[64];
    int m_Age;
}
void b_write()
{
    ofstream ofs;
    Person p = {"张三"， 18};
    ofs.open("test.txt", ios::out|ios::binary);
    ofs.write((const char*)&p, sizeof(p));//写文件
    ofs.close();
}
void b_read()
{
    ifstream ifs("test,txt", ios::in|ios::binary);
    //ifs.open("test.txt", ios::in|ios::binary);
    if(!ifs.is_open())
    {
        cout << "failed" << endl;
        return;
    }
    Person p;
    ifs.read((char*)&p, sizeof(p));
    ifs.close();
    cout << p.m_Name << " " << p.m_Age << endl;
}
void main()
{
    b_write();
    b_read();
}
```

## 8 C++模板

### 8.1 函数模板

建立一个通用函数，其返回值类型和形参类型可以不具体制定，用一个虚拟类型来代替。(类型参数化)

```c++
template<typename T>//typename也可用class代替
void swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

void main()
{
    int a = 10;
    int b = 20;
    swap<int>(a, b);//显式指定类型
    swap(a, b);//自动类型推导
}
```

模板函数调用方法：

1、显式指定类型

```c++
swap<int>(a, b);
```

2、自动类型推导

必须推导出一致的数据类型T才能使用

```c++
swap(a, b);
```

函数模板可以发生重载。

### 8.2 类模板

类模板与函数模板的主要区别：

1、类模板没有自动类型推导的使用方式。

2、类模板的模板参数列表中可以有默认参数。

```c++
template<class NameType, class AgeType = int>
```

**类模板成员函数和普通类成员函数的区别**

* 普通类中的成员函数一开始就可以创建
* 类模板中的成员函数在调用时才创建

```c++
class Person
{
    public:
    void showPerson()
    {
        cout << "show person" << endl;
    }
}

template<class T>
class Myclass
{
    public:
    T obj;
    void fun()//函数处于未创建状态，因此可以编译通过。
    {
        obj.showPerson();
    }
}

void main()
{
    Myclass<Person> m;//成员函数开始被创建
}
```

#### 8.2.1 类模板对象做函数参数

1、指定传入类型(常用)

```c++
template<class NameType, class AgeType = int>
class Person
{
    public:
    NameType name;
    AgeType age;
}
void printPerson(Person<string, int> &p)//指定参数类型
{
    cout << p.name << endl;
}
void main()
{
    Person<string, int> p;
    printPerson(p);
}
```

2、参数模板化

```c++
template<class T1, class T2>
void printPerson(Person<T1, T2> &p)
{
     cout << p.name << endl;
}
```

3、整个类模板化

```c++
template<class T>
void printPerson(T &p)
{
    cout << p.name << endl;
}
```

#### 8.2.2类模板的继承

* 当父类是类模板时，子类在继承时须指定出父类中T的类型
* 若想灵活指定，则子类也须变为模板

```c++
template<class T>
class Base
{
    T m;
};

class Son:public Base<int>//必须指定出父类T类型
{

};

template<class T>
class Son2:public Base<T>//或者子类也变为模板
{

};
```

#### 8.2.3 类模板成员函数的类外实现

```c++
template <class T1, class T2>
class Person
{
public:
    Person(T1 name, T2 age);//类内声明
    T1 m_name;
    T2 m_age;
}
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->m_name = name;
    this->m_age = age;
}
```

#### 8.2.4 类模板分文件编写

* 由于类模板成员函数创建时机是在调用阶段，导致分文件编写时链接不到成员函数：

`person.h`文件：

```c++
#ifndef PERSON_H
#define PERSON_H
template <class T1, class T2>//声明类
class Person
{
public:
    Person(T1 name, T2 age);//类内声明
    T1 m_name;
    T2 m_age;
}
#endif
```

`person.cpp`文件:

```c++
#include "person.h"
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)//构造函数类外实现
{
    this->m_name = name;
    this->m_age = age;
}
```

`main.cpp`文件

```c++
#include "person.h"

void main()
{
    Person<string, int> p("张三"， 18);//报错，链接不到构造函数
}
```

解决方法：

将声明和实现写在同一个文件中，并改后缀名为`.hpp`

## 内联函数

* 在类内定义的函数会被编译器自动声明为内联函数，inline关键字是对编译器的建议，最终是否能成为内联函数，由编译器决定。

* 什么时候适合使用内联函数？

​            短小而频繁调用的函数。

* 对linline函数的定义最好放在头文件中，在定义前加inline关键字。

## 9. STL(Standard Template Library)

STL六大部件：容器(Containers)    空间配置器(Allocators)   算法(Algorithms)  迭代器(Iterators)   适配器(Adapters)   仿函数(Functors)

### 容器

#### 序列容器

**Array**

**Vector**

赋值：

* `assign(beg, end);`       //将[beg, end)区间中的数据拷贝赋值。
* `assign(n, elem);`        //将n个elem拷贝赋值。

容量操作

* `empty(); `                            //判断容器是否为空

* `capacity();`                      //容器的容量

* `size();`                              //返回容器中元素的个数

* `resize(int num);`             //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
  
  ​                          //如果容器变短，则末尾超出容器长度的元素被删除。

* `resize(int num, elem);`  //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
  
  ​                              //如果容器变短，则末尾超出容器长度的元素被删除

插入和删除

* `push_back(ele);`                                         //尾部插入元素ele
* `pop_back();`                                                //删除最后一个元素
* `insert(const_iterator pos, ele);`        //迭代器指向位置pos插入元素ele
* `insert(const_iterator pos, int count,ele);`//迭代器指向位置pos插入count个元素ele
* `erase(const_iterator pos);`                     //删除迭代器指向的元素   返回删除元素的下一元素迭代器
* `erase(const_iterator start, const_iterator end);`//删除迭代器从start到end之间的元素    返回删除元素的下一元素迭代器
* `clear();`                                                        //删除容器中所有元素

数据存取

* `at(int idx); `     //返回索引idx所指的数据
* `operator[]; `       //返回索引idx所指的数据
* `front(); `            //返回容器中第一个数据元素
* `back();`              //返回容器中最后一个数据元素

元素互换

* `swap(vec);`  // 将vec与本身的元素互换

```c++
//清空内存
vector<int> v(10, 3);
vector<int>().swap(v);//清空v
//收缩内存 使capacity==size
vector<int>(v).swap(v);
```

预留空间

功能：减少vector在动态扩展容量时的扩展次数。

函数原型：

* `reserve(int len);`//容器预留len个元素长度，预留位置不初始化，元素不可访问。

**string**

**函数原型：**

查找与替换

* `int find(const string& str, int pos = 0) const;`              //查找str第一次出现位置,从pos开始查找
* `int find(const char* s, int pos = 0) const; `                     //查找s第一次出现位置,从pos开始查找
* `int find(const char* s, int pos, int n) const; `               //从pos位置查找s的前n个字符第一次位置
* `int find(const char c, int pos = 0) const; `                       //查找字符c第一次出现位置
* `int rfind(const string& str, int pos = npos) const;`      //查找str最后一次位置,从pos开始查找
* `int rfind(const char* s, int pos = npos) const;`              //查找s最后一次出现位置,从pos开始查找
* `int rfind(const char* s, int pos, int n) const;`              //从pos查找s的前n个字符最后一次位置
* `int rfind(const char c, int pos = 0) const;  `                      //查找字符c最后一次出现位置
* `string& replace(int pos, int n, const string& str); `       //替换从pos开始n个字符为字符串str
* `string& replace(int pos, int n,const char* s); `                 //替换从pos开始的n个字符为字符串s

插入与删除

* `string& insert(int pos, const char* s);  `                //插入字符串
* `string& insert(int pos, const string& str); `        //插入字符串
* `string& insert(int pos, int n, char c);`                //在指定位置插入n个字符c
* `string& erase(int pos, int n = npos);`                    //删除从Pos开始的n个字符 

获取子串

* `string substr(int pos = 0, int n = npos) const;`   //返回由pos开始的n个字符组成的字符串

**Deque**

赋值

* `deque& operator=(const deque &deq); `         //重载等号操作符

* `assign(beg, end);`                                           //将[beg, end)区间中的数据拷贝赋值给本身。

* `assign(n, elem);`                                             //将n个elem拷贝赋值给本身。

容器大小操作与vector相同，无容量概念。

两端插入操作：

- `push_back(elem);`          //在容器尾部添加一个数据
- `push_front(elem);`        //在容器头部插入一个数据
- `pop_back();`                   //删除容器最后一个数据
- `pop_front();`                 //删除容器第一个数据

指定位置操作：

* `insert(pos,elem);`         //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
* `insert(pos,n,elem);`     //在pos位置插入n个elem数据，无返回值。
* `insert(pos,beg,end);`    //在pos位置插入[beg,end)区间的数据，无返回值。
* `clear();`                           //清空容器的所有数据
* `erase(beg,end);`             //删除[beg,end)区间的数据，返回下一个数据的位置。
* `erase(pos);`                    //删除pos位置的数据，返回下一个数据的位置。

**stack**

常用接口

数据存取：

* `push(elem);`      //向栈顶添加元素
* `pop();`                //从栈顶移除第一个元素
* `top(); `                //返回栈顶元素

大小操作：

* `empty();`            //判断堆栈是否为空
* `size(); `              //返回栈的大小

**queue**

- 入队   --- push
- 出队   --- pop
- 返回队头元素   --- front
- 返回队尾元素   --- back
- 判断队是否为空   --- empty
- 返回队列大小   --- size

**List**

* `reverse();`   //反转链表
* `sort();`        //链表排序
* `erase();`     //删除元素

Forward-List

#### 关联式容器（二叉树结构）

##### **Set/Multiset:**(红黑树)

* 所有元素在插入时被自动排序,默认排序规则为从小到大。利用仿函数可以改变排序规则。
* set不允许容器有重复的元素。set插入数据的同时会返回插入结果，表示插入是否成功。
* multiset允许容器中有重复的元素。
* set插入元素时使用insert。
* 对于自定义数据类型，set必须指定排序规则才可以插入数据。
* 正确地修改`set`中元素值的做法：先删除该元素，再插入修改后的该元素

查找与统计

* `find(key);`                  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
* `count(key);`                //统计key的元素个数，对于set，结果为0或1

pair对组

* 第一个元素为key,起索引作用，第二个元素为value

```c++
pair<type, type> p (value1, value2);
pair<type, type> p = make_pair( value1, value2 );
cout << p.second;
cout << p.first;
```

##### Map/Multimap:(红黑树)

* map中所有元素都是pair
* 所有元素会根据键值自动排序。默认从小到大，利用仿函数可改变排序规则。对于自定义数据类型，需指定排序规则。
* map不允许有重复的key值元素
* mulyimap允许有重复key值元素

```
map <int, int> m;
m.insert(pair<int, int>(1, 10));
```

插入与删除

- `insert(elem);`           //在容器中插入元素。
- `clear();`                    //清除所有元素
- `erase(pos);`              //删除pos迭代器所指的元素，返回下一个元素的迭代器。
- `erase(beg, end);`    //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
- `erase(key);`            //删除容器中值为key的元素。

查找与统计

- `find(key);`                  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end();
- `count(key);`                //统计key的元素个数  对于map，结果为0或1

#### 无序容器（哈希表）

**查找时间复杂度为1**

##### Unordered Set/Multiset:

`#include<unordered_set>`

```c++
template <class Key,//存储元素的类型
          class Hash = hash(Key),//哈希函数
          class Pred = equal_to<Key>,//衡量两个元素是否相等的标准（该容器不能存放相等元素）
          class Alloc = allocator<Key>//分配器对象的类型
          >class unordered_set;
```

* T类型的对象在容器中的位置由它们的哈希值确定，因此对于自定义数据类型需要定义一个`Hash<T>`函数。默认的哈希函数只适用于基本数据类型（包括string）。
* `unordered_set`不能存放重复元素,且存放的值不能被修改， `unordered_multiset`可以存放相同元素。
* `set`会对插入元素自动排序，而`unordered_set`不会排序

##### Unordered Map/Multimap:

```c++
template< class Key,//键值的类型
          class T,//值的类型
          class Hash = hash<Key>,//哈希函数
          class Pred = equal_to<Key>,//判定键值相同的规则
          class Alloc = allocator<pair<const Key, T>>//分配器对象类型
          >class unordered_map;
```

* `unordered_map`无序存放，键值不能重复。
* 更新元素：`unordered_map[key] = value`，如果键值不存在，将插入该键值。

#### 优先队列

具有队列的所有特性，在此基础上添加了排序功能，本质是由堆实现的。

（与队列`front()`不同，优先队列使用`top()`访问队首/堆顶元素）

```c++
template <typename T, typename Container=std::vector<T>, typename Compare=std::less<T>>
class priority_queue
```

参数列表：

`T`:数据类型

`Container`:容器类型，默认为`vector`

`Compare`:比较的方式，默认为`less`，升序排列

```c++
//升序队列，小顶堆
priority_queue<int, vector<int>, greater<int> > q;
//降序队列，大顶堆
priority_queue<int, vector<int>, less<int> > q;
//greater,less为内建的函数对象。
```

插入时时间复杂度？

### 仿函数（函数对象）

* 重载函数调用操作符的类，其对象称为函数对象。

* 函数对象使用重载()时，行为类似函数调用，也叫仿函数。

* 本质是一个类，不是函数。

特点：

* 函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
* 函数对象超出普通函数的概念，函数对象可以有自己的状态
* 函数对象可以作为参数传递

```c++
class Myadd
{
    public:
        int operator()(int v1, int v2)
        {
            return v1 + v2;
        }
    int count;//可以有自己的内部状态
}

void test(Myadd &add)//可以作为参数传递
{
    add(1, 2);
}
```

#### 谓词

判断、断言

* 返回bool类型的仿函数
* 一个输入参数称为一元谓词
* 两个输入参数为二元谓词

```c++
class MyCompare//二元谓词
{
public:
    bool operator()(int num1, int num2)
    {
        return num1 > num2;
    }
};
```

#### 内建函数

* STL内建的一些函数对象
* 需引入头文件`#include<functional>`

分类：

* 算数仿函数
* 关系仿函数
* 逻辑仿函数

### STL常用算法

* 算法主要是由头文件`<algorithm>` `<functional>` `<numeric>`组成。
* `<algorithm>`是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等
* `<numeric>`体积很小，只包括几个在序列上面进行简单数学运算的模板函数
* `<functional>`定义了一些模板类,用以声明函数对象。

#### 遍历算法

`for_each(iterator beg, iterator end, _func);`//遍历容器元素

搬运容器到另一个容器中。

`transform(iterator beg1, iterator end1, iterator beg2, _func);`

//beg1 源容器开始迭代器

//end1 源容器结束迭代器

//beg2 目标容器开始迭代器

//_func 函数或者函数对象

//目标容器需要提前开辟空间

#### 查找算法

* `find(iterator beg, iterator end, value)`查找元素  找到返回指定元素迭代器，未找到返回结束时迭代器。

* `find_if(iterator beg, iterator end, _pred)`按条件查找元素

​        // 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置

​        // beg 开始迭代器

​        // end 结束迭代器

​        // _Pred 函数或者谓词（返回bool类型的仿函数）

* `adjacent_find`查找相邻重复元素，返回相邻元素的第一个位置的迭代器。

* `bool binary_search(iterator beg, iterator end, value)`**二分查找法**， 查找指定元素是否存在

* ```c++
  ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val);//在[first, last)内二分查找不小于val的第一个数，返回其迭代器。
  ```
  
  ```c++
  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,//二分查找指定范围内大于val的第一个数
                               const T& val);
  ```

* ```c++
  pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);//二分查找指定范围内等于val的数     查找成功时，第 1 个迭代器指向的是 [first, last) 区域中第一个等于 val 的元素；
                  第 2 个迭代器指向的是 [first, last) 区域中第一个大于 val 的元素。
  ```

* `count(iterator beg, iterator end, value);  `按值统计元素出现次数，统计自定义数据类型时，需配合重载`operator==`

* `count_if(iterator beg, iterator end, _Pred);`按条件统计元素出现次数

#### 排序、打乱、合并、反转算法

* `sort(iterator beg, iterator end, _Pred);  `

* `random_shuffle(iterator beg, iterator end);  `指定范围内元素随机调整顺序 使用时需加随机数种子

* `merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);`两个容器元素合并，并存储到另一容器中。合并的两个容器必须是有序序列。

* `void reverse(iterator beg, iterator end);  `反转指定范围元素

#### 拷贝和替换算法

- `copy(iterator beg, iterator end, iterator dest)`                      // 容器内指定范围的元素拷贝到另一容器中
- `replace(iterator beg, iterator end, oldvalue, newvalue);  `             // 将容器内指定范围的旧元素修改为新元素
- `replace_if (iterator beg, iterator end, _pred, newvalue);`          // 容器内指定范围满足条件的元素替换为新元素
- `swap`                     // 互换两个容器的元素

#### 算数算法

`#include <numeric>`

* `accumulate(iterator beg, iterator end, value)`    //计算容器累计和   起始迭代器， 结束迭代器， 起始值
* `fill(iterator beg, iterator end, value);  `向容器中填充指定元素

#### 集合算法

* `set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  `求两个集合的交集，并放目标容器中，**目标容器需要提前开辟空间**。两个集合必须是有序序列。
* `set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest)`求两个集合的并集，并放到目标容器中，必须是有序序列。
* `set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  `求两个集合的差集。

## lambda表达式

可以快速声明一个匿名函数对象。
![lambda](C:\Users\qmj\OneDrive\图片\lambda.png)

### 捕获列表

[]是lambda表达式的引出符。
捕获列表能够捕获上下文中的变量供lambda表达式使用。

```c++
class A
{
    public:
    int i=0;
    void func(int x, int y)
    {
        auto f1 = []{return i;};//错误，未捕获任何变量
        auto f2 = [=]{return i;};//以值传递方式捕获所有外部变量
        auto f3 = [&]{return i+x+y};//以引用方式捕获所有外部变量
        auto f4 = [&i, x, y]{return i+x+y;};//引用方式捕获i，值传递方式捕获x,y
        auto f5 = [this]{return i;};//捕获this指针，可以在lambda表达式中使用当前类的成员函数和成员变量
        auto f6 = [=]() mutable {return i++;};//使用mutable时不可省略()
    }
}
```

* lambda表达式默认按值捕获外部变量，无法对其进行修改，如要修改，可以使用引用方式捕获，或加mutable关键字。见`f6`

### 参数列表

与普通函数的参数列表一致，如果不需要参数传递，则可以省略`()`.

### mutable修饰符

### 异常说明

用于lambda表达式内部函数抛出异常。

### 返回类型

以追踪返回类型形式声明函数的返回类型，可以在不需要返回值时连同`->`一起省略。

### 字符串分割

`string substr ( size_t pos = 0, size_t n = npos ) const;`

### strlen和sizeof

```c
//strlen是一个函数
size_t strlen(const char* str);//返回字符串长度，不包含空字符，遇到第一个空字符\0就结束
//sizeof是一个单目运算符
//返回缓冲区的长度，包括空字符。
char str[10];
sizeof(str);//返回10
char* pstr;
sizeof(pstr);//返回指针的字节大小，即8
```

### malloc/free

```c
//分配指定字节的内存，返回void*指针
void* malloc(size_t size);
//使用时，根据需要将void*指针转换为对应的指针
char* str = (char*)malloc(16);
free(str);//释放空间
```

### calloc/malloc/realloc

```c
//calloc比malloc多一个参数，第一个参数为要申请的类型的空间个数，第二个参数为每个参数的字节大小
//malloc申请的空间值是随机的，calloc申请后会将空间进行初始化为0
void* calloc(size_t n, size_t, size);
```

```c
//用于对动态内存进行扩容，ptr为指向原来空间基址的指针，new_size为需要扩充的容量大小
void realloc(void* ptr, size_t new_size);
```

### sprintf

发送格式化输出到 **str** 所指向的字符串。

```c
int sprintf(char *str, const char *format, ...)
```

## 类的构造函数定义为private（单例模式）

对于类本身，可以利用static公有成员，因为它独立于class对象之外，不必构造对象就可以使用它们！在某个static函数中创建该class的对象，并以引用或指针的形式将其返回（不以对象返回，主要是构造函数是私有的，外部不能创建临时对象），就获得了这个对象的使用权。

例：

```c++
class processpool{
private:
    processpool(int listenfd, int process_number);
public:
    static processpool* create(int listenfd, int process_number)
    {
        if(!m_instance)//保证只存在一个类的实例
        {
            m_instance = new processpool(listenfd, process_number);
        }
        return m_instance;
    }
private:
    static processpool* m_instance;//类的静态实例
};
```

## 左值、右值、左值引用、右值引用

> 左值：左值是存储单元内的值，有实际的存储地址，可以取地址。前置自增是左值。
>
> 右值：右值不是存储单元内的值，可以是寄存器内的值也可以是立即数，不可以取地址。
>
> 纯右值：
>
> * 字面值（除字符串字面值外）
> * 后置自增自减表达式（`a++`,`a--`）
> * 算术表达式
> * 逻辑表达式
> * 比较表达式
> * lambda表达式
> * 取地址表达式

```c++
int a = 5;//a为左值，5为右值
```

> 左值引用：能指向左值，不能指向右值。用`&`符号引用左值。
>
> 右值引用：①为了避免临时对象非必要的昂贵的拷贝操作。②在模板函数中按照参数的实际类型进行转发。用`&&`符号引用右值，只能指向右值。

```c++
int a = 5;
int &ref_a = a;//左值引用指向左值,编译通过
int &ref_a = 5;//左值引用指向右值，编译不过
```

**左值引用指向右值加个`const`就可以编译通过**,这也是为什么用`const&`作为函数入口参数的原因。

```c++
const int &ref_a = 5;//编译通过
void push_back(const value_type& val);//const&可以直接传值   &不能直接传值
vec.push_back(5);//可以直接传值
```

右值引用

```c++
int a = 5;
int &&ref_a = 5;//指向右值，编译通过    ref_a本身是左值
int &&ref_a = a;//指向左值，编译不过
ref_a = 6;//右值引用可以修改右值
```

右值引用指向左值

```c++
int a = 5;
int &&ref_a = std::move(a);//左值强制转化为右值
```

### std::move()

功能：将一个左值强制转化为右值引用，从实现上来看，`std::move`基本等同于一个类型转换`static_cast<T&&>(lvalue)`。

右值引用应用场景

①实现移动语义

在STL容器中实现了以**右值引用**为参数的**移动构造函数**和**移动赋值**重载函数。传入参数为左值，意味着拷贝，传入参数为右值，意味着移动。

对于持有动态内存的对象，在构造和赋值时一般需要在堆区申请内存实现深拷贝，而对于即将消亡的右值对象，其实只需要接管它所持有的资源即可，无需深拷贝，因此使用移动构造和移动赋值可以浅拷贝获得右值的资源。

```c++
class Array{
	public:
    // 深拷贝构造
    Array(const Array& temp_array) {
        size_ = temp_array.size_;
        data_ = new int[size_];//申请内存
        for (int i = 0; i < size_; i ++) {
            data_[i] = temp_array.data_[i];
        }
    }
    
    // 移动构造  接管temp_arry的资源
    Array(Array&& temp_array) {
        data_ = temp_array.data_;
        size_ = temp_array.size_;
        // 为防止temp_array析构时delete data，提前置空其data_      
        temp_array.data_ = nullptr;
    }
};
```

当传入参数为左值但想利用移动语义来优化性能时，可以使用`std::move`将左值转化为右值

```c++
std::string str1 = "aacsac";
std::vector<std::string> vec;
vec.push_back(str1);//传统方法，拷贝
vec.push_back(std::move(str1));//避免拷贝，str1会失去原有值

//vector的方法定义
void push_back(const value_type& val);
void push_back(value_type&& val);
```

②完美转发

`std::forward<T>(u)` 可以实现左右值互转

当`T`为左值引用类型时，`u`将被转换为`T`类型的左值；

否则，将被转换为`T`类型的右值。

所谓转发，就是通过一个函数将参数继续转交给另一个函数进行处理，原参数可能是右值，可能是左值，如果还能继续保持参数的原有特征，那么它就是完美的。

## c++深拷贝与浅拷贝

>浅拷贝：按位复制
>
>深拷贝：在堆区重新申请内存，进行拷贝

c++类的默认拷贝构造函数是浅拷贝。

```c++
class example{
    //自己实现的深拷贝
	example(const example& exp)
    {
        //p = exp.p;//浅拷贝
        p = new int(*exp.p);//深拷贝
    }
    int* p;
};
```

对于持有指针的对象，浅拷贝只是指针的拷贝，新对象与被拷贝对象中的指针仍然指向同一段内存，在析构时会发生重复`delete`。

深拷贝与浅拷贝的区别就在于深拷贝会在堆内存中另外申请空间来储存数据，从而也就解决了指针悬挂的问题。简而言之，当数据成员中有指针时，必须要用深拷贝。

## emplace_back和push_back

[一文轻松搞懂emplace_back与push_back - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/610294692)

`push_back`在容器尾部添加元素时，首先会构造这个元素，然后将这个元素拷贝或移动到容器中；

`emplace_back`会直接在容器尾部构造这个元素，省去了移动或拷贝步骤。

`push_back`可以接受传入一个构造参数，`emplace_back`可以接受多个构造参数，直接原地构造对象。

## new/delete和malloc/free的异同

都可以用于动态申请内存和释放内存。

1.属性区别

`new/delete`是C++关键字，需要编译器支持；

`malloc/free`是C语言库函数，使用时需要引入头文件`<stdlib.h>`；

2.使用区别

`malloc`需要显式指定申请内存的大小（以字节为单位）；

`new`无需显式填入内存大小，编译器会根据类型自动计算大小；

C++允许重载`new/delete`，`malloc`不允许重载。

3.返回类型区别

`malloc`分配成功时返回`void*`，需要通过强制类型转换将`void*`转为所需类型；分配失败时返回`NULL`，可以通过判断返回值得知是否分配成功；

`new`分配成功时返回的是对象类型的指针，无需类型转换；分配失败时抛出`bac_alloc`异常，程序会异常退出，可以通过异常捕捉来捕获该异常；

4.定义对象系统调度过程区别

使用`new`操作符分配内存会经历三个步骤：

* 调用`operator new`函数（数组是`operator new[]`）分配一块足够的空间以便存储特定类型的对象（底层默认使用`malloc`实现）；
* 运行相应的构造函数以构造对象，并为其传入初值；
* 构造完成后返回一个指向该对象的指针。

使用`delete`释放内存时会经历两个步骤：

* 调用对象的析构函数；
* 调用`operator delete`释放内存空间（底层默认使用`free`实现）。

5.内存区域区别

`new`分配的内存位于自由存储区，`malloc`分配的内存位于堆区。

堆是操作系统维护的一块内存，而自由存储是C++中通过new与delete动态分配和释放对象的抽象概念。堆与自由存储区并不等价。

但是多数情况下，new实现的基础仍然是C语言的malloc和free，但程序员也可以通过重载操作符，改用其他内存来实现自由存储。

6.内存扩张

使用`malloc`分配内存后，发现不够用可以用`realloc`函数来扩张内存大小，`realloc`会先判断当前内存后面是否还有足够的空间，如果有，则在后面扩充，否则从新申请一块空间，将当前空间的内容拷贝过去；

`new`没有内存扩张机制。

### 有了malloc/free为什么还需要new/delete?

对于非内部数据类型的对象而言，只用`malloc/free`无法满足动态对象的要求，对象在创建时需要自动执行构造函数，在销毁前需要自动执行析构函数因此C++语言 需要一个能完成动态内存分配和初始化工作的运算符`new`，以及一个能完成清理与释放内存工作的运算符`delete`。

[C++经典面试题（最全，面中率最高） - fcyh - 博客园 (cnblogs.com)](https://www.cnblogs.com/yjd_hycf_space/p/7495640.html)

[C++面试集锦( 面试被问到的问题 ) - Y1 - 博客园 (cnblogs.com)](https://www.cnblogs.com/Y1Focus/p/6707121.html)

### new申请的内存可以free吗

可以，但不安全，使用`free`释放内存时不会调用对象的析构函数，当对象持有动态内存时，就会造成内存泄露。

## int[]和int*的区别

* `int[]`用来声明数组，数组的大小必须在声明时指定；`int*`声明指向整数类型的指针。
* `int[]`在定义时自动分配内存，大小固定；`int*`需要手动分配内存。
* `int[]`具有固定大小，无法改变指向；`int*`没有固定大小，可以指向不同大小的数组。
* 对指针取`sizeof`得到的是指针大小；对数组名取`sizeof`得到的是数组大小。
* 做函数形参时，没有区别。

## 指针和引用使用场景区别？

需要使用指针的场合：

* 需要指向空值时；
* 需要在不同时刻指向不同对象时。

## 智能指针

[C++ 智能指针最佳实践&源码分析 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/436290273)

智能指针本身是一个类，可以用来管理我们所申请的动态内存。

C++支持三种智能指针：

* `unique_ptr`
* `shared_ptr`
* `weak_ptr`

智能指针有一个通用规则：`->`表示调用指针原有的方法，`.`表示调用智能指针本身的方法。

智能指针只能管理堆对象，不能管理栈对象。栈上对象在离开其作用域时会自动销毁，如果将其指针交给智能指针，会造成二次销毁。

智能指针本身是一个栈上分配的对象。根据栈上分配的特性，在离开作用域后，会自动调用其析构方法。

### unique_ptr

`unique_ptr`独占对象的所有权，即两个`unique_ptr`不能同时指向同一个对象，这体现在：

1. `unique_ptr`不能被复制到另一个`unique_ptr`；
2. `unique_ptr`只能通过移动语义将所持对象的所有权转移到另一个`unique_ptr`。

```c++
std::unique_ptr<A> a1(new A());
std::unique_ptr<A> a2 = a1;//报错，不能复制
std::unique_ptr<A> a2 = std::move(a1);//转移a1对对象的所有权，转移后a1不再拥有任何指针。
```

`unique_ptr`支持的方法：

* `get()`：获取其保存的原生指针；
* `bool()`：判断是否拥有指针；
* `release()`：释放所管理指针的所有权，但不销毁原指针，返回原指针；
* `reset()`：释放并销毁原指针，如果传入一个新指针，将管理这个指针。

```c++
std::unique_ptr<A> a1(a2.release());//转移所有权
a1.reset(new A());//释放并销毁原对象，并管理一个新对象
a1.reset();//释放并销毁原对象
a1 = nullptr;//释放并销毁原对象
```

使用场景：一般在不需要多个指向同一个对象的指针时使用。如这个对象在某个对象或方法的内部时优先使用`unique_ptr`。

**源码解析**

```c++
template <class _Tp, class _Dp = default_delete<_Tp> >
class _LIBCPP_TEMPLATE_VIS unique_ptr {
public:
  typedef _Tp element_type;
  typedef _Dp deleter_type;
  typedef typename __pointer_type<_Tp, deleter_type>::type pointer;
  //...
 private:
  	__compressed_pair<pointer, deleter_type> __ptr_;
}
```

`unique_ptr`有两个模板参数：`_Tp`和`_Dp`:

* `_Tp`:表示原生指针的类型；
* `_Dp`：表示析构器，开发者可以自定义指针销毁的方法，`default_delete<_Tp>`其实就是标准的`delete`。

`unique_ptr`中唯一的数据成员是原生指针和析构器的pair。

### shared_ptr

`shared_ptr`共享对象的所有权，多个`shared_ptr`可以拥有同一个原生指针的所有权。

`shared_ptr`支持的方法：

* `get()`：获取其保存的原生指针；
* `bool()`：判断是否拥有指针；
* `reset()`：释放并销毁原指针，如果传入一个新指针，将管理这个指针；
* `unique()`：当引用计数为1时返回true；
* `use_count()`：返回引用计数大小。

最安全的分配和使用动态内存的方法是调用`make_shared`标准库函数，此函数在动态内存中分配一个对象并初始化它，返回指向此对象的`shared_ptr`。若使用`new`可能会出现用原生指针初始化了两个`shared_ptr`的问题，造成对象的重复释放。

```c++
shared_ptr<int> p = make_shared<int>();
auto p = make_shared<int>();
```

每个`shared_ptr`都有一个关联的引用计数器，无论何时拷贝一个`shared_ptr`时，引用计数都会递增。当给`shared_ptr`赋予一个新值或是`shared_ptr`被销毁，计数器就会递减。一旦一`shared_ptr`的计数器变为0，它就会自动释放所管理的对象。

**源码解析**

```c++
template<class _Tp>
class shared_ptr
{
public:
    typedef _Tp element_type;

private:
    element_type*      __ptr_;
    __shared_weak_count* __cntrl_;
    //...
}
```

`shared_ptr`主要有两个成员变量，一个是原生指针,一个是控制块指针。

### weak_ptr

`weak_ptr`是为了配合`shared_ptr`解决**循环引用**问题而存在的，`weak_ptr`本身不能直接调用原生指针的方法,需要升级为`shared_ptr`方可。`weak_ptr`不能改变所指对象的引用计数。

循环引用：两个对象彼此都持有对对方的引用，导致它们的引用计数永远不会为0，无法释放。

```c++
class A{
  public:
    std::shared_ptr<B> b_ptr;
};
class B{
  public:
    std::shared_ptr<A> a_ptr;
};

std::shared_ptr<A> a = std:make_shared<A>();//A对象引用计数为1
std::shared_ptr<B> b = std::make_shared<B>();//B对象引用计数为1
a->b_ptr = b;//B对象引用计数为2
b->a_ptr = a;//A对象引用计数为2
//当a 和 b离开作用域时，调用他们的析构函数，A对象和B对象的引用计数均减一，但仍不为0，所以其管理的对象不会被释放，造成内存泄漏
//A对象不会被释放，且A对象的成员变量b_ptr持有对B对象的引用，所以B对象不会被释放，而B对象的成员变量a_ptr持有对A对象的引用，所以A对象不会被释放。
```

解决办法：将其中一方的成员变量设为`weak_ptr`。`weak_ptr`无法直接访问其指向的对象，必须先使用`lock()`函数转为`shared_ptr`，同时在访问前，应使用`expired()`判断其指向的对象是否被释放。

`weak_ptr`支持的方法：

* `expired()`：判断所指向的原生指针是否被释放；
* `use_count()`：返回所指向原生指针的引用计数；
* `lock()`：返回`shared_ptr`,若原生指针已被释放，返回空的`shared_ptr`。
* `reset()`：将本身置空。

为什么要使用智能指针？

1. 避免内存泄漏；
2. 解决多线程下对象析构问题。

智能指针常见面试题：

1. 智能指针的实现原理？

   智能指针本质是一个类，用这个类来管理我们申请的动态内存的指针，然后在析构函数中对动态内存进行释放，在类对象的生命周期结束时会自动调用类的析构函数，避免了没能手动释放内存造成的内存泄露。

   C++支持三种智能指针，`unique_ptr`，`shared_ptr`，`weak_ptr`，`unique_ptr`独占对对象所有权，不能进行拷贝构造或赋值，只能进行所有权的转移，如使用`std::move()`或成员函数`release()`放弃所有权；`shared_ptr`允许共享对象的所有权，内部采用了引用计数，表示指向这个对象的智能指针的个数，`shared_ptr`在析构时，首先会将所指对象的引用计数减一，然后判断当引用计数为0时，释放所指向的对象。`weak_ptr`指针本身不具有对所指对象的所有权，不能访问所指对象，是为了配合`shared_ptr`解决循环引用问题而存在的，它不会改变所指对象的引用计数，当需要访问所指对象时，必须利用`lock()`成员函数升级为`shared_ptr`才能访问，并且在访问前最好用`expired()`判空。

   

## C++内存模型

#### 执行前

C++程序在执行前，其内存可以分为两个区域：

* 代码区：存放编译后的二进制代码；
  * 代码区是共享的，对于被频繁执行的程序，只要在内存中有一份代码即可；
  * 代码区是只读的，防止程序意外修改了指令。
* 全局区：存放**全局变量**、**静态变量**和**常量**，在程序结束后由操作系统释放。

#### 执行后

* 栈区：由编译器自动分配和释放，存放函数的参数值、局部变量等；
* 堆区：由程序员分配和释放，若程序员不释放，程序结束时由操作系统回收；
* 全局区：
  * 数据区：存放已初始化的全局变量、静态变量和常量；
  * BSS区：存放未初始化的全局变量和静态变量。
* 代码区：存放编译后的二进制代码；

#### 自由存储区

自由存储是C++通过`new`和`delete`分配和释放对象的抽象概念，通过`new`申请的内存即位于自由存储区，通过`malloc`申请的内存位于堆区。

**自由存储区和堆区是否等价？**

不等价。默认情况下编译器是借由`malloc`和`free`来实现`new`和`delete`的，这个时候自由存储区即位于堆上，但程序员也可以通过重载操作符，改用其它内存来实现自由存储，此时自由存储区就不等于堆了。

## 内存对齐，字节对齐

为什么要内存对齐：

提高处理器读取内存的效率。

尽管内存是以字节为单位，但大部分处理器并不会按字节来存取内存，一般会以双字节、四字节、八字节为单位存取，这些单位称为内存存取粒度。内存对齐的结果是使内存中数据的首地址是CPU单次获取数据大小的整数倍。

对齐规则：

* 基本数据类型的对齐值就是其`sizeof`的值；
* 结构体的对齐值是其成员的最大对齐值；
* 编译器可以设置一个最大对齐值，实际对齐值是该类型的对齐值与默认对齐值取最小值。

成员对齐：

* 第一个成员相对结构体首地址偏移为0；
* 后续成员偏移地址是自身对齐值的整数倍；

整体对齐：

* 结构体总大小是成员最大对齐值的整数倍。



## C++面向对象

面向过程：面向过程是以过程为中心的编程思想，将问题分解为一个个步骤，通过函数实现每个步骤，然后依次调用。

优点：性能比面向对象高，类的调用需要实例化；

缺点：不易维护和扩展

面向对象：面向对象以对象为中心，通过分析问题，分解出一个个对象，通过不同对象之间的调用组合来解决问题。建立对象的目的不是为了完成某个步骤，而是为了描述某个事物在解决问题过程中的行为。

优点：易维护，易扩展，可以设计出低耦合的系统；

缺点：性能比较低，类的实例化开销较大。

面向对象三大特征：封装、继承、多态。

### 封装

将数据和操作数据的方法封装成类，对外隐藏成员属性和实现细节，只提供接口来与外界交互。

优点：增强了数据安全性，隐藏了实现细节，对外只提供接口，方便类自身的修改。

### 继承

子类可以继承父类的属性和方法，并进行扩展，提高了代码复用性。

### 多态

一种接口，多种实现。

多态分为静态多态和动态多态。

#### 静态多态

在编译期间就可以确定函数的调用地址，地址早绑定，也叫静态联编。

通常通过函数重载，运算符重载，和模板来实现。

#### 动态多态

运行时才能确定函数调用地址，地址晚绑定。

子类继承父类，并重写父类虚函数。

基类指针指向派生类对象，并调用虚函数。

#### 虚函数表

实现动态绑定的核心是虚函数表。

每个包含了虚函数的类都包含一个虚表。

* 虚表是一个指针数组，每个元素对应一个虚函数的函数指针，虚函数表在编译阶段创建。
* 虚表属于类，而不是属于某个具体的对象，同一个类的所有对象都是用同一个虚表。
* 类的每个对象都有一个指向虚表的指针`*_vptr`。
* 拥有虚函数的类，其派生类也会拥有虚表，派生类拥有的虚表数量根据继承的基类数量而定。
* 派生类的虚函数表顺序与继承时的顺序相同。
* 派生类自己的虚函数放在第一个虚函数表的后面。
* 虚函数表的指针位于对象实例中最前面的位置。

覆盖：

派生类重写了基类的虚函数，则该虚函数地址被放在基类对应的虚函数的位置。

多继承：

派生类继承多个基类的虚表，自己的虚函数放在第一个基类虚表的后面。

构造函数和析构函数可以是虚函数吗？

构造函数不可以是虚函数，因为`vptr`是在构造函数中初始化的，如果构造函数是虚函数，那么调用构造函数时需要去虚函数表中找构造函数的指针，而此时`vptr`还没有初始化，无法找到虚函数表。

析构函数可以是虚函数且最好是虚函数。当父类析构是虚函数时，释放对象时会先调用子类析构函数，再调用父类析构，否则只会调用父类析构函数，可能造成内存泄漏。

### 虚基类/虚继承

用来解决多重继承带来的二义性问题和内存空间浪费问题。

```c++
class A{};
class B:virtual public A{};
class C:virtual public A{};
```

## 隐藏和覆盖

**隐藏（hide）**

当在派生类中定义了与基类中成员函数同名的成员函数时，基类的成员函数将被**隐藏**。使用派生类对象将无法直接访问被隐藏的基类函数，除非使用作用域运算符显式指定基类名称。

* 隐藏通过函数名称来确定，参数列表可以相同可以不同；
* 隐藏不会发生动态绑定。

```c++
son.Father::func();
```

**覆盖（override）**

派生类重写了基类的虚函数，则该虚函数地址被放在基类对应的虚函数的位置。

* 派生类中**函数名**、**参数列表**、**返回值**都与基类函数相同；
* 通过`virtual`关键字来实现，父类函数是虚函数；
* 建议使用`override`关键字来显式标记覆盖基类的虚函数。

## RAII机制

RAII（**R**esource **A**cquisition **I**s **I**nitialization）资源获取即初始化，是C++管理资源，避免泄露的方法。使用局部对象来管理资源，在构造函数中初始化资源，在析构函数中销毁资源。智能指针使用的就是RAII思想，因为智能指针本质上是栈对象，在离开作用域时会释放它所管理的对象。

## 哈希表扩容原理

哈希算法：根据设定的哈希函数将一组关键字映射到一个有限的地址区间上的算法，一般用于快速查找。

装载因子：表示哈希表的装满程度。

装载因子 = 元素个数 / 哈希表长度

当哈希表的装载大于默认的装载因子时（一般默认0.75），哈希冲突一般比较严重，其查找性能也随之降低，就需要扩容。

扩容方案：

每次扩容时，哈希表的容量增加为原先的两倍，新建一个新的哈希表，并将原有的所有元素重新插入到新的哈希表中，在重新插入时，会使用新的哈希函数计算元素的哈希值。

### 解决哈希冲突

#### 开放定址法

在遇到哈希冲突时，找一个新的空闲的哈希地址。

* 线性探测法：当某个位置产生哈希冲突时，从产生冲突的下一个位置起查找空闲位置；
* 平方探测法：用冲突单元加上1的平方、2的平方去探测空闲位置。

#### 链地址法

将产生冲突的元素用链表组织起来，将链表的头结点放在对应的哈希单元。

#### 再哈希法

同时构造多个不同的哈希函数，当H1产生冲突时，再用H2计算，直到冲突不再产生。增加了计算量。

#### 建立公共溢出区

将哈希表分为公共表和溢出表，将发生冲突的都存放在溢出表。

#### 

拷贝构造函数使用值传递会造成无限递归。

## vector扩容

扩容时机：当`size`大于`capacity`时，会发生扩容。

扩容时重新分配更大的内存，将旧数据拷贝到新内存中，释放旧的内存。

vs以1.5倍扩容，GCC以2倍扩容。使用1.5倍扩容在多次扩容后，可以复用之前释放的空间。

`vector`中维护了三个指针，一个指向首元素地址，一个指向最后一个元素的下一个地址，一个指向分配的内存的末尾。

## 对vector频繁调用push_back的影响

对vector频繁调用`push_back`会导致存储空间的重新分配，重新分配更大的内存，再将原有数据拷贝到新的空间中，再释放原有内存，引起性能下降。

推荐使用`reserve`预先分配空间。

vector空间只增不减，可以使用`swap`来释放空间。

```c++
vector<int>().swap(vec);//清空vec内存
vector<int>(vec).swap(vec);//清空vec空内存
```

## 如何实现栈？

### 数组实现

使用一个固定长度的数组，然后用一个计数器`count`记录栈顶，栈为空时计数器为-1；

入栈：将`count`+1，然后将元素放入`count`处，注意判断数组是否已满；

出栈：将`count`-1，需判断栈是否为空；

返回栈顶元素：返回`nums[count]`，需判断栈是否为空。

栈满后可以使用`realloc`扩容。

### 链表实现

创建栈：声明一个头指针，指向栈顶，初始时栈顶为空；

入栈：创建一个节点，插入到头指针后面；

出栈：将头指针指向下下个节点。

访问栈顶元素：返回头节点的下个节点即可。

## 如何实现队列？

### 数组实现

使用两个计数器记录队头和队尾，入队时队尾指针后移，出队时队头指针后移，尾指针移动到末尾后可以利用队头前面的空闲空间。

### 链表实现

创建一个头结点，指向队头，记录队尾指针，入队时直接在队尾加节点，更新队尾节点，出队时删除队头节点。

## 红黑树

红黑树是一种自平衡的二叉搜索树，可以在O（logn）时间内完成查找、插入、删除操作。它在每个节点增加了一个存储位记录节点的颜色，通过从根节点到叶子节点简单路径上颜色的约束，**红黑树保证最长路径不超过最短路径的两倍**，因而近似平衡。

为什么要有红黑树？

二叉搜索树在极端情况下，只有一侧有节点，此时二叉树退化为链表，操作时间复杂度变为O（n)，于是出现了红黑树。

红黑树的性质：

* 每个节点或是黑色，或是红色；
* 根节点是黑色；
* 每个叶子节点是黑色（指为空的叶子节点）；
* 红色节点的子节点和父节点都是黑色；
* 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点；

红黑树的操作：

1. 旋转：左旋，右旋
2. 插入，插入新节点时，这个节点是红色，可能会出现两个连续的红色节点，因此需要调整。如果插入的是根节点，则将节点设为黑色。

## sort的底层原理

`vector`和`deque`适用排序算法。

`sort`结合了快速排序、插入排序和堆排序三种排序。

* 针对大的数据量，首先使用快排，递归排序；
* 当递归深度超过阈值时，改用堆排序；
* 当数据规模小于阈值时，改用插入排序。

## C++异常处理

### 异常的基本思想：

让一个函数在发现了自己无法处理的错误时，抛出一个异常，然后它的调用者能够处理这个问题。将**问题检测和问题处理相分离**。

一方面，一个库的作者可以检测发生了运行时错误，但一般不知道怎么去处理，因为和用户的具体应用有关；另一方面，库的使用者知道怎样处理这些错误，但无法检测它们何时发生。

* `throw`：抛出异常，抛出异常后，程序控制权转移到与之匹配的`catch`模块；
* `catch`：在想要处理问题的地方，用`catch`捕获异常；
* `try`：`try`块中放置可能抛出异常的代码，`try`中的代码称为保护代码，后面通常跟一个或多个`catch`语句。
* 栈展开：当抛出一个异常后，程序会暂停当前函数的执行过程，并开始寻找与之匹配的`catch`模块，如果找不到，则退出函数，在调用当前函数的外层函数中继续寻找。沿着嵌套函数的调用链不断查找，此过程即栈展开过程。如果找不到，程序就会被终止。

`throw`抛出的异常类型与`catch`捕获的异常类型要一致。

`catch(...)`表示捕获任意类型的异常。

### c语言的错误处理方式

* 使用整型返回值标识错误；
* 使用errno宏（全局整型变量）来记录错误；

缺点：

* 不一致问题，有的返回1表示成功，有的0表示成功；
* 函数返回值只有一个，返回错误码就无法返回别的信息。

### 异常的优点

* 不可忽略。函数返回值可以忽略，程序员可能会忘记编写错误判断代码，但异常如果不被捕获，程序就会终止，这会促使开发出来的程序更健壮；
* 返回值没有语义信息，但异常可以包含语义信息；

### 异常的缺点

* 性能问题；
* 内存回收问题，在释放内存之前发生了异常。

### noexcept关键字

跟在函数参数列表后面，表示这个函数不会抛出异常。

## C++如何排查内存泄露？

C++内存泄漏原因：

* 申请了内存没有释放，`new/delete`和`malloc/free`没有成对使用；
* 父类析构没有设置为虚函数，导致持有动态内存的子类发生内存泄漏；

排查内存泄漏：

* 检查代码，看`new/delete`是否成对出现，或者程序是否在`delete`之前就`return `了；
* 检查父类析构是不是虚函数；
* 使用内存检查工具。`valgrind`。

防止内存泄露方法：

* 使用智能指针

# STL六大组件

## allocator

`allocator`是一个模板类，位于`<memory>`头文件中，提供了一种统一接口，用于在STL中进行动态内存的分配和释放。

主要通过两个成员函数来分配和释放内存：`allocate`和`deallocate`;

此外，还提供构造和析构对象的功能，`construct()`函数用于在已分配的内存上构造对象，`destroy()`函数用于销毁对象。

功能：

* 分配内存
* 构造对象
* 析构对象
* 释放内存

将内存分配和对象构造分离开来，使用了`placement new`技术，`placement new`技术实际上就是将一个对象构造在指定的内存区域中,这个内存区域可以是在堆上，也可以是在栈上。

STL采用了两级配置器，一级配置器主要考虑大块内存（大于128字节），使用`malloc`和`free`来实现；二级配置器主要为小块内存而设计，为了解决内存碎片问题，采用链表来维护内存池。

## Adapter

适配器在STL中扮演着**转换器**的角色，用于**将一种接口转换为另一种接口**。

根据目标接口的类型，可以分为三类：

* 容器适配器，改变容器的接口；
* 迭代器适配器，改变迭代器的接口；
* 仿函数适配器，改变仿函数的接口。

### 容器适配器

容器适配器有三种，栈（stack），队列（queue）和优先队列（priority_queue）,都是在deque基础上封装的。

## Iterator

提供了一个统一的遍历容器元素的接口，而不用管容器的内部结构。

迭代器失效：对于序列式容器，删除和插入元素会使元素之后的迭代器都失效。

# 大数据的排序方法

1. 100G数据，只有100M内存，怎么排序？

* 将数据拆分存入多个小文件，每个小文件分别排序；
* 多路归并，写入最终文件。

2. topN问题，求100G数据中前100大的数？

* 小根堆，维护100个数。

3. 10G数据，数据范围在1-1000，怎么排序？

* 桶排序思想，扫描一遍数据，将数据存入100个有序编号的小文件中，1-10在第一个文件，11-20在第二个文件...以此类推；
* 对每个小文件快速排序，之后有序读取每个小文件即可。

[(213条消息) 使用小内存处理海量数据问题(个人总结)_小内存比较两个大文件_hellosrc | remake的博客-CSDN博客](https://blog.csdn.net/weixin_46141936/article/details/121126244?spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-3-121126244-blog-101351437.235^v38^pc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-3-121126244-blog-101351437.235^v38^pc_relevant_default_base3&utm_relevant_index=4)

