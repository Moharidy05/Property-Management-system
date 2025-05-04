// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include <string>



class User; // Forward declaration

class Property {
public:
    User* listedBy;
    int id;
    string title;
    string location;
    double price;
    int bedrooms;
    float squareFootage;
    string propertyType;

    Property(User* user, int pid, const string& t, const string& loc,
        double pr, int beds, float sqft, const string& type)
        : listedBy(user), id(pid), title(t), location(loc),
        price(pr), bedrooms(beds), squareFootage(sqft), propertyType(type) {}
};


#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

vector<Property> searchProperties(
    const unordered_map<int, Property>& properties,
    const string& locationFilter,
    double minPrice,
    double maxPrice,
    int minBedrooms,
    const string& typeFilter,
    float minSquareFootage,
    float maxSquareFootage)
{
    vector<Property> results;

    for (const auto& pair : properties) {
        const Property& p = pair.second;

        bool locationMatch = locationFilter.empty() || p.location == locationFilter;
        bool priceMatch = p.price >= minPrice && p.price <= maxPrice;
        bool bedroomsMatch = p.bedrooms >= minBedrooms;
        bool typeMatch = typeFilter.empty() || p.propertyType == typeFilter;
        bool squareFootageMatch = p.squareFootage >= minSquareFootage && p.squareFootage <= maxSquareFootage;

        if (locationMatch && priceMatch && bedroomsMatch && typeMatch && squareFootageMatch) {
            results.push_back(p);
        }
    }

    return results;
}

/*

using namespace std;

int main() {
    unordered_map<int, Property> properties;

    
    User* user1 = nullptr; 

    
    properties[1] = Property(user1, 1, "Modern Apartment", "Cairo", 250000, 3, 1200.5, "Apartment");
    properties[2] = Property(user1, 2, "Cozy Villa", "Giza", 500000, 4, 2000.0, "Villa");


    vector<Property> results = searchProperties(properties, "Cairo", 200000, 300000, 2, "",10,888);

    // Display results
    for (const auto& p : results) {
        cout << "ID: " << p.id << ", Title: " << p.title
            << ", Location: " << p.location << ", Price: " << p.price
            << ", Bedrooms: " << p.bedrooms << ", Type: " << p.propertyType << endl;
    }

    return 0;
}*/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
