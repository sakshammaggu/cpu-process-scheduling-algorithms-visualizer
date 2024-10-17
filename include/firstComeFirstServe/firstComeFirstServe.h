#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class FCFSScheduler {
private:
    vector<Process> processes; // List of processes to schedule
    vector<pair<int, int>> ganttChart; // Gantt chart stores process ID and end time
    int currentTime; // Keeps track of the current time in the CPU

public:
    FCFSScheduler(); // Constructor to initialize FCFS Scheduler
    void addProcess(const Process& process); // Function to add a process
    void execute(); // Function to execute the scheduling algorithm
    void displayResults() const; // Function to display the results
    void displayGanttChart() const; // Function to display the Gantt chart
};

#endif