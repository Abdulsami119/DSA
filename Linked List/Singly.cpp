#include<iostream>
using namespace std;

class student {
public:
	int rollno;
	string name;
};


class Node {
public:
	student data;
	Node* next;

	Node(string n, int r) : data{ r, n }, next(nullptr) {
	}
};


class linked_list {
public:
	Node* head;
	linked_list() : head(nullptr) {
	}

	void insert_start(string n, int r) { //  1. new node next points to head 2. new node becomes the new head
		Node* new_node = new Node(n, r);
		new_node->next = head;
		head = new_node;
	}

	void insert_end(string n, int r) {// 1. traverse to the end of the list 2. new node next points to nullptr 3. last node next points to new node
		Node* new_node = new Node(n, r);
		if (head == nullptr) {
			head = new_node;
			return;
		}
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new_node;
	}

	int add_all() {
		int sum = 0;
		if (head == nullptr) {
			return -1;
		}
		Node* temp = head;
		while (temp) {
			sum = sum + temp->data.rollno;
			temp = temp->next;
		}
		return sum;
	}

	void insert_after(string n, int r, int key_r) { // 1. traverse to the node with roll number key_r 2. new node next points to temp next 3. temp next points to new node
		Node* new_node = new Node(n, r);
		Node* temp = head;
		while (temp && temp->data.rollno != key_r) { //reaches the node with roll number key_r
			temp = temp->next;
		}
		if (temp == nullptr) {
			cout << "Roll number not found!" << endl;
			return;
		}
		new_node->next = temp->next;
		temp->next = new_node;
	}

	void delete_start() {
		if (head == nullptr) {
			cout << "List is empty!" << endl;
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
	}

	void delete_end() {
		if (head == nullptr) {
			cout << "List is empty!" << endl;
			return;
		}
		if (head->next == nullptr) {
			delete head;
			head = nullptr;
			return;
		}
		Node* temp = head;
		while (temp->next->next != nullptr) { //reaches the second last node
			temp = temp->next;
		}
		delete temp->next;
		temp->next = nullptr;
	}

	void delete_node(int key_r) {
		if (head == nullptr) {
			cout << "List is empty!" << endl;
			return;
		}
		if (head->data.rollno == key_r) {
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}
		Node* temp = head;
		while (temp->next && temp->next->data.rollno != key_r) { //reaches the node before the node to be deleted
			temp = temp->next;
		}
		if (temp->next == nullptr) {
			cout << "Roll number not found!" << endl;
			return;
		}
		Node* del_node = temp->next; //you can also, temp-next= temp->next-next; then, delete temp->next; but, this way is more readable
		temp->next = del_node->next;
		delete del_node;
	}

	void search(int r) {
		Node* temp = head;
		while (temp) {
			if (temp->data.rollno == r) {
				cout << "Roll number: " << temp->data.rollno << ", Name: " << temp->data.name << endl;
				return;
			}
			temp = temp->next;
		}
		cout << "Roll number not found!" << endl;
	}

	void display() {
		Node* temp = head;
		while (temp) {
			cout << "Roll number: " << temp->data.rollno << ", Name: " << temp->data.name << endl;
			temp = temp->next;
		}
	}


};


int main() {
	linked_list list;
	list.insert_end("Alice", 1);
	list.insert_end("Bob", 2);
	list.insert_start("Charlie", 3);
	int sum = list.add_all();
	cout << "SUM =" << sum << endl;
	list.insert_after("David", 4, 2);
	list.display();
	cout << "After deleting start:" << endl;
	list.delete_start();
	list.display();
	cout << "After deleting end:" << endl;
	list.delete_end();
	list.display();
	cout << "After deleting node with roll number 1:" << endl;
	list.delete_node(1);
	list.display();
	cout << "Searching for roll number 2:" << endl;
	list.search(2);
	cout << "Searching for roll number 5:" << endl;
	list.search(5);
	return 0;
}