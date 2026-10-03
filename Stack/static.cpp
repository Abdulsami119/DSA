/*
 * STATIC STACK (array-based)           Lec 4 - Stack
 * -----------------------------------------------------
 * LIFO: Last In, First Out. Only the TOP is accessible.
 *
 * Static = fixed-size array, so the stack can OVERFLOW (full).
 *
 * KEY RULE:  top = index of the top element
 *            top == -1            -> stack is EMPTY  (underflow if you pop)
 *            top == size - 1      -> stack is FULL   (overflow if you push)
 *
 * Trace (size 5):
 *   start      top=-1  []
 *   push(A)    top= 0  [A]
 *   push(B)    top= 1  [A B]
 *   push(C)    top= 2  [A B C]
 *   pop()      top= 1  [A B]     (C stays in memory but is ignored)
 */

#include <iostream>
using namespace std;

class Stack {
private:
    int* myArray;   // storage for the elements
    int  size;      // capacity (fixed once the stack is created)
    int  top;       // index of the top element, -1 when empty

public:
    // CONSTRUCTION: allocate the array, start empty (top = -1)
    Stack(int s) {
        size = s;
        myArray = new int[size];
        top = -1;
    }

    // Free the array when the stack is destroyed (avoids memory leak)
    ~Stack() {
        delete[] myArray;
    }

    // EMPTY: no elements when top is still -1
    bool isEmpty() const {
        return top == -1;
    }

    // FULL: last valid index is size-1, so top there means no room left
    bool isFull() const {
        return top == size - 1;
    }

    // PUSH: check full -> move top up -> store value.
    // Order matters: increment FIRST, otherwise we overwrite the old top.
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow: can't push " << value << endl;
            return;
        }
        myArray[++top] = value;     // ++top then store (same as top++; arr[top]=value)
    }

    // POP: check empty -> just move top down (logical removal).
    // The old value remains in the array but is above top, so it is ignored
    // and will be overwritten by the next push.
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow: nothing to pop" << endl;
            return;
        }
        top--;
    }

    // PEEK / TOP: read the top WITHOUT removing it (top does not move).
    // Returns -1 as an error value if empty (assumes -1 isn't a real element).
    int peek() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return myArray[top];
    }

    // OUTPUT (debugging): print from top down to bottom (index top -> 0)
    void display() const {
        if (isEmpty()) {
            cout << "[empty]" << endl;
            return;
        }
        cout << "Top -> ";
        for (int i = top; i >= 0; i--)
            cout << myArray[i] << " ";
        cout << "<- Bottom" << endl;
    }
};

int main() {
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);
    s.display();                                   // Top -> 30 20 10 <- Bottom
    cout << "Peek: " << s.peek() << endl;          // 30

    s.pop();
    s.display();                                   // Top -> 20 10 <- Bottom

    // Fill it up to demonstrate overflow (capacity is 5)
    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70);                                    // Stack Overflow

    // Empty it to demonstrate underflow
    while (!s.isEmpty()) s.pop();
    s.pop();                                       // Stack Underflow
    return 0;
}