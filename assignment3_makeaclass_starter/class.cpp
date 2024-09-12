#include "class.h"

Student::Student() {}

Student::Student(const std::string &s, int a, int n, int id)
// 当你在函数参数中不使用引用（即使用按值传递）时，C++ 会创建一个参数对象的副本,万一对象很大或很复杂就很麻烦
{
    name = s;
    age = a;
    class_number = n;
    studentId = id;
}

void Student::SetName(const std::string &s)
{
    name = s;
}

void Student::SetAge(int a)
{
    age = a;
}

void Student::SetClassNumber(int n)
{
    class_number = n;
}

int Student::GetAge() const
{
    return age;
}

const std::string &Student::GetName() const
// 类似地，当函数返回一个对象时，如果返回值不是引用，C++ 会创建返回对象的副本。
// 但是返回 private 成员的引用的 有风险！❗🈶
// 虽然这样可以避免不必要的拷贝，但直接返回 private 成员的引用存在以下风险：
// 违反封装原则：暴露了类的内部实现。尽管 name 是 private 的，但通过返回引用，外部代码依然可以访问到它（如果没有 const 限定符，甚至可以修改它），这可能会导致不安全的操作。
// 对象生命周期问题：如果返回的是局部对象的引用或临时对象的引用，可能会在使用时导致未定义行为。
{
    return name;
}

int Student::GetClassNumber() const
{
    return class_number;
}
