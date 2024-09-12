#include "user.h"
#include <set>
#include <iostream>
#include <string>

User::User() : name("")
{
}

User::~User()
{
}

User::User(const User &u) : name(u.name), friends(u.friends)
{
}

User::User(User &&u) : name(std::move(u.name)), friends(std::move(u.friends))
{
}

User &User::operator=(User &&u)
{
    // TODO: insert return statement here
    if (this != &u)
    {
        name = std::move(u.name);
        friends = std::move(u.friends);
    }
    return *this;
}

User::User(std::string name) : name(name)
{
    // TODO: Implement the additional constructor here!
}

std::string User::getName() const
{
    return name;
}

std::set<User> &User::getFriends()
{
    return friends;
}

// A const version is needed to allow read-only access to the friends set!
const std::set<User> &User::getFriends() const
{
    return friends;
}

void User::setName(std::string name)
{
    this->name = name;
}

// TODO: Implement the < operator overload here!
// set一般插入元素时，默认使用关键字类型的< 运算符来比较两个关键字，故一般插入后为升序!
// set 存储元素不重复！
bool User::operator<(const User &others) const
{
    return name < others.name;

    /*
        // 原始方法
        const std::string &str1 = name;
        const std::string &str2 = others.getName();
        int len1 = str1.length();
        int len2 = str2.length();
        int minLen = std::min(len1, len2);
        for (int i = 0; i < minLen; i++)
        {
            if (str1[i] < str2[i])
            {
                return true;
            }
            else if (str1[i] > str2[i])
            {
                return false;
            }
        }
        if (len1 < len2)
        {
            return true;
        }
        else
        {
            return false;
        }*/
}