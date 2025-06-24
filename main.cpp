#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

// Patient structure
struct Patient {
    string name;
    int age;
    string problem;
    int priority;

    // Comparator overloading: lower priority number->higher urgency
    bool operator<(const Patient& other) const {
        return priority > other.priority;
    }
};

// Priority Queue to manage patients
priority_queue<Patient> pq;
vector<Patient> patientList;

// Map medical problems to priority values
unordered_map<string, int> problemPriority = {
    {"heart attack", 1},
    {"fracture", 2},
    {"fever", 4},
    {"cold", 5},
    {"checkup", 6}
};

// Add a new patient to the priority queue
void addPatient(const string& name, int age, const string& problem) {
    int priority = problemPriority.count(problem) ? problemPriority[problem] : 10; // default low priority
    Patient p{name, age, problem, priority};
    pq.push(p);
    patientList.push_back(p);
    cout << "Patient added with priority: " << priority << "\n";
}

// Serve the highest priority patient
void servePatient() {
    if (pq.empty()) {
        cout << "No patients to serve.\n";
        return;
    }

    Patient top = pq.top();
    pq.pop();

    for (auto it = patientList.begin(); it != patientList.end(); ++it) {
        if (it->name == top.name && it->age == top.age && it->problem == top.problem) {
            patientList.erase(it);
            break;
        }
    }

    cout << "Serving patient:\n";
    cout << "- Name: " << top.name << "\n";
    cout << "- Age: " << top.age << "\n";
    cout << "- Problem: " << top.problem << "\n";
}
void searchPatient(const string& name) {
    bool found = false;
    for (const auto& p : patientList) {
        if (p.name == name) {
            cout << "\nPatient Found:\n";
            cout << "- Name: " << p.name
                 << ", Age: " << p.age
                 << ", Problem: " << p.problem
                 << ", Priority: " << p.priority << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No patient found with the name \"" << name << "\".\n";
    }
}
// Display all patients in the queue (copy, then pop)
void displayQueue() {
    if (pq.empty()) {
        cout << "No patients are waiting.\n";
        return;
    }

    cout << "\nPatients in the queue (from highest to lowest priority):\n";
    priority_queue<Patient> tempPQ = pq; // copy, because pop() modifies original
    while (!tempPQ.empty()) {
        Patient p = tempPQ.top();
        tempPQ.pop();
        cout << "- Name: " << p.name
             << ", Age: " << p.age
             << ", Problem: " << p.problem
             << ", Priority: " << p.priority << "\n";
    }
}

// Remove a patient by name
void removePatient(const string& name) {
    bool removed = false;

    // Remove from list
    auto it = patientList.begin();
    while (it != patientList.end()) {
        if (it->name == name) {
            it = patientList.erase(it);
            removed = true;
        } else {
            ++it;
        }
    }

    if (!removed) {
        cout << "No patient found with the name \"" << name << "\" to remove.\n";
        return;
    }
    // Rebuild the priority queue
        while (!pq.empty()) pq.pop();
    for (const auto& p : patientList) {
        pq.push(p);
    }

    cout << "All entries for \"" << name << "\" removed from the queue.\n";
}

int main() {
    int choice;
    string name, problem;
    int age;

    do {
        cout << "\n=== Hospital Priority Queue System ===\n";
        cout << "1. Add Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Show Queue\n";
        cout << "4. Exit\n";
        cout << "5. Search Patient\n";
        cout << "6. Remove Patient\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // ignore leftover newline

        switch (choice) {
            case 1:
                cout << "Enter patient's name: ";
                getline(cin, name);
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter problem: ";
                getline(cin, problem);
                addPatient(name, age, problem);
                break;

            case 2:
                servePatient();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                cout << "Exiting program. Thank you!\n";
                break;
            case 5:
                cout << "Enter patient's name to search: ";
                getline(cin, name);
                searchPatient(name);
                break;
            case 6:
                cout << "Enter patient's name to remove: ";
                getline(cin, name);
                removePatient(name);
                break;

            default:
                cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
