#include <set>
#include <string>

class User
{
public:
    // TODO: write special member functions, including default constructor!
    User();                                  // default constructor
    ~User();                                 // destructor
    User(const User &u);                     // copy constructor
    User &operator=(const User &u) = delete; // copy assignment operator
    User(User &&u);                          // move constructor
    User &operator=(User &&u);               // move assignment operator
    User(std::string name);

    // getter functions
    std::string getName() const;
    std::set<User> &getFriends();
    const std::set<User> &getFriends() const;

    // setter functions
    void setName(std::string name);

    // TODO: add the < operator overload here!
    bool operator<(const User &others) const;

private:
    std::string name;
    std::set<User> friends;
};