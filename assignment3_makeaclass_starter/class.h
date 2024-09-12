// Blank header file
#include <iostream>

class Student
{
public:
    Student();
    Student(const std::string &s, int a, int n, int id);

    void SetName(const std::string &s);
    void SetAge(int a);
    void SetClassNumber(int n);
    int GetAge() const;
    const std::string &GetName() const;
    int GetClassNumber() const;

public:
    int studentId;

private:
    std::string name;
    int age;
    int class_number;
};
