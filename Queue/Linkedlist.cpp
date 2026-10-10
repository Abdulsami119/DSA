/*
 * DYNAMIC QUEUE (linked list)             Lec 5 - Queues
 * -----------------------------------------------------
 * FIFO again, but nodes are allocated on demand: no fixed size, no
 * isFull(), and no wasted slots like the linear array queue.
 *
 *   front -> [11|*]-> [12|*]-> [13|NULL] <- rear
 *
 *   ENQUEUE = add a node at the END   (rear)  -> O(1) thanks to the rear pointer
 *   DEQUEUE = remove the FIRST node   (front) -> O(1)
 *
 * We keep TWO pointers. Without rear we would have to walk the whole list
 * on every enqueue to find the end.
 *
 * KEY RULE:  front == nullptr  -> queue is EMPTY
 *            (when empty, rear is nullptr too)
 */

#include <iostream>
using namespace std;

struct Node {
    int   data;
    Node* next;
};

class LinkedQueue {
private:
    Node* front;    // first node (next to be served)
    Node* rear;     // last node (most recently added)

public:
    // CONSTRUCTION: both pointers null = empty queue
    LinkedQueue() {
        front = nullptr;
        rear = nullptr;
    }

    // Destructor: dequeue everything so all nodes are deleted
    ~LinkedQueue() {
        while (!isEmpty()) dequeue();
    }

    // EMPTY: no first node. (No isFull needed; memory is the only limit.)
    bool isEmpty() const {
        return front == nullptr;
    }

    // ENQUEUE: add a node at the rear.
    //   1. create the node, next = nullptr (it will be the last node)
    //   2. EMPTY case: the new node is both front and rear
    //   3. otherwise: link the old rear to it, then move rear onto it
    void enqueue(int x) {
        Node* temp = new Node;
        temp->data = x;
        temp->next = nullptr;

        if (isEmpty()) {
            front = rear = temp;    // first node is both ends
            return;
        }
        rear->next = temp;          // old last node points to the new one
        rear = temp;                // new node becomes the last
    }

    // DEQUEUE: remove and return the front node's data.
    //   1. remember the node in temp and save its data (we delete it below)
    //   2. move front to the next node
    //   3. SPECIAL CASE: if that was the only node, front is now null, so
    //      rear must be set to null as well. Otherwise rear would dangle
    //      pointing at deleted memory.
    //   4. delete the old node
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: nothing to dequeue" << endl;
            return -1;
        }
        Node* temp = front;
        int value = temp->data;
        front = front->next;
        if (front == nullptr)       // list became empty
            rear = nullptr;
        delete temp;
        return value;
    }

    // GET FRONT: read the first node's data without removing it
    int getFront() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return front->data;
    }

    // OUTPUT (debugging): walk front -> rear using a temp pointer
    void display() const {
        if (isEmpty()) {
            cout << "[empty]" << endl;
            return;
        }
        cout << "Front -> ";
        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "<- Rear" << endl;
    }
};

int main() {
    LinkedQueue q;

    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    q.display();                                    // Front -> 11 12 13 <- Rear
    cout << "Front: " << q.getFront() << endl;      // 11

    cout << "Dequeued: " << q.dequeue() << endl;    // 11
    q.display();                                    // Front -> 12 13 <- Rear

    q.enqueue(14);                                  // no wasted-space problem here
    q.display();                                    // Front -> 12 13 14 <- Rear

    while (!q.isEmpty()) q.dequeue();               // drains the queue, rear reset to null
    q.dequeue();                                    // Underflow
    q.enqueue(99);                                  // still works after being emptied
    q.display();                                    // Front -> 99 <- Rear
    return 0;
}