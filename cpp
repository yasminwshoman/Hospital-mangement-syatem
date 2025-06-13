#include <iostream>
#include <vector>
#include <string>
using namespace std;

// -------------------- Data Structures --------------------
struct Patient {
    long long ID;
    string firstName;
    string lastName;
    int age;
    string bloodGroup;
    char gender;
    string specialization;
};

// -------------------- Specialization Selection --------------------
string selectSpecialization() {
    int specChoice;
    string selected;

    cout << "\n1. General Practitioner\n";
    cout << "2. Cardiologist\n";
    cout << "3. Pulmonologist\n";
    cout << "4. Plastic Surgeon\n";
    cout << "5. Pediatrician\n";
    cout << "6. Neurologist\n";
    cout << "7. Dermatologist\n";
    cout << "8. Orthopedic\n";
    cout << "Choice: ";
    cin >> specChoice;

    switch (specChoice) {
    case 1: selected = "General Practitioner"; break;
    case 2: selected = "Cardiologist"; break;
    case 3: selected = "Pulmonologist"; break;
    case 4: selected = "Plastic Surgeon"; break;
    case 5: selected = "Pediatrician"; break;
    case 6: selected = "Neurologist"; break;
    case 7: selected = "Dermatologist"; break;
    case 8: selected = "Orthopedic"; break;
    default: selected = "General Practitioner";
    }

    return selected;
}

// -------------------- Department Class --------------------
class Department {
private:
    string name;
    vector<Patient> queue;

    bool searchID(long long id) {
        for (auto& p : queue)//for (int i = 0; i < queue.size(); ++i)
            if (p.ID == id) return true;
        return false;
    }

public:
    Department(string deptName) {
        name = deptName;
    }

    string getName() const { return name; }
    vector<Patient>& getQueue() { return queue; }

    void displayPatient(const Patient& p) const {
        cout << "\n👤 Patient Info:";
        cout << "\nFirst Name: " << p.firstName;
        cout << "\nLast Name: " << p.lastName;
        cout << "\nGender: " << p.gender;
        cout << "\nAge: " << p.age;
        cout << "\nBlood Group: " << p.bloodGroup;
        cout << "\nMobile Number: " << p.ID;
        cout << "\nSpecialization: " << p.specialization << "\n";
    }

    Patient inputPatient() {
        Patient p;
        cout << "\n📋 Register New Patient\n";
        cout << "Enter First Name: ";
        cin >> p.firstName;
        cout << "Enter Last Name: ";
        cin >> p.lastName;
        cout << "Enter Blood Group: ";
        cin >> p.bloodGroup;
        cout << "Enter Gender (m/f): ";
        cin >> p.gender;
        cout << "Enter Age: ";
        cin >> p.age;
        cout << "Enter Mobile Number: ";
        cin >> p.ID;

        if (searchID(p.ID)) {
            cout << "❌ Patient already exists!\n";
            p.ID = 0;
            return p;
        }

        p.specialization = selectSpecialization();
        return p;
    }

    void addPatientEnd() {
        Patient p = inputPatient();
        if (p.ID != 0) {
            queue.push_back(p);
            cout << "✅ Patient added.\n";
        }
    }

    void addPatientFront() {
        Patient p = inputPatient();
        if (p.ID != 0) {
            queue.insert(queue.begin(), p);
            cout << "✅ Emergency patient added to front.\n";
        }
    }

    void takeToDoctor() {
        if (queue.empty()) {
            cout << "🚫 No patients in queue. Please register a patient first using option 1 or 2.\n";
            return;
        }
        Patient p = queue.front();
        queue.erase(queue.begin());
        displayPatient(p);
        cout << "✅ Sent to doctor.\n";
    }

    void listPatients() const {
        if (queue.empty()) {
            cout << "🚫 No patients in queue.\n";
            return;
        }
        for (const auto& p : queue) {
            displayPatient(p);
            cout << "----------------------------------\n";
        }
    }

    void listPatientsBySpecialization(const string& spec) const {
        bool found = false;
        for (const auto& p : queue) {
            if (p.specialization == spec) {
                displayPatient(p);
                cout << "----------------------------------\n";
                found = true;
            }
        }
        if (!found) {
            cout << "🚫 No patients found for specialization: " << spec << "\n";
        }
    }
};

// -------------------- User Base Class --------------------
class User {
protected:
    string name;
    long long id;
public:
    virtual void dashboard(vector<Department>& departments) = 0;
    virtual ~User() {}
};

// -------------------- Doctor --------------------
class Doctor : public User {
private:
    string specialization;
public:
    Doctor(string n, long long i, string s) {
        name = n;
        id = i;
        specialization = s;
    }

    void dashboard(vector<Department>& departments) override {
        cout << "\n👨‍⚕️ Doctor Dashboard — Dr. " << name
            << " (" << specialization << ")\n";

        // Show only departments with patients of matching specialization
        vector<int> validIndexes;
        for (int i = 0; i < departments.size(); ++i) {
            for (const Patient& p : departments[i].getQueue()) {
                if (p.specialization == specialization) {
                    validIndexes.push_back(i);
                    break;
                }
            }
        }

        if (validIndexes.empty()) {
            cout << "🚫 No departments contain patients for your specialization.\n";
            return;
        }

        int choice;
        do {
            cout << "\nSelect Department to view patients:\n";
            for (int i = 0; i < validIndexes.size(); ++i)
                cout << i + 1 << ". " << departments[validIndexes[i]].getName() << "\n";
            cout << validIndexes.size() + 1 << ". Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice >= 1 && choice <= validIndexes.size()) {
                departments[validIndexes[choice - 1]].listPatientsBySpecialization(specialization);
            }
            else if (choice != validIndexes.size() + 1) {
                cout << "❌ Invalid choice.\n";
            }

        } while (choice != validIndexes.size() + 1);

        cout << "👋 Doctor session ended.\n";
    }
};

// -------------------- Administrator --------------------
class Administrator : public User {
public:
    Administrator(string n, long long i) {
        name = n;
        id = i;
    }

    void dashboard(vector<Department>& departments) override {
        for (Department& dept : departments) {
            int menu;
            do {
                cout << "\n🏥 Managing Department: " << dept.getName() << "\n";
                cout << "1. Add Normal Patient\n";
                cout << "2. Add Critically Ill Patient\n";
                cout << "3. Take Patient to Doctor\n";
                cout << "4. List All Patients\n";
                cout << "5. List by Specialization\n";
                cout << "6. Next Department\n";
                cout << "Choice: ";
                cin >> menu;

                switch (menu) {
                case 1: dept.addPatientEnd(); break;
                case 2: dept.addPatientFront(); break;
                case 3: dept.takeToDoctor(); break;
                case 4: dept.listPatients(); break;
                case 5: {
                    string spec = selectSpecialization();
                    dept.listPatientsBySpecialization(spec);
                    break;
                }
                case 6: break;
                default: cout << "❌ Invalid option.\n";
                }
            } while (menu != 6);
        }

        cout << "👋 Admin session ended.\n";
    }
};

// -------------------- Main --------------------
int main() {
    vector<Department> departments = {
        Department("General Clinic"),
        Department("Heart Clinic"),
        Department("Lung Clinic"),
        Department("Plastic Surgery")
    };

    string role;
    cout << "🔐 Login as (doctor/admin): ";
    cin >> role;

    User* user = nullptr;

    if (role == "doctor") {
        string docName, spec;
        long long docID;
        cout << "Enter your full name: ";
        cin.ignore();
        getline(cin, docName);
        cout << "Enter your ID: ";
        cin >> docID;
        spec = selectSpecialization();
        user = new Doctor(docName, docID, spec);
    }
    else if (role == "admin") {
        string adminName;
        long long adminID;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, adminName);
        cout << "Enter your ID: ";
        cin >> adminID;
        user = new Administrator(adminName, adminID);
    }
    else {
        cout << "❌ Invalid role.\n";
        return 0;
    }

    user->dashboard(departments);
    delete user;
    return 0;
}
