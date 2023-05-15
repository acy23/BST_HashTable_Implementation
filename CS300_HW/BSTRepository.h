#ifndef BST_H
#define BST_H

#include <iostream>
using namespace std;

template <typename T>
class BST {
public:
    BST();
    ~BST();

    void insert(T* data);
    T* getByID(int id);
    T* getByFullName(string firstName, string lastName);
    void remove(int id);
    void display();

private:
    struct BSTNode {
        T* data;
        BSTNode* left;
        BSTNode* right;
    };

    BSTNode* root;

    void destroy(BSTNode* node);
    //BSTNode* insert(BSTNode* node, T* data);
    BSTNode* remove(BSTNode* node, int id);
    BSTNode* minValueNode(BSTNode* node);
    void displayHelper(BSTNode* node, int level);
};

#endif // BST_H