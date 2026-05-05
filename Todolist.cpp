#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

/*
    Priority levels for tasks
*/
enum Priority {
    LOW,
    MEDIUM,
    HIGH
};

/*
    Task structure
*/
struct Task {
    string description;
    bool completed;
    Priority priority;
};

/*
    Function declarations
*/
void showMenu();
void addTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void markCompleted(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);

void saveTasks(const vector<Task>& tasks);
void loadTasks(vector<Task>& tasks);

string priorityToString(Priority p);
Priority stringToPriority(const string& p);
void clearInput();

/*
    MAIN
*/
int main() {
    vector<Task> tasks;

    loadTasks(tasks); // Load saved tasks at startup

    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addTask(tasks); break;
            case 2: viewTasks(tasks); break;
            case 3: markCompleted(tasks); break;
            case 4: removeTask(tasks); break;
            case 5:
                saveTasks(tasks);
                cout << "Tasks saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}

/*
    MENU
*/
void showMenu() {
    cout << "\n========== TO-DO LIST MANAGER ==========\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Remove Task\n";
    cout << "5. Save & Exit\n";
    cout << "Enter choice: ";
}

/*
    ADD TASK
*/
void addTask(vector<Task>& tasks) {
    clearInput();

    Task t;
    cout << "Enter task description: ";
    getline(cin, t.description);

    int p;
    cout << "Priority (1=Low, 2=Medium, 3=High): ";
    cin >> p;

    t.priority = (p == 3) ? HIGH : (p == 2) ? MEDIUM : LOW;
    t.completed = false;

    tasks.push_back(t);

    cout << "Task added successfully!\n";
}

/*
    VIEW TASKS
*/
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\nNo tasks available.\n";
        return;
    }

    cout << "\n========== TASK LIST ==========\n";

    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". "
             << tasks[i].description
             << " | Priority: " << priorityToString(tasks[i].priority)
             << " | Status: " << (tasks[i].completed ? "Completed" : "Pending")
             << "\n";
    }
}

/*
    MARK COMPLETED
*/
void markCompleted(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    int idx;
    cout << "Enter task number: ";
    cin >> idx;

    if (idx >= 1 && idx <= tasks.size()) {
        tasks[idx - 1].completed = true;
        cout << "Marked as completed!\n";
    } else {
        cout << "Invalid index.\n";
    }
}

/*
    REMOVE TASK
*/
void removeTask(vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    int idx;
    cout << "Enter task number: ";
    cin >> idx;

    if (idx >= 1 && idx <= tasks.size()) {
        tasks.erase(tasks.begin() + idx - 1);
        cout << "Task removed.\n";
    } else {
        cout << "Invalid index.\n";
    }
}

/*
    SAVE TO FILE
    Format: description|completed|priority
*/
void saveTasks(const vector<Task>& tasks) {
    ofstream file("tasks.txt");

    for (const auto& t : tasks) {
        file << t.description << "|"
             << t.completed << "|"
             << t.priority << "\n";
    }

    file.close();
}

/*
    LOAD FROM FILE
*/
void loadTasks(vector<Task>& tasks) {
    ifstream file("tasks.txt");
    if (!file) return;

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Task t;
        string comp, pr;

        getline(ss, t.description, '|');
        getline(ss, comp, '|');
        getline(ss, pr, '|');

        t.completed = stoi(comp);
        t.priority = static_cast<Priority>(stoi(pr));

        tasks.push_back(t);
    }

    file.close();
}

/*
    HELPERS
*/
string priorityToString(Priority p) {
    if (p == HIGH) return "High";
    if (p == MEDIUM) return "Medium";
    return "Low";
}

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
