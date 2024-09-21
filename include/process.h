#ifndef PROCESS_H
#define PROCESS_H

// Class representing a process in the CPU scheduling simulation
class Process {
public:
    int id;                // Unique ID of the process
    int arrivalTime;       // Time at which the process arrives in the ready queue
    int burstTime;         // Total CPU burst time (execution time) required by the process
    int remainingTime;     // Remaining CPU burst time that the process needs
    int waitingTime;       // Total waiting time for the process (in the ready queue)
    int turnaroundTime;    // Total turnaround time (completion time - arrival time)
    
    // Constructor to initialize the process with its ID, arrival time, and burst time
    Process(int id, int arrivalTime, int burstTime) {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
        this->remainingTime = burstTime; // Initially, remaining time is the same as burst time
        this->waitingTime = 0;           // Waiting time is initialized to 0
        this->turnaroundTime = 0;        // Turnaround time is initialized to 0
    }
};

#endif