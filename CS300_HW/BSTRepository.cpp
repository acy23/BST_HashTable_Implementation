#include "BSTRepository.h"

// Default constructor
template <typename T>
BST<T>::BST() {
    root = nullptr;
}

// Destructor
template <typename T>
BST<T>::~BST() {
    destroy(root);
}

template <typename T>
void BST<T>::destroy(BSTNode* node) {
    if (node == nullptr) {
        return;
    }

    BSTNode* current = node;
    BSTNode* temp;

    while (current != nullptr) {
        if (current->right != nullptr) {
            temp = current->right;
            delete current;
            current = temp;
        }
    }
}

// Insert a node into the binary search tree
template <typename T>
void BST<T>::insert(T* data) {
    BSTNode* newNode = new BSTNode;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    BSTNode* current = root;
    while (true) {
        if (data->id < current->data->id) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        }
        else if (data->id > current->data->id) {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
        else {
            // Node with the same id already exists, do nothing
            delete newNode; // Clean up the unused node
            return;
        }
    }
}

template <typename T>
T* BST<T>::getByID(int id) {
    BSTNode* current = root;
    while (current != nullptr) {
        if (current->data->id == id) {
            return current->data;
        }
        else if (id < current->data->id) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename T>
T* BST<T>::getByFullName(string firstName, string lastName) {
    BSTNode* current = root;
    while (current != nullptr) {
        if (current->data->firstName == firstName && current->data->lastName == lastName) {
            return current->data;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename T>
void BST<T>::remove(int id) {
    root = remove(root, id);
}

template <typename T>
typename BST<T>::BSTNode* BST<T>::remove(BSTNode* node, int id) {
    if (node == nullptr) {
        return node;
    }
    else if (id < node->data->id) {
        node->left = remove(node->left, id);
    }
    else if (id > node->data->id) {
        node->right = remove(node->right, id);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            BSTNode* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            BSTNode* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data->id);
        }
    }
    return node;
}

template <typename T>
typename BST<T>::BSTNode* BST<T>::minValueNode(BSTNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
void BST<T>::display()
{
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }

    displayHelper(root, 0);
}

template <typename T>
void BST<T>::displayHelper(BSTNode* node, int level)
{
    if (node == nullptr) {
        return;
    }

    displayHelper(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << node->data << endl;
    displayHelper(node->left, level + 1);
}


