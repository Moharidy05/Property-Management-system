#ifndef REALESTATEPORTAL_H
#define REALESTATEPORTAL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_map>  

#include "User.h"
#include "Admin.h"
#include "Property.h"

using namespace std;

// Forward declarations if needed (not strictly necessary now)
class User;

class RealEstatePortal {
public:
    vector<User> users;
    int nextUserId = 1;
    vector<Admin> admins;
    unordered_map<int, Property> properties;
    const string USERS_FILE = "users.txt";

    
    RealEstatePortal(vector<User> u, vector<Admin> ad, unordered_map<int, Property> prop);

    bool registerUser();
    User* login(string username, string password);
    void run();
};

#endif // REALESTATEPORTAL_H
