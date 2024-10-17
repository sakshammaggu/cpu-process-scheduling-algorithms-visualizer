#include <iostream>
#include <algorithm>
#include <iomanip>

#include "../../include/shortestJobFirst/shortestJobFirst.h"

using namespace std;

// Constructor initializes the current time to 0
SJFScheduler::SJFScheduler() {
    this->currentTime = 0;
}

void SJFScheduler::addProcess(const Process& process) {
    processes.push_back(process); // Add the process to the list
}

void SJFScheduler::execute() {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    });

    vector<bool> isCompleted(processes.size(), false); // Track completed processes
    int completed = 0;

    while (completed != processes.size()) {
        int shortestIndex = -1;
        int minBurstTime = 1e9;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] && processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                shortestIndex = i;
            }
        }

        // If no process is found, increment time (CPU is idle)
        if (shortestIndex == -1) {
            ++currentTime;
            continue;
        }

        // Execute the shortest job
        Process &shortestProcess = processes[shortestIndex];
        ganttChart.push_back({shortestProcess.id, currentTime}); // Record start time
        currentTime += shortestProcess.burstTime; // Advance time by burst time
        ganttChart.push_back({shortestProcess.id, currentTime}); // Record end time

        // Calculate waiting time and turnaround time
        shortestProcess.waitingTime = currentTime - shortestProcess.arrivalTime - shortestProcess.burstTime;
        shortestProcess.turnaroundTime = shortestProcess.burstTime + shortestProcess.waitingTime;

        // Mark the process as completed
        isCompleted[shortestIndex] = true;
        ++completed;
    }
}

void SJFScheduler::displayResults() const {
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

void SJFScheduler::displayGanttChart() const {
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