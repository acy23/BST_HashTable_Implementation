#include <iostream>
#include <fstream>

#include "BSTRepository.cpp"

#include "HashTableRepository.h";

using namespace std;

struct UserData {
    
    int id;
    string firstName;
    string lastName;
    string phoneNumber;
    string city;

    // Operator overloading 
    friend ostream& operator<<(ostream& os, const UserData& data) {
        os << "ID: " << data.id << ", Name: " << data.firstName << " " << data.lastName << ", Phone Number: " << data.phoneNumber << ", City: " << data.city;
        return os;
    }
};


template<typename T>
void insertFromFile(HashTable<T>& hashtable, BST<T>& bst, const string& filename, float loadFactorThreshold) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Failed to open file.");
    }

    int previousCapacity = hashtable.getCapacity();
    int previousItemCount = hashtable.size();

    int userId = 1;

    string line;
    string firstName, lastName, phoneNumber, city;

    while (file >> firstName >> lastName >> phoneNumber >> city) {

        // Create a UserData object
        UserData data;
        data.id = userId; 
        data.firstName = firstName;
        data.lastName = lastName;
        data.phoneNumber = phoneNumber;
        data.city = city;

        // Insert the UserData object into the BST
        bst.insert(data);

        // Insert the UserData object into the hash table
        hashtable.insert(data);

        // Calculate the current load factor
        float currentLoadFactor = static_cast<float>(hashtable.size()) / hashtable.getCapacity();

        // Check if the load factor exceeds the threshold
        if (currentLoadFactor > loadFactorThreshold) {
            // Rehash the hash table
            int newTableSize = hashtable.getCapacity() * 2;  // Double the table size

            // Print the rehashing information
            cout << "Rehashing occurred." << endl;
            cout << "Previous Capacity: " << previousCapacity << ", Previous Load: " << currentLoadFactor << endl;
            cout << "Current Capacity: " << newTableSize << ", Current Load: " << currentLoadFactor << endl;
            cout << "Number of Items: " << hashtable.size() << endl;
            cout << endl;

            previousCapacity = newTableSize;
            previousItemCount = hashtable.size();
        }

        userId++;
    }

    file.close();

    // Print the final item count and load factor
    float finalLoadFactor = static_cast<float>(hashtable.size()) / hashtable.getCapacity();
    cout << "Processing finished." << endl;
    cout << "Final Item Count: " << hashtable.size() << endl;
    cout << "Final Load Factor (λ): " << finalLoadFactor << endl;
}

int main()
{
    BST<UserData> bst;
    HashTable<UserData> hashTable;

    // Customly setting the id prop in the UserData struct.
    int userId = 1;

    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    // Reading file.
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Error: could not open file '" << filename << "'." << endl;
        return 1;
    }
    
    insertFromFile(hashTable, bst, filename, 0.7);

    //int id;
    //string firstName;
    //string lastName;
    //string phoneNumber;
    //string city;

    //// Creating data structures.
    //while (inputFile >> firstName >> lastName >> phoneNumber >> city) {
    //    UserData data = { id = userId, firstName, lastName, phoneNumber, city };
    //    userId++;
    //    bst.insert(data);
    //    hashTable.insert(data);
    //}

    UserData data = hashTable.getByID(175);
    cout << data << endl;

    return 0;
}
