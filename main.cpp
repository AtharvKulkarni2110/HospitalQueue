#include <iostream>
#include <string>

using namespace std;

// Each patient is a node in the queue (linked list)
struct Patient {
    string name;
    int age;
    string problem;
    Patient* next; // Points to the next patient
};

class HospitalQueue {
private:
    Patient* front; 
    Patient* rear;  

public:
    HospitalQueue() {
        front = rear = nullptr; 
    }

    // Add a new patient at the end of the queue
    void addPatient(string name, int age, string problem) {
        // Create a new patient
        Patient* newPatient = new Patient{name, age, problem, nullptr};

        if (rear == nullptr) { // Queue is empty
            front = rear = newPatient;
        } else {
            rear->next = newPatient; // Add at end
            rear = newPatient;
        }

        cout << " Patient added to the queue.\n";
    }

    // Remove the first patient from the queue
    void servePatient() {
        if (front == nullptr) { // No one to serve
            cout << " No patients in the queue.\n";
            return;
        }

        // Show the patient being served
        cout << " Serving patient: " << front->name << endl;

        // Move front to the next patient
        Patient* temp = front;
        front = front->next;

       
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp; // Free memory
    }

    // Show all patients waiting in the queue
    void displayQueue() {
        if (front == nullptr) {
            cout << " No patients are waiting.\n";
            return;
        }

        cout << "\n Patients in the queue:\n";

        Patient* current = front;
        while (current != nullptr) {
            cout << "- Name: " << current->name
                 << ", Age: " << current->age
                 << ", Problem: " << current->problem << endl;
            current = current->next; // Go to next patient
        }
    }

    // Free memory when program ends
    ~HospitalQueue() {
        while (front != nullptr) {
            Patient* temp = front;
            front = front->next;
            delete temp;
        }
    }
};


int main() {
    HospitalQueue hospital;
    int choice;
    string name, problem;
    int age;

    do {
        // Menu options
        cout << "\n=== Hospital Queue System ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Show Queue\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // Remove leftover newline

        switch (choice) {
            case 1:
                cout << "Enter patient's name: ";
                getline(cin, name);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter problem: ";
                getline(cin, problem);
                hospital.addPatient(name, age, problem);
                break;

            case 2:
                hospital.servePatient();
                break;

            case 3:
                hospital.displayQueue();
                break;

            case 4:
                cout << "Exiting program. Thank you!\n";
                break;

            default:
                cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 4); // Keep looping until user exits

    return 0;
}
