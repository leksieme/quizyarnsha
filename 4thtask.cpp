#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
#include <iostream>
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main() {
    pid_t pid1, pid2, pid3;
    int status;
    
    cout << "========================================" << endl;
    cout << "FORK WITH WAIT SYSTEM CALL DEMONSTRATION" << endl;
    cout << "========================================" << endl;
    cout << "Main Parent Process PID: " << getpid() << endl << endl;
    
    // CREATE FIRST CHILD PROCESS
    pid1 = fork();
    if (pid1 == 0) {
        // Child Process 1
        cout << "Child Process 1:" << endl;
        cout << "  Process ID: " << getpid() << endl;
        cout << "  Parent ID: " << getppid() << endl;
        cout << "  Status: Child Process 1 is running..." << endl;
        sleep(1);
        cout << "  Child Process 1 completed!" << endl;
        exit(0);
    }
    
    // CREATE SECOND CHILD PROCESS
    pid2 = fork();
    if (pid2 == 0) {
        // Child Process 2
        cout << "Child Process 2:" << endl;
        cout << "  Process ID: " << getpid() << endl;
        cout << "  Parent ID: " << getppid() << endl;
        cout << "  Status: Child Process 2 is running..." << endl;
        sleep(2);
        cout << "  Child Process 2 completed!" << endl;
        exit(0);
    }
    
    // CREATE THIRD CHILD PROCESS
    pid3 = fork();
    if (pid3 == 0) {
        // Child Process 3
        cout << "Child Process 3:" << endl;
        cout << "  Process ID: " << getpid() << endl;
        cout << "  Parent ID: " << getppid() << endl;
        cout << "  Status: Child Process 3 is running..." << endl;
        sleep(3);
        cout << "  Child Process 3 completed!" << endl;
        exit(0);
    }
    
    // PARENT PROCESS WAITS FOR ALL CHILDREN
    cout << "\nParent Process waiting for all children..." << endl;
    cout << "Parent PID: " << getpid() << endl << endl;
    
    // Wait for first child
    cout << "Waiting for Child Process 1 (PID: " << pid1 << ")..." << endl;
    waitpid(pid1, &status, 0);
    cout << "Child Process 1 has finished." << endl << endl;
    
    // Wait for second child
    cout << "Waiting for Child Process 2 (PID: " << pid2 << ")..." << endl;
    waitpid(pid2, &status, 0);
    cout << "Child Process 2 has finished." << endl << endl;
    
    // Wait for third child
    cout << "Waiting for Child Process 3 (PID: " << pid3 << ")..." << endl;
    waitpid(pid3, &status, 0);
    cout << "Child Process 3 has finished." << endl << endl;
    
    cout << "========================================" << endl;
    cout << "All child processes completed!" << endl;
    cout << "Parent Process " << getpid() << " is exiting..." << endl;
    cout << "========================================" << endl;
    
    return 0;
}
void roundRobin(vector<Process>& processes, int timeQuantum) {
    queue<Process*> readyQueue;
    int currentTime = 0;
    int completed = 0;
    
    sort(processes.begin(), processes.end(), 
         [](const Process& a, const Process& b) {
             return a.arrivalTime < b.arrivalTime;
         });
    
    int idx = 0;
    
    while (completed < processes.size()) {
        // Add arriving processes to ready queue
        while (idx < processes.size() && processes[idx].arrivalTime <= currentTime) {
            readyQueue.push(&processes[idx]);
            idx++;
        }
        
        if (readyQueue.empty()) {
            currentTime = processes[idx].arrivalTime;
            continue;
        }
        
        Process* current = readyQueue.front();
        readyQueue.pop();
        
        int executeTime = min(timeQuantum, current->remainingTime);
        currentTime += executeTime;
        current->remainingTime -= executeTime;
        
        // Add newly arrived processes
        while (idx < processes.size() && processes[idx].arrivalTime <= currentTime) {
            readyQueue.push(&processes[idx]);
            idx++;
        }
        
        if (current->remainingTime == 0) {
            current->completionTime = currentTime;
            current->turnaroundTime = current->completionTime - current->arrivalTime;
            current->waitingTime = current->turnaroundTime - current->burstTime;
            completed++;
        } else {
            readyQueue.push(current);
        }
    }
}

void display(const vector<Process>& processes) {
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime 
             << "\t" << p.completionTime << "\t\t" << p.turnaroundTime 
             << "\t\t" << p.waitingTime << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 8, 8, 0, 0, 0},
        {2, 1, 4, 4, 0, 0, 0},
        {3, 2, 2, 2, 0, 0, 0},
        {4, 3, 1, 1, 0, 0, 0}
    };
    
    int timeQuantum = 2;
    
    roundRobin(processes, timeQuantum);
    display(processes);
    
    return 0;
}