#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << " - Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Process " << i + 1 << " - Burst Time: ";
        cin >> processes[i].burstTime;
    }
    
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    // FCFS Scheduling
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

    // Display results
    cout << "\n" << setw(10) << "Process" << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time" << setw(15) << "Completion" 
         << setw(15) << "Turnaround" << setw(15) << "Waiting Time" << "\n";
    cout << string(85, '-') << "\n";

    float avgTurnaround = 0, avgWaiting = 0;
    for (int i = 0; i < n; i++) {
        cout << setw(10) << processes[i].id << setw(15) << processes[i].arrivalTime
             << setw(15) << processes[i].burstTime << setw(15) << processes[i].completionTime
             << setw(15) << processes[i].turnaroundTime << setw(15) << processes[i].waitingTime << "\n";
        avgTurnaround += processes[i].turnaroundTime;
        avgWaiting += processes[i].waitingTime;
    }

    avgTurnaround /= n;
    avgWaiting /= n;

    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << avgTurnaround << "\n";
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWaiting << "\n";

    return 0;
}