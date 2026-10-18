#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node {
public:

	int data;
	Node* left;
	Node* right;

	Node() {
		data = 0;
		left = nullptr;
		right = nullptr;
	}
	Node(int value) {
		data = value;
		left = nullptr;
		right = nullptr;
	}

};


class BinaryTree {
public:

	Node* root;

	BinaryTree() {
		root = nullptr;
	}

	Node* BuildTree() {
		int value;
		cout << "Enter value (-1 for no node): ";
		cin >> value;
		if (value == -1) {
			return nullptr;
		}
		Node* newNode = new Node(value);
		cout << "Enter left child of " << value << endl;
		newNode->left = BuildTree();
		cout << "Enter right child of " << value << endl;
		newNode->right = BuildTree();
		return newNode;
	}

	void PreOrder(Node* node) { //root, left, right
		if (node == nullptr) {
			return;
		}
		cout << node->data << " ";
		PreOrder(node->left);
		PreOrder(node->right);
	}
	void InOrder(Node* node) { //left, root, right
		if (node == nullptr) {
			return;
		}
		InOrder(node->left);
		cout << node->data << " ";
		InOrder(node->right);
	}
	void PostOrder(Node* node) { //left, right, root
		if (node == nullptr) {
			return;
		}
		PostOrder(node->left);
		PostOrder(node->right);
		cout << node->data << " ";
	}

	void bfs(Node* root) {             //level order traversal
		if (root == nullptr) return;

		queue<Node*> open;   //queue is used for bfs
		open.push(root);

		while (!open.empty()) {
			Node* X = open.front();
			open.pop();
			cout << X->data << " "; //here we can also do some processing on the node, like searching for a value, etc.

			if (X->left)  open.push(X->left);
			if (X->right) open.push(X->right);
		}
	}
	void dfs(Node* root) {         //depth first traversal (similar to pre-order)
		if (root == nullptr) return;

		stack<Node*> open; //same as bfs but using stack instead of queue
		open.push(root);

		while (!open.empty()) {
			Node* X = open.top();
			open.pop();
			cout << X->data << " "; //here we can also do some processing on the node, like searching for a value, etc.

			if (X->right) open.push(X->right);
			if (X->left)  open.push(X->left);
		}
	}
};

int main() {
	BinaryTree tree;

	cout << "Build your Binary Tree" << endl;
	tree.root = tree.BuildTree();

	cout << "\nPreOrder:  ";
	tree.PreOrder(tree.root);

	cout << "\nInOrder:   ";
	tree.InOrder(tree.root);

	cout << "\nPostOrder: ";
	tree.PostOrder(tree.root);

	cout << "\nBFS:       ";
	tree.bfs(tree.root);

	cout << "\nDFS:       ";
	tree.dfs(tree.root);

	cout << endl;
	return 0;
}