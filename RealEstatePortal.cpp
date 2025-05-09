#include "RealEstatePortal.h"
#include "User.h" // Assuming you have a user.h header file
// #include "admin.h" // Uncomment if you have an admin.h header file
#include"Admin.h"
#include"Property.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <limits> // Required for numeric_limits

using namespace std; // Included as requested

// Implementation of the RealEstatePortal class member functions

/*
// Uncomment and implement if you need to load/save users from/to a file
void RealEstatePortal::loadUsers() {
    ifstream file(USERS_FILE);
    if (!file) return;

    while (file.peek() != EOF) {
        User user(0, "", "", "", "", ""); // Assuming User constructor takes id, username, password, email, phone, role
        user.loadFromFile(file); // You would need to implement User::loadFromFile
        users.push_back(user);
        nextUserId = max(nextUserId, user.userId + 1);
        // Consume the rest of the line after loading a user if necessary
        // file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}

void RealEstatePortal::saveUsers() {
    ofstream file(USERS_FILE);
    for (const auto& user : users) {
        user.saveToFile(file); // You would need to implement User::saveToFile
    }
    file.close();
}

RealEstatePortal::RealEstatePortal() {
    loadUsers();
}

RealEstatePortal::~RealEstatePortal() {
    saveUsers();
}
*/
RealEstatePortal::RealEstatePortal(vector<User> u, vector<Admin> ad, unordered_map<int, Property> prop)
    : users(u), admins(ad), properties(prop) {
    // Constructor body if needed
}

bool RealEstatePortal::registerUser() {
    string username, password, email, phone;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone: ";
    getline(cin, phone);
    

    for (const auto& user : users) {
        if (user.phone == phone || user.username == username) {
            cout << "Username or phone number already exists!\n";
            return false;
        }
    }
    users.emplace_back(nextUserId++, username, password, email, phone); // Assuming User constructor matches this signature

    cout << "Registration successful!\n";
    return true;
}

User* RealEstatePortal::login(string username, string password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            cout << "Login successful!\n";
            return &user;
        }
    }
    cout << "Invalid username or password!\n";
    return nullptr;
}

void RealEstatePortal::run() {
    int choice;

    while (true) {
        cout << "\n=== Real Estate Portal ===\n";
        cout << "Login as : \n 1.Admin \n 2.User\n";
        cin>>choice;
        if(choice==1)
        {
            Admin* admin=Admin::login(admins);

            if(admin != nullptr){
                admin->handleActions(users,properties,admins);
            }
            else{
                return;
            }
        }
        else if(choice==2){ 
            cout << "1. Register\n2. Login\n3. Exit\nChoose an option: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Use ignore with limits to clear the buffer

            if (choice == 3) {
                break;
            }

            switch (choice) {
                case 1: {
                    registerUser();
                    break;
                }

                case 2: {
                    string username, password;
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    User* loggedInUser = login(username, password);
                    if (loggedInUser) {
                        while (true) {
                            cout << "\n=== User Dashboard ===\n";
                            cout << "1. View Profile\n2. Edit Profile\n3. Change password\n4. Logout\nChoose an option: ";
                            cin >> choice;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer


                            if (choice == 4) { // Changed to 4 for logout as per menu
                                break;
                            }

                            switch (choice) {
                                case 1:
                                    loggedInUser->viewProfile(); // You need to implement User::viewProfile()
                                    break;
                                case 2:
                                    loggedInUser->editProfile(); // You need to implement User::editProfile()
                                    break;
                                case 3:
                                    loggedInUser->changePassword(); // You need to implement User::changePassword()
                                    break;
                                // Case 4 is handled by the outer if condition
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
        else{
            cout << "Invalid option!\n";
            return;
        }

    }
}
    

int main(){
    
        vector<Admin> admins;
        vector<User> users;
        unordered_map<int, Property> properties;
    
        cout << "Initializing Real Estate Portal...\n";
    
        // Create a default admin
        Admin admin(1, "saif hendy", "123", "seif@gmail.com", "01015709329");
        admins.push_back(admin);
    
        // Create some initial users
        User user1(1, "john_doe", "pass123", "john@example.com", "01012345678");
        User user2(2, "jane_doe", "secure456", "jane@example.com", "01087654321");
        users.push_back(user1);
        users.push_back(user2);
    
        // Create some initial properties
        properties = {
            {1, {1, "123 Main St, Anytown", 250000.0f, "A cozy 3-bedroom house in a quiet neighborhood.", 3, false, true}}, // Approved
            {2, {2, "456 Oak Ave, Somewhere City", 450000.0f, "Spacious downtown apartment with a view.", 2, true, true}},    // Approved and Highlighted
            {3, {3, "789 Pine Ln, Rural Area", 150000.0f, "Small cabin perfect for a weekend getaway.", 1, false, false}},  // Not Approved
            {4, {4, "101 Maple Dr, Suburbia", 320000.0f, "Family home with a large backyard.", 4, false, true}},          // Approved
            {5, {5, "222 Elm St, Downtown", 550000.0f, "Luxury penthouse with modern amenities.", 2, true, false}}       // Not Approved but Highlighted (might need logic adjustment if highlight requires approval)
        };

        RealEstatePortal portal( users,admins, properties);

        portal.run();
        

}