#ifndef LRTF_H
#define LRTF_H

#include <vector>
#include <utility>

#include "../process.h"

using namespace std;

class LRTFScheduler {
private:
    vector<Process> processes;  // Stores the list of processes
    vector<pair<int, int>> ganttChart;  // To store process ID and time points in the Gantt Chart
    int currentTime;  // Keeps track of the current time in the system

public:
    LRTFScheduler();  
    void addProcess(const Process& process);  // Adds a new process to the scheduler
    void execute();  // Executes the LRTF scheduling algorithm
    void displayResults() const;  // Displays the waiting time and turnaround time for each process
    void displayGanttChart() const;  // Displays the Gantt Chart for the executed processes
};

#endif