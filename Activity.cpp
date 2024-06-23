#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;


class Node {
public:
    int data;
    string patientName;
    Node* next;

    Node(int value, string name) {
        data = value;
        patientName = name;
        next = nullptr;
    }
};


class Queue {
private:
    Node* front;
    Node* rear;
    int ticketNumber;

    void displayLoadingAnimation(const string& message, int durationMs) {
        cout << message;
        for (int i = 0; i < 3; ++i) {
            cout << ".";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(durationMs));
        }
        cout << endl;
    }

public:
    // Queue 
    Queue() {
        front = nullptr;
        rear = nullptr;
        ticketNumber = 1;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(string patientName) {
        Node* newNode = new Node(ticketNumber++, patientName);

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        displayLoadingAnimation("Issuing ticket", 300);
        cout << "Ticket issued to " << patientName << " with ticket number " << newNode->data << endl;
    }

    int peek() {
        if (!isEmpty()) {
            return front->data;
        } else {
            cout << "Queue is empty!\n";
            return -1;
        }
    }

    string peekPatient() {
        if (!isEmpty()) {
            return front->patientName;
        } else {
            return "Queue is empty!";
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            displayLoadingAnimation("Calling Patient", 300);
            cout << "Processed ticket number " << front->data << " for " << front->patientName << endl;
            front = front->next;
            delete temp;
            if (front == nullptr) {
                rear = nullptr;
            }
        } else {
            cout << "Queue is empty! No ticket to process.\n";
        }
    }

    void displayQueue() {
        if (!isEmpty()) {
            Node* temp = front;
            while (temp != nullptr) {
                cout << "Ticket Number: " << temp->data << " | Patient Name: " << temp->patientName << endl;
                temp = temp->next;
            }
        } else {
            cout << "Queue is empty!\n";
        }
    }
};

int main() {
    Queue q;
    int choice;
    string patientName;

    do {
        cout << "\nHospital Queue System Menu:\n";
        cout << "1. Issue Ticket\n";
        cout << "2. Peek Current Ticket\n";
        cout << "3. Call in next Patient\n";
        cout << "4. Display Queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter patient name: ";
            getline(cin, patientName);
            q.enqueue(patientName);
            break;
        case 2:
            cout << "Current ticket number: " << q.peek() << " | Patient Name: " << q.peekPatient() << endl;
            break;
        case 3:
            q.dequeue();
            break;
        case 4:
            cout << "Current Queue:\n";
            q.displayQueue();
            break;
        case 5:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
