#include <iostream>
#include <limits.h> // For INT_MIN

using namespace std;

// Define the structure for a node in the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;
    
    // Constructor to create a new node
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Function to perform inorder traversal (LNR: Left, Node, Right)
// and track the maximum value seen in the tree
void inorderTraversal(Node* root, int& maxValue) {
    if (root == nullptr) {
        return;
    }
    
    // Traverse left subtree
    inorderTraversal(root->left, maxValue);
    
    // Visit root node and update the maximum value
    if (root->data > maxValue) {
        maxValue = root->data;
    }
    cout << root->data << " ";
    
    // Traverse right subtree
    inorderTraversal(root->right, maxValue);
}

// Helper function to insert a node in the binary tree (for testing purposes)
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

int main() {
    // Create a binary tree
    Node* root = nullptr;
    
    // Insert nodes (unsorted)
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    // Track the maximum value seen during the traversal
    int maxValue = INT_MIN;  // Initialize with the minimum possible integer value
    
    // Perform inorder traversal and track the maximum value
    cout << "Inorder Traversal: ";
    inorderTraversal(root, maxValue);
    
    cout << "\nMaximum value in the tree: " << maxValue << endl;
    
    return 0;
}
