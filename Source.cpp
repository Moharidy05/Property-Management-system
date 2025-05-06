
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct Property {
    int id;
    string location;
    float price;
    string description;
    int bedrooms;
    bool isHighlighted = false;

    void display() {
        cout << "ID: " << id << "\nLocation: " << location << "\nPrice: " << price
            << "\nDescription: " << description << "\nBedrooms: " << bedrooms
            << "\nHighlighted: " << (isHighlighted ? "Yes" : "No") << "\n";
    }
};

unordered_map<int, Property> properties;

void addProperty() {
    Property p;
    cout << "Enter Property ID: "; cin >> p.id;
    cout << "Enter Location: "; cin.ignore(); getline(cin, p.location);
    cout << "Enter Price: "; cin >> p.price;
    cout << "Enter Description: "; cin.ignore(); getline(cin, p.description);
    cout << "Enter Number of Bedrooms: "; cin >> p.bedrooms;
    properties[p.id] = p;
    cout << "Property added successfully.\n";
}

void removeProperty() {
    int id;
    cout << "Enter Property ID to remove: ";
    cin >> id;

    if (properties.erase(id)) {
        cout << "Property removed successfully.\n";
    }
    else {
        cout << "Property not found.\n";
    }
}

void editProperty() {
    int id;
    cout << "Enter Property ID to edit: ";
    cin >> id;
    auto it = properties.find(id);
    if (it != properties.end()) {
        Property& p = it->second;
        cout << "Enter new price: "; cin >> p.price;
        cout << "Enter new description: "; cin.ignore(); getline(cin, p.description);
        cout << "Edit successful.\n";
    }
    else {
        cout << "Property not found.\n";
    }
}

void highlightProperty() {
    int id;
    cout << "Enter Property ID to highlight: ";
    cin >> id;
    auto it = properties.find(id);
    if (it != properties.end()) {
        it->second.isHighlighted = true;
        cout << "Property highlighted.\n";
    }
    else {
        cout << "Property not found.\n";
    }
}

void displayAllProperties() {
    for (auto& pair : properties) {
        pair.second.display();
        cout << "------------------------\n";
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Property\n2. Remove Property\n3. Edit Property\n4. Highlight Property\n5. Display All Properties\n0. Exit\nChoose: ";
        cin >> choice;

        switch (choice) {
        case 1: addProperty(); break;
        case 2: removeProperty(); break;
        case 3: editProperty(); break;
        case 4: highlightProperty(); break;
        case 5: displayAllProperties(); break;
        case 0: return 0;
        default: cout << "Invalid choice.\n";
        }
    }
}
