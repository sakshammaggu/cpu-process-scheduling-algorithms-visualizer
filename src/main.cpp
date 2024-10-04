#include <iostream>

#include "../include/roundRobin/roundRobin.h"
#include "../algorithms/roundRobin/roundRobin.cpp"

#include "../include/longestJobFirst/longestJobFirst.h"
#include "../algorithms/longestJobFirst/longestJobFirst.cpp"

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

void runLongestJobFirstTestCases() {
    cout << "Running Longest Job First Scheduler Test Cases\n";

    cout << "Test Case 1:\n";
    LJFScheduler scheduler1;
    scheduler1.addProcess(Process(1, 1, 2));  // Process 1: arrival time = 1, burst time = 2
    scheduler1.addProcess(Process(2, 2, 5));  // Process 2: arrival time = 2, burst time = 5
    scheduler1.addProcess(Process(3, 3, 3));  // Process 3: arrival time = 3, burst time = 3
    scheduler1.addProcess(Process(4, 4, 8));  // Process 4: arrival time = 4, burst time = 8
    scheduler1.execute();
    scheduler1.displayResults();
    scheduler1.displayGanttChart();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    cout << "Test Case 2:\n";
    LJFScheduler scheduler2;
    scheduler2.addProcess(Process(1, 1, 2)); // Process 1: arrival time = 1, burst time = 2
    scheduler2.addProcess(Process(2, 2, 4)); // Process 2: arrival time = 2, burst time = 4
    scheduler2.addProcess(Process(3, 3, 6)); // Process 3: arrival time = 3, burst time = 6
    scheduler2.addProcess(Process(4, 4, 8)); // Process 4: arrival time = 4, burst time = 8
    scheduler2.execute();
    scheduler2.displayResults();
    scheduler2.displayGanttChart();
}

int main() {
    runRoundRobinTestCases();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;

    runLongestJobFirstTestCases();

    cout<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
    
    return 0;
}