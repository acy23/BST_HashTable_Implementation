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

    int TABLE_SIZE = 6000;

private:
    struct HashTableNode {
        T data;
        int key;
        HashTableNode* next;
    };

    std::vector<HashTableNode*> table;

    int hashFunction(int key);
};

template<typename T>
HashTable<T>::HashTable() {
    table = std::vector<HashTableNode*>(TABLE_SIZE, nullptr);
}

template<typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
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
    return key % TABLE_SIZE;
}

template<typename T>
void HashTable<T>::insert(T data) {
    int key = data.id; // Assuming 'id' is the integer key in the UserData struct

    int index = hashFunction(key);

    HashTableNode* newNode = new HashTableNode;
    newNode->data = data;
    newNode->key = key;
    newNode->next = nullptr;

    if (table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        HashTableNode* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

template<typename T>
T HashTable<T>::getByID(int id) {
    int index = hashFunction(id);

    HashTableNode* current = table[index];
    while (current != nullptr) {
        if (current->key == id) {
            return current->data;
        }
        current = current->next;
    }

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
    for (int i = 0; i < TABLE_SIZE; i++) {
        std::cout << "[" << i << "] ";
        HashTableNode* current = table[i];
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
}

#endif // HASHTABLE_H
