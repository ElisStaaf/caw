#ifndef PASSWORD_H
#define PASSWORD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

struct Password {
    std::string name;
    std::string password;
    std::string category;
    std::string website;
    std::string login;
};

class PasswordManager {
private:
    std::string filename;
    std::vector<Password> passwords;
    std::vector<std::string> categories;

    /* Function prototypes */
    void encryptFile();
    void decryptFile();
    bool isPasswordUsed(const std::string &password) const;
    std::string randomPassword(int length, bool upperCase, bool lowerCase, bool specialChar) const;

public:
    PasswordManager(const std::string &file);

    /* Function prototypes */
    void searchPasswords(const std::string &query) const;
    void sortPasswords(const std::vector<std::string> &firstPasswd);
    void addPassword();
    void editPassword();
    void removePassword();
    void addCategory();
    void removeCategory();
    void printVector();
};

#endif
