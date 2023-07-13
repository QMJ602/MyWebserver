# 常规操作

## 注意事项

1. 在类中定义`vector<>`并指定其大小时

```c++
//这样定义会报错，因为无法区分这是成员函数还是成员变量的定义
vector<int> vec(2, 1);
vector<int> vec(2);
//正确方法
vector<int> vec = vector<int>(2, 1);
vector<int> vec{1, 1};
```

2. 对于`unordered_map`如果表中原本不存在`x`，只要执行了索引操作`mp[x]`，就会新建`x`项，`mp.size()`就会+1.

## 随机数

```c
int rand();//返回0~RAND_MAX(32767)的整数
void srand(unsigned int seed);//用来设置rand()的随机种子
time(NULL);//返回1970.1.1至今经历的时间，以秒为单位<time.h>
```

将`time(NULL)`作为`srand`的参数算种子，再用`rand()`产生随机数

```c
srand(time(NULL));
rand();
```

## 求组合数

直接求取可能会越界，利用下面公式递推：
$$
C^{j}_i=C^{j}_{i-1}+C^{j-1}_{i-1}
$$

## 位运算的优先级低于==和!=

先位运算再判断相等与否时，位运算要加括号。

6169.最长优雅子数组

## 数据范围内的极值

```c++
INT_MAX  //有符号整型最大值
INT_MIN  //有符号整型最小值
```

## 合并`vector`

```cpp
vector<int> a{1, 2, 3};
vector<int> b(3,0);
a.insert(a.end(), b.begin(), b.end());
```

## **取绝对值**

```c
#include<stdlib.h>
abs(int x);//整数
fabs(float x);//浮点
```

## iota()

用于给容器批量递增赋值

```c++
#include<numeric>
vector<int> a;
a.resize(26);
iota(a.begin(), a.end(), 0);
//a 的值为 0，1，2，3，...,25
```

## atoi()

```c
int atoi(const char *str);//把str所指向的字符串转化为一个整数
```

## vector删除尾部元素

```c++
vector<int> vc(2, 1);
string s(2, a);
s.pop_back();
vc.pop_back();
```

* 对于二维的`vector`的`sort()`排序，默认按照第二维的第一个元素升序排序。
  
    如c
  
  ```c++
  vector<vector<int>> a({{1,2}, {3,2}});
  sort(a.begin(), a.end());//默认按照 1，3顺序排序，也可以写lambda表达式来指定排序策略
  sort(a.begin(), a.end(), [](vector<int> x1, vector<int> x2){return x1[0]<x2[0];});
  ```
## 字符串分割

`string substr ( size_t pos = 0, size_t n = npos ) const;`

* `emplace_back()`向容器尾部插入元素，作用等同于`push_back()`但比`push_back()`高效。

## 数据转换

**string 转 int**

```c++
int stoi(string s);
```

**int 转 string**

```c++
string to_string(int val);
```

**char*转int**

```c++
int atoi(char* s);
```

**char*转string**

```c++
char* a = "abc";
string s(a);//构造初始化
string s = a;//直接赋值
```

**string转char***

```c++
const char* c_str();
string s("abdc");
char a[10];
strcpy(a, s.c_str());//a是一个临时指针，不能对其操作，要使用strcpy()
```

判断是否大写字母或小写字母

```c
int isupper(char c);  // A~Z
int islower(char c);  // a~z
char tolower(char c); //大写变小写
char toupper(char c); //小写变大写
```

判断字符是否是数字

```c++
int isdigit(char c);
```

# 约瑟夫环（leetcode 1823）

设有n个元素，每次删除第k个元素，则最终留下的元素为获胜者为$f(n,k)$,当只有一个元素时，$f(1,k)$即为1。

![](C:\Users\qmj\OneDrive\图片\ysfh.jpg)

假设当前n为5，k为3，则如表（1）所示，第一次删除后，会删除3，下次删除将从4开始，即为表（2）的情况。

考虑$f(4,3)$,即为从表（3）开始删除，对比表（2）和表（3）可以发现，此时的$f(5,3)$和$f(4,3)$留下的胜出者在表中的位置一定是相同的，只是那个位置的数字不同。因此我们需要找出表（2）和表（3）中相同位置处数字的关系。

$f(5,3)$的第二次删除是从编号为k的元素的下一个元素开始，即第二次删除时起点为k+1,所以表（2）和（3）中位置为第i个位置处的数字关系为

num2 = num3 + k      num3 + k < = n

num2 = (num3 + k) % n   num3 + k > n

可以用一个公式表示为：

num3 = (num2 + k - 1) % n + 1  

那么不管$f(5,3)$和$f(4,3)$最终留下来的是哪个位置的元素，它们都满足关系：

f(5,3) = (f(4,3)+k-1) % n+1

* 不要将有符号数和无符号数比大小，比如`int`型和`vector.size()`比大小。
* 深度优先遍历（递归）841
* 广度优先遍历（队列）841

# 前缀树/字典树

非典型的多叉树模型——一次建树，多次查询

应用场景：字符串前缀问题

![](https://gitee.com/qin_minjie/imagebed/raw/master/images/image-20220919155958952.png)

结点：

```c++
struct TrieNode{
	bool isEnd;//该结点是否是一个串的结束
    vector<TrieNode*> next(26);//字母映射表   保存了当前结点下一个字符的连接   如果next[0]存在，则说明下一个字符有a
}
```

https://leetcode.cn/problems/implement-trie-prefix-tree/solution/trie-tree-de-shi-xian-gua-he-chu-xue-zhe-by-huwt/

208.实现Trie

2416.字符串的前缀分数和

648.单词替换

677.键值映射

211.添加与搜索单词

# 堆

* 大根堆：每个节点的值都大于或等于其子节点的值，在堆排序中用于升序排列。

* 小根堆：每个节点的值都小于等于其子节点的值，在堆排序中用于降序排列。

**堆排序平均时间复杂度为O（nlogn)**

堆排序是不稳定排序

## 堆怎么实现？

堆是一颗完全二叉树，可以用数组来实现。在插入数据时，根据相应的规则来进行调整。

大根堆：每个节点的值都小于它的父节点的值。

## priority_queue

`priority_queue`定义了一个元素有序排列的队列，队列头部的元素优先级最高，底层以堆实现。

`priority_queue`的定义如下：

```c++
template <typename T, typename Container=std::vector, typename Compare=std::less<T>>
class priority_queue    //存储对象的类型， 存储元素的底层容器， 函数指针类型  默认为less<T>,即最大的元素排在最前面
```

```c++
priority_queue<int, vector<int>, greater<int>> q;//小根堆
priority_queue<int, vector<int>, less<int>> q;//大根堆（默认）
```

[(165条消息) c++优先队列priority_queue（自定义比较函数）_菊头蝙蝠的博客-CSDN博客_c++优先队列自定义比较](https://blog.csdn.net/qq_21539375/article/details/122128445)

问题：发现`priority_queue<type, container, compare>`中，不能传具体的函数指针。

这里compare传入的应该是函数指针的类型，而不是具体的函数指针:

```c++
//假设自定义了比较函数
bool cmp(int a, int b)
{
    return a > b;
}
//创建优先队列
priority_queue<int, vector<int>, decltype(&cmp)> q(cmp);//自动推断函数类型
priority_queue<int, vector<int>, cmp> q;//这种写法是错的
```

`priority_queue`的操作：

`push()`：插入元素，内部自动排序

`emplace()`：调用传入参数的构造函数插入元素，内部自动排序

`top()`：返回优先级最高的元素的引用

`pop()`：移除优先级最高的元素

`size()`：返回队列中元素个数

`empty()`：判断队列是否为空

## 题目

23.合并k个有序链表

# KMP算法

字符串匹配算法

库函数：

```c
 //查找needle第一次出现位置，返回该位置指针，不存在时返回null
char *strstr(const char *haystack, const char *needle);
//查找str第一次出现位置,从pos开始查找
int find(const string& str, int pos = 0) const;
```

文本串长度`n`，模式串长度`m`：

* 暴力解法时间复杂度`O(nm)`

* KMP时间复杂度`O(n+m)`：匹配过程`O(n)`，生成`pmt`数组`O(m)`

**前缀表pmt**：记录下标`i`（包括`i`）之前的字符串中，有多大长度的相同前缀后缀。(前缀不包含最后一个元素，后缀不包含第一个元素)

[算法学习笔记(13): KMP算法 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/105629613)

求pmt代码

模式串错一位进行自我匹配，相当于用前缀匹配后缀。

```c++
//pmt[0] = 0;
for(int i = 1, j = 0; i < plen; ++i)
{
	while(j && p[i] != p[j]) j = pmt[j-1];//匹配不成功，回退j
    if(p[i] == p[j]) j++;
    pmt[i] = j;
}
```

得到pmt数组后匹配代码：

```c++
for(int i=0, j=0; i < s.length(); ++i)
{
    while(j && s[i] != p[j]) j = pmt[j-1];//匹配不成功，回退j
    if(s[i] == p[j]) j++;
    if(j == p.length())//匹配成功
    {
        j = pmt[j-1];//回退j，继续后面的匹配
  		index = i - j + 1;//子串在目标串中的位置
    }
}
```

28. 找出字符串中第一个匹配项的下标

# 栈

394.字符串解码

栈的基本套路：遇到左括号和其它字符入栈，遇到右括号，出栈到左括号，处理，处理结果入栈，重复上述过程。

用栈实现队列：

维护入栈和出栈，新加入的元素放进入栈，弹出元素时从出栈弹出，当出栈为空时，将入栈元素全部放进出栈中。

用队列实现栈：

新加入元素直接push，并记录队尾元素即为栈top元素，当需要pop时，出队元素重新入队，直到弹出队尾元素。

71.简化路径

# 数组

在C++中，二维数组在地址上是连续的.

240.搜索二维矩阵Ⅱ

## 二分查找

### STL二分查找接口

```c++
bool binary_search(iterator beg, iterator end, value);//二分指定元素是否存在
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val);//在[first, last)内二分查找不小于val的第一个数，返回其迭代器。
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last,//二分查找指定范围内大于val的第一个数
                             const T& val);

pair<ForwardIterator,ForwardIterator> equal_range (ForwardIterator first, ForwardIterator last, const T& val);//二分查找指定范围内等于val的数.     查找成功时，第 1 个迭代器指向的是 [first, last) 区域中第一个等于 val 的元素；第 2 个迭代器指向的是 [first, last) 区域中第一个大于 val 的元素。
```

时间复杂度：`Olog(n)`

使用二分法的前提条件：

* 有序数组
* 数组中元素不重复（否则用二分法查到的目标值下标可能是不唯一的）

704.二分查找

注意搜索区间的概念，如果定义搜索区间`[left, right]`为左闭右闭区间，那么循环条件应该为`while(left<=right)`,因为`left==right`时是有意义的，同时区间的更新应为`left=mid+1`和`right=mid-1`

因为mid已被搜索过。

如果定义搜索区间`[left, right)`为左闭右开区间，那么循环条件应该为`while(left<right)`,因为`left==right`时是无意义的，同时区间的更新应为`left=mid+1`和`right=mid`，因为右侧是开区间，所以右侧边界右侧边界将不会被搜索，所以赋值为`mid`

```c++
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while(left <= right)//左右闭区间
        {
            int mid = (right - left)/2 + left;//防止溢出，等同于（right+left)/2
            if(nums[mid] == target)
            {
                return mid;
            }
            else if(nums[mid] > target)
            {
                right = mid - 1;
            }
            else 
            {
                left = mid + 1;
            }
        }
        return -1;
    }
```

35.搜索插入位置

34.在排序数组中查找元素的第一个和最后一个位置

二分查找处理含重复元素的有序数组的情况：

```c++
if(nums[mid] >= target)//如果判断条件是这样，则最后找到的是目标元素第一次出现的位置
{
	right = mid - 1;
}
else
{
	left = mid + 1;
}
//***********************************************
if(nums[mid] <= target)//如果判断条件是这样，则最后找到的是目标元素最后一次出现的位置
{
	left = mid + 1;
}
else
{
	right = mid - 1;
}
```

**注意循环结束后left和right可能会超出数组下下标范围**

旋转数组33. 81.

`mid`左右必有一边是有序数组，如果`target`在有序的那一边范围内，就对有序的一边二分查找，否则在无序的那一边继续寻找含有`target`的有序数组

如何判断`mid`的左右哪段是有序数组？

当`nums[mid] > nums[0]`时，`mid`左边必是有序数组，否则，`mid`右边是有序数组。

## 前缀和

对于数组`nums`，新建一个数组`prefix`,用`prefix[i]`记录`nums[0]...nums[i-1]`之和。

**前缀和技巧适用于快速、频繁地计算一个索引区间内的元素之和。**

303.区域和检索

304.二维区域和检索——二维前缀和

## 差分数组

**差分数组适用于频繁对原始数组的某个区间元素进行增减。**

对`nums`数组构造一个`diff`差分数组，`diff[i]`表示`nums[i]`和`nums[i-1]`之差：

```c++
diff[0] = nums[0];
for(int i=1;i<nums.size();++i)
{
	diff[i] = nums[i] - nums[i-1];
}
```

那么可以由`diff`反推`nums`数组：

```c
nums[0] = diff[0];
for(int i=1;i<nums.size();++i)
{
	nums[i] = nums[i-1] + diff[i];
}
```

假如给`nums`数组`i~j`区间元素都加3，那么只需要给`diff[i]+3`和`diff[j+1]-3`即可。

1109.航班预定统计

1094.拼车

## 二维矩阵遍历技巧

矩阵顺时针旋转90°：先以主对角线为中心反转，再将每一行反转。

矩阵逆时针旋转90°：先以副对角线为中心反转，再将每一行反转。

48.旋转图像

**螺旋遍历**

确定上下左右边界，边界随着遍历更新。

54.螺旋矩阵  59.螺旋矩阵Ⅱ

# 带权重的随机选择算法

528.按权重随机选择  看到权重应想到前缀和

前缀和+二分查找

# 双指针

27.移除元素

定义快慢指针，快指针负责查找不需要移除的元素，慢指针负责逐个更新数组元素

26.删除有序数组中的重复项

快指针负责遍历，遇到与慢指针不同的，就把慢指针加1，快指针值赋给慢指针

83.删除排序链表的重复元素

977.有序数组的平方

167.两数之和Ⅱ  —— **当数组有序时就应当考虑是否可以用双指针**

344.反转字符串

11.盛水最多的容器

双指针指向两端的柱子，假设左边柱子比右边短，那么左指针需要向右移动。因为此时右边任意一条柱子与左柱构成的容器容积一定小于当前容积。左柱子限制了最大高度，右指针左移只会减小宽度，所以左边柱子就可以被淘汰了。

## 滑动窗口

参考*labuladong*

多用于解决子串问题

* 右边界什么时候扩张 （窗口内子串不满足要求时扩张）

* 左边界什么时候收缩（窗口内子串满足要求时收缩）

209.长度最小的子数组

904.水果成篮

76.最小覆盖子串

567.字符串的排列

438.找到字符串中所有字符异位词

3.无重复字符的最长子串

1004.最大连续1的个数

424.替换后的最长重复字符（不太常见的滑动窗形式，不需要收缩窗口大小）

## Rabin-Karp字符匹配算法

核心思想：用数字表示字符串，借助滑动窗口与哈希来匹配

比如ASCII 0~255码表示的256个符号就可以用数字0~255来表示，一个长度为L的ASCII字符串就可以等价为一个L位的256进制数字，将这个数字存入哈希表，每次移动窗口，计算对应数字，与哈希表比较即可完成匹配。

假设有十进制数字8632，给末尾添加数字3：

```c
int number = 8632;
number = number * 10 + 3;
```

去掉第一位数字8：

```c
number = number - 8 * pow(10, 3);
```

由此可以推导出L位R进制数的处理：

```c++
number = number * R + 3;//末尾添加
number = number - 8 * pow(R, L-1);//去除头部
```

问题：`number`可能太大会溢出，采用取余运算。取余运算又会带来新的问题，即不同的数字的取余结果相同，产生了冲突。解决办法是在匹配到哈希值时，再暴力匹配哈希值对应的字符串和当前是否相同。

取余运算律：

```c++
X % Q == (X + Q) % Q;
(X + Y) % Q = (X % Q + Y % Q) % Q;
```

187.重复的DNA序列

28.实现strstr()

# 常数时间查找，删除，和随机访问元素

1、用数组存储元素，保证随机访问时间复杂度为O(1)

2、用哈希表存储元素和元素下标，保证查找和删除复杂度为O(1)

3、删除数组中元素时，先根据哈希表得知元素在数组中的下标，再把元素交换至数组尾部，然后`pop_back()`，时间复杂度也是O(1)

380. O(1)时间查找插入和返回随机元素

710. 黑名单中的随机数

030.剑指offer

# 链表

> **什么时候需要用到虚拟头节点？**
>
> 当需要创建一个新链表时，可以用虚拟头节点简化边界处理。

86.分隔链表

23.合并k个有序链表——使用堆排序每次从k个结点中找出最小的那一个结点。

## 单链表的倒数第k个节点

要求一次遍历找到链表的倒数第k个结点。

方法：

让一个指针`p1`指向链表的头节点，然后令`p1`走`k`步，此时再令一个指针`p2`指向链表的头节点，然后`p1`与`p2`一起走，当`p1`为空时，`p2`就走到了倒数第`k`个结点。

题目：

19. 删除链表的倒数第N个结点。——注意虚拟头结点的使用

## 反转链表

递归解法

206.反转链表

```c++
ListNode* reverseList(ListNode* head)
{
    if(!head || !head->next)
        return head;
    ListNode* last = reverseList(head->next);//反转以head->next开始的链表
    head->next->next = head;//把原来的head->next也就是反转后的末尾结点的下一个指向head
    head->next = nullptr;//head现在是末尾元素，下一个指向空
    return last;
}
```

92.反转链表Ⅱ  反转链表的第`left`到第`right`个结点

```c++
ListNode* successor;
ListNode* reverse(ListNode* head, int n)//反转链表的前n个结点
{
    if(n == 1)//递归到第n个结点了
    {
        successor = head->next;//记录下第n+1个结点
        return head;
    }
    ListNode* last = reverse(head->next, n-1);
    head->next->next = head;
    head->next = successor;//头节点最终指向第n+1个结点，（递归中间的头结点的指向会被外层递归覆盖，所以最后只有真正的头节点指向了第n+1个结点）
    return last;
}
ListNode* reverseBetween(ListNode* head, int left, int right)
{
    if(left == 1)//当递归到以left结点为开头的链表
    {
        return reverse(head, right);
    }
    head->next = reverseBetween(head->next, left-1, right-1);//对于以head->next开头的链表来说，是反转其第(left-1, right-1)结点，不断递归以下一个结点为头的链表。
    return head;
}
```

25. K个一组反转链表

递归思想

```c++
/** 反转区间 [a, b) 的元素，注意是左闭右开 */
ListNode reverse(ListNode a, ListNode b) {
    ListNode pre, cur, nxt;
    pre = null; cur = a; nxt = a;
    // while 终止的条件改一下就行了
    while (cur != b) {
        nxt = cur.next;
        cur.next = pre;
        pre = cur;
        cur = nxt;
    }
    // 返回反转后的头结点
    return pre;
}

ListNode reverseKGroup(ListNode head, int k) {
    if (head == null) return null;
    // 区间 [a, b) 包含 k 个待反转元素
    ListNode a, b;
    a = b = head;
    for (int i = 0; i < k; i++) {
        // 不足 k 个，不需要反转，base case
        if (b == null) return head;
        b = b.next;
    }
    // 反转前 k 个元素
    ListNode newHead = reverse(a, b);
    // 递归反转后续链表并连接起来
    a.next = reverseKGroup(b, k);
    return newHead;
}
```

## 快慢指针技巧

876.链表的中间结点

设置快慢指针，快指针每次走两步，慢指针每次走一步，当快指针走到头时，慢指针即在中间结点。

141.判断链表是否有环

160.相交链表

1、哈希表

2、双指针技巧，为了使p1和p2同时到达公共结点，可以让p1先遍历A，完了接着遍历B，让p2先遍历B，完了接着遍历A，最终两个指针会同时到达公共结点

# 后缀表达式

也称逆波兰式，不包含括号，运算符放在两个运算对象的后面，所有计算严格从左到右进行。

前缀表达式：也称波兰式，运算符处于两个操作数的前面。

## 后缀表达式计算

1. 创建栈，从左到右扫描表达式；
2. 遇到数字，压入栈中；遇到运算符则弹出栈顶两个元素，使用运算符进行运算，然后将结果压入栈中；
3. 重复步骤2直到扫描结束，最后弹出计算结果。

150.逆波兰表达式求值

## 中缀表达式转后缀表达式

1. 创建运算符栈`s1`和操作数数组`a2`，然后扫描中缀表达式；
2. 如果是操作数，直接放入数组`a2`;
3. 如果是运算符，栈`s1`为空或栈顶符号为左括号，或者优先级比栈顶运算符高，则入栈结束该步骤；否则将`s1`栈顶运算符弹出放入操作数数组`a2`,然后重复该步骤；
4. 如果是左括号，直接压入运算符栈`s1`，如果是右括号，依次弹出`s1`的运算符放入`a2`，直至遇到左括号结束，并将左右括号舍弃；
5. 循环步骤2-4直至扫描结束，并将`s1`剩余运算符依次弹出放入数组`a2`，数组`a2`就是后缀表达式；

# 二叉树

* 满二叉树：只有度为0的节点和度为2的节点，且度为0的节点在同一层，深度为k，则有2^k-1个节点。
* 完全二叉树：只有最底层节点可以不满，且最底层节点都连续集中在最左边。
* 二叉搜索树BST：左子树上所有节点的值均小于根节点的值，右子树上所有节点的值均大于根节点的值。
* 平衡二叉树AVL：是一棵空树或左右子树的高度差绝对值不大于1，并且左右子树也是平衡二叉树。

## 前中后序遍历

113.路径总和Ⅱ

```c++
void traverse(TreeNode* root)
{
	if(root == nullptr)
		return;
    //前序位置  在进入节点时
	traverse(root->left);
    //中序位置
	traverse(root->right);
    //后序位置  在离开结点时
}
```

链表与数组均可前后序遍历，例如链表的后序遍历，可以实现倒序打印：

```c++
void traverse(ListNode* head)
{
    if(head == nullptr)
        	return;
   	traverse(head->next);
    cout << head->val << endl;
    //后序位置
}
```

前序位置是自顶向下的，后序位置是自底向上的。

只有后序位置能够通过返回值获取左右子树的信息。如计算每个结点的左右子树各有多少个结点：

```c++
int count(TreeNode* root)
{
    if(root == nullptr)
        	return 0;
    int leftCount = count(root->left);
    int rightCount = count(root->right);
    return leftCount + rightCount + 1;
}
```

如果用前序遍历写出了递归套递归，那么可以考虑是否能用后序遍历进行优化。与子树相关的问题可以优先考虑后序位置。

543.二叉树的直径

111. 二叉树的最小深度

与求最大深度不同，深度计算的终点必须是叶子节点，即没有左右子节点。

### 两棵二叉树的递归遍历

输入参数分别是两棵树的根节点

**101.对称二叉树**

## 二叉树递归解法的两种思路

（1）遍历二叉树得到答案——对应回溯算法

​	116.填充每个结点的下一个右侧指针——递归方法

（2）分解成子问题得到答案——对应动态规划算法

​	114.二叉树展开为链表

## 层序遍历

515.在每个树行中找最大值

```c++
vector<int> largestValues(TreeNode* root) {//层序遍历
        vector<int> ret;
        if(root == nullptr)
        {
            return ret;
        }
        queue<TreeNode*> Q;
        Q.push(root);
        while(!Q.empty())
        {
            int num = Q.size();//可以记录每一层有多少个结点
            int level_max = INT_MIN;
            for(int i=0;i<num;++i)//遍历每一层，如果不需要区分 “层”，那么就不需要这个for循环
            {
                TreeNode* node = Q.front();
                Q.pop();
                level_max = max(level_max, node->val);
                if(node->left)
                {
                    Q.push(node->left);
                }
                if(node->right)
                {
                    Q.push(node->right);
                }
            }
            ret.emplace_back(level_max);
        }
        return ret;
    }
```

## 完美二叉树

所有叶子结点都在同一层，所有父节点都有左右子节点

## 二叉树构造

构造整棵树 = 根结点 + 构造左子树 + 构造右子树

654.最大二叉树

递归思路：找到数组中的最大值，构造为根节点，然后用最大值左边的数组再去构造二叉树，作为根节点的左子树；用最大值右边的数组再去构造二叉树，作为根节点的右子树

105.从前序与中序遍历构造二叉树

剑指 offer07. 重建二叉树

已知前序遍历数组`preorder`和中序遍历数组`inorder`

构造思路：找到根结点，划分出左子树的`preorder`和`inorder`与右子树的`preorder`和`inorder`，递归构造。

关键知识：一个树的前序遍历的第一个元素为根结点，中序遍历结果中根结点左边为左子树，右边为右子树。

![image-20220912112002492](https://gitee.com/qin_minjie/imagebed/raw/master/images/image-20220912112002492.png)

（1）`preorder[0]`即为根结点，其结点在数组的分布为  根 ——左子树 ——右子树

（2）根据`preorder[0]`在`inorder`中找出根结点，则根结点左侧为左子树，右侧为右子树     其结点在数组分布为  左子树 ——根 ——右子树

（3）由2可以得知左右子树的结点数目，由此可以推算出`preorder`中左子树和右子树元素的范围。

（4）至此可以分别得到左右子树的`preorder`和`inorder`的数据范围，进行递归构造。

106.从中序遍历与后序遍历构造二叉树

构造思路：找到根结点，划分出左子树的`postorder`和`inorder`与右子树的`postorder`和`inorder`，递归构造。

关键知识：一个树的后序遍历的最后一个元素为根结点，中序遍历结果中根结点左边为左子树，右边为右子树。

后序遍历数组中结点分布： 左子树——右子树——根结点

（1）由后序遍历结果找到根结点

（2）根据根结点在中序遍历数组中的位置确定左右子树结点数目，并产生左右子树的`inorder`

（3）根据左右子树结点数目得到后序遍历数组中左右子树元素范围，产生左右子树的`postorder`

889.根据前序和后序遍历构造二叉树

（1）利用`preorder`第二个元素作为左子树根节点，在`postorder`中找到该结点，其左侧即为左子树元素

![img](https://labuladong.gitee.io/algo/images/%e4%ba%8c%e5%8f%89%e6%a0%91%e7%b3%bb%e5%88%972/8.jpeg)

## 二叉树序列化

297.二叉树的序列化与反序列化

可以用前序遍历生成序列化字符串，再利用这字符串前序递归构造二叉树。因为字符串记录了空指针信息，因此，只用一个前序遍历字符串就可以构造出二叉树。

前序遍历序列化字符串构造二叉树：正常前序遍历，遇到空标识返回即可。

```c++
    TreeNode* construct(string& s, int& index)
    {
        if(index >= s.length()) 
        {
            return nullptr;
        }
        if(s[index] == 'n')//空标识
        {
            index++;
            return nullptr;
        }
        string cur;
        while(s[index] != '&')//分隔符
        {
            cur.push_back(s[index]);
            index++;
        }
        index++;
        TreeNode* root = new TreeNode(stoi(cur));
        root->left = construct(s, index);
        root->right = construct(s, index);
        return root;
    }
```

652.寻找重复的子树

利用后序位置把每棵树的序列化结果都存进哈希表中，判断重复即可。

## 二叉搜索树

二叉搜索树BST：

* 对于BST中的每一个结点，其左子树的值小于该结点的值，右子树的值大于该结点的值，且其左子树和右子树也是BST。
* 二叉搜索树的中序遍历结果是升序。

230.二叉搜索树中第k小的元素

BST中查找第k小的元素

常规思路：中序遍历，到第k个停止。最坏时间复杂度O(N)

改进思路：在二叉树结点中维护额外信息——以当前结点为根的二叉树有多少个结点

```c++
class TreeNode {
    int val;
    // 以该节点为根的树的节点总数
    int size;
    TreeNode left;
    TreeNode right;
}
```

这样当前结点的排名就可以通过`node->left->size`得到，通过与k比较，去选择查找左子树还是右子树。时间复杂度为O(logN)

538.把二叉搜索树转换为累加树——反序中序遍历

**98.验证二叉树**

方法一：中序遍历二叉树，每次记录遍历的值，判断当前值是否大于上一个值，如果都大于，说明是升序。

方法二：利用BST左子树所有节点小于根节点，右子树所有节点大于根节点，限定当前二叉树的数值上下界`(lower, upper)`,当访问当前结点的左子树时，`upper=root->val`,访问右子树时，`lower=root->val`。

### BST增删改

框架

```c++
void BST(TreeNode* root, int target)
{
    if(root->val == target)
      //找到目标，执行操作
    if(root->val < target)
        BST(root->right, target);
    if(root->val > target)
        BST(root->left, target);
}
```

701.二叉搜索树中的插入操作

#### 删除结点

* 当目标结点没有左右子树时，直接删除即可
* 当目标结点只有一个子树，则用其子树代替该结点
* 当目标结点有左右子树时，用左子树中最大的结点或右子树中最小的结点来代替当前结点，并删除左子树中最大的结点或右子树中最小的结点

```c++
    TreeNode* getMin(TreeNode* root)
    {
        if(root->left)
            return getMin(root->left);
        else
            return root;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr)
            return nullptr;
        if(root->val == key)//找到目标结点
        {
            if(root->left == nullptr)//左子树为空。返回右子树
                return root->right;
            if(root->right == nullptr)//右子树为空，返回左子树
                return root->left;
            //左右子树都不为空，找到右子树最小结点
            TreeNode* minNode = getMin(root->right);
            //在右子树中删除这个最小结点
            root->right = deleteNode(root->right, minNode->val);
            //用该结点替换root
            minNode->left = root->left;
            minNode->right = root->right;
            root = minNode;
            return root;
        }
        if(root->val > key)
        {
            root->left = deleteNode(root->left, key);
        }
        if(root->val < key)
        {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
```

450.删除二叉搜索树中的结点

### 计算BST的种类数

涉及二叉搜索树种类数时，应能想到以不同的值作为根节点去计算种类数。利用BST中序递增的性质，确定了根节点，就可以确定根节点左侧有多少个结点，右侧有多少个结点。

96.不同的二叉搜索树

动态规划解法：题目给定结点值实际为升序排列，考虑以`dp(n+1)`数组存储不同结点数的二叉搜索树种类数。分别以每个值作为根结点，则其左子树结点数和右子树结点数可知，根据左右子树结点数目可分别在`dp`中查到左子树有多少种，右子树有多少种，那么以当前结点为根的BST种类数即为左右子树种类数乘积。

递归解法：

```c++
int count(int lo, int hi)//计算lo~hi区间的BST种数
{
	if(lo > hi)
        return 1;
    int res = 0;
    for(int i=lo;i<=hi;++i)
    {//以i作为根节点
        int left = count(lo, i-1);
        int right = count(i+1, hi);
        res += left * right;
    }
    return res;
}
```

### 构造不同种类的二叉搜索树

95.不同的二叉搜索树Ⅱ

## 扁平化嵌套列表迭代器

341.扁平化嵌套列表迭代器

解法1：深度优先遍历将元素存进vector，然后依次返回。

解法2：深度优先遍历，并用栈来维护当前的迭代器，调用`next`时返回迭代器指向元素，形成惰性访问。

## 二叉树最近公共祖先

236.二叉树的最近公共祖先

## 完全二叉树、满二叉树

完全二叉树：编号连续，与同深度满二叉树对应位置编号相同。即只有最后一层可以不满，且每一层都是紧凑靠左排列。

具有$n$个结点的完全二叉树的深度为$\lfloor{log_2n}\rfloor+1$（$\lfloor{x}\rfloor$表示不大于$x$的最大整数）

![complete](https://gitee.com/qin_minjie/imagebed/raw/master/images/complete.png)



满二叉树：每层都是满的，叶子结点只能出现在最下一层。

![perfect](https://gitee.com/qin_minjie/imagebed/raw/master/images/perfect.png)

深度为$k$的二叉树至多有$2^{k}-1$个结点，即深度为$k$的满二叉树有$2^{k}-1$个结点。

222. 完全二叉树的结点个数

# 归并排序

归并排序采用分治法，为稳定排序算法，一般用于总体无序，但各子项相对有序的数列。

时间复杂度O(nlogn)

代码框架

```c++
//类似于二叉树的后序位置
void sort(vector<int>& nums, int lo, int hi)
{
    if(lo==hi)
    {
        return;
    }
    int mid = (lo + hi) / 2;
    sort(nums, lo, mid);//排序左半边
    sort(nums, mid+1, hi);//排序右半边
    merge(nums, lo, mid, hi);//合并两个排序后的半边。合并思路类似于合并两个有序链表
}
```

912.排序数组

## 逆序对问题

**核心思路：**利用归并排序框架，在**合并左右两个有序数组**时，当`nums[i] <= nums[j]`时，从`mid+1~j-1`的元素均小于`nums[i]`，且在`nums`中的位置均在`i`后面，所以从`mid+1~j-1`的元素与`nums[i]`构成了逆序对。同理，当右边的有序数组已经用完，而左侧还未用完时，当前的`nums[i]`大于右侧数组的所有元素，与右侧数组的所有元素构成了逆序对。

其中合并代码：

```c++
void merge(vector<int>& nums, int lo, int mid, int hi)//合并lo~mid  和 mid+1~hi两个有序数组,合并结果先放入temp，然后导入nums
{
	int i = lo, j = hi;
    for(int k=lo;k<=hi;++k)
    {
       if(i == mid+1)
            {
                temp[k] = nums[j++];
            }
            else if(j == hi+1)
            {
                count += hi - mid;//mid+1~hi的所有元素都小于当前的i元素，构成逆序对
                temp[k] = nums[i++];
            }
            else if(nums[i] <= nums[j])//mid+1~j-1的元素值在nums中的位置都在i元素的后面，且都小于i的元素值，与i元素形成了逆序对
            {
                temp[k] = nums[i++];
                count += j - mid - 1;
            }
            else
            {
                temp[k] = nums[j++];
            }
    }
    for(int i=lo;i<=hi;++i)
    {
        nums[i] = temp[i];
    } 
    
}
```

剑指offer 51.数组中的逆序对

315.计算右侧小于当前元素的个数

493. 翻转对

# 快速排序

快速排序理想情况下**时间复杂度是O(NlogN),空间复杂度O(logN)**

极端情况下最坏时间复杂度O(N^2),空间复杂度O(N)（空间复杂度代表递归调用的层级）

快速排序是不稳定排序，对于序列中相同的元素，排序后它们的相对位置可能发生改变。

思想：先确定一个元素在有序数组中的位置（大于它的放左边，小于它的放右边），再递归处理该元素左半边元素和右半边元素。

快排的过程就是构造二叉搜索树的过程。

快排基准元素的选择：

* 固定基准选择，每次选取第一个元素做基准
* 随机基准选择，随机选取一个元素做基准
* 三数取中法，选取数组开头、中间、结尾三个数中的中间值作为基准元素。

核心框架：

```c++
void quickSort(vector<int>& nums, int lo, int hi)
{
    if(lo >= hi)
        return;
    int p = partition(nums, lo, hi);//分割函数，将基准元素排序，并返回基准元素在有序数组中的位置
    quickSort(nums, lo, p-1);//排序左半边
    quickSort(nums, p+1, hi);//排序右半边
}
```

`partition`函数：

```c++
//partition函数目的为：随机选取一个元素作为基准元素，将数组中大于该元素的放到左边，小于该元素的放到右边，并返回排序后该元素的下标。
int partition(vector<int>& nums, int lo, int hi)
{
    int p_index = rand()%(hi-lo+1) + lo;//随机取得基准元素
    swap(nums[p_index], nums[lo]);//把基准元素交换到头部
    int p_value = nums[lo];
    int i = lo+1, j = hi;//从两头开始，当i遇到大于p_value元素时停下，j遇到小于p_value元素时停下，交换i,j元素，直到i>j,类似于双指针
    while(i <= j)
    {
        while(i <= hi && nums[i] < p_value)//当i停下时，i的左侧都小于p_value
        {
            i++;
        }
        while(j > lo && nums[j] >= p_value)//当j停下时，nums[j] < p_value,j的右侧都大于等于p_value
        {
            j--;
        }
        if(i >= j)
        {
            break;
        }
        swap(nums[i], nums[j]);//i<j时交换
	}
    swap(nums[j], nums[lo]);//把基准元素换到最终的j处，j的右侧必然大于等于p_value
    return j;
}
```

另一种`partition`函数的写法：

参考：[912. 排序数组 - 力扣（Leetcode）](https://leetcode.cn/problems/sort-an-array/solutions/1311934/duo-chong-pai-xu-yi-wang-da-jin-kuai-pai-wgz4/)

```c++
int partition(vector<int>& nums, int lo, int hi)
{
    int index = rand() % (hi - lo + 1) + lo; // 随机选择基准元素
    int value = nums[index];
    swap(nums[lo], nums[index]);
    int left = lo, right = hi;
    while(left < right)
    {
        while(left < right && nums[right] >= value) right--;
        nums[left] = nums[right];
        while(left < right&& nums[left] <= value) left++;
        nums[right] = nums[left];
    }
    //left == right 时退出循环
    nums[left] = value;
    return left;
}
```

912.排序数组

## 快速选择算法

是快速排序算法的变体，一般用来解决K-th Element问题，只需找到第k大的元素，而无需对k的左右元素进行排序

215.数组中第k个最大元素

快速排序一次`partition`后返回下标`p`，此时`p`左边的元素小于`nums[p]`,`p`右边的元素大于`p`，此时将`p`和`k`相比较，假如`p==k-1`,则`nums[p]`就是要找的元素，如果`p>k-1`,说明要找的元素在`p`的左边，否则要找的元素在`p`的右边。

框架

```c++
int ret;
void quickSort(vector<int>& nums, int lo, int hi, int k)//注意，题目要求第k大元素，所以partition中应该降序排列
{
    if(lo >= hi)
    {
        ret = nums[lo];
        return;
    }
    int p = partition(nums, lo, hi);
    if(p == k-1)//因为p是下标，所以k-1
    {
        ret = nums[p];
        return;
    }
    else if(p > k-1)
    {
        quickSort(nums, lo, p-1, k);
    }
    else
    {
        quickSort(nums, p+1, hi, k);
    }
}
```

时间复杂度O(N)

# 插入排序

稳定排序，时间复杂度O（n^2）

将一条记录插入到已排好序的数组中。

```c++
void InsertSort(vector<int> nums)
{
    for(int i = 1; i < nums.size(); ++i)
    {
        if(nums[i] < nums[i-1])
        {
            int j;
            int temp = nums[i];
            for(j = i-1; j >= 0 && temp < nums[j]; --j)
            {
                nums[j+1] = nums[j];
            }
            nums[j+1] = temp;
        }
    }
}
```

稳定排序：排序前和排序后相等元素的相对位置不变。

* 归并排序
* 插入排序
* 冒泡排序

不稳定排序：

* 快速排序
* 堆排序
* 选择排序

# 堆排序

大根堆：每个节点的值都大于其左右节点的值；

小根堆：每个节点的值都小于其左右节点的值。

用数组来存储，对于索引为`i`的节点：

* 父节点为`(i-1)/2`;
* 左孩子：`2 * i + 1`;
* 右孩子：`2 * i + 2`.

**堆排序基本思想**：

* 首先将待排数组构造成一个大根堆，此时，数组最大值即为堆顶；
* 将顶端的数与末尾的数交换，此时末尾元素为最大值，剩余代排元素为前`n-1`个元素；
* 将剩余`n-1`个元素再构造成大根堆，然后将堆顶元素与第`n-1`个元素交换，再去排前`n-2`个元素，如此反复。

**元素下沉规则：**

* 对于元素`i`若和它的左右子节点`2*i+1`和`2*i+2`，若`nums[i]`大于左右子节点的值，则不用下沉；
* 若`nums[i]`小于左右子节点中的最大值，则交换这两个节点，当前节点被交换到子节点位置；
* 继续下沉交换后的那个子节点。

**建堆规则：**

* 从最后一个非叶子节点开始，向上遍历，对每个节点执行下沉操作；
* 叶子节点无需下沉；
* 最后一个非叶子节点即为最后一个节点的父节点：`(nums.size()-1-1)/2`

代码：

```c++
// 下沉某个元素
// 待排数组，待下沉索引，下沉到end为止,end及之后的元素是已经拍好的有序元素。
void shiftDown(vector<int>& nums, int index, int end) 
{
    while(2 * index + 1 < end)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest_son = left;
        if(right < end && nums[left] < nums[right]) // 获取较大的子节点索引
        {
            largest_son = right;
        }
        if(nums[index] < nums[largest_son]) // 需要下沉
        {
            swap(nums[index], nums[largest_son]);
            index = largest_son;
        }
        else  // 不需要下沉
            break;
    }
}
// 建堆
void createHeap(vector<int>& nums)
{
    //从最后一个非叶子节点开始向上遍历，下沉每个节点
    for(int i = (nums.size()-2)/2; i >= 0; --i)
    {
        shiftDown(nums, i, nums.size());
    }
}

void headSort(vector<int>& nums)
{
    int n = nums.size();
    createHeap(nums);
    for(int i = n-1; i > 0; --i)
    {
        swap(nums[0], nums[i]);
        shiftDown(nums, 0, i);
    }
}
```

建堆时间复杂度O（n),调整时间复杂度O(nlogn)，总时间复杂度O(nlogn)。

# 桶排序

将要排序的数据先分到几个有序的桶里，每个桶里的数据再单独排序，再把每个桶里的数据有序取出。

时间复杂度O(n)。

适合外部排序，即数据量大，无法全部加载到内存中。

例如：

10G的数据，数据范围在[1-1000]：

扫描一遍数据，将数据划分到100个有序编号的文件中，其中1-10放在第一个文件，11-20放在第二个文件...以此类推；

每个文件中的数据再进行快速排序；

之后按顺序读出每个文件的数据即可。

# 单调栈

在每次入栈之前，弹出栈顶所有小于当前元素的元素，保证栈内元素有序（栈顶最小，栈底最大）

涉及**下一个更大元素**、**大于某个数的第一个元素**字眼都可以用单调栈解决。

496.下一个更大元素Ⅰ

①从后向前遍历数组，若当前元素大于等于栈顶元素，则弹出栈顶，直到当前元素小于栈顶或栈为空为止；

②则当前元素右侧第一个更大的数即为栈顶元素；

③将当前元素入栈。

是否存在当前元素的右侧更大元素在之前的循环中被弹出了？

不存在，若那个元素被弹出了，说明栈顶有更大的元素替代了它，这个栈顶元素才是解。

503.下一个更大元素Ⅱ

316.去除重复字母

**处理环形数组**

环形遍历示例：

```
[1, 2, 3] --->[1, 2, 3, 1, 2]
```

通过取模运算来实现：

```c++
int n = nums.size();
//正向遍历
for(int i = 0;i < 2 * n - 1;++i)
{
	cout << nums[i % n] << endl;
}
//逆序遍历
for(int i = 2 * n - 2; i >= 0; --i)
{
    cout << nums[i % n] << endl;
}
```

739.每日温度

84.柱状图中最大的矩形（hot100）  ——对每个柱子高度求左右边界，转化为求下一个更小元素——单调栈

85.最大矩形（hot100）——对于每一层，求84的最大矩形

# 单调队列

既能够维护队列元素先进先出的时间顺序，又能维护队列中所有元素的最值。

应用场景：239.滑动窗口最大值

```c++
//单调队列数据结构，使用deque实现
class MontonicQueue{
public:
    deque<int> que;
    void push(int n)//在队尾添加元素，并将小于n的元素全部删除
    {
        while(!que.empty() && n > que.back())
        {
            que.pop_back();
        }
        que.push_back(n);
    }
    int max()//返回当前队列中的最大值
    {
        return que.front();
    }
    void pop(int n)//队头元素如果是n，删除它，如果不是n，说明后进来的元素在队头，说明n因为小于后进来的元素已经被移除了
    {
        if(!que.empty() && n == que.front())
        {
            que.pop_front();
        }
    }
};
```

# 回溯

回溯算法就是N叉树的前后序遍历问题。

```python
#是否走到路径尽头
for 选择 in 选择列表:
    # 做选择
    将该选择从选择列表移除
    路径.add(选择)
    backtrack(路径, 选择列表)
    # 撤销选择
    路径.remove(选择)
    将该选择再加入选择列表
```

46.全排列

51. N皇后问题

37.解数独——**提前返回**，注意什么时候会获得需要的结果，在获得需要的结果后立即返回。

22.括号生成 

判断括号合法的核心：在任意位置，已放置左括号的数量大于等于右括号的数量，否则括号不合法。

131.分割回文串

递归穷举每种分割方案。

132.分割回文串Ⅱ

动态规划

`dp[i]`表示`s[0:i]`串能分割的最小次数
$$
f[i] = min\{f[j]\}+1\\0<=j<i
$$
其中`s[j+1:i]`需要是一个回文串。

**698.划分为k个相等子集**——**用一个整数的各个位来记录数组各元素是否被用过。**

排列组合问题

* *无重复元素，不可重复选*

  通过设置`start`可以保证元素被选取的相对顺序，即不会出现重复的集合。

  78.子集   

  77.组合    剪枝：当剩下元素取不够`k`个数时可以直接退出

* *有重复元素不可重复选*

  90.子集Ⅱ

  40.组合总和Ⅱ

  在`nums`有重复元素时保证最终选出的子集不会有重复：

  前提：如果当前元素等于上一个元素，且上一个元素没有被选取，那么选择当前元素后最终的子集一定会和选了上一个元素但没选当前元素的集合重复。所以在判断到当前元素和上个元素相同且上个元素没有被选取时，需要跳过。

  方法：先对`nums`排序，使相同的元素挨在一起，然后在回溯中做选择时，判断当前元素不是`start`且当前元素等于上个元素时跳过。

  ```c++
  for(int i = start; i<nums.size();++i)
  {
      //例如[1,2,2],当选择了第一个2时，会进入下一层回溯，那时i==start,因此会出现1,2,2的选择
  	if(i > start && nums[i] == nums[i-1])
      {
          continue;
  	}
      ...
      backtrack(nums, i+1);
      ...
  }
  ```

  47.全排列Ⅱ
  
  有重复元素的全排列
  
  * 对`nums`排序，使相同元素挨在一起
  * **保证相同元素在排列中的相对位置不变**。即当当前元素等于上一个元素，而上一个元素还没有被放入排列时，当前元素就不能被放入排列。
  
  ```c++
      void backtrack(vector<int>& nums, int used)
      {
          if(subset.size() == nums.size())
          {
              ret.emplace_back(subset);
              return;
          }
          for(int i=0;i<nums.size();++i)
          {
              if(used & 1 << i) continue;//这个元素已经被放入排列
              //当前元素等于上个元素，且上个元素没有被放入排列，则跳过   保证重复元素在排列中的的相对顺序不变
              if(i > 0 && nums[i] == nums[i-1] && !(used & 1 << (i-1))) continue;
              subset.emplace_back(nums[i]);
              used |= 1 << i;
              backtrack(nums, used);
              subset.pop_back();
              used ^= 1 << i;
          }
      }
  ```

* *无重复元素，可重复选*

  39.组合总和

  将`start`由`i+1`改为`i`即可。

# 岛屿问题

**核心**：用DFS/BFS遍历二维数组

DFS框架：

```c++
void dfs(vector<vector<int>& grid, int i, int j, vector<bool>& visited)
{
    //超出边界
    if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
    {
        return;
    }
    if(visited[i][j]) return;
    dfs(grid, i - 1, j, visited); // 上
    dfs(grid, i + 1, j, visited); // 下
    dfs(grid, i, j - 1, visited); // 左
    dfs(grid, i, j + 1, visited); // 右
}
```

200.岛屿数量

1254.统计封闭岛屿数目

1905.统计子岛屿

864.获取所有钥匙的最短路径

# BFS

BFS找到目标节点时，走的步数一定是最小的。因此，当图的边权重都相等时，BFS找到目标节点时，就是最短路径。而当权重不相等且都为正数时，就需要用Dijkstra算法。

752.打开转盘锁

773.滑动谜题

把开始的`board`抽象为一个节点，那么它的子结点就是几种不同的交换方案得到的新`board`，使用bfs，并记录访问过的节点，这样就抽象为最短步数问题。

864.获取所有钥匙的最短路径

# 图论

邻接表：把结点x的所有邻居都存在一个列表中，然后把这个列表和x关联起来。——邻接表无法快速判断两个结点是否相邻

邻接矩阵：二维矩阵，如果结点x和y是相连的，就把`matrix[x][y]`设为`true`——邻接矩阵占用的存储空间更多

**度**

* 在无向图中，每个结点相连的边数即为度
* 有向图中，区分入度和出度，入度为进入结点的边数，出度为走出结点的边数。

## 图深度优先遍历DFS

代码框架：

```c++
void dfs(vector<vector<int>>& adj, int i)//邻接表， 当前结点
{
    //处理当前结点
    
    //遍历邻居结点
    for(auto x : adj[i])
    {
        dfs(adj, x);
    }
    //当前结点后面的结点均已处理完，现在离开当前结点
}
```

797.所有可能的路径

## 环检测

1、DFS

设置状态`visited[i]`

* `visited[i]=0` 当前结点未访问
* `visited[i]=1`  当前结点访问中
* `visited[i]=2`当前结点已访问完 

当当前结点未访问时，执行dfs；

当前结点访问中时，说明有环，直接退出；

当前结点已访问完时，说明之前已经由其他路径访问过该结点，无须重复访问，跳过该结点。

```c++
bool valid = false;//是否有环
void dfs(vector<int>& adjacency, int i)
{
    visited[i] = 1;//当前结点设为访问中
    for(auto x:adjacency[i])
    {
        if(!visited[x])//未访问过
        {
            dfs(adjacency, x);
            if(valid)//发现有环，退出
                return;
        }
        else if(visited[x] == 1)//正在访问
        {
            valid = true;//有环.退出
            return;
        }
        //visited[x] == 2时，说明已经访问过，无须重复访问
    }
    //当前结点访问结束
    visited[i] = 2;
}
```

2、BFS

207.课程表

## 拓扑排序

拓扑排序是一个有向无环图的所有顶点的线性序列，满足以下两个条件：

* 每个顶点出现且只出现一次
* 若存在一条从顶点A到顶点B的路径，那么在序列中顶点A在顶点B的前面。

如果有向图中存在环，则无法进行拓扑排序。

1、DFS解法

后序遍历的结果反转，即为拓扑排序结果。`visited[i]`状态保证了每个结点只会被访问一次，因此从不同的节点出发的DFS不会产生重复。

2、BFS解法

(1) 计算每个节点的入度

(2) 入度为0的节点入队

(3) 不断弹出队列中的节点，并把当前节点的邻居节点的入度-1，当某个节点的入度减为0时，入队

(4) 如果遍历的节点数等于总节点数目，则说明无环。

210.课程表Ⅱ

## 二分图判定

二分图的顶点集可分割为两个互不相交的子集，图中每条边依附的两个顶点都分属于这两个子集，且两个子集内的顶点不相邻。

对于任意一条边，其两个顶点都可以被染为不同的颜色。

判定思路：遍历一遍图，相邻的节点染上不同的颜色，看看是否可以成功染色所有节点。

DFS：深度优先搜索节点，并记录节点是否被遍历过（不需要区分正在遍历还是已经遍历完成），如果没被遍历过，则给其染上与父节点不同的颜色，如果被遍历过，则判断其颜色是否和父节点相同，如果相同，则说明不是二分图。

BFS：利用bfs框架解决。

785.判断二分图

886.可能的二分法

## 并查集Union-Find

https://zhuanlan.zhihu.com/p/93647900

并查集用于解决一些**元素分组问题，它管理一系列不相交元素的集合**，并支持两种操作：

* **合并（union）**:把两个不相交的集合合并为一个集合。先找到两个集合的根节点，然后把其中一个设为另一个的父节点。
* **查询（find）**:查询两个元素是否在同一个集合中。元素顺着其父节点向上查询，直到根节点，看两个元素是否有相同的根节点。

并查集的重要思想：用集合中一个元素代表集合，这个元素即根节点。一开始每个元素都各自为一个集合，把它们的父节点设为它们自己。当两个元素需要合并时，就把其中一个的父节点设为另一个节点。

数据结构：为每个节点`x`维护一个父节点`fa[x]`,单个元素集合的元素父节点是其本身`fa[x] = x`。

```c++
//合并
void merge(int i, int j)
{
    fa[find[i]] = find(j);//i的根节点的父节点设为j的根节点
}
//查询
int find(int x)
{
    if(x == fa[x])//到达根节点
    {
        return x;
    }
    return find(fa[x]);//递归查询父节点的根节点
}
```

### 路径压缩

简单的合并可能会导致集合呈现为链式：

![7](https://gitee.com/qin_minjie/imagebed/raw/master/images/7.jpg)

而我们查询时只需要关心一个节点的根节点，因此可以压缩每个节点到其根节点的路径，最好每个节点的父节点就是它的根节点。

![8](https://gitee.com/qin_minjie/imagebed/raw/master/images/8.jpg)



压缩方法：在find的过程中动态调整结构，将沿途的每个节点的父节点设为根节点。这样每查询一次就可能会优化一次结构。

```c++
int find(int x)
{
    if(x == fa[x])//到了根节点
    {
        return x;
    }
    fa[x] = find(fa[x]);//递归查询根节点  并把x的父节点fa[x]设为根节点
    return fa[x];//返回父节点，此时父节点已经是根节点
}
```

### 按秩合并

由于路径压缩只在查询时优化结构，因此集合图不一定会呈现为菊花图（最大深度2层），在这种情况下合并两个集合时，最好的做法是把深度小的树往深度大的树上合并，这样不会增加树的深度。因此维护一个`rank`数组记录每个节点的子树深度，合并时比较两个根节点的深度再合并。

但由于路径压缩过程中节点的子树深度会发生变化，需要实时修改`rank`，这样会使代码变复杂，因此按秩合并并不常用。

130.被围绕的区域    设置一个虚拟节点`dummy`，把边缘的'O'和`dummy`合并起来。然后遍历内部元素，将'O'与它四周的'O'合并起来，这样暴露的'O'就成为一个集合，且集合中含有`dummy`,被包围的'O'各自成为集合，集合中没有`dummy`,只需遍历元素，看是否和`dummy`在一个集合即可。

990.等式方程的可满足性

684.冗余连接

## 最小生成树

**树就是无环连通图**

生成树：在图中找一棵包含图中所有节点的树。生成树是含图中所有节点的无环连通子图。

最小生成树：对于加权图，所有可能的生成树中权重最小的那棵树。

#### Kruskal算法

用并查集算法来保证树的合法性，即无环且连通。

在什么情况下加入一条边会使得树中产生环？

如果添加的这条边的两个节点本来就在同一连通分量里，那么添加这条边会产生环，反之，则不会产生环。判断两个节点是否连通，则使用并查集算法。

最小生成树，即是若干边的集合mst，这些边满足：

* 包含图中所有节点——确保最后只生成了一棵树，即只有一个连通分量
* 不存在环
* 权重和最小

采用贪心思路：

将所有边按照权重从小到大排序，从权重最小的开始遍历，如果这条边和mst中其他边不形成环，则这条边是最小生成树的一部分。

时间复杂度：O(mlogm),m为边数

1584.连接所有点的最小费用

### Prim算法

#### 切分定理

将一幅图切分为两个不重叠且非空的节点集合。被切断的边叫做横切边。对于任意一种切分，其中权重最小的那条边，一定是构成最小生成树的一条边。

https://labuladong.gitee.io/algo/2/22/55/

1584.连接所有点的最小费用

### Dijkstra算法

给定起点start,计算start到所有点的最短路径

本质：从start开始BFS图，记录起点到每个点的路径，每次取最小的路径。

优化：优先队列

时间复杂度：O(ElogV)   E为图中边的条数，V为图中的节点数。

743 网络延迟时间。

1631.最小体力消耗路径

1514.概率最大的路径

代码模板

```c++
int start, end;//起点和终点
struct Node{
  int id;
  int distFromStart;
    Node(int id, int dist):id(id), distFromStart(dist){}
};
struct cmp{
  bool operator() (Node& a, Node& b){
      return a.distFromStart > b.distFromStart;//升序排列
  }  
};
vector<vector<pair<int, int>>> graph;//图的邻接表  pair<id,weight>
vector<int> dist(n, INT_MAX);//记录从start到每个点的最短路径
dist[start] = 0;
priority_queue<Node, vector<Node>, cmp> pq;
//也可用pair来简化写法
priority_queue<pair<int,int>, vector<pair<int, int>>, less<int>> pq;//pair<距离， id> 优先队列会默认按照pair.first排序
pq.emplace(Node(start, 0));
while(!pq.empty())
{
    Node cur = pq.top();
    pq.pop();
    if(cur.id == end) break; //如果只是找start到end的最短路径，则第一次遇到end时就可以退出了
    if(cur.distFromStart > dist[cur.id]) continue; //已经有更短的路径到达此点，则略过
    for(auto x : graph[cur.id])
    {
        int distFromStart = dist[cur.id] + x.second;
        if(distFromStart < dist[x.first])
        {
            dist[x.first] = distFromStart;
            pq.emplace(Node(x.first, distFromStart));
        }
    }
}
```



# LRU算法（Least Recently Used）

146.LRU缓存

内存满时，优先删除那些久未使用的数据。

核心数据结构：哈希链表——哈希表+双向链表

* 具有时序特征，以区分最近使用的和久未使用的。
* 支持快速查找、插入和删除，以将最近使用的移至头部。
* `get()`:查找指定元素，如果存在则返回，并将该元素提到头部。
* `put()`：如果已存在该元素，则更新其值并提到头部，若不存在，则插入元素到头部。插入后若数据超出容量，则删除最久未使用的元素，即链表尾部元素。

# 动态规划

适用于有重叠子问题和最优子结构性质的问题，是一种自底向上的算法。（递归是自顶向下）

给定一个问题，把问题层层拆分成子问题，直到子问题可以直接解决，然后保存子问题的答案，减少重复计算。

爬楼梯：爬到n级楼梯的方法数 = 爬到n-1 和爬到n-2的方法之和。

动态规划与分治的区别：动态规划的子问题是有关联的，分治的子问题是相互独立的。

三要素：

* 重叠子问题
* 最优子结构
* 状态转移方程

##  **滚动数组优化**

63.不同路径Ⅱ      

基本dp思想：使用二维数组来存储以每个点为终点的路径总和，则当前点的路径总和=正上方点的路径数 + 左边点的路径数

滚动数组优化：使用一维数组`paths`来存储以该行中每个点为终点的路径总和数,则`paths`的更新策略为 `paths[j] = paths[j] + paths[j-1]`

* 等号右边的`paths[j]`为上一行存储的`j`位置处的路径数，即当前点的正上方的点的路径总和数，`paths[j-1]`为当前点左边点的路径综合数。
* 考虑边界条件，当处于第一行时，当前点上方没有点，而因为`paths`元素初始化为0，`paths[j] = 0 + paths[j-1]`满足;当`j=0`时，`j`左侧没有点,`paths[j]`值等于其正上方的点的值，因此`paths[j]`不用做改变,满足。

416.可滚动数组优化

96.不同的二叉搜索树

* 问题可以分解为分别以每个节点为根节点所能构成的树的个数之和

* 对于二叉搜索树，当以有序数组的第i个元素作为根节点时，前i-1个节点必在左子树，后n-1个节点必在右子树。
* 以第i个节点为根节点，构成的树的种类数=i-1个节点构成的树的类数* n-i个节点构成的树的种类树

令$G(n)$为$n$个节点构成的二叉搜索数数目

$F(n,i)$表示以第i个节点为根结点的n个节点构成的二叉搜索树数目

$$
G(n)=\sum_{i=1}^n F(i, n)
$$

$$
F(n, i)=G(i-1)*G(n-i)
$$

## **01背包问题**

有n件物品和一个最大容量为w的背包，第i件物品的重量是weight[i]，得到的价值为value[i]，每件物品只能用一次，求将哪些物品放入背包里物品的价值总和最大。

解法：

二维dp,令`dp[i][j]`表示将从前`i`个物品中选择放入容量为`j`的背包中，所能获得的最大价值。每个物品有放入和不放入两种选择，则

```c
if(j < weight[i])//当背包容量小于第i件物品的重量时，第i件物品不可能放进去
{
	dp[i][j] = dp[i-1][j];
}
else//当背包容量大于第i件物品的重量时，第i件物品可以不放，也可以放
{
	dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i]);
}
```

初始化：

当背包容量`j`为0时，不管前多少件物品都不能放进去，所以`dp[:][0]=0`

完整代码：

```c++
int n = weight.size();
vector<vector<int>>dp(n+1, vector<int>(w+1, 0));

for(int i=1;i<=n;++i)
{
    for(int j=1;j<=w;++j)
    {
        if(j < weight[i-1])//当背包容量小于第i件物品的重量时，第i件物品不可能放进去
        {
            dp[i][j] = dp[i-1][j];
        }
        else//当背包容量大于第i件物品的重量时，第i件物品可以不放，也可以放
        {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]]+value[i-1]);//因为value下标从0开始，这里的i表示第i件物品，所以要减一
        }
    }
}
```

可以用滚动数组优化:

```c++
int n = weight.size();
vector<int> dp(w+1, 0);
for(int i=1;i<=n;++i)
{
    for(int j=w;j>=weight[i-1];--j)//j < weight[i-1]即背包容量小于当前重量dp[i][j] = dp[i-1][j]
    {
        dp[j] = max(dp[j], dp[j-weight[i-1]]+value[i-1]);
    }
}
```

题目：

416.分割等和子集

背包容量：数组和的1/2

494，1049

## **完全背包问题**

根据第`i`种物品放多少件进行决策：
$$
F[i][j] = max(F[i-1][j-k*weight[i]] + k*value[i])   0\leq k*weight[i] \leq j
$$
状态方程：(不放第i件物品或至少放一件第i件物品)
$$
F[i][j] = max(F[i-1][j], F[i][j-weight[i]]+value[i])
$$

322.零钱兑换

518零钱兑换Ⅱ  对遍历的先后顺序有要求。

**完全背包问题**，即可以重复选择的问题，可能需要考虑**内外循环的先后顺序**，如果外循环是`target`（背包），内循环是`nums`（物品），则为排列（有放入顺序不同但元素相同的情况）；外循环是`nums`（物品），内循环是`target`（背包）则为组合。

139.单词拆分 使用哈希表做字符串快速查找。

## 打家劫舍

 213.打家劫舍Ⅱ  **数组成环** ，因为首尾元素不能同时出现，考虑两种情况：1、考虑前`n-1`个元素， 2、考虑后`n-1`个元素，取两种情况最大值即可。  

### 树形dp 

337.打家劫舍Ⅲ

解法一：

递归+记录中间结果

解法二：

树形dp

## 买卖股票最佳时机——状态机

188.买卖股票最佳时机。

状态+选择

共有三种状态：第几天，最大交易次数限制，是否持有股票

https://labuladong.gitee.io/algo/3/28/96/

## 子序列类型

300.最长递增子序列     

32.最长有效括号（hot100）

定义：`dp[i]`表示以`nums[i]`为结尾的最长递增子序列的长度——**解决子序列问题的套路之一**

354.俄罗斯套娃：二维最长递增子序列

先对w升序排序，w相同的按h降序排序，然后对h求最长递增子序列。避免了h升序序列中w相同的情况。若h2>h1，则w2一定也大于w1。

同理，53.最大子序和

1143.最长公共子序列   (不连续)—— 两个序列，一般用二维dp

1035.不相交的线（不连续）  与1143同理。

718.最长重复子数组 （连续）

**编辑距离**

72.编辑距离（两个字符串的递归问题，二维dp）

定义`dp[i][j]`表示以第`i`个字符结尾的`word1`串和以第`j`个字符结尾的`word2`串的最小编辑距离

初始化：`dp[i][0]=i, dp[0][j] = j`

当`word1[i-1] == word2[j-1]`时，`dp[i][j] = dp[i-1][j-1]`

当`word1[i-1] != word2[j-1]`时，`dp[i][j]`为以下三项中的最小值

* `dp[i-1][j]+1`  `word1`的前`i-1`个字符和`word2`前`j`个字符的编辑距离 + 删除`word1`第`i`个元素的操作
*    `dp[i][j-1]+1`  `word1`的前`i`个字符和`word2`前`j-1`个字符的编辑距离 + 删除`word2`第`j`个元素的操作
* `dp[i-1][j-1]+1`  `word1`的前`i-1`个字符和`word2`前`j-1`个字符的编辑距离+将`word1`的第`i`个元素替换为`word2`的第`j`个元素的操作

583.两个字符串的删除操作（编辑距离）

剑指 Offer II 095. 最长公共子序列

115.不同的子序列（！！！）

**回文**

647.回文子串  

定义`dp[i][j]`为以下标`i`开始到下标`j`的子串是否是回文串

注意遍历的顺序   `dp[i][j]=(s[i]==s[j]&&dp[i+1][j-1])` 从左下角开始遍历

也可用中心扩散法。

516.最长回文子序列

从左下角开始遍历

# 贪心

376.摆动序列

统计波峰和波谷的数量，注意边界处也是波峰和波谷。

4.最大子数组和

当连续累加和为负数时应当舍弃当前累加，从下一个元素开始重新累加。

55.跳跃游戏 ——计算最大覆盖范围

135.分发糖果

分两次遍历，每次只改变一侧的糖果数，依次向后更改。

134.加油站

当从x无法到达y时，那么从x和y中间的任意一点z都无法到达y。因为从x到达z时油箱可能还有油，这都无法到达y，那么从z空油出发肯定无法到达y。

1005.K次反转取最大的数组和

按绝对值排序，从大到小遍历，遇到负数，反转符号，遍历完成后k还有剩余，则反复反转最小的数字。

406.根据身高重建队列

452.射爆气球

合并区间思想，先排序，然后遍历检查是否满足合并区间条件

738.单调递增数字

从后向前检查，如果遇到当前位上的数字比下一位的数字大，那么当前位上的数字-1，并把之后的位都设为9

## 扫描线技巧

NC147. 主持人调度

最大重叠区间问题，利用扫描线技巧，从左至右扫描，遇到左端点，`count+1`，遇到右端点`count-1`，求出过程中`count`的最大值。

分别对区间的左端点和右端点进行排序，利用双指针进行扫描。



# ACM模式知识

牛客练习

[(0条未读通知) 牛客竞赛_ACM/NOI/CSP/CCPC/ICPC算法编程高难度练习赛_牛客竞赛OJ (nowcoder.com)](https://ac.nowcoder.com/acm/contest/5657#question)

## cin

`cin`是标准输入流`istream`类的对象，用于从标准输入读取数据。

`cin`从标准输入缓冲区中读取数据，缓冲区为空时，`cin`会阻塞等待数据的到来。

`cin >>`

可以连续从键盘输入数据，以空格、tab、换行作为分隔符。当缓冲区第一个字符是分隔符时,`cin`会忽略并读取下一个字符。

`cin.get()`

`cin.get`读取时不会忽略分隔符。

1. 读取一个字符：

```c++
char a;
char b;
a = cin.get();
cin.get(b);
```

# 正则表达式



c++11正则表达式库：`std::regex`

```
#include <regex>
```

函数

```c++
bool regex_match(string s, regex pattern)    //匹配指定字符串整体是否符合
bool regex_search(string s,  regex pattern)   //匹配字符串中符合的子字符串,只要有目标出现就返回
string regex_replace(string s,regex p,string replace_str)  //替换字符串中指定的字符串
```

正则文法

|  符号  |              意义              |
| :----: | :----------------------------: |
|   ^    |          匹配行的开头          |
|   $    |          匹配行的结尾          |
|   .    |        匹配任意单个字符        |
| [...]  |   匹配 [ ] 中的任意一个字符    |
| (...)  |            设定分组            |
|   \    |            转义字符            |
|   \d   |         匹配数字[0-9]          |
|   \D   |             \d取反             |
|   \w   |  匹配字母[a-z]，数字，下划线   |
|   \W   |             \w取反             |
|   \s   |            匹配空格            |
|   \S   |             \s取反             |
|   +    |    前面的元素重复1次或多次     |
|   *    |      前面的元素重复任意次      |
|   ？   |     前面的字符重复0次或1次     |
|  {n}   |       前面的字符重复n次        |
| {n, }  |     前面的字符至少重复n次      |
| {n, m} | 前面的元素至少重复n次，至多m次 |
|   \|   |             逻辑或             |

用法：

```c++
#include<regex>
string s = "192.0.0.2";
regex reg("^(([0-9]|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9]\\d|1\d{2}|2[0-4][0-9]|25[0-5])$");
bool ismatch = regex_match(s, reg);
```

# 高效筛选素数（质数）

素数定义：只有1和它本身两个因数。（1不是素数）

204.计数质数   求小于n的素数数量

朴素算法：遍历2~n-1，分别判断是否是素数

```c++
bool isPrime(int x) // 判断2~x-1之间是否有x的因数
{
    // 因子判断只需到sqrt(x)
    for(int i = 2; i * i <= x; ++i)
    {
        if(x % i == 0)
            return false;
    }
    return true;
}
int countPrimes(int n)
{
    int res = 0;
    for(int i = 2; i < n; ++i)
    {
        if(isPrime(i))
            res++;
    }
    return res;
}
```

优化一：

* 除了2以外其它偶数都不可能是素数，因此第一层循环可以只判断除2外的奇数。
* 奇数不可能有偶数因子，因此第二层循环可以只遍历奇数。

```c++
bool isPrime(int x)
{   //奇数不可能存在偶数因子
    for(int i = 3; i * i <= x; i += 2)// 3 5 7 9
    {
        if(x % i == 0)
            return false;
    }
    return true;
}
int countPrimes(int n) {
    int res = 0;
    if(n <= 2) return res;
    //除了2，其它偶数都不是素数
    for(int i = 3; i < n; i += 2) // 3 5 7 9 11 13
    {
        if(isPrime(i))
            res++;
    }
    return res+1;//加上2
}
```

优化二：埃氏筛选法

核心思想：如果一个数是质数，那么它的整数倍（不包括自身）必然不是质数。从小到大遍历，如果一个数是质数，则将它的整数倍都标记为合数。

优化：如果一个数`i`是质数，那么从`i*i`开始标记`i`的整数倍为合数。因为`i*i`前面的`2*i`,`3*i`必然在`i`是`2`或`3`时标记过了。

时间复杂度O(nloglogn)

```c++
class Solution {
public:
    int countPrimes(int n) {
        //埃氏筛
        int res = 0;
        vector<bool> isPrime(n, true);
        for(int i = 2; i < n; ++i)
        {
            if(isPrime[i])
            {
                res++;
                //从i*i开始标记i的整数倍为合数
                if((long) i * i < (long) n)
                {
                    for(int j = i * i; j < n; j += i)
                    {
                        isPrime[j] = false;
                    }
                }
            }
        }
        return res;
    }
};
```

# 字符串乘法

令`m`和`n`分别表示`num1`和`num2`的长度，并且它们均不为0，则`num1`和`num2`的乘积长度为`m + n - 1`或`m + n`。

用两个指针在`num1`和`num2`上移动，计算`num1[i]`和`num2[j]`的乘积，同时将乘积叠加到`res`的正确位置。`num1[i]`和`num2[j]`的乘积对应的是`res[i+j]`和`res[i+j+1]`的位置。

43.字符串相乘

```c++
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0") return "0";
        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> res(n1 + n2);
        for(int i = 0; i < n1; ++i)
        {
            for(int j = 0; j < n2; ++j)
            {
                int number1 = num1[i] - '0';
                int number2 = num2[j] - '0';
                res[i + j + 1] += number1 * number2;
            }
        }
        int carry = 0;
        for(int i = res.size() - 1; i >= 0; --i)
        {
            res[i] += carry;
            carry = res[i] / 10;
            res[i] %= 10;
        }
        int start = res[0] == 0 ? 1 : 0;
        string result;
        for(int i = start; i < res.size(); ++i)
        {
            char c = res[i] + '0';
            result.push_back(c);
        }
        return result;
    }
```

# 42.接雨水

**核心思路：**位置`i`能装下的水为等于左右两边最高柱子中较小的那个减去`i`位置的高度。

```c++
water[i] = min(l_max, r_max) - height[i];
```

![jieyushui](C:\Users\qmj\OneDrive\图片\jieyushui.jpg)

可以预先求出每个位置左边最高的柱子和右边最高的柱子，然后遍历每个位置计算存水量。

```c++
int trap(vector<int>& height)
{
	int n = height.size();
    vector<int> l_max(n, 0);
    vector<int> r_max(n, 0);
    for(int i = 1; i < n; ++i)
    {
        l_max[i] = max(l_max[i-1], height[i-1]);
    }
    for(int i = n-2; i >= 0; --i)
    {
        r_max[i] = max(r_max[i+1], height[i+1]);
    }
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        int cur = min(l_max[i], r_max[i]) - height;
        res += cur > 0 ? cur : 0;
    }
    return res;
}
```

双指针优化：

思路与11.盛水最多的容器相同

用`left`和`right`指向左右两边

```c++
int trap(vector<int>& height)
{
	int n = height.size();
    int left = 0, right = n-1;
    int l_max = 0, r_max = 0;
    int res = 0;
    while(left < right)
    {
        l_max = max(l_max, height[left]);
        r_max = max(r_max, height[right]);
        if(l_max < r_max)
        {
            res += l_max - height[left];
            left++;
        }
        else
        {
            res += r_max - height[right];
            right--;
        }
    }
    return res;
}
```

单调栈解法

维护一个单调栈，栈中元素递减

```c++
int trap(vector<int>& height) {
    stack<int> stk;
    //单调栈，栈中元素递减
    int res = 0;
    for(int i = 0; i < height.size(); ++i)
    {
        while(!stk.empty() && height[stk.top()] < height[i])
        {
            int cur_index = stk.top();
            stk.pop();
            if(stk.empty()) break;
            int left = stk.top();
            int he = min(height[left], height[i]) - height[cur_index];
            int wide = i - left - 1;
            res += he * wide; 
        }
        stk.push(i);
    }
    return res;
}
```

# 其它题目

31.下一个排列 

寻找下一个更大字典序的排列：

​    1.如果元素都是降序排列，那没有更大的字典序了；

​    2.下一个字典序比当前字典序大的那个决定性元素应该靠后，例如：123456->123465而不是612345，因此从后向前查找；

​    3.应该从这个决定性元素的右边找到比它大的元素交换过来，并且这个比它大的元素尽可能小

​    3.从后向前查找到第一个不是降序排列的元素，说明此元素后面有比它大的元素，可以交换过来；

​    4.再次从后向前查找到比它大的那个最小的元素，进行交换；

​    5.最后将当前元素的后面元素按升序排列。

### rand5(0~4)生成rand7(0~6)

rand5 * 5生成0，5，10，15，20

rand5 * 5 + rand5+1生成1~25，取1~21对7取余，得到0~6.

```c++
int myrand(int x)
{
	return rand() % x;
}

int rand7()
{
    int temp = myrand(5) * 5 + myrand(5) + 1;//1-25
    while(temp > 21)
    {
        temp = myrand(5) * 5 + myrand(5) + 1;//1-25
    }//temp <= 21
    return temp % 7;
}
```





