#include <iostream>
#include <iomanip>

#include "../../include/roundRobin/roundRobin.h"

using namespace std;

RoundRobinScheduler::RoundRobinScheduler(int timeQuantum) {
    // Initialize the scheduler with the given time quantum and set current time to 0
    this->timeQuantum = timeQuantum;
    this->currentTime = 0;
}

void RoundRobinScheduler::addProcess(const Process& process) {
    // Add the given process to the list of processes to be scheduled
    processes.push_back(process);
}

void RoundRobinScheduler::execute() {
    // Execute the Round Robin scheduling algorithm
    bool done;
    while (true) {
        done = true;  // Assume all processes are completed
        for (auto &process : processes) {
            if (process.remainingTime > 0) {
                // If a process still has remaining execution time, it is not done
                done = false;

                if (process.remainingTime > timeQuantum) {
                    // If the remaining time is more than the time quantum, process for time quantum
                    currentTime += timeQuantum;
                    process.remainingTime -= timeQuantum;

                    // Record the process ID and the current time in the Gantt chart
                    ganttChart.push_back({process.id, currentTime});
                } else {
                    // If remaining time is less than or equal to time quantum, finish the process
                    currentTime += process.remainingTime;
                    process.waitingTime = currentTime - process.arrivalTime - process.burstTime;
                    process.turnaroundTime = process.burstTime + process.waitingTime;
                    process.remainingTime = 0;

                    // Record the process ID and the current time in the Gantt chart
                    ganttChart.push_back({process.id, currentTime});
                }
            }
        }

        // If all processes are completed, break out of the loop
        if (done) break;
    }
}

void RoundRobinScheduler::displayResults() const {
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

void RoundRobinScheduler::displayGanttChart() const {
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