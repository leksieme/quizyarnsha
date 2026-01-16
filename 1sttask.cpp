#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;


int main() 
{
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
    
    // Wait for third child
    cout << "Waiting for Child Process 3 (PID: " << pid3 << ")..." << endl;
    waitpid(pid3, &status, 0);
    cout << "Child Process 3 has finished." << endl << endl;
    
    // Wait for second child
    cout << "Waiting for Child Process 2 (PID: " << pid2 << ")..." << endl;
    waitpid(pid2, &status, 0);
    cout << "Child Process 2 has finished." << endl << endl;
    
    // Wait for first child
    cout << "Waiting for Child Process 1 (PID: " << pid1 << ")..." << endl;
    waitpid(pid1, &status, 0);
    cout << "Child Process 1 has finished." << endl << endl;
    
    cout << "========================================" << endl;
    cout << "All child processes completed!" << endl;
    cout << "Parent Process " << getpid() << " is exiting..." << endl;
    cout << "========================================" << endl;
    
    return 0;
}
