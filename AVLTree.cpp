#include "AVLTree.h"


template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLTree() : root(nullptr), nodeCount(0) {}

template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::~AVLTree() {
    clear();
}

template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>::AVLTree(const AVLTree& other) : root(nullptr), nodeCount(0) {
    deepCopyTree(root, other.root);
}

// This is an assignment operator to copy the contents of one AVLTree to another.
template <typename KeyType, typename ValueType>
AVLTree<KeyType, ValueType>& AVLTree<KeyType, ValueType>::operator=(const AVLTree& other) {
    // This prevents asigning something to itself
    if (this != &other) {
        clear();
        deepCopyTree(root, other.root);
    }
    return *this;
}

// Insert a new node with a key into the AVL tree
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& val) {
    insertNode(key, val, root);
}

template <typename KeyType, typename ValueType>
map<ValueType, int> AVLTree<KeyType, ValueType>::getNode(const KeyType& key) {
    return getNodeData(key, root);
}

template <typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::getSize() const {
    return nodeCount;
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::clear() {
    clear(root);
    nodeCount = 0;
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::clear(AVLNode*& node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }
}
// Function to insert a node into the tree while keeping balance 
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insertNode(const KeyType& key, const ValueType& val, AVLNode*& node) {
    if (node == nullptr) {
        node = new AVLNode(key, val); // Creates a new node if position is empty
        nodeCount++;
    } else if (key < node->key) {
        insertNode(key, val, node->left); // This recursively inserts into the left subtree
    } else if (key > node->key) {
        insertNode(key, val, node->right);
    } else {
        node->values[val]++; // If we find the key exists, then we update the frequency
    }
    balanceTree(node);
}
// Insert a node with a specific frequency for the value
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::insertNode(const KeyType& key, const ValueType& val, int frequency, AVLNode*& node) {
    if (node == nullptr) {
        node = new AVLNode(key, val); //Creates new node if empty
        node->values[val] = frequency; // initializes node with given frequencu
        nodeCount++;
    } else if (key < node->key) {
        insertNode(key, val, frequency, node->left);
    } else if (key > node->key) {
        insertNode(key, val, frequency, node->right);
    } else {
        node->values[val] = frequency; // If the key exist we set the frequency
    }
    balanceTree(node);
}

template <typename KeyType, typename ValueType>
map<ValueType, int> AVLTree<KeyType, ValueType>::getNodeData(const KeyType& key, AVLNode* node) {
    if (node == nullptr) {
        return map<ValueType, int>();
    } else if (key < node->key) {
        return getNodeData(key, node->left);
    } else if (key > node->key) {
        return getNodeData(key, node->right);
    } else {
        return node->values;
    }
}
// Function to balance AVL Tree
template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::balanceTree(AVLNode*& node) {
    if (node == nullptr) return;
    //checks for left impalance 
    if (getNodeHeight(node->left) - getNodeHeight(node->right) > 1) {
        if (getNodeHeight(node->left->left) >= getNodeHeight(node->left->right)) {
            rotateLeft(node); 
        } else {
            rotateDoubleLeft(node); 
        }
        //checks for right inbalance
    } else if (getNodeHeight(node->right) - getNodeHeight(node->left) > 1) {
        if (getNodeHeight(node->right->right) >= getNodeHeight(node->right->left)) {
            rotateRight(node);
        } else {
            rotateDoubleRight(node);
        }
    }
    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

template <typename KeyType, typename ValueType>
int AVLTree<KeyType, ValueType>::getNodeHeight(AVLNode* node) {
    return node == nullptr ? 0 : node->height;
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateLeft(AVLNode*& node) {
    AVLNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
    node = temp;
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateRight(AVLNode*& node) {
    AVLNode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
    node = temp;
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateDoubleLeft(AVLNode*& node) {
    rotateRight(node->left);
    rotateLeft(node);
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::rotateDoubleRight(AVLNode*& node) {
    rotateLeft(node->right);
    rotateRight(node);
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::deepCopyTree(AVLNode*& dest, AVLNode* src) {
    if (src != nullptr) {
        dest = new AVLNode(src->key, src->values.begin()->first);
        deepCopyTree(dest->left, src->left);
        deepCopyTree(dest->right, src->right);
        nodeCount++;
    }
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::printTree(ostream& out, AVLNode* node) {
    if (node != nullptr) {
        printTree(out, node->left);
        out << node->key;
        for (const auto& item : node->values) {
            out << "; " << item.first << "," << item.second;
        }
        out << endl;
        printTree(out, node->right);
    }
}

template <typename KeyType, typename ValueType>
void AVLTree<KeyType, ValueType>::printTree(ostream& out) {
    printTree(out, root);
}
