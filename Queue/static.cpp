/*
 * STATIC QUEUE (array-based, linear)      Lec 5 - Queues
 * -----------------------------------------------------
 * FIFO: First In, First Out.
 *   - ENQUEUE adds at the REAR
 *   - DEQUEUE removes from the FRONT
 *
 * Both indices start at -1:
 *   rear  = index of the LAST element
 *   front = index just BEFORE the first element
 *           (so the first element lives at front + 1)
 *
 * KEY RULES (as on the slides):
 *   empty:  front == rear
 *   full :  rear == size - 1
 *   enqueue: myArray[++rear] = value
 *   dequeue: return myArray[++front]
 *
 * Trace (size 5):
 *   start        front=-1 rear=-1  []
 *   enqueue(11)  front=-1 rear= 0  [11]
 *   enqueue(12)  front=-1 rear= 1  [11 12]
 *   dequeue()    front= 0 rear= 1  [12]        (returns 11)
 *
 * KNOWN PROBLEM of a linear queue: slots before front are never reused.
 * Once rear reaches size-1 the queue says "full" even if the front part of
 * the array is empty. The fix is a circular queue (rear = (rear+1) % size).
 */

#include <iostream>
using namespace std;

class Queue {
private:
    int* myArray;   // storage
    int  size;      // fixed capacity
    int  front;     // one position BEFORE the first element
    int  rear;      // position of the last element

public:
    // CONSTRUCTION: allocate array; empty queue has front = rear = -1
    Queue(int s) {
        size = s;
        myArray = new int[size];
        front = -1;
        rear = -1;
    }

    ~Queue() {
        delete[] myArray;
    }

    // EMPTY: front caught up with rear -> no elements between them
    bool isEmpty() const {
        return front == rear;
    }

    // FULL: rear has hit the last slot. (Not moved back when front moves,
    // which is exactly the wasted-space problem noted above.)
    bool isFull() const {
        return rear == size - 1;
    }

    // ENQUEUE: check full -> increment rear -> store value.
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow: can't enqueue " << value << endl;
            return;
        }
        myArray[++rear] = value;
    }

    // DEQUEUE: check empty -> increment front -> return that element.
    // Because front starts one BEFORE the first element, ++front lands on it.
    // The slot is not erased, it just falls behind front.
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow: nothing to dequeue" << endl;
            return -1;      // error value (assumes -1 isn't real data)
        }
        return myArray[++front];
    }

    // GET FRONT: look at the first element WITHOUT removing it.
    // It sits at front + 1 (we don't change front, so no ++front here).
    int getFront() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return myArray[front + 1];
    }

    // OUTPUT (debugging): live elements are from front+1 up to rear
    void display() const {
        if (isEmpty()) {
            cout << "[empty]" << endl;
            return;
        }
        cout << "Front -> ";
        for (int i = front + 1; i <= rear; i++)
            cout << myArray[i] << " ";
        cout << "<- Rear" << endl;
    }
};

int main() {
    Queue q(5);

    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    q.display();                                     // Front -> 11 12 13 <- Rear
    cout << "Front: " << q.getFront() << endl;       // 11

    cout << "Dequeued: " << q.dequeue() << endl;     // 11
    q.display();                                     // Front -> 12 13 <- Rear

    q.enqueue(14);
    q.enqueue(15);
    q.enqueue(16);                                   // Overflow (rear hit index 4,
                                                     // even though index 0 is free!)
    while (!q.isEmpty()) q.dequeue();
    q.dequeue();                                     // Underflow
    return 0;
}