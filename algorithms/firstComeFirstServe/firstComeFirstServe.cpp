#include <iostream>
#include <algorithm>
#include <iomanip>

#include "../../include/firstComeFirstServe/firstComeFirstServe.h"

using namespace std;

// Constructor to initialize the scheduler
FCFSScheduler::FCFSScheduler() {
    this->currentTime = 0; // Initialize current time to 0
}

void FCFSScheduler::addProcess(const Process& process) {
    processes.push_back(process); // Add process to the list
}

void FCFSScheduler::execute() {
    // Sort processes by their arrival time
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    for (auto& process : processes) {
        // If the current time is less than the process arrival time, CPU is idle
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime; // CPU remains idle until process arrives
        }

        ganttChart.push_back({process.id, currentTime}); // Record the start time in Gantt chart
        currentTime += process.burstTime; // Advance current time by burst time
        ganttChart.push_back({process.id, currentTime}); // Record the end time in Gantt chart

        // Calculate waiting and turnaround time for the process
        process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
        process.turnaroundTime = process.burstTime + process.waitingTime;
    }
}

void FCFSScheduler::displayResults() const {
    cout << setw(10) << "Process" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time" 
         << setw(15) << "Waiting Time" 
         << setw(15) << "Turnaround Time" << "\n";

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (const auto& process : processes) {
        cout << setw(10) << "P" + to_string(process.id)
             << setw(15) << process.arrivalTime
             << setw(15) << process.burstTime
             << setw(15) << process.waitingTime
             << setw(15) << process.turnaroundTime << "\n";

        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    // Calculate averages
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

    // Display averages
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void FCFSScheduler::displayGanttChart() const {
    // Display the Gantt chart with process IDs
    cout << "\nGantt Chart:\n";
    for (const auto& entry : ganttChart) {
        cout << "| P" << entry.first << " ";  // Process ID
    }
    cout << "|\n";

    // Display the time markers under the Gantt chart
    cout << "0"; // Start time
    for (const auto& entry : ganttChart) {
        cout << "    " << entry.second;  // End time of each process
    }
    cout << endl;
}