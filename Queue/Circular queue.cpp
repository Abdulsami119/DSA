#include <iostream>
using namespace std;

// Circular Queue implemented with a plain array (static implementation)
// Idea: when rear reaches the last index, it wraps around to index 0
// so the empty slots at the start of the array can be reused.

class CircularQueue
{
public:
    int *myArray;   // array that stores the elements of the queue
    int size;       // maximum number of elements the queue can hold
    int front;      // index of the front element (the one removed next)
    int rear;       // index of the last element (the one added most recently)

    CircularQueue(int s);
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    int dequeue();
    int getFront();
    void display();
};

// Constructor: create the array and mark the queue as empty
CircularQueue::CircularQueue(int s)
{
    myArray = new int[s];
    size = s;
    front = -1;     // -1 in both front and rear means the queue is empty
    rear = -1;
}

// Queue is empty only when front is still -1
bool CircularQueue::isEmpty()
{
    return front == -1;
}

// Queue is full when the next position after rear (with wrap-around)
// is the front. In other words, rear has caught up with front from behind.
bool CircularQueue::isFull()
{
    return (rear + 1) % size == front;
}

void CircularQueue::enqueue(int value)
{
    if (isFull())
    {
        cout << "Queue Overflow" << endl;
        return;
    }

    if (isEmpty())
    {
        // first element ever inserted: both front and rear start at 0
        front = 0;
        rear = 0;
    }
    else
    {
        // move rear one step forward; % size makes it wrap to 0
        // when it goes past the last index
        // e.g. size = 5, rear = 4  ->  (4 + 1) % 5 = 0
        // e.g. size = 5, rear = 2  ->  (2 + 1) % 5 = 3
        rear = (rear + 1) % size;
    }

    myArray[rear] = value;
}

int CircularQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue Underflow" << endl;
        return -1;
    }

    int temp = myArray[front];   // save the value to return

    if (front == rear)
    {
        // there was only one element, so the queue becomes empty again
        front = -1;
        rear = -1;
    }
    else
    {
        // move front one step forward, also wrapping around
        front = (front + 1) % size;
    }

    return temp;
}

// Look at the front value without removing it
int CircularQueue::getFront()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return -1;
    }
    return myArray[front];
}

// Print elements from front to rear (follows the wrap-around too)
void CircularQueue::display()
{
    if (isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    int i = front;
    while (true)
    {
        cout << myArray[i] << " ";
        if (i == rear)          // reached the last element, stop
            break;
        i = (i + 1) % size;     // otherwise go to the next slot (wraps around)
    }
    cout << endl;
}

int main()
{
    CircularQueue Q(5);

    // fill the queue completely
    Q.enqueue(11);
    Q.enqueue(12);
    Q.enqueue(13);
    Q.enqueue(14);
    Q.enqueue(15);
    Q.display();            // 11 12 13 14 15

    Q.enqueue(16);          // Queue Overflow (no space left)

    // remove two elements, this frees up index 0 and 1
    cout << "Dequeued: " << Q.dequeue() << endl;   // 11
    cout << "Dequeued: " << Q.dequeue() << endl;   // 12

    // these two go into the freed slots at the start of the array
    // (a normal linear queue would have said "full" here)
    Q.enqueue(16);          // rear wraps around to index 0
    Q.enqueue(17);          // rear moves to index 1
    Q.display();            // 13 14 15 16 17

    cout << "Front element: " << Q.getFront() << endl;   // 13

    return 0;
}