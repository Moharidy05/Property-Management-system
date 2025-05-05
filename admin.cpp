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

   
    void showDashboard() {
        cout << "\n----- Admin Dashboard -----\n";
        cout << "1. Show all users\n";
        cout << "2. Approve pending listings\n";
        cout << "3. Disable a user\n";
        cout << "4. Exit\n";
    }

   
    void addUser(User u) {
        users.push_back(u);
    }

  
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

    
    void approveListings() {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].hasPendingListing) {
                users[i].hasPendingListing = false;
                cout << "Listing approved for user: " << users[i].username << '\n';
            }
        }
    }

   
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

  
    void handleActions() {
        int choice;
        while (true) {
            showDashboard();
            cout << "\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) listUsers();
            else if (choice == 2) approveListings();
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
int main() {
    Admin admin;

    // بيانات تجريبية للمستخدمين
    admin.addUser({ 1, "Ali", "ali@mail.com", true, true });
    admin.addUser({ 2, "Sara", "sara@mail.com", true, false });
    admin.addUser({ 3, "Omar", "omar@mail.com", true, true });

    if (admin.login()) {
        admin.handleActions();
    }

    return 0;
}


