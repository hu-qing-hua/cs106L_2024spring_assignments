TODO: Delete this line and answer the short questions in the assignment within this file!
# 1
这里不需要按序查找，并且unordered_set运行速度更快，所以可以用unordered_set;
a valid hash function:哈希值：将字符串的每个字符都与31相乘，再累加求和（31是质数，有效减少冲突）;
哈希值相同则判断字符串是否相等，相等则不插入，不相等则用链地址法。
https://medium.com/geekculture/data-structures-multi-set-vs-set-vs-unordered-set-bcc4f6609ac9
# 2
1. change changing the backing container of the std::queue from its default value:
---->
```cpp
std::queue<T, Container> queue_name;
```
默认是deque;
定义可以改成
```cpp
//T: The type of the elements stored in the queue.
 std::queue<T, std::vector<T>> myQueue;
 或者
 std::queue<T, std::list<T>> myQueue;
 ```
2. 可以改变backing container 的好处：可以按需求选择合适的实现方法。如果是要频繁pop的情况，用vector不适合，vector从头删除元素不高效
The choice of the underlying container can impact the performance of the container adaptor. 
For example, std::deque is generally more efficient for std::queue because it supports constant-time insertions and deletions from both ends, 
unlike std::vector which has linear time complexity for these operations.
3. Container adaptors are “wrappers” to existing containers!
可以让用户更方便地使用容器。
可以构造特定功能的数据结构，像std::stack,std::queue,std::priority_queue;
std::stack,std::queue -->默认底层是std::dequeue
std::priority_queue   -->默认底层是std::vector
# 3
1. 原因：
if store names themselves:
就像下面的例子：
```cpp
#include <iostream>
#include <queue>
int main() {
    std::queue<int> myqueue;
    int n = 10;
    int& a = n;
    myqueue.push(a);  // 将 a（即 n）推入队列
    std::cout << myqueue.front();  // 输出队列的第一个元素
}
```
这样其实是存储对name的值的副本，queue会取到值，分配新的空间放这个值。
这种做法肯定是比较浪费的,如何不复制存储呢
优化->
<font color=red>第一种：存指针</font>
例如
```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int*> myqueue;
    int n = 10;
    myqueue.push(&n);  

    std::cout << *(myqueue.front());  

    n = 20;  
    std::cout << *(myqueue.front());  
}
```

<font color=red>第二种：智能指针</font>

```cpp
#include <iostream>
#include <queue>
#include <memory>

int main() {
    std::queue<std::shared_ptr<int>> myqueue;
    int n = 10;
    myqueue.push(std::make_shared<int>(n));  

    std::cout << *(myqueue.front()) << std::endl;  

    n = 20;  
    *(myqueue.front()) = n;  
    std::cout << *(myqueue.front()) << std::endl;  
}

```
*我们知道智能指针和普通指针很大的区别就是它可以自动管理内存。当智能指针不再使用时（超出作用域或引用计数归零），它会自动释放所管理的资源。
而使用原始指针分配动态内存时（例如使用 new），你需要手动管理内存的释放（例如使用 delete）。如果你忘记释放内存，或者在错误的时间释放内存，就可能导致内存泄漏或悬空指针等问题。*

但是这里第一种方法也没有delete
因为：
如果指针指向一个栈上的变量，比如第一种方法中，指针指向 n，这是不涉及动态内存分配的，因此不需要 delete。栈上的变量在超出作用域时自动释放。
但如果new了，动态分配情况下，是要delete的
```cpp
int* p = new int(10);
// 必须在不需要时手动释放
delete p;
```

那我在main.cpp里用的是普通指针，会有什么问题吗->
我的queue存储的是一个普通指针，studentName是局部变量，它的生命周期在一次循环结束就结束了，但是studentName是一个生命周期为全局的变量的引用，我存储它的地址，会不会出现存储被销毁地址的情况
>Your observation is correct. While studentName in your find_matches function is a reference to a string in the std::unordered_set\<std::string\> (which has a global or long-term scope within the program), the reference itself is perfectly safe because the lifetime of the string objects in the std::unordered_set continues until the set is destroyed.
Since the std::unordered_set owns the strings, they remain valid as long as the set exists. When you store a pointer to studentName (which is a reference to an element in the set) in the priority queue, you're effectively storing a pointer to an element with a lifetime bound to the std::unordered_set.
Here's the key point:
studentName is a reference: It references an element in the std::unordered_set, so the actual data it refers to lives as long as the set does.
Pointers in the priority queue: Since you're storing pointers to elements in the std::unordered_set, those pointers remain valid as long as the std::unordered_set itself is not destroyed or modified in a way that invalidates iterators (e.g., by removing elements).
Thus, there is no risk of accessing a destroyed object in this context because the strings in the std::unordered_set are not destroyed as long as the set exists and is unmodified.
However, if the std::unordered_set is cleared or destroyed before you access the pointers in the priority queue, then those pointers would become dangling, leading to undefined behavior. But as long as the set is intact, your current implementation is safe.
---chatgpt


<br>
<br>



<font color=red>第三种：使用 std::reference_wrapper 存储引用。</font>
因为**std::queue不能存储引用!**
>引用的性质：引用在 C++ 中并不是一个完整的对象，而是一个别名，绑定到另一个对象的内存地址。引用本身没有存储内存地址的能力，因此不能像指针或值那样被容器存储。
标准容器的要求：C++ 标准容器（如 std::queue, std::vector, std::list 等）要求其元素必须是可以复制和赋值的对象，而引用不符合这一要求。引用不能被复制，也不能通过赋值操作改变其绑定的对象，因此不能直接存储在标准容器中。

但如果真的想存储引用，就用 std::reference_wrapper 包装一下。

2. 应该是问超出该set作用域而引用了它的指针
"What happens if the original set where the names are stored goes out of scope and the pointers are referenced?"

If the original std::unordered_set\<std::string\>, where the names are stored, goes out of scope, the following sequence of events occurs:

Destruction of the Set: When the std::unordered_set\<std::string\> goes out of scope, its destructor is called. This leads to the destruction of all its elements (i.e., all the std::string objects in the set).

Invalidation of Pointers: The pointers stored in your std::priority_queue still point to the memory locations where the std::string objects used to be. However, since those objects have been destroyed, these pointers now become dangling pointers—they point to memory that is no longer valid.

Undefined Behavior: If you try to dereference any of these dangling pointers after the set has been destroyed, the behavior is undefined. This could lead to a crash, unexpected results, or other erratic behavior since you're accessing memory that is no longer allocated for the std::string objects.
```cpp
{
    std::unordered_set<std::string> mySet = get_applicants("students.txt");
    auto myqueue = find_matches(mySet);

    // mySet goes out of scope here, as the block ends
}
// If you try to use myqueue after this block, it leads to undefined behavior:
std::cout << *(myqueue.top()) << std::endl;  // This is undefined behavior!

```
In this example, after the block ends, mySet is destroyed, and the strings it contained are also destroyed. The pointers in myqueue become invalid, and dereferencing them will likely cause a runtime error.

**Solution**:
To prevent this issue, ensure that the std::unordered_set<std::string> remains in scope for as long as you need to access the pointers stored in the std::priority_queue. This can be managed by:
Keeping the set alive for the required duration.
Or, if you really need the strings to outlive the scope, you could consider using dynamically allocated strings (with new or std::shared_ptr<std::string>) to ensure their lifetime extends beyond the set's scope. However, this approach comes with its own complexities and potential pitfalls related to memory management.