#include <fmx.h>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma hdrstop

#include "LoginForm.h"
#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

TMyLoginForm *MyLoginForm;

__fastcall TMyLoginForm::TMyLoginForm(TComponent* Owner)
    : TForm(Owner), root(nullptr)
{
    // Initialize the user list by loading users from the file
    loadUsers();
}

void TMyLoginForm::insert(User* &node, std::string name, int age, std::string username, std::string password) {
    if (node == nullptr) {
        node = new User(name, age, username, password);
    } else if (username < node->username) {
        insert(node->left, name, age, username, password);
    } else {
        insert(node->right, name, age, username, password);
    }
}

User* TMyLoginForm::search(User* node, std::string username, std::string password) {
    if (node == nullptr) {
        return nullptr;
    } else if (username == node->username && password == node->password) {
        return node;
    } else if (username < node->username) {
        return search(node->left, username, password);
    } else {
        return search(node->right, username, password);
    }
}

void TMyLoginForm::loadUsers() {
    std::ifstream file("users.txt");
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, username, password;
            int age;
            std::getline(ss, name, ',');
            ss >> age;
            ss.ignore(); // ignore the comma
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');

            std::string decryptedUsername = decrypt(username);
            std::string decryptedPassword = decrypt(password);

            insert(root, name, age, decryptedUsername, decryptedPassword);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading." << std::endl;
    }
}

std::string TMyLoginForm::decrypt(std::string data) {
    for (char &c : data) {
        c -= 3; // reverse Caesar cipher
    }
    return data;
}

void __fastcall TMyLoginForm::LoginButtonClick(TObject *Sender) {
    std::string username = AnsiString(UsernameEdit->Text).c_str();
    std::string password = AnsiString(PasswordEdit->Text).c_str();

    User* found = search(root, username, password);
    if (found) {
		StatusLabel->Text = "Login Successful";
		MyInterfaceForm->Show();

    } else {
        StatusLabel->Text = "Login Failed";
    }
}




