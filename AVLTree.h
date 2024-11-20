// Tree Template Implementation
// Authored by Antonio Flores 11/19/2024

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <map>
using namespace std;

template <typename key, typename value>
class AVLTree {
private:

    // This structure represents a node in the AVL Tree
    struct AVLNode {
        key k;
        map<value, int> v;
        int height;
        AVLNode* left;
        AVLNode* right;

        //This is the constructor for the AVL node
        AVLNode(const key& k, const value& v)
            : k(k), height(0), left(nullptr), right(nullptr) {
            this->v[v] = 1; // Initializes frequency count
        }
    };

    AVLNode* root;
    int size;

    // Private function declarations

    void clear(AVLNode*& n);

    map<value, int> getNode(const key&, AVLNode*& n);

    void insert(const key&, const value&, AVLNode*& n);

    void insert(const key&, const value&, const int&, AVLNode*& n);

    void balance(AVLNode*& n);

    int height(AVLNode* n);

    void clone(AVLNode*& thisNode, AVLNode* copyNode);

    void rotateLeft(AVLNode*& n);

    void rotateRight(AVLNode*& n);

    void rotateDoubleLeft(AVLNode*& n);

    void rotateDoubleRight(AVLNode*& n);

    void printTree(ostream&, AVLNode*& n);

public:
    // Constructor
    AVLTree();
    // Copy constructor
    AVLTree(const AVLTree& other);
    // Destructor
    ~AVLTree();

    AVLTree& operator=(const AVLTree& other);

    // These are the public function declarations
    void clear();

    void insert(const key&, const value&);

    void insert(const key&, const value&, const int&);

    map<value, int> getNode(const key&);

    int getSize() const;

    void printTree(ostream&);
};


#include "AVLTree.cpp"

#endif
