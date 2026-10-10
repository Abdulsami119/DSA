/*
 * DYNAMIC STACK (linked list)          Lec 4 - Stack
 * -----------------------------------------------------
 * Same LIFO behaviour, but memory is allocated one node at a time,
 * so there is no fixed size and no isFull() needed.
 *
 * The TOP of the stack is the HEAD of the list. Push and pop both work at
 * the head, which makes them O(1) (no need to walk the list).
 *
 *   top -> [30|*]-> [20|*]-> [10|NULL]
 *
 * KEY RULE:  top == nullptr  -> stack is EMPTY
 */

#include <iostream>
using namespace std;

// One node of the list: the data plus a pointer to the node BELOW it
struct Node {
    int   data;
    Node* next;
};

class Stack {
private:
    Node* top;      // pointer to the top node (nullptr when empty)

public:
    // CONSTRUCTION: empty stack, top points at nothing
    Stack() {
        top = nullptr;
    }

    // Destructor: pop everything so every node gets deleted (no leaks)
    ~Stack() {
        while (!isEmpty()) pop();
    }

    // EMPTY: no nodes at all
    bool isEmpty() const {
        return top == nullptr;
    }

    // PUSH: insert a new node at the HEAD of the list.
    //   1. create the node and store the value
    //   2. point the new node's next at the current top
    //   3. make the new node the top
    // Steps 2 and 3 MUST be in this order, else we lose the old list.
    void push(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;        // link to old top first
        top = newNode;              // then move top to the new node
    }

    // POP: remove the head node.
    //   1. remember the node in temp (so we can still delete it)
    //   2. move top to the next node
    //   3. delete the old node (this is a REAL removal, unlike the array)
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow: nothing to pop" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    // PEEK / TOP: read the head node's data without removing it
    int peek() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return top->data;
    }

    // OUTPUT (debugging): walk from the top down using a temp pointer.
    // Use a copy of top so we never move the real top pointer.
    void display() const {
        if (isEmpty()) {
            cout << "[empty]" << endl;
            return;
        }
        cout << "Top -> ";
        Node* current = top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "<- Bottom" << endl;
    }
};

int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);
    s.display();                            // Top -> 30 20 10 <- Bottom
    cout << "Peek: " << s.peek() << endl;   // 30

    s.pop();
    s.display();                            // Top -> 20 10 <- Bottom

    s.pop();
    s.pop();
    s.pop();                                // Stack Underflow
    s.display();                            // [empty]
    return 0;
}