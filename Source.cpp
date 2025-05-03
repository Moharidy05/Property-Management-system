#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct User {
    string name;
    string password;
    string phone;
    string role;
    bool active;
};


class UserManager {
private:
    map<string, User> users;
    string currentUser;

    void saveUsers() {
        ofstream file("users.txt");
        for (const auto& userPair : users) {
            file << userPair.first << " "
                << userPair.second.name << " "
                << userPair.second.password << " "
                << userPair.second.phone << " "
                << userPair.second.role << " "
                << userPair.second.active << "\n";
        }
    }

    void loadUsers() {
        ifstream file("users.txt");
        if (!file) return;

        string email;
        User user;
        while (file >> email >> user.name >> user.password
            >> user.phone >> user.role >> user.active) {
            users[email] = user;
        }
    }

    bool isUsernameTaken(const string& username) {
        for (const auto& userPair : users) {
            if (userPair.second.name == username) {
                return true;
            }
        }
        return false;
    }

    bool verifyCurrentPassword(const string& email, const string& password) {
        return users[email].password == password;
    }

    void viewProfile() {
        if (currentUser.empty()) {
            cout << "Not logged in!\n";
            return;
        }

        User& user = users[currentUser];
        cout << "\nProfile\nName: " << user.name
            << "\nEmail: " << currentUser
            << "\nPhone: " << user.phone
            << "\nRole: " << user.role << "\n";
    }

    void editProfile() {
        if (currentUser.empty()) {
            cout << "Not logged in!\n";
            return;
        }

        User& user = users[currentUser];
        cout << "\nEdit Profile\nCurrent name: " << user.name << "\nNew name: ";
        cin >> user.name;
        cout << "Current phone: " << user.phone << "\nNew phone: ";
        cin >> user.phone;
        cout << "Profile updated!\n";
    }

    void logout() {
        currentUser = "";
        cout << "Logged out.\n";
    }


public:
    UserManager() { loadUsers(); }
    ~UserManager() { saveUsers(); }

    bool registerUser() {
        string email;
        User newUser;

        cout << "\nRegistration\n";
        cout << "Email: ";
        cin >> email;




        if (users.count(email)) {
            cout << "Email already exists!\n";
            return false;
        }

        cout << "Name: ";
        cin >> newUser.name;




        cout << "Password: ";
        cin >> newUser.password;





        cout << "Phone: ";
        cin >> newUser.phone;





        cout << "Role (buyer/seller): ";
        cin >> newUser.role;





        newUser.active = true;
        users[email] = newUser;
        cout << "Registration successful!\n";
        return true;
    }

    bool login() {
        string email, password;
        cout << "\nLogin\nEmail: ";
        cin >> email;


        cout << "Password: ";
        cin >> password;



        if (!users.count(email) || users[email].password != password) {
            cout << "Invalid username or password!\n";
            return false;
        }

        if (!users[email].active) {
            cout << "Account inactive!\n";
            return false;
        }

        currentUser = email;
        cout << "Welcome, " << users[email].name << "!\n";
        return true;
    }

    bool changeUsername() {
        if (currentUser.empty()) {
            cout << "Not logged in!\n";
            return false;
        }


        string newUsername;
        cout << "\nEnter new username: ";
        cin >> newUsername;



        if (isUsernameTaken(newUsername)) {
            cout << "Username already taken! Please choose another.\n";
            return false;
        }


        users[currentUser].name = newUsername;
        saveUsers();
        cout << "Username changed successfully to: " << newUsername << "\n";
        return true;
    }

    bool changePassword() {
        if (currentUser.empty()) {
            cout << "Not logged in!\n";
            return false;
        }

        string currentPass, newPass, confirmPass;
        cout << "\nChange Password\n";

        cout << "Enter current password: ";
        cin >> currentPass;



        if (!verifyCurrentPassword(currentUser, currentPass)) {
            cout << "Incorrect current password!\n";
            return false;
        }

        cout << "Enter new password: ";
        cin >> newPass;



        cout << "Confirm new password: ";
        cin >> confirmPass;



        if (newPass != confirmPass) {
            cout << "Passwords don't match!\n";
            return false;
        }

        if (newPass.length() < 8) {
            cout << "Password must be at least 8 characters!\n";
            return false;
        }

        users[currentUser].password = newPass;
        saveUsers();
        cout << "Password changed successfully!\n";
        return true;
    }
    void manageProfile() {
        int c;
        do {
            cout << endl << "I. View Profile "
                << endl << "II. Edit Profile"
                << endl << "III. Change Username"
                << endl << "V. Change Password "
                << endl << "Choice: ";
            cin >> c;

            switch (c) {
            case 1: viewProfile(); break;
            case 2: editProfile(); break;
            case 3: changeUsername(); break;
            case 4: changePassword(); break;
            default: cout << "Invalid choice!\n";
            }
        } while (c != 0);
    }   

    void showMenu() {
        int choice;
        do {
            cout << endl << "1. Register "
                << endl << "2. Login"
                << endl << "3. Manage Profile"
                << endl << "4. Logout "
                << endl << "0. Exit "
                << endl << "Choice: ";
            cin >> choice;

            switch (choice) {
            case 1: registerUser(); break;
            case 2: login(); break;
            case 3:manageProfile();
            case 4: logout(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    UserManager manager;
    manager.showMenu();
    return 0;
}