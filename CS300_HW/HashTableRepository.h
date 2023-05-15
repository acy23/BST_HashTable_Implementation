#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

template <typename T>
class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(T data);
    T getByID(int id);
    void remove(int id);
    void display();

    int size() const;             // Return the number of items in the hash table
    int getCapacity() const;      // Return the current capacity of the hash table
private:
    struct HashTableNode {
        T data;
        int key;
        HashTableNode* next;
    };

    std::vector<HashTableNode*> table;
    int capacity;   // Current capacity of the hash table
    int itemCount;  // Number of items in the hash table

    int hashFunction(int key);
    void rehash();  // Rehash the hash table to increase the capacity
};

template<typename T>
HashTable<T>::HashTable() {
    capacity = 107;  // Set the initial capacity
    table = std::vector<HashTableNode*>(capacity, nullptr);
    itemCount = 0;
}

template<typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        HashTableNode* current = table[i];
        while (current != nullptr) {
            HashTableNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

template<typename T>
int HashTable<T>::hashFunction(int key) {
    return key % capacity;
}

template<typename T>
void HashTable<T>::insert(T data) {
    int key = data.id;
    int index = hashFunction(key);

    HashTableNode* newNode = new HashTableNode;
    newNode->data = data;
    newNode->key = key;
    newNode->next = nullptr;

    // If no nodes exist at the current index, insert the new node
    if (table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        // Otherwise, traverse the linked list and insert at the end
        HashTableNode* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    itemCount++;  // Increment the item count

    float loadFactor = static_cast<float>(itemCount) / capacity;
    if (loadFactor > 0.7f) {
        rehash();  // Rehash the hash table if the load factor exceeds the threshold
    }
}

template<typename T>
T HashTable<T>::getByID(int id) {
    int index = hashFunction(id);

    // Traverse the linked list at the current index to find the data item
    HashTableNode* current = table[index];
    while (current != nullptr) {
        if (current->key == id) {
            return current->data;
        }
        current = current->next;
    }

    // If the data item is not found, throw an exception
    throw std::runtime_error("Data item not found.");
}

template<typename T>
void HashTable<T>::remove(int id) {
    int index = hashFunction(id);

    HashTableNode* current = table[index];
    HashTableNode* prev = nullptr;
    while (current != nullptr) {
        if (current->key == id) {
            if (prev == nullptr) {
                table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }

    throw std::runtime_error("Data item not found.");
}

template<typename T>
void HashTable<T>::display() {
    for (int i = 0; i < capacity; i++) {
        std::cout << "[" << i << "] ";
        HashTableNode* current = table[i];
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
}

template<typename T>
int HashTable<T>::size() const {
    return itemCount;
}

template<typename T>
int HashTable<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void HashTable<T>::rehash() {
    int newCapacity = capacity * 2;  // Double the capacity
    std::vector<HashTableNode*> newTable(newCapacity, nullptr);

    // Reinsert all the elements into the new table
    for (int i = 0; i < capacity; i++) {
        HashTableNode* current = table[i];
        while (current != nullptr) {
            HashTableNode* next = current->next;
            int newIndex = current->key % newCapacity;
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            current = next;
        }
    }

    table = std::move(newTable);  // Move the new table into the member variable
    capacity = newCapacity;       // Update the capacity
}



#endif // HASHTABLE_H
