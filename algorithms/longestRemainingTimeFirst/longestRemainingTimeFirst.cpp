#include <iostream>
#include <iomanip>

#include "../../include/longestRemainingTimeFirst/longestRemainingTimeFirst.h"

using namespace std;

LRTFScheduler::LRTFScheduler() {
    this->currentTime = 0;  // Initialize current time to 0
}

void LRTFScheduler::addProcess(const Process& process) {
    processes.push_back(process);  // Add the incoming process to the process list
}

void LRTFScheduler::execute() {
    int totalProcesses = processes.size();  // Total number of processes
    int completed = 0;  // Tracks how many processes have completed execution
    vector<bool> isCompleted(totalProcesses, false);  // Tracks whether a process is completed or not

    while (completed != totalProcesses) {
        int longestIndex = -1;  // Index of the process with the longest remaining time
        int maxRemainingTime = -1;  // Tracks the maximum remaining time of the current processes

        // Find the process with the longest remaining time that has arrived and isn't completed
        for (int i = 0; i < totalProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] && processes[i].remainingTime > maxRemainingTime) {
                maxRemainingTime = processes[i].remainingTime;
                longestIndex = i;
            }
        }

        // If no valid process is found, increment the time (i.e., the CPU is idle)
        if (longestIndex == -1) {
            ganttChart.push_back({-1, ++currentTime});  // Record idle time in the Gantt Chart with process ID -1
            continue;
        }

        // Execute the process with the longest remaining time
        Process &longestProcess = processes[longestIndex];
        if (ganttChart.empty() || ganttChart.back().first != longestProcess.id) {
            ganttChart.push_back({longestProcess.id, currentTime});  // Start the process in the Gantt Chart
        }
        
        longestProcess.remainingTime -= 1;  // Execute for 1 unit of time
        currentTime += 1;  // Increment the current time

        // If the process has completed, calculate its waiting and turnaround times
        if (longestProcess.remainingTime == 0) {
            longestProcess.waitingTime = currentTime - longestProcess.arrivalTime - longestProcess.burstTime;
            longestProcess.turnaroundTime = longestProcess.burstTime + longestProcess.waitingTime;
            isCompleted[longestIndex] = true;  // Mark the process as completed
            completed++;
        }

        ganttChart.push_back({longestProcess.id, currentTime});  // Update the end time for the process
    }
}

void LRTFScheduler::displayResults() const {
    cout << setw(10) << "Process"
        << setw(15) << "Arrival Time"
        << setw(15) << "Burst Time"
        << setw(15) << "Waiting Time"
        << setw(15) << "Turnaround Time" << "\n";

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Display process information and calculate the totals for average calculation
    for (const auto& process : processes) {
        cout << setw(10) << "P" + to_string(process.id)
            << setw(15) << process.arrivalTime
            << setw(15) << process.burstTime
            << setw(15) << process.waitingTime
            << setw(15) << process.turnaroundTime << "\n";

        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    // Calculate and display average times
    double avgWaitingTime = static_cast<double>(totalWaitingTime) / processes.size();
    double avgTurnaroundTime = static_cast<double>(totalTurnaroundTime) / processes.size();

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

void LRTFScheduler::displayGanttChart() const {
    cout << "\nGantt Chart:\n";

    // Print process execution in Gantt Chart
    for (const auto& entry : ganttChart) {
        if (entry.first == -1) {
            cout << "| Idle ";
        } else {
            cout << "| P" << entry.first << " ";
        }
    }
    cout << "|\n";

    // Print timings
    cout << "0";  // Start time
    for (const auto& entry : ganttChart) {
        cout << "    " << entry.second;
    }
    cout << endl;
}