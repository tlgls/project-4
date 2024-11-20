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
        AVLNode(const key& k, const value& v)
            : k(k), height(0), left(nullptr), right(nullptr) {
            this->v[v] = 1; // Initializes frequency count
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

    map<ValueType, int> getNode(const KeyType& key);

    void insert(const KeyType& key, const ValueType& val);

    int getSize() const;

    void printTree(ostream& out);
};

#include "AVLTree.cpp"  

#endif 
