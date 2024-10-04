#include <iostream>
#include <iomanip>

#include "../../include/longestJobFirst/longestJobFirst.h"

using namespace std;

LJFScheduler::LJFScheduler() {
    // Initialize current time to 0
    this->currentTime = 0;
}

void LJFScheduler::addProcess(const Process& process) {
    // Add the given process to the list of processes
    processes.push_back(process);
}

void LJFScheduler::execute() {
    // Execute the Longest Job First (LJF) scheduling algorithm
    int completedProcesses = 0;

    while (completedProcesses < processes.size()) {
        int longestIndex = -1;
        int longestBurst = -1;

        // Select the process with the longest burst time among arrived processes
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime && processes[i].burstTime > longestBurst) {
                longestBurst = processes[i].burstTime;
                longestIndex = i;
            }
        }

        if (longestIndex != -1) {
            // Process the longest job
            Process &process = processes[longestIndex];
            currentTime += process.remainingTime;  // Move the time forward by the remaining burst time
            process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
            process.turnaroundTime = process.burstTime + process.waitingTime;
            process.remainingTime = 0;             // Mark the process as completed
            ganttChart.push_back({process.id, currentTime}); // Store ID and end time
            ++completedProcesses;
        } else {
            // If no process has arrived yet, advance the time to the next process's arrival
            int nextArrivalTime = 1e9;
            for (const auto& process : processes) {
                if (process.remainingTime > 0) {
                    nextArrivalTime = min(nextArrivalTime, process.arrivalTime);
                }
            }
            currentTime = max(currentTime, nextArrivalTime);
        }
    }
}

void LJFScheduler::displayResults() const {
    // Display table headers
    cout << setw(10) << "Process" 
         << setw(15) << "Arrival Time" 
         << setw(15) << "Burst Time" 
         << setw(15) << "Waiting Time" 
         << setw(15) << "Turnaround Time" << "\n";
    
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Display the results for each process
    for (const auto& process : processes) {
        cout << setw(10) << "P" + to_string(process.id)
             << setw(15) << process.arrivalTime
             << setw(15) << process.burstTime
             << setw(15) << process.waitingTime
             << setw(15) << process.turnaroundTime << "\n";

        // Accumulate total waiting time and turnaround time for averages
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    // Calculate and display average waiting time and average turnaround time
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void LJFScheduler::displayGanttChart() const {
    // Display Gantt chart with process IDs
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