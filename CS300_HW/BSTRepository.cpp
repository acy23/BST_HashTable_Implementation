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

// Recursively destroy the binary search tree
template <typename T>
void BST<T>::destroy(BSTNode* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Insert a node into the binary search tree
template <typename T>
void BST<T>::insert(T data) {
    root = insert(root, data);
}

// Recursively insert a node into the binary search tree
template <typename T>
typename BST<T>::BSTNode* BST<T>::insert(BSTNode* node, T data) {
    if (node == nullptr) {
        node = new BSTNode;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
    }
    else if (data.id < node->data.id) {
        node->left = insert(node->left, data);
    }
    else if (data.id > node->data.id) {
        node->right = insert(node->right, data);
    }
    else {
        // Node with same id already exists, do nothing
    }

    return node;
}

template <typename T>
T BST<T>::getByID(int id) {
    BSTNode* current = root;
    while (current != nullptr) {
        if (current->data.id == id) {
            return current->data;
        }
        else if (id < current->data.id) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    throw runtime_error("ID not found in the BST");
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
    else if (id < node->data.id) {
        node->left = remove(node->left, id);
    }
    else if (id > node->data.id) {
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
            node->right = remove(node->right, temp->data.id);
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
