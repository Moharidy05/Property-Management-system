void compareProperties(const unordered_map<int, Property>& properties, const vector<int>& propertyIds) {
    if (propertyIds.size() > 4) {
        cout << "You can only compare up to 4 properties at once.\n";
        return;
    }

    cout << "Comparing Properties:\n";
    cout << left << setw(15) << "Field";

    // Print property headers
    for (int id : propertyIds) {
        if (properties.find(id) != properties.end()) {
            cout << setw(25) << ("Property ID " + to_string(id));
        }
        else {
            cout << setw(25) << ("[ID " + to_string(id) + " Not Found]");
        }
    }
    cout << endl;

    // Define the fields to compare
    vector<string> fields = { "Location", "Price", "Bedrooms", "Type", "Square Ft" };

    // Print each field for all properties
    for (const string& field : fields) {
        cout << left << setw(15) << field;
        for (int id : propertyIds) {
            auto it = properties.find(id);
            if (it != properties.end()) {
                const Property& p = it->second;
                if (field == "Location") cout << setw(25) << p.location;
                else if (field == "Price") cout << setw(25) << p.price;
                else if (field == "Bedrooms") cout << setw(25) << p.bedrooms;
                else if (field == "Type") cout << setw(25) << p.propertyType;
                else if (field == "Square Ft") cout << setw(25) << p.squareFootage;
            }
            else {
                cout << setw(25) << "N/A";
            }
        }
        cout << endl;
    }
}
