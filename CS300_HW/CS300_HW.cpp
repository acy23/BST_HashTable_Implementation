#include <iostream>
#include <fstream>

#include "BSTRepository.h"
#include "BSTRepository.cpp"

#include "HashTableRepository.h";
#include "HashTableRepository.cpp";

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
    
    int id;
    string firstName;
    string lastName;
    string phoneNumber;
    string city;

    // Creating data structures.
    while (inputFile >> firstName >> lastName >> phoneNumber >> city) {
        UserData data = { id = userId, firstName, lastName, phoneNumber, city };
        userId++;
        bst.insert(data);
        hashTable.insert(data);
    }

    UserData data = hashTable.getByID(2);
    cout << data << endl;

    return 0;
}
