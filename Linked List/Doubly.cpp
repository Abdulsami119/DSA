#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    int patientID;
    string name;
    string department;

    Node* next;
    Node* prev;

    Node(int id, string n, string d)
    {
        patientID = id;
        name = n;
        department = d;
        next = NULL;
        prev = NULL;
    }
};
class PatientList
{
private:
    Node* head;
    Node* tail;

public:
    PatientList()
    {
        head = NULL;
        tail = NULL;
    }
    void addPatient(int id, string name, string department)
    {
        Node* newNode = new Node(id, name, department);

        if (head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void removePatient(int id)
    {
        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->patientID == id)
            {
				if (temp->prev != NULL) //not the first node
                    temp->prev->next = temp->next;
				else //first node
                    head = temp->next;

				if (temp->next != NULL)     //not the last node 
                    temp->next->prev = temp->prev;
				else //last node
                    tail = temp->prev;

                delete temp;
                cout << "Patient removed.\n";
                return;
            }

            temp = temp->next;
        }

        cout << "Patient not found.\n";
    }
    void searchPatient(string name)
    {
        Node* temp = head;

        while (temp)
        {
            if (temp->name == name)
            {
                cout << "Patient ID: " << temp->patientID << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Department: " << temp->department << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Patient not found.\n";
    }
    void displayForward()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            cout << temp->patientID << "  "
                << temp->name << "  "
                << temp->department << endl;

            temp = temp->next;
        }
    }
    void displayBackward()
    {
        Node* temp = tail;

        while (temp != NULL)
        {
            cout << temp->patientID << "  "
                << temp->name << "  "
                << temp->department << endl;

            temp = temp->prev;
        }
    }
    void findPatient(int id)
    {
        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->patientID == id)
            {
                cout << "Patient Found\n";
                cout << "ID: " << temp->patientID << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Department: " << temp->department << endl;
                return;
            }

            temp = temp->next;
        }

        cout << "Patient not found.\n";
    }
};

int main()
{
    PatientList patients;

    patients.addPatient(101, "Ali", "Cardiology");
    patients.addPatient(102, "Ahmed", "Neurology");
    patients.addPatient(103, "Usman", "Orthopedic");
    patients.addPatient(104, "Hamza", "ENT");

    cout << "Patients Forward:\n";
    patients.displayForward();

    cout << "\nPatients Backward:\n";
    patients.displayBackward();

    cout << "\nSearching Patient:\n";
    patients.searchPatient("Ahmed");

    cout << "\nFinding Patient by ID:\n";
    patients.findPatient(103);

    cout << "\nRemoving Patient:\n";
    patients.removePatient(102);

    cout << "\nPatients after removal:\n";
    patients.displayForward();

    return 0;
}
