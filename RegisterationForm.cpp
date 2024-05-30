#include <fmx.h>
#include <fstream>
#include <sstream>
#include <iostream>
#pragma hdrstop

#include "RegisterationForm.h"
#include "User.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"

TMyRegistrationForm *MyRegistrationForm;

__fastcall TMyRegistrationForm::TMyRegistrationForm(TComponent* Owner)
    : TForm(Owner), root(nullptr)
{
    loadUsers();
}

void TMyRegistrationForm::insert(User* &node, std::string name, int age, std::string username, std::string password) {
    if (node == nullptr) {
        node = new User(name, age, username, password);
    } else if (username < node->username) {
        insert(node->left, name, age, username, password);
    } else {
        insert(node->right, name, age, username, password);
	}
}

User* TMyRegistrationForm::search(User* node, std::string username, std::string password) {
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

void TMyRegistrationForm::saveToFile(User* user) {
	std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << user->name << "," << user->age << "," << user->username << "," << user->password << "\n";
        file.close();
        StatusLabel->Text = "Information Saved";
    } else {
        StatusLabel->Text = "Failed to open file!";
    }
}

void TMyRegistrationForm::saveToPortfolio(User* user) {
    std::ofstream file("portfolio.txt", std::ios::app);
    if (file.is_open()) {
        file << user->name << " "
             << user->age << " "
             << user->username << " "
			 << user->password << " "
             << user->balance << " "
             << user->totalStock << "\n";
        file.close();
        StatusLabel->Text = "Information Saved to Portfolio";
    } else {
        StatusLabel->Text = "Failed to open portfolio file!";
    }
}

void TMyRegistrationForm::loadUsers() {
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

std::string TMyRegistrationForm::encrypt(std::string data) {
    for (char &c : data) {
        c += 3; // simple Caesar cipher for demonstration
    }
    return data;
}

std::string TMyRegistrationForm::decrypt(std::string data) {
    for (char &c : data) {
        c -= 3; // reverse Caesar cipher
    }
    return data;
}

void __fastcall TMyRegistrationForm::SaveButtonClick(TObject *Sender) {
    std::string name = AnsiString(NameEdit->Text).c_str();
    int age = StrToInt(AgeEdit->Text);
    std::string username = AnsiString(UsernameEdit->Text).c_str();
    std::string password = AnsiString(PasswordEdit->Text).c_str();

    std::string encryptedUsername = encrypt(username);
	std::string encryptedPassword = encrypt(password);

    User* newUser = new User(name, age, encryptedUsername, encryptedPassword);
    insert(root, name, age, username, password);
    saveToFile(newUser);
    saveToPortfolio(newUser);

    NameEdit->Text = "";
	AgeEdit->Text = "";
    UsernameEdit->Text = "";
    PasswordEdit->Text = "";
}




