#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    int userId;
    string username;
    string password;
    string email;

    User(int id, string uname, string pwd, string mail)
        : userId(id), username(uname), password(pwd), email(mail) {}

    void displayProfile() const {
        cout << "User ID: " << userId << "\nUsername: " << username
             << "\nEmail: " << email << "\n";
    }

    void saveToFile(ofstream& file) const {
        file << userId << " " << username << " " << password << " " << email << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> userId;
        file >> username >> password >> email;
    }
};

class RealEstatePortal {
private:
    vector<User> users;
    int nextUserId = 1;
    const string USERS_FILE = "users.txt";

public:
    void loadUsers() {
        ifstream file(USERS_FILE);
        if (!file) return;

        while (file.peek() != EOF) {
            User user(0, "", "", "");
            user.loadFromFile(file);
            users.push_back(user);
            nextUserId = max(nextUserId, user.userId + 1);
        }
        file.close();
    }

    void saveUsers() {
        ofstream file(USERS_FILE);
        for (const auto& user : users) {
            user.saveToFile(file);
        }
        file.close();
    }

    RealEstatePortal() {
        loadUsers();
    }

    ~RealEstatePortal() {
        saveUsers();
    }

    bool registerUser(string username, string password, string email) {
        for (const auto& user : users) {
            if (user.username == username) {
                cout << "Username already exists!\n";
                return false;
            }
        }
        users.emplace_back(nextUserId++, username, password, email);
        saveUsers();
        cout << "Registration successful!\n";
        return true;
    }

    User* login(string username, string password) {
        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                cout << "Login successful!\n";
                return &user;
            }
        }
        cout << "Invalid username or password!\n";
        return nullptr;
    }
};

int main() {
    RealEstatePortal portal;
    int choice;
    string username, password, email, newEmail, newPassword;

    while (true) {
        cout << "\n=== Real Estate Portal ===\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 3) {
            break;
        }

        switch (choice) {
        case 1:
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Enter email: ";
            getline(cin, email);
            portal.registerUser(username, password, email);
            break;

        case 2: {
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            User* loggedInUser = portal.login(username, password);
            if (loggedInUser) {
                while (true) {
                    cout << "\n=== User Dashboard ===\n";
                    cout << "1. View Profile\n2. Update Profile\n3. Logout\nChoose an option: ";
                    cin >> choice;
                    cin.ignore();

                    if (choice == 3) {
                        break;
                    }

                    switch (choice) {
                    case 1:
                        loggedInUser->displayProfile();
                        break;
                    case 2:
                        cout << "Enter new email (or press Enter to skip): ";
                        getline(cin, newEmail);
                        cout << "Enter new password (or press Enter to skip): ";
                        getline(cin, newPassword);
                        if (!newEmail.empty()) {
                            loggedInUser->email = newEmail;
                        }
                        if (!newPassword.empty()) {
                            loggedInUser->password = newPassword;
                        }
                        portal.saveUsers();
                        cout << "Profile updated successfully!\n";
                        break;
                    default:
                        cout << "Invalid option!\n";
                        break;
                    }
                }
            }
            break;
        }

        default:
            cout << "Invalid option!\n";
            break;
        }
    }

    return 0;
}
