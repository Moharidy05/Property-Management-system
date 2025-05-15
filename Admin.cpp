#include "Admin.h"
#include "Property.h" // Include Property header for PropertyManagement
#include "RealEstatePortal.h" // Include RealEstatePortal header for creating an instance
#include"User.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits> // Required for numeric_limits

using namespace std; // Included as requested

// Constructor definition
Admin::Admin(int id, string uname, string pwd, string mail, string ph)
    : User(id, uname, pwd, mail, ph)
{
    // Constructor body if needed
}
// Member function definitions
Admin* Admin::login(vector<Admin>& admins) {
    string inputUsername, inputPassword;
    cout << "Enter admin username: \n";
    cin.ignore();
    getline(cin, inputUsername);
    cout << "Enter admin password: \n";
    getline(cin, inputPassword);

    for (Admin& admin : admins) {
        if (admin.username == inputUsername && admin.password == inputPassword) {
            cout << "\nLogin successful.\n";
            return &admin;
        }
    }

    cout << "\nInvalid credentials. Access denied.\n";
    return nullptr;
}

void Admin::showDashboard() {
   
    cout << "\n----- Admin Dashboard -----\n";
    cout << "1. Show all users\n";
    cout << "2. Manage users\n";
    cout << "3. Approve a property\n";
    cout << "4. Manage properties \n";
    cout << "5. Manage Admin profile\n";
    cout << "6. Exit\n";
}

void Admin::listUsers(const vector<User>& users) {
    system("cls"); // Clear the console (Windows specific)
    cout << "\n--- All Users ---\n";
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    for (const User& user : users) {
        cout << "ID: " << user.userId
             << ", Username: " << user.username
             << ", Email: " << user.email
             << ", Active: " << (user.active ? "Yes" : "No") << '\n';
    }
 
}

void Admin::approveListing(unordered_map<int, Property>& properties) {
    system("cls"); // Clear the console (Windows specific)
    cout << "-------- List of Unapproved Properties --------\n";
    bool foundUnapproved = false;
    for (const auto& entry : properties) {
        const Property& p = entry.second;
        if (!p.approved) {
            foundUnapproved = true;
            cout << "------------------------------------\n";
            cout << "Property ID: " << p.id << "\n"
                 << "Location: " << p.location << "\n"
                 << "Price: " << p.price << "\n"
                 << "Description: " << p.description << "\n"
                 << "Bedrooms: " << p.bedrooms << "\n";
        }
    }

    if (!foundUnapproved) {
        cout << "No unapproved properties found.\n";
        return;
    }

    int choice;
    cout << "Enter the property ID you want to approve (or 0 to cancel): ";
    cin >> choice;

    if (cin.fail()) { // Handle non-integer input
        cout << "Invalid input. Please enter a number.\n";
        cin.clear(); // Clear the error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
        return;
    }

    if (choice == 0) {
        cout << "Approval cancelled.\n";
        return;
    }

    auto it = properties.find(choice);
    if (it != properties.end()) {
        if (!it->second.approved) {
            it->second.approved = true;
            cout << "Property " << choice << " approved successfully.\n";
        } else {
            cout << "Property " << choice << " is already approved.\n";
        }
    } else {
        cout << "Invalid property ID.\n";
    }
     // Clear the rest of the line after reading the ID
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
     
}

void Admin::addUser(vector<User>& users) {
    // Create a temporary RealEstatePortal instance to use its registerUser function
    // Note: This creates a new portal instance each time. If users need to be persistent
    // across admin sessions, you would need to pass the main users vector to this function.
    system("cls"); // Clear the console (Windows specific)
    string uname, pwd, email, phone;
    int id;
    cout << "Enter user ID: ";
    cin >> id;
    for(User user : users){
        if(user.userId == id){
            cout << "User ID already exists.\n";
            return;
        }
    }
    cin.ignore();
    cout << "Enter username: ";
    getline(cin, uname);
    cout << "Enter password: ";
    getline(cin, pwd);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone (optional): ";
    getline(cin, phone);
    User user(id, uname, pwd, email, phone);
    users.push_back(user);
    cout << "User added successfully.\n";
}

void Admin::removeUser(vector<User>& users) {
    system("cls"); // Clear the console (Windows specific)
    cout << "\n--- Remove User ---\n";
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    cout << "Registered users:\n";
    for (const User& user : users) {
        cout << "User ID: " << user.userId << ", Username: " << user.username << "\n";
    }
    int id;
    cout << "Enter user id you want to remove : \n";
    cin >> id;
    // Clear the newline character
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->userId == id) {
            users.erase(it);
            cout << "User with ID " << id << " removed successfully.\n";
            return; // Exit after removing
        }
    }
    cout << "User with ID " << id << " not found.\n";
}

void Admin::disableUser(vector<User>& users) {
    system("cls"); // Clear the console (Windows specific)
    cout << "\n--- Disable User ---\n";
    int userId;
    cout << "Enter user id you want to deactivate : \n";
    cin >> userId;
    // Clear the newline character
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (User& user : users) {
        if (user.userId == userId) {
            user.active = false;
            cout << "User " << user.username << " has been disabled.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void Admin::manageProfile() {
    system("cls"); // Clear the console (Windows specific)
    int choice;
    while (true) {
        cout << "\n--- Manage Admin Profile ---\n";
        cout << "1. View profile\n";
        cout << "2. Edit profile\n";
        cout << "3. Change password\n";
        cout << "4. Go back <-\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) { // Handle non-integer input
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            continue; // Go back to the start of the loop
        }

        if (choice == 4) {
            break; // Exit the loop
        }

        switch (choice) {
            case 1:
                viewProfile(); // Inherited from User
                break;
            case 2:
                editProfile(); // Inherited from User
                break;
            case 3:
                changePassword(); // Inherited from User
                break;
            default:
                cout << "Enter a valid option \n";
                break;
        }
         // Add a small delay or prompt to continue
        // cout << "Press Enter to continue...";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // cin.get(); // Wait for user to press Enter
    }
}

void Admin::manageUser(vector<User>& users) {
    system("cls"); // Clear the console (Windows specific)
    int choice;
    while (true) {
        cout << "\n--- Manage Users Menu ---\n";
        cout << "1. Disable a user\n";
        cout << "2. Remove a user\n";
        cout << "3. Add a user\n";
        cout << "4. Go back <-\n"; // Changed to 4 for consistency
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) { // Handle non-integer input
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            continue; // Go back to the start of the loop
        }

        if (choice == 4) { // Changed to 4 for consistency
            break; // Exit the loop
        }

        switch (choice) {
            case 1:
                disableUser(users);
                break;
            case 2:
                removeUser(users);
                break;
            case 3:
                addUser(users); // Note: This uses a new RealEstatePortal instance.
                break;
            default:
                cout << "Enter a valid option \n";
                break;
        }
         // Add a small delay or prompt to continue
        // cout << "Press Enter to continue...";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // cin.get(); // Wait for user to press Enter
    }
}


void Admin::handleActions(vector<User>& users, unordered_map<int, Property>& properties, const vector<Admin>& admins) {
    
    system("cls"); // Clear the console (Windows specific)
    int choice;
    PropertyManagement propertyManager; // Create an instance of PropertyManagement
    
    while (true) {
        showDashboard();
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail()) { // Handle non-integer input
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            continue; // Go back to the start of the loop
        }

        if (choice == 6) { // Exit option
            break;
        }

        // Clear the newline character after reading choice, before potential getline in called functions
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        switch (choice) {
            case 1:
                listUsers(users);
                break;
            case 2:
                manageUser(users); // Pass the users vector
                break;
            case 3:
                approveListing(properties); // Pass the properties map
                break;
            case 4:
                propertyManager.manageProperties(this->userId,properties); // Use the propertyManager instance
                break;
            case 5:
                manageProfile(); // Manage the current Admin's profile
                break;
            default:
                cout << "Enter a valid option \n";
                break;
        }
         // Add a small delay or prompt to continue
        // cout << "Press Enter to continue...";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // cin.get(); // Wait for user to press Enter
    }
}


