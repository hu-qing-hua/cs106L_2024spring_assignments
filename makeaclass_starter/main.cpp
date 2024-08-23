
/*
 * Assigment 3: Make a class!
 * Requirements:
 * Must have a custom constructor ✅
 * Must have a default constructor ✅
    - i.e. constructor overloading
 * Must have private members (functions and/or variables) ✅
 * Must have public members (functions) ✅
 * Must have at least one getter function ✅
 * Must have at least one setter function ✅
 */
#include "class.h"
int main()
{
  // initialize class and run this file
  Student s("linda", 12, 25, 45);
  std::cout << "Name: " << s.GetName() << " Age: " << s.GetAge() << " ClassNumber: " << s.GetClassNumber() << " studentId: " << s.studentId << std::endl;
  s.SetName("bob");
  s.SetAge(2);
  s.SetClassNumber(34);
  std::cout << "Name: " << s.GetName() << " Age: " << s.GetAge() << " ClassNumber: " << s.GetClassNumber() << " studentId: " << s.studentId << std::endl;
  return 0;
}

// 第一次编译的时候 g++ -g main.cpp class.cpp -o main.exe
// class.cpp也要编译，不然找不到

// 修改tasks.jison文件