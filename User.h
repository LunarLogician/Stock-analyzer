#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string name;
    int age;
    std::string username;
    std::string password;
    double balance;
    int totalStock;
    User* left;
    User* right;

	User(std::string name, int age, std::string username, std::string password, double balance = 100.0, int totalStock = 500)
        : name(name), age(age), username(username), password(password), balance(balance), totalStock(totalStock), left(nullptr), right(nullptr) {}
};

#endif // USER_H

