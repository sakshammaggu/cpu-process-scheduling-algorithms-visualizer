#include <iostream>

#include "../include/roundRobin/roundRobin.h"
#include "../algorithms/roundRobin/roundRobin.cpp"
#include "../include/process.h"

using namespace std;

void runRoundRobinTestCases() {
    cout << "Running Round Robin Scheduler Test Cases\n";
    
    cout << "Test Case 1: \n";
    RoundRobinScheduler rr1(4);        // Time quantum of 4
    rr1.addProcess(Process(1, 0, 5));  // Process 1: arrival time = 0, burst time = 5
    rr1.addProcess(Process(2, 1, 8));  // Process 2: arrival time = 1, burst time = 8
    rr1.addProcess(Process(3, 2, 6));  // Process 3: arrival time = 2, burst time = 6
    rr1.execute();
    rr1.displayResults();
    rr1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "\nTest Case 2: \n";
    RoundRobinScheduler rr2(2);        // Time quantum of 2
    rr2.addProcess(Process(1, 0, 10)); // Process 1: arrival time = 0, burst time = 10
    rr2.addProcess(Process(2, 2, 4));  // Process 2: arrival time = 2, burst time = 4
    rr2.addProcess(Process(3, 3, 6));  // Process 3: arrival time = 3, burst time = 6
    rr2.addProcess(Process(4, 5, 9));  // Process 4: arrival time = 5, burst time = 9
    rr2.execute();
    rr2.displayResults();
    rr2.displayGanttChart();
}

int main() {
    runRoundRobinTestCases();
    return 0;
}