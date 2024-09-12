/*
Assignment 2: Marriage Pact

This assignment asks you to discover your one true love using containers and pointers.
There are two parts: implement get_applicants and find_matches.

Submit to Paperless by 11:59pm on 2/1/2024.
*/
#include <iostream>
#include <string>
#include <queue>
// #include <set>
#include <unordered_set>

#include <fstream>

// struct compare//未被调用，因为queue存储的是指针
// {
//     bool operator()(const std::string &a, const std::string &b)
//     {
//         // return a.size() > b.size();这样是错的！
//         return a.size() < b.size();
//     }
// };

struct compare
{
    bool operator()(const std::string *a, const std::string *b)
    {
        return a->size() < b->size();
    }
};

std::unordered_set<std::string>
get_applicants(std::string filename)
{
    // TODO: Implement this function. Feel free to change std::set to std::unordered_set if you wish!
    std::ifstream studentTable(filename);
    std::unordered_set<std::string> studentSet;
    if (studentTable.is_open())
    {
        std::string studentName;
        while (getline(studentTable, studentName))
        {
            studentSet.emplace(studentName);
        }
    }
    else
    {
        std::cout << "error:can not open the file" << std::endl;
    }
    studentTable.close();
    // for (const std::string& x: studentSet) std::cout << " " << x<<std::endl;;
    return studentSet;
}

std::priority_queue<const std::string *, std::vector<const std::string *>, compare> find_matches(std::unordered_set<std::string> &students)
{
    // TODO: Implement this function.
    char firstNameInitial, lastNameInitial;
    std::priority_queue<const std::string *, std::vector<const std::string *>, compare> potentialMatch;
    std::unordered_set<std::string>::iterator it;

    std::cout << "please input your initials:\n";
    std::cin >> firstNameInitial >> lastNameInitial;

    for (it = students.begin(); it != students.end(); ++it)
    {
        // std::string studentName = *it; x 这样是创建了一个局部变量，potentialMatch会指向这个局部变量的值
        const std::string &studentName = *it;
        int pos = studentName.find(" ");
        if (pos != std::string::npos && studentName[0] == firstNameInitial && studentName[pos + 1] == lastNameInitial)
        // std::string::npos 是 std::string 类中定义的一个常量，用来表示“查找失败”或“无效位置”。它的值通常是 -1,查找失败会返回npos
        {
            // potentialMatch.emplace(it); × it确实可以像指针一样用于访问集合中元素的值。但它并不直接是指向字符串的普通指针，而是一个迭代器对象，通过它可以访问集合中的元素。
            potentialMatch.emplace(&studentName);
        }
    }
    return potentialMatch;
}

int main()
{
    // Your code goes here. Don't forget to print your true love!
    std::unordered_set<std::string> mySet = get_applicants("students.txt");
    auto myqueue = find_matches(mySet);
    if (myqueue.empty())
    {
        std::cout << "NO STUDENTFOUND.\n";
    }
    else
    {
        std::cout << *(myqueue.top()) << std::endl;
    }
    return 0;
}
