
#include <iostream>
#include <queue>
using namespace std;

// Node of the binary tree
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor initializes the node
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Function to create the binary tree
Node* buildTree() {
    int value;

    cout << "Enter data (-1 for no node): ";
    cin >> value;

    // -1 means there is no node
    if (value == -1) {
        return nullptr;
    }

    // Create a new node
    Node* newNode = new Node(value);

    // Create the left subtree
    cout << "Enter left child of " << value << endl;
    newNode->left = buildTree();

    // Create the right subtree
    cout << "Enter right child of " << value << endl;
    newNode->right = buildTree();

    return newNode;
}

// Breadth-First Search (BFS)
// Visits nodes level by level using a queue
void BFS(Node* root) {
    if (root == nullptr) {
        return;
    }

    queue<Node*> q;

    // Insert the root into the queue
    q.push(root);

    while (!q.empty()) {
        // Get the first node from the queue
        Node* current = q.front();
        q.pop();

        // Visit and print the current node
        cout << current->data << " ";

        // Add left child to the queue
        if (current->left != nullptr) {
            q.push(current->left);
        }

        // Add right child to the queue
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}

// Depth-First Search (DFS)
// Explores the left branch deeply before the right branch
void DFS(Node* root) {
    // Base case: stop if the node does not exist
    if (root == nullptr) {
        return;
    }

    // Visit the current node first
    cout << root->data << " ";

    // Explore the left subtree
    DFS(root->left);

    // Explore the right subtree
    DFS(root->right);
}

int main() {
    cout << "Build your Binary Tree" << endl;

    Node* root = buildTree();

    cout << "\nBreadth-First Search (BFS): ";
    BFS(root);

    cout << "\nDepth-First Search (DFS): ";
    DFS(root);

    cout << endl;

    return 0;
}
