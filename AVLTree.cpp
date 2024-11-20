#include "AVLTree.h"

// Constructor
template <typename key, typename value>
AVLTree<key, value>::AVLTree() : root(nullptr), size(0) {}

// Copy constructor
template <typename key, typename value>
AVLTree<key, value>::AVLTree(const AVLTree& other) : root(nullptr), size(0) {
    clone(root, other.root);
}

// Destructor
template <typename key, typename value>
AVLTree<key, value>::~AVLTree() {
    clear();
}

// Assignment operator
template <typename key, typename value>
AVLTree<key, value>& AVLTree<key, value>::operator=(const AVLTree& other) {
    if (this != &other) {
        clear();
        clone(root, other.root);
    }
    return *this;
}

// Clears the tree
template <typename key, typename value>
void AVLTree<key, value>::clear() {
    clear(root);
    size = 0;
}

// Clears the tree recursively
template <typename key, typename value>
void AVLTree<key, value>::clear(AVLNode*& n) {
    if (n != nullptr) {
        clear(n->left);
        clear(n->right);
        delete n;
        n = nullptr;
    }
}

// Insert function (without frequency)
template <typename key, typename value>
void AVLTree<key, value>::insert(const key& k, const value& v) {
    insert(k, v, root);
}

// Insert function (with frequency)
template <typename key, typename value>
void AVLTree<key, value>::insert(const key& k, const value& v, AVLNode*& n) {
    if (n == nullptr) {
        n = new AVLNode(k, v);
        size++;
    } else if (k < n->k) {
        insert(k, v, n->left);
    } else if (k > n->k) {
        insert(k, v, n->right);
    } else {
        n->v[v]++;
    }
    balance(n);
}

// Insert function with frequency
template <typename key, typename value>
void AVLTree<key, value>::insert(const key& k, const value& v, const int& freq, AVLNode*& n) {
    if (n == nullptr) {
        n = new AVLNode(k, v);
        n->v[v] = freq;
        size++;
    } else if (k < n->k) {
        insert(k, v, freq, n->left);
    } else if (k > n->k) {
        insert(k, v, freq, n->right);
    } else {
        n->v[v] = freq;
    }
    balance(n);
}

// Retrieve the node's map of values by key
template <typename key, typename value>
map<value, int> AVLTree<key, value>::getNode(const key& k) const {
    return getNode(k, root);
}

// Retrieve the node's map of values by key (helper function)
template <typename key, typename value>
map<value, int> AVLTree<key, value>::getNode(const key& k, AVLNode* n) const {
    if (n == nullptr) {
        return map<value, int>();
    } else if (k < n->k) {
        return getNode(k, n->left);
    } else if (k > n->k) {
        return getNode(k, n->right);
    } else {
        return n->v;
    }
}

// Get the size of the tree
template <typename key, typename value>
int AVLTree<key, value>::getSize() const {
    return size;
}

// Get the height of a node
template <typename key, typename value>
int AVLTree<key, value>::height(AVLNode* n) const {
    return n == nullptr ? -1 : n->height;
}

// Balance the tree after insertion
template <typename key, typename value>
void AVLTree<key, value>::balance(AVLNode*& n) {
    if (n == nullptr) return;

    if (height(n->left) - height(n->right) > 1) {
        if (height(n->left->left) >= height(n->left->right)) {
            rotateRight(n);
        } else {
            rotateDoubleRight(n);
        }
    } else if (height(n->right) - height(n->left) > 1) {
        if (height(n->right->right) >= height(n->right->left)) {
            rotateLeft(n);
        } else {
            rotateDoubleLeft(n);
        }
    }
    n->height = max(height(n->left), height(n->right)) + 1;
}

// Rotate left function
template <typename key, typename value>
void AVLTree<key, value>::rotateLeft(AVLNode*& n) {
    AVLNode* temp = n->right;
    n->right = temp->left;
    temp->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    temp->height = max(height(temp->right), n->height) + 1;
    n = temp;
}

// Rotate right function
template <typename key, typename value>
void AVLTree<key, value>::rotateRight(AVLNode*& n) {
    AVLNode* temp = n->left;
    n->left = temp->right;
    temp->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    temp->height = max(height(temp->left), n->height) + 1;
    n = temp;
}

// Double rotate left function
template <typename key, typename value>
void AVLTree<key, value>::rotateDoubleLeft(AVLNode*& n) {
    rotateRight(n->right);
    rotateLeft(n);
}

// Double rotate right function
template <typename key, typename value>
void AVLTree<key, value>::rotateDoubleRight(AVLNode*& n) {
    rotateLeft(n->left);
    rotateRight(n);
}

// Clone function (to copy another AVL tree)
template <typename key, typename value>
void AVLTree<key, value>::clone(AVLNode*& thisNode, AVLNode* copyNode) {
    if (copyNode == nullptr) {
        thisNode = nullptr;
    } else {
        thisNode = new AVLNode(copyNode->k, value()); // Dummy value, actual map copied below
        thisNode->v = copyNode->v;
        thisNode->height = copyNode->height;
        clone(thisNode->left, copyNode->left);
        clone(thisNode->right, copyNode->right);
    }
}

// Print tree in-order
template <typename key, typename value>
void AVLTree<key, value>::printTree(ostream& os) const {
    printTree(os, root);
}

// Print tree recursively (helper function)
template <typename key, typename value>
void AVLTree<key, value>::printTree(ostream& os, AVLNode* n) const {
    if (n != nullptr) {
        printTree(os, n->left);
        os << n->k;
        for (const auto& [val, freq] : n->v) {
            os << " -> [" << val << ", " << freq << "]";
        }
        os << endl;
        printTree(os, n->right);
    }
}
