#ifndef BSTSET_H
#define BSTSET_H

#include "provided.h"
#include "support.h"

#include <iostream>
#include <algorithm>


using namespace std;
template <typename T>


class BSTSet {
private:
    struct Node {
        T* data;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& value) {
            data = new T(value);
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        ~Node() {
            delete data;
        }
    };

    Node* root;

public:
    BSTSet() {
        root = nullptr;
    }

    ~BSTSet() {
        clear(root);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    class SetIterator {
        Node* current;

    public:
        SetIterator() : current(nullptr) {}
        SetIterator(Node* node) : current(node) {}
        SetIterator(const SetIterator& other) = default;

        ~SetIterator() {
          
        }

        SetIterator& operator=(const SetIterator& other) {
            current = other.current;
            return *this;
        }

        bool operator==(const SetIterator& other) const {
            return current == other.current;
        }

        const T* get_and_advance() {
            if (!current) return nullptr;
            const T* temp = current->data;

            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                Node* parent = current->parent;
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return temp;
        }
    };

    void insert(const T& value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* cur = root;
        Node* parent = nullptr;
        while (cur) {
            parent = cur;
            if (value < *(cur->data)) {
                cur = cur->left;
            } else if (*(cur->data) < value) {
                cur = cur->right;
            } else {
                *(cur->data) = value;
                return;
            }
        }
        Node* newNode = new Node(value);
        newNode->parent = parent;

        if (value < *(parent->data)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    SetIterator find(const T& value) const {
        Node* current = root;
        while (current) {
            if (value == *(current->data)) {
                return SetIterator(current);
            } else if (value < *(current->data)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        cout << "Not found: " << value << endl;

        return SetIterator(nullptr);
    }

    SetIterator find_first_not_smaller(const T& value) const {
        Node* current = root;
        Node* candidate = nullptr;

        while (current) {
            if (value <= *(current->data)) {
                candidate = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
       
        return SetIterator(candidate);
    }
};

#endif
