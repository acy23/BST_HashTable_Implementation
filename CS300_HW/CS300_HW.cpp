#include <iostream>
#include <fstream>

#include "BSTRepository.cpp"

#include "HashTableRepository.h";

#include <string>
#include <chrono>

using namespace std;

struct UserData {

    UserData()
    {
            
    }

    int id;
    string firstName;
    string lastName;
    string phoneNumber;
    string city;

    // Operator overloading 
    friend ostream& operator<<(ostream& os, const UserData *data) {
        os << "ID: " << data->id << ", Name: " << data->firstName << " " << data->lastName << ", Phone Number: " << data->phoneNumber << ", City: " << data->city;
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
    int itemCount = 0;

    string line;
    string firstName, lastName, phoneNumber, city;

    while (file >> firstName >> lastName >> phoneNumber >> city) {
        
        itemCount++;
        // Create a UserData object
        UserData *data = new UserData;
        data->id = userId; 
        data->firstName = firstName;
        data->lastName = lastName;
        data->phoneNumber = phoneNumber;
        data->city = city;

        // Insert the UserData object into the BST
        bst.insert(data);

        // Insert the UserData object into the hash table
        hashtable.insert(data);
        
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

    string firstname , lastname;
    cout << "Enter full name: ";
    cin >> firstname >> lastname;

    string inputFirstname = firstname;
    string inputLastname = lastname;

    //cout << hashData << endl;
    //cout << bstData << endl;

    int k = 500;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++) {
        UserData *bstData = bst.getByFullName(inputFirstname, inputLastname);
    }

    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "\nTime: " << BSTTime.count() / k << "\n";
    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < k; i++) {
        UserData* hashTableData = hashTable.getByFullName(inputFirstname, inputLastname);
    }

    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);

    std::cout << "\nTime: " << HTTime.count() / k << "\n";

    return 0;
}
