#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

enum Color
{
    RED,
    BLACK
};
template <typename T>
struct RBNode
{
    T value;
    Color color;
    RBNode<T> *left, *right, *parent;

    RBNode(const T &value) : value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RBTree
{
private:
    RBNode<T> *root;

public:
    RBTree() : root(nullptr) {}
    RBNode<T> *getRoot() const { return root; }

    void inOrder(RBNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        inOrder(node->left, items);
        items.push_back(node->value);
        inOrder(node->right, items);
    }

    void preOrder(RBNode<T> *node, vector<T> &items) const
    {
        if (node == nullptr)
            return;
        items.push_back(node->value);
        preOrder(node->left, items);
        preOrder(node->right, items);
    }

    void leftRotation(RBNode<T> *node)
    {
        RBNode<T> *newRoot = node->right;
        node->right = newRoot->left;
        if (newRoot->left != nullptr)
        {
            newRoot->left->parent = node;
        }
        newRoot->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = newRoot; // New root for the tree
        }
        else if (node == node->parent->left)
        {
            node->parent->left = newRoot;
        }
        else
        {
            node->parent->right = newRoot;
        }
        newRoot->left = node;
        node->parent = newRoot;
    }

    void rightRotation(RBNode<T> *node)
    {
        RBNode<T> *newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right != nullptr)
        {
            newRoot->right->parent = node;
        }
        newRoot->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = newRoot; // New root for the tree
        }
        else if (node == node->parent->left)
        {
            node->parent->left = newRoot;
        }
        else
        {
            node->parent->right = newRoot;
        }
        newRoot->right = node;
        node->parent = newRoot;
    }

    // find the leftmost node (which has the smallest value)
    RBNode<T> *findMin(RBNode<T> *node) const
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // find the rightmost node (which has the largest value)
    RBNode<T> *findMax(RBNode<T> *node) const
    {
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node;
    }

    // balance method after inserting a new node //
    void balance(RBNode<T> *node)
    {
        while (node != root && node->parent->color == RED)
        {
            if (node->parent == node->parent->parent->left)
            {
                // Uncle is right child
                RBNode<T> *uncle = node->parent->parent->right;
                if (uncle && uncle->color == RED)
                {
                    // Case 1: Uncle is red
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent; // Move up
                }
                else
                {
                    // Case 2: Uncle is black
                    if (node == node->parent->right)
                    {
                        node = node->parent; // Rotate left
                        leftRotation(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotation(node->parent->parent); // Rotate right
                }
            }
            else
            {
                // Symmetric case: Parent is right child
                RBNode<T> *uncle = node->parent->parent->left;
                if (uncle && uncle->color == RED)
                {
                    // Case 1: Uncle is red
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent; // Move up
                }
                else
                {
                    // Case 2: Uncle is black
                    if (node == node->parent->left)
                    {
                        node = node->parent; // Rotate right
                        rightRotation(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotation(node->parent->parent); // Rotate left
                }
            }
        }
        root->color = BLACK; // Ensure the root is black
    }

    // switch //
    void switch_nodes(RBNode<T> *u, RBNode<T> *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        if (v != nullptr)
        {
            v->parent = u->parent;
        }
    }

    // Fix the Red-Black Tree after deletion to handle the "Double Black" case
    void DB(RBNode<T> *node)
    {
        while (node != root && (node == nullptr || node->color == BLACK))
        {
            if (node == node->parent->left)
            {
                RBNode<T> *sibling = node->parent->right;
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotation(node->parent);
                    sibling = node->parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK))
                {
                    sibling->color = RED;
                    node = node->parent;
                }
                else
                {
                    if (sibling->right == nullptr || sibling->right->color == BLACK)
                    {
                        if (sibling->left != nullptr)
                            sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotation(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    leftRotation(node->parent);
                    node = root;
                }
            }
            else
            {
                RBNode<T> *sibling = node->parent->left;
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotation(node->parent);
                    sibling = node->parent->left;
                }
                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK))
                {
                    sibling->color = RED;
                    node = node->parent;
                }
                else
                {
                    if (sibling->left == nullptr || sibling->left->color == BLACK)
                    {
                        if (sibling->right != nullptr)
                            sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotation(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rightRotation(node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr)
            node->color = BLACK;
    }

    // deleteNode //
    void deleteNode(RBNode<T> *node)
    {
        RBNode<T> *y = node;
        RBNode<T> *x = nullptr;
        bool original_color = y->color; // Store the original color of node y

        if (node->left == nullptr)
        {
            // Case 1: Node has no left child (or no children)
            x = node->right;
            switch_nodes(node, node->right);
        }
        else if (node->right == nullptr)
        {
            // Case 2: Node has no right child, only a left child
            x = node->left;
            switch_nodes(node, node->left);
        }
        else
        {
            // Case 3: Node has two children
            y = findMin(node->right);  // Find the smallest node in the right subtree
            original_color = y->color; // Store the original color of y
            x = y->right;

            if (y->parent == node)
            {
                if (x != nullptr)
                {
                    x->parent = y; // If x exists, update its parent to y
                }
            }
            else
            {
                switch_nodes(y, y->right); // Replace y with its right child
                y->right = node->right;    // Link y to node's right subtree
                if (y->right != nullptr)
                {
                    y->right->parent = y; // Update parent of y's new right child
                }
            }
            switch_nodes(node, y); // Replace node with y
            y->left = node->left;  // Link y to node's left subtree
            if (y->left != nullptr)
            {
                y->left->parent = y; // Update parent of y's new left child
            }
            y->color = node->color; // Copy node's color to y
        }

        // Fix the Red-Black Tree if we deleted a black node
        if (original_color == BLACK && x != nullptr)
        {
            DB(x);
        }

        delete node;
    }

    // insert //
    void insert(const T &value)
    {
        RBNode<T> *newNode = new RBNode<T>(value);
        RBNode<T> *base = root, *tmp = nullptr;

        while (base != nullptr)
        {
            tmp = base;
            if (newNode->value < base->value)
            {
                base = base->left;
            }
            else
            {
                base = base->right;
            }
        }

        newNode->parent = tmp;
        if (tmp == nullptr)
        {
            root = newNode;
        }
        else if (newNode->value < tmp->value)
        {
            tmp->left = newNode;
        }
        else
        {
            tmp->right = newNode;
        }
        balance(newNode);
    }

    // delete //
    void remove(const T &value)
    {
        RBNode<T> *base = root;
        while (base != nullptr)
        {
            if (value < base->value)
            {
                base = base->left;
            }
            else if (value > base->value)
            {
                base = base->right;
            }
            else
            {
                deleteNode(base);
                return;
            }
        }
        cout << "Node with value " << value << " not found in the tree." << endl;
    }

    // Validation of RBT Properties
    bool validateRBTreeProperties(RBNode<T> *node, int &blackCount, int currentBlackCount) const
    {
        // Base case: reach a null node, which counts as a black leaf
        if (node == nullptr)
        {
            if (blackCount == -1)
            {
                // Set the black count for the first time when we reach the first leaf
                blackCount = currentBlackCount;
            }
            return blackCount == currentBlackCount; // All paths must have the same black count
        }

        // Red-Black Tree property 4: If a node is red, both children must be black
        if (node->color == RED)
        {
            if ((node->left && node->left->color == RED) || (node->right && node->right->color == RED))
            {
                return false;
            }
        }

        // Count black nodes
        if (!node->color == RED)
        {
            currentBlackCount++;
        }

        // Recursively check left and right subtrees
        return validateRBTreeProperties(node->left, blackCount, currentBlackCount) &&
               validateRBTreeProperties(node->right, blackCount, currentBlackCount);
    }

    bool validateRBTree() const
    {
        if (root == nullptr)
        {
            return true; // An empty tree is a valid Red-Black Tree
        }

        // Property 2: The root must be black
        if (root->color == RED)
        {
            return false;
        }

        int blackCount = -1; // Initialize the black node count
        return validateRBTreeProperties(root, blackCount, 0);
    }
};
//////////////////////////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////

void testRBTreeProperties(RBTree<int> &rbt)
{
    if (rbt.validateRBTree())
    {
        cout << "Tree is valid!" << endl;
    }
    else
    {
        cout << "Tree is invalid!" << endl;
    }
}

int main()
{
    RBTree<int> rbt;

    // Insert values into the RBTree
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    rbt.insert(5);
    rbt.insert(1);

    testRBTreeProperties(rbt);

    // Print the in-order traversal before deletion
    vector<int> inOrderItems;
    rbt.inOrder(rbt.getRoot(), inOrderItems);
    cout << "In-order before deletion: ";
    for (const int &item : inOrderItems)
    {
        cout << item << " ";
    }
    cout << endl;

    // Delete a value from the tree
    rbt.remove(20);

    testRBTreeProperties(rbt);
    // Print the in-order traversal after deletion
    inOrderItems.clear();
    rbt.inOrder(rbt.getRoot(), inOrderItems);
    cout << "In-order after deletion: ";
    for (const int &item : inOrderItems)
    {
        cout << item << " ";
    }
    cout << endl;

    // Check pre-order traversal
    vector<int> preOrderItems;
    rbt.preOrder(rbt.getRoot(), preOrderItems);
    cout << "Pre-order traversal: ";
    for (const int &item : preOrderItems)
    {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}
