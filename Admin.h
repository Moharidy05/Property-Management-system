#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map> // For using unordered_map
#include "User.h" // Include the User header since Admin inherits from User
#include "Property.h" // Include Property header for approveListing and manageProperties


using namespace std; // Included as requested (Note: Generally avoided in header files)

// Forward declaration for RealEstatePortal if needed (though including the header is fine here)
// class RealEstatePortal;

class Admin : public User {
public:
    // Constructor declaration
    Admin(int id, string uname, string pwd, string mail, string ph = "");

    // Member function declarations
    static Admin* login(vector<Admin>& admins);
    void showDashboard();
    void listUsers(const vector<User>& users);
    void approveListing(unordered_map<int, Property>& properties);
    void addUser(vector<User>&users); // Declared here, implementation will be in .cpp
    void removeUser(vector<User>& users);
    void disableUser(vector<User>& users);
    void manageProfile(); // Declared here, implementation will be in .cpp
    void manageUser(vector<User>& users); // Declared here, implementation will be in .cpp
    void handleActions(vector<User>& users, unordered_map<int, Property>& properties, const vector<Admin>& admins);
    void activateUser(vector<User>& users);
};

#endif // ADMIN_H
