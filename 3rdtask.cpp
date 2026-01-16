#include <iostream> // Include header for input and output streams
#include <vector> // Include header for vector container
#include <algorithm> // Include header for algorithms like sort
#include <climits> // Include header for integer limits like INT_MAX
using namespace std; // Use the standard namespace

struct Process { // Define a structure to represent a process
    int id; // Process ID
    int arrivalTime; // Time when process arrives
    float burstTime; // Time required for process execution
    float completionTime; // Time when process completes
    float turnaroundTime; // Turnaround time (completion - arrival)
    float waitingTime; // Waiting time (turnaround - burst)
};

int main() { // Main function entry point
    int n; // Variable to store number of processes
    cout << "Enter number of processes: "; // Prompt user for number of processes
    cin >> n; // Read number of processes from input
    
    vector<Process> processes(n); // Create a vector of Process structures
    
    // Input process details
    for (int i = 0; i < n; i++) { // Loop through each process
        processes[i].id = i + 1; // Assign process ID starting from 1
        cout << "Process " << i + 1 << ":\n"; // Display process number
        cout << "  Arrival Time: "; // Prompt for arrival time
        cin >> processes[i].arrivalTime; // Read arrival time
        cout << "  Burst Time: "; // Prompt for burst time
        cin >> processes[i].burstTime; // Read burst time
    }
    
    // Sort by arrival time first
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) { // Sort processes by arrival time
        return a.arrivalTime < b.arrivalTime; // Compare arrival times
    });
    
    // SJF Scheduling
    float currentTime = 0; // Initialize current time to 0
    vector<bool> completed(n, false); // Vector to track completed processes
    
    for (int i = 0; i < n; i++) { // Loop for each process scheduling
        // Find process with shortest burst time among available processes
        float minBurst = INT_MAX; // Initialize minimum burst time to max
        int selectedProcess = -1; // Index of selected process
        
        for (int j = 0; j < n; j++) { // Loop through all processes
            if (!completed[j] && processes[j].arrivalTime <= currentTime  // Check if process is not completed and arrived
                && processes[j].burstTime < minBurst) { // And has shorter burst time
                minBurst = processes[j].burstTime; // Update min burst
                selectedProcess = j; // Select this process
            }
        }
        
        if (selectedProcess == -1) { // If no process is available
            // No process available, jump to next arrival
            for (int j = 0; j < n; j++) { // Find the next arriving process
                if (!completed[j]) { // If not completed
                    currentTime = processes[j].arrivalTime; // Set current time to its arrival
                    i--; // Decrement i to retry this iteration
                    break; // Break the loop
                }
            }
            continue; // Continue to next iteration
        }
        
        currentTime += processes[selectedProcess].burstTime; // Add burst time to current time
        processes[selectedProcess].completionTime = currentTime; // Set completion time
        processes[selectedProcess].turnaroundTime =  // Calculate turnaround time
            processes[selectedProcess].completionTime - processes[selectedProcess].arrivalTime; // Completion minus arrival
        processes[selectedProcess].waitingTime =  // Calculate waiting time
            processes[selectedProcess].turnaroundTime - processes[selectedProcess].burstTime; // Turnaround minus burst
        completed[selectedProcess] = true; // Mark process as completed
    }
    
    // Display results
    cout << "\n\nProcess Scheduling (SJF):\n"; // Print header for results
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n"; // Print table headers
    cout << "---\t-------\t-----\t----------\t----------\t-------\n"; // Print separator
    
    float avgWaiting = 0, avgTurnaround = 0; // Variables for averages
    
    for (int i = 0; i < n; i++) { // Loop to display each process
        cout << processes[i].id << "\t" << processes[i].arrivalTime << "\t" // Print process details
             << processes[i].burstTime << "\t" << processes[i].completionTime << "\t\t"
             << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << "\n";
        
        avgWaiting += processes[i].waitingTime; // Accumulate waiting time
        avgTurnaround += processes[i].turnaroundTime; // Accumulate turnaround time
    }
    
    cout << "\nAverage Waiting Time: " << avgWaiting / n << "\n"; // Print average waiting time
    cout << "Average Turnaround Time: " << avgTurnaround / n << "\n"; // Print average turnaround time
    
    return 0; // Return success
}