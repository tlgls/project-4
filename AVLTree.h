// Tree Template Implementation
// Authored by Antonio Flores 11/19/2024

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <map>

using namespace std;

template <typename KeyType, typename ValueType>
class AVLTree {
private:
// This structure represents a node in the AVL Tree
struct AVLNode {
        KeyType key;  
        map<ValueType, int> values;  
        AVLNode* left;  
        AVLNode* right;  
        int height;  
           //This is the constructor for the AVL node
        // Constructor for the AVLNode
        AVLNode(const KeyType& key, const ValueType& value)
        : key(key), height(0), left(nullptr), right(nullptr) {
        this->values[value] = 1;  // Initializes frequency count
        }
    };

private:
    AVLNode* root;  
    int nodeCount;  

    // Private function declarations
    void clear(AVLNode*& node);

    map<ValueType, int> getNodeData(const KeyType& key, AVLNode* node);

    void insertNode(const KeyType& key, const ValueType& val, AVLNode*& node);

    void insertNode(const KeyType& key, const ValueType& val, int frequency, AVLNode*& node);

    void balanceTree(AVLNode*& node);

    int getNodeHeight(AVLNode* node);

    void deepCopyTree(AVLNode*& dest, AVLNode* src);

    void rotateLeft(AVLNode*& node);

    void rotateRight(AVLNode*& node);

    void rotateDoubleLeft(AVLNode*& node);

    void rotateDoubleRight(AVLNode*& node);

    void printTree(ostream& out, AVLNode* node);

public:
    // constructor
    AVLTree();  
    //Copy constructor
    AVLTree(const AVLTree& other);  
    // Destructor
    ~AVLTree();  

    //Public Funtion Declarations
    AVLTree& operator=(const AVLTree& other);  

    void clear();

    map<ValueType, int> getNode(const KeyType& key) const;

    void insert(const KeyType& key, const ValueType& val);

    int getSize() const;

    void printTree(ostream& out) const;
};

#include "AVLTree.cpp"  

#endif 
