#include "HashTableRepository.h";

//int TABLE_SIZE = 6000;
//
//// Constructor
//template<typename T>
//HashTable<T>::HashTable() {
//    table = std::vector<HashTableNode*>(TABLE_SIZE, nullptr);
//}
//
//// Destructor
//template<typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        HashTableNode* current = table[i];
//        while (current != nullptr) {
//            HashTableNode* temp = current;
//            current = current->next;
//            delete temp;
//        }
//    }
//}
//
//// Hash function to generate index
//template<typename T>
//int HashTable<T>::hashFunction(int key) {
//    return key % TABLE_SIZE;
//}
//
//// Insert a new data item into the hash table
//template<typename T>
//void HashTable<T>::insert(T data) {
//    int key = data.getId();
//    int index = hashFunction(key);
//
//    HashTableNode* newNode = new HashTableNode;
//    newNode->data = data;
//    newNode->key = key;
//    newNode->next = nullptr;
//
//    // If no nodes exist at the current index, insert the new node
//    if (table[index] == nullptr) {
//        table[index] = newNode;
//    }
//    else {
//        // Otherwise, traverse the linked list and insert at the end
//        HashTableNode* current = table[index];
//        while (current->next != nullptr) {
//            current = current->next;
//        }
//        current->next = newNode;
//    }
//}
//
//// Retrieve data item from the hash table based on its ID
//template<typename T>
//T HashTable<T>::getByID(int id) {
//    int index = hashFunction(id);
//
//    // Traverse the linked list at the current index to find the data item
//    HashTableNode* current = table[index];
//    while (current != nullptr) {
//        if (current->key == id) {
//            return current->data;
//        }
//        current = current->next;
//    }
//
//    // If the data item is not found, throw an exception
//    throw std::runtime_error("Data item not found.");
//}
//
//// Remove data item from the hash table based on its ID
//template<typename T>
//void HashTable<T>::remove(int id) {
//    int index = hashFunction(id);
//
//    // Traverse the linked list at the current index to find the data item to remove
//    HashTableNode* current = table[index];
//    HashTableNode* prev = nullptr;
//    while (current != nullptr) {
//        if (current->key == id) {
//            // Remove the data item from the linked list
//            if (prev == nullptr) {
//                table[index] = current->next;
//            }
//            else {
//                prev->next = current->next;
//            }
//            delete current;
//            return;
//        }
//        prev = current;
//        current = current->next;
//    }
//
//    // If the data item is not found, throw an exception
//    throw std::runtime_error("Data item not found.");
//}
//
//// Display the contents of the hash table
//template<typename T>
//void HashTable<T>::display() {
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        std::cout << "[" << i << "] ";
//        HashTableNode* current = table[i];
//        while (current != nullptr) {
//            std::cout << current->data << " -> ";
//            current = current->next;
//        }
//        std::cout << "nullptr" << std::endl;
//    }
//}
