#include <iostream>
using namespace std;

struct Node
{
    string name;
    Node* next;
};

Node* head = NULL;

// Add doctor
void addDoctor(string name)
{
    Node* newNode = new Node;
    newNode->name = name;

    if (head == NULL)
    {
        head = newNode;
        newNode->next = head;
    }
    else
    {
        Node* temp = head;

        while (temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;
    }

    cout << "Doctor added." << endl;
}

// Remove doctor
void removeDoctor(string name)
{
    if (head == NULL)
    {
        cout << "Schedule is empty." << endl;
        return;
    }

    Node* temp = head;
    Node* previous = NULL; 

    // If only one doctor exists
    if (head->next == head)
    {
        if (head->name == name)
        {
            delete head;
            head = NULL;
            cout << "Doctor removed." << endl;
        }
        else
        {
            cout << "Doctor not found." << endl;
        }

        return;
    }

    // Removing head
    if (head->name == name)
    {
        while (temp->next == head) {
            temp = temp ->next;
       }
        temp ->next = head->next;
		Node* toDelete = head;
        head = head->next;
		delete toDelete;

        //alternate
		// Node* toDelete = head;
		// head = head->next;
		// temp->next = head;
		// delete toDelete;

		cout << "Doctor removed." << endl;
		return;
    }
    
    // Removing another doctor

    /*
    Alternate Method

    temp = head->next
    while(temp!=head)
    {
     if ( temp->next->data.name == name)
      {
      Node *todelete = temp->next;
      temp->next= delete->next;
      delete todelete;
    */


    temp = head;
    do
    {
        previous = temp;
        temp = temp->next;

        if (temp->name == name)
        {
            previous->next = temp->next;
            delete temp;

            cout << "Doctor removed." << endl;
            return;
        }

    } while (temp != head);

    cout << "Doctor not found." << endl;
}

// Display duty schedule
void displaySchedule()
{
    if (head == NULL)
    {
        cout << "Schedule is empty." << endl;
        return;
    }

    Node* temp = head;

    cout << "\nDuty Schedule:" << endl;

    do
    {
        cout << temp->name << " -> ";
        temp = temp->next;

    } while (temp != head);

    cout << "Back to " << head->name << endl;
}

// Find next doctor
void nextDoctor()
{
    if (head == NULL)
    {
        cout << "Schedule is empty." << endl;
        return;
    }

    cout << "Next doctor on duty: " << head->name << endl;

    head = head->next;
}

int main()
{
    int choice;
    string name;

    do
    {
        cout << "\n--- Doctor Duty Schedule ---" << endl;
        cout << "1. Add Doctor" << endl;
        cout << "2. Remove Doctor" << endl;
        cout << "3. Display Duty Schedule" << endl;
        cout << "4. Find Next Doctor on Duty" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter doctor name: ";
            cin >> name;
            addDoctor(name);
            break;

        case 2:
            cout << "Enter doctor name to remove: ";
            cin >> name;
            removeDoctor(name);
            break;

        case 3:
            displaySchedule();
            break;

        case 4:
            nextDoctor();
            break;

        case 5:
            cout << "Program ended." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}