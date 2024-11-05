#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "manager.hh"

void PasswordManager::encryptFile() {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        for (const auto &password: passwords) {
            file.write(reinterpret_cast<const char *>(&password), sizeof(password));
        }
        file.close();
    } else {
        std::cout << "[ERROR]: Couldn't save file.\n";
    }
}

void PasswordManager::decryptFile() {
    passwords.clear();

    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        while (!file.eof()) {
            Password password;
            file.read(reinterpret_cast<char *>(&password), sizeof(password));
            if (!file.eof()) {
                passwords.push_back(password);
            }
        }
        file.close();
    } else {
        std::cout << "[ERROR]: Couldn't read file.\n";
    }
}

bool PasswordManager::isPasswordUsed(const std::string &password) const {
    for (const auto &entry: passwords) {
        if (entry.password == password) {
            return true;
        }
    }
    return false;
}


PasswordManager::PasswordManager(const std::string &file) : filename(file) {
    decryptFile();
}

void PasswordManager::searchPasswords(const std::string &query) const {
    std::cout << "Searched passwords:\n";

    for (const auto &password: passwords) {
        if (password.name.find(query) != std::string::npos ||
            password.password.find(query) != std::string::npos ||
            password.category.find(query) != std::string::npos ||
            password.website.find(query) != std::string::npos ||
            password.login.find(query) != std::string::npos) {

            std::cout << "Name: " << password.name << std::endl;
            std::cout << "Password: " << password.password << std::endl;
            std::cout << "Category: " << password.category << std::endl;
            std::cout << "Website: " << password.website << std::endl;
            std::cout << "Login: " << password.login << std::endl;
            std::cout << std::endl;
        }
    }
}

void PasswordManager::sortPasswords(const std::vector<std::string> &fields) {
    std::vector<Password> result = passwords;

    sort(result.begin(), result.end(), [&fields](const Password &firstPasswd, const Password &secondPasswd) -> bool {
        for (const auto &field: fields) {
            if (field == "name") {
                if (firstPasswd.name != secondPasswd.name) {
                    return firstPasswd.name < secondPasswd.name;
                }
            } else if (field == "password") {
                if (firstPasswd.password != secondPasswd.password) {
                    return firstPasswd.password < secondPasswd.password;
                }
            } else if (field == "category") {
                if (firstPasswd.category != secondPasswd.category) {
                    return firstPasswd.category < secondPasswd.category;
                }
            } else if (field == "website") {
                if (firstPasswd.website != secondPasswd.website) {
                    return firstPasswd.website < secondPasswd.website;
                }
            } else if (field == "login") {
                if (firstPasswd.login != secondPasswd.login) {
                    return firstPasswd.login < secondPasswd.login;
                }
            }
        }
        return false;
    });

    std::cout << "Sorted passwords:\n";

    for (const auto &password: result) {
        std::cout << "Name: " << password.name << std::endl;
        std::cout << "Password: " << password.password << std::endl;
        std::cout << "Category: " << password.category << std::endl;
        std::cout << "Website: " << password.website << std::endl;
        std::cout << "Login: " << password.login << std::endl;
        std::cout << std::endl;
    }
}

std::string PasswordManager::randomPassword(int length, bool upperCase, bool lowerCase, bool specialChar) const {
    srand(time(NULL));
    const std::string lowerChars = "abcdefghijklmnopqrstuvwxyz";
    const std::string upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string specialChars = "!@#$%^&*()-+=~`;:'?/";

    std::string combinedChars;

    if (upperCase) {
        combinedChars += upperChars;
    }
    if (lowerCase) {
        combinedChars += lowerChars;
    }
    if (specialChar) {
        combinedChars += specialChars;
    }

    std::string result;

    int combinedCharsLength = combinedChars.length();

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % combinedCharsLength;
        result += combinedChars[randomIndex];
    }

    return result;

}


void PasswordManager::printVector() {
    std::cout << "Available categories: " << std::endl;
    for (const auto &category: categories) {
        std::cout << "* " << category << std::endl;
    }
}

void PasswordManager::addPassword() {
    Password password;
    std::cout << "Adding new password:" << std::endl;

    do {
        std::cout << "Name: ";
        getline(std::cin, password.name);
    } while (password.name.empty());

    std::cout << "Do you want to generate random password? [y/n]: ";
    char generateChoice;
    std::cin >> generateChoice;
    tolower(generateChoice);
    std::cin.ignore();

    if (generateChoice == 'y') {
        int length;
        bool includeUppercase, includeLowercase, includeSpecialChars;

        std::cout << "Password length: ";
        std::cin >> length;
        std::cin.ignore();

        std::cout << "Include uppercase letters? [y/n]: ";
        char upperChoice;
        std::cin >> upperChoice;
        std::cin.ignore();
        tolower(upperChoice);
        includeUppercase = (upperChoice == 'y');

        std::cout << "Include lowercase letters? [y/n]: ";
        char lowerChoice;
        std::cin >> lowerChoice;
        std::cin.ignore();
        tolower(lowerChoice);
        includeLowercase = (lowerChoice == 'y');

        std::cout << "Include special characters? [y/n]: ";
        char specialChoice;
        std::cin >> specialChoice;
        std::cin.ignore();
        tolower(specialChoice);
        includeSpecialChars = (specialChoice == 'y');

        password.password = randomPassword(length, includeUppercase, includeLowercase, includeSpecialChars);
    } else if (generateChoice == 'n') {
        do {
            std::cout << "Password: ";
            getline(std::cin, password.password);
            if (isPasswordUsed(password.password)) {
                std::cout << "Password is already used and can be unsafe.\n";
            }
        } while (password.password.empty());
    } else {
        std::cout << "Error. \n";
    }

    std::cout << "Do you want to add category that has been already created? [y/n]: ";
    char categoryChoice;
    std::cin >> categoryChoice;
    tolower(categoryChoice);
    std::cin.ignore();
    if (categoryChoice == 'y') {
        printVector();
        std::cout << "Category: ";
        getline(std::cin, password.category);
    } else {
        do {
            std::cout << "Category: ";
            getline(std::cin, password.category);
        } while (password.category.empty());
    }

    std::cout << "Website (optional): ";
    getline(std::cin, password.website);

    std::cout << "Login (optional): ";
    getline(std::cin, password.login);

    passwords.push_back(password);
    encryptFile();
}

void PasswordManager::editPassword() {
    std::string name;
    std::cout << "Enter name of the password to edit: ";
    getline(std::cin, name);

    bool found = false;

    for (auto &password: passwords) {
        if (password.name == name) {
            std::cout << "Editing password:" << std::endl;
            std::cout << "Name: " << password.name << std::endl;

            std::cout << "New name (click enter if stays the same): ";
            getline(std::cin, name);
            if (!name.empty()) {
                password.name = name;
            }

            std::cout << "New password (click enter if stays the same): ";
            getline(std::cin, password.password);

            std::cout << "New category (click enter if stays the same): ";
            getline(std::cin, password.category);

            std::cout << "New website (click enter if stays the same): ";
            getline(std::cin, password.website);

            std::cout << "New login (click enter if stays the same): ";
            getline(std::cin, password.login);

            encryptFile();

            std::cout << "Password edited." << std::endl;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "[ERROR]: Password not found." << std::endl;
    }
}

void PasswordManager::removePassword() {
    std::string name;
    std::cout << "Enter the name of the password to delete: ";
    getline(std::cin, name);

    std::cout << "You are about to delete a password. Are you sure? [y/n]: " << std::endl;
    char confirmation;
    std::cin >> confirmation;
    tolower(confirmation);
    std::cin.ignore();

    if (confirmation == 'y') {
        auto it = remove_if(passwords.begin(), passwords.end(), [&name](const Password &password) {
            return password.name == name;
        });

        if (it != passwords.end()) {
            passwords.erase(it, passwords.end());
            encryptFile();
            std::cout << "Password deleted." << std::endl;
        } else {
            std::cout << "[ERROR]: Password not found." << std::endl;
        }
    } else {
        std::cout << "Operation canceled." << std::endl;
    }
}

void PasswordManager::addCategory() {
    std::string category;
    std::cout << "Enter name of the category: ";
    getline(std::cin, category);
    categories.push_back(category);

    std::cout << "Category added." << std::endl;
}

void PasswordManager::removeCategory() {
    std::string category;
    std::cout << "Enter name of the category to delete: ";
    getline(std::cin, category);

    auto it = remove_if(passwords.begin(), passwords.end(), [&category](const Password &password) {
        return password.category == category;
    });
    passwords.erase(it, passwords.end());
    encryptFile();

    std::cout << "Category deleted." << std::endl;


}

bool fileExists(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}

void printMenu() {
    std::cout << R"(
  /$$$$$$   /$$$$$$  /$$      /$$
 /$$__  $$ /$$__  $$| $$  /$ | $$
| $$  \__/| $$  \ $$| $$ /$$$| $$
| $$      | $$$$$$$$| $$/$$ $$ $$
| $$      | $$__  $$| $$$$_  $$$$
| $$    $$| $$  | $$| $$$/ \  $$$
|  $$$$$$/| $$  | $$| $$/   \  $$
 \______/ |__/  |__/|__/     \__/
    )";
    std::cout << "\nCAW is a possibly secure password manager.";
    std::cout << "\nIt has support for tags, websites, logins etc!";
    std::cout << "\nIt also inhibits *some* sort of security (but";
    std::cout << "\ndon't rely on it.) Enjoy the password manager!\n\n";
}

int main() {
    std::string filename;
    int choice;
    std::string query;
    std::vector<std::string> sortFields;
    char input;
    printMenu();
    std::cout << "% ";
    getline(std::cin, filename);
    std::cout << std::endl;

    PasswordManager manager(filename);

    if (!fileExists(filename)) {
        std::cout << "[ERROR]: File doesn't exist.\n";
        return 1;
    }

    while (1) {
        std::cout << "1. Search password" << std::endl;
        std::cout << "2. Sort password" << std::endl;
        std::cout << "3. Add password" << std::endl;
        std::cout << "4. Edit password" << std::endl;
        std::cout << "5. Delete password" << std::endl;
        std::cout << "6. Add category" << std::endl;
        std::cout << "7. Delete category" << std::endl;
        std::cout << "8. Close program" << std::endl;

        std::cout << "\n% ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter query: ";
                getline(std::cin, query);
                manager.searchPasswords(query);
                std::cout << "Type q to continue: ";
                std::cin >> input;
                tolower(input);
                if (input == 'q')
                    break;
            case 2:
                sortFields.clear();
                while (true) {
                    std::string field;
                    std::cout << "Enter field/fields to sort (type q to close): ";
                    getline(std::cin, field);
                    if (field == "q" || field == "Q") {
                        break;
                    }
                    sortFields.push_back(field);
                }
                manager.sortPasswords(sortFields);
                std::cout << "Type q to continue: ";
                std::cin >> input;
                tolower(input);
                if (input == 'q')
                    break;
            case 3:
                manager.addPassword();
                break;
            case 4:
                manager.editPassword();
                break;
            case 5:
                manager.removePassword();
                break;
            case 6:
                manager.addCategory();
                break;
            case 7:
                manager.removeCategory();
                break;
            case 8:
                return 0;
            default:
                std::cout << "Invalid option." << std::endl;
                break;
        }
        std::cout << std::endl;
    }
}
