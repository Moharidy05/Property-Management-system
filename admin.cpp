#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct User {
    int id;
    string username;
    string email;
    bool isActive;
    bool hasPendingListing;
};

class Admin {
private:
    string adminUsername = "admin";
    string adminPassword = "1234";
    vector<User> users;

public:
    // تسجيل الدخول
    bool login() {
        string username, password;
        cout << "Enter admin username: ";
        cin >> username;
        cout << "Enter admin password: ";
        cin >> password;

        if (username == adminUsername && password == adminPassword) {
            cout << "\nLogin successful!\n";
            return true;
        }
        else {
            cout << "\nInvalid credentials. Access denied.\n";
            return false;
        }
    }

    // عرض لوحة التحكم
    void showDashboard() {
        cout << "\n----- Admin Dashboard -----\n";
        cout << "1. Show all users\n";
        cout << "2. Approve a user's pending listing\n";
        cout << "3. Disable a user\n";
        cout << "4. Exit\n";
    }

    // إضافة مستخدم
    void addUser(User u) {
        users.push_back(u);
    }

    // عرض المستخدمين
    void listUsers() {
        cout << "\n--- All Users ---\n";
        for (int i = 0; i < users.size(); i++) {
            cout << "ID: " << users[i].id
                << ", Username: " << users[i].username
                << ", Email: " << users[i].email
                << ", Active: " << (users[i].isActive ? "Yes" : "No")
                << ", Pending Listing: " << (users[i].hasPendingListing ? "Yes" : "No")
                << '\n';
        }
    }

    // موافقة على إعلان مستخدم محدد
    void approveListingForUser(int userId) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].id == userId) {
                if (users[i].hasPendingListing) {
                    users[i].hasPendingListing = false;
                    cout << "Listing approved for user: " << users[i].username << '\n';
                }
                else {
                    cout << "User has no pending listings.\n";
                }
                return;
            }
        }
        cout << "User not found.\n";
    }

    // تعطيل مستخدم
    void disableUser(int userId) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].id == userId) {
                users[i].isActive = false;
                cout << "User " << users[i].username << " has been disabled.\n";
                return;
            }
        }
        cout << "User not found.\n";
    }

    // التعامل مع لوحة التحكم
    void handleActions() {
        int choice;
        while (true) {
            showDashboard();
            cout << "\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) listUsers();
            else if (choice == 2) {
                int id;
                cout << "Enter User ID to approve listing: ";
                cin >> id;
                approveListingForUser(id);
            }
            else if (choice == 3) {
                int id;
                cout << "Enter User ID to disable: ";
                cin >> id;
                disableUser(id);
            }
            else if (choice == 4) {
                cout << "Exiting...\n";
                break;
            }
            else cout << "Invalid choice. Try again.\n";
        }
    }
};
