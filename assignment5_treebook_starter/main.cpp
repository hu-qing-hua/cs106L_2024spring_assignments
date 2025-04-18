#include <iostream>
#include "User.h"

// TODO: Implement the non-member function + operator overload here!
User &operator+(User &a, User &b)
{
    a.getFriends().insert(b.getName());
    b.getFriends().insert(a.getName());
    return a;
}

void printFriends(const User &user)
{
    std::cout << user.getName() << " is friends with: " << std::endl;
    for (auto &user : user.getFriends())
    {
        std::cout << "  " << user.getName() << std::endl;
    }
}

int main()
{
    // create a bunch of users
    User alice("Alice");
    User bob("Bob");
    User charlie("Charlie");
    User dave("Dave");

    // make them friends
    alice + bob;
    alice + charlie;

    dave + bob;
    charlie + dave;

    // print out their friends
    printFriends(alice);
    printFriends(bob);
    printFriends(charlie);
    printFriends(dave);

    return 0;
}