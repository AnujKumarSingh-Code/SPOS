#include<bits/stdc++.h>
using namespace std;

struct Process{
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;
    bool comp;
};

bool comp(Process a, Process b){
    return a.at < b.at; // Sort by arrival time initially
}

void premptiveSJF(vector<Process>& p){
    int n = p.size();
    int cnt = 0;
    int ctm = 0;
    
    while(cnt != n){
        int ind = -1, mn = INT_MAX;
        for(int i = 0; i < n; i++){
            if(!p[i].comp && p[i].at <= ctm && p[i].rt < mn){
                ind = i;
                mn = p[i].rt;
            }
        }
        
        if(ind == -1) {
            ctm++;
        } else {
            p[ind].rt--;
            if(p[ind].rt == 0){
                p[ind].comp = true;
                p[ind].ct = ctm + 1; // Completion time is current time + 1
                p[ind].wt = p[ind].ct - p[ind].at - p[ind].bt;
                p[ind].tat = p[ind].wt + p[ind].bt;
                cnt++;
            }
            ctm++;
        }
    }
}

int main(){
    int n;
    
    cin >> n;
    vector<Process> p(n);
    
    
    for(int i = 0; i < n; i++){
        cin >> p[i].id >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].comp = false;
    }
    
    sort(p.begin(), p.end(), comp); // Sort by arrival time initially
    premptiveSJF(p);
    
    // Sort by process ID before output
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.id < b.id;
    });
    
    for(int i = 0; i < n; i++){
        cout << "Process ID: " << p[i].id << " Completion Time: " << p[i].ct 
             << " Waiting Time: " << p[i].wt << " Turnaround Time: " << p[i].tat << endl;
    }
}





// This code implements the Preemptive Shortest Job First (SJF) scheduling algorithm, also known as Shortest Remaining Time First (SRTF). In this algorithm, at each time unit, the process with the smallest remaining burst time is chosen for execution, and if a new process arrives with a shorter burst time, it preempts the current process.

// Let’s go over the code and its functionality step by step.

// Structure and Variables
// Struct Process:

// id: Process ID.
// at: Arrival Time.
// bt: Burst Time (total time required by the process).
// rt: Remaining Time (initially equal to bt, and decrements as the process runs).
// ct: Completion Time.
// wt: Waiting Time.
// tat: Turnaround Time.
// comp: Completion flag to mark if the process has finished executing.
// Comparison Function comp:

// This function sorts processes based on their arrival times (at), so processes that arrive earlier are considered first.
// Preemptive SJF Scheduling Function: premptiveSJF
// This function performs the core scheduling by simulating the process execution in real-time.

// Initialize Counters:

// n holds the number of processes.
// cnt counts completed processes.
// ctm (Current Time) tracks the simulated clock time.
// While Loop (cnt != n):

// The loop runs until all processes have completed.
// Process Selection Loop:

// For each time unit (ctm), it scans all processes to find the one that meets these conditions:
// The process has not completed (!p[i].comp).
// The process has arrived (p[i].at <= ctm).
// The process has the smallest remaining time (p[i].rt < mn).
// Execution Logic:

// If a process with the shortest remaining time is found:
// It decrements its remaining time (p[ind].rt--).
// If p[ind].rt becomes 0, the process completes:
// comp is set to true.
// Completion time (ct) is set as the current time + 1.
// Waiting time (wt) is calculated as:
// Waiting Time
// =
// Completion Time
// −
// Arrival Time
// −
// Burst Time
// Waiting Time=Completion Time−Arrival Time−Burst Time
// Turnaround time (tat) is the sum of waiting time and burst time:
// Turnaround Time
// =
// Waiting Time
// +
// Burst Time
// Turnaround Time=Waiting Time+Burst Time
// cnt is incremented to indicate one more process is completed.
// If no process is found (all are either completed or haven’t arrived), ctm increments by 1 to wait for the next arrival.
// Main Function main
// Input and Initialization:

// Reads n (number of processes).
// Reads each process’s id, at, and bt, setting rt to bt and initializing comp to false.
// Initial Sorting:

// Sorts processes by arrival time using comp.
// Scheduling:

// Calls premptiveSJF to simulate scheduling.
// Output:

// Sorts the processes by ID for organized output.
// Prints each process’s ID, completion time (ct), waiting time (wt), and turnaround time (tat).
// Example Execution
// Suppose we have the following input:

// plaintext
// Copy code
// 3
// 1 0 8
// 2 1 4
// 3 2 2
// For each process:

// Process 1 arrives at time 0 and needs 8 units of CPU time.
// Process 2 arrives at time 1 and needs 4 units.
// Process 3 arrives at time 2 and needs 2 units.
// The program would execute as follows:

// Time 0: Process 1 starts executing (it’s the only one available).
// Time 1: Process 2 arrives but has a shorter remaining time, so it preempts Process 1.
// Time 2: Process 3 arrives, which has an even shorter burst time, so it preempts Process 2.
// Time 4: Process 3 completes, and Process 2 resumes.
// Time 8: Process 2 completes, and Process 1 resumes.
// Time 16: Process 1 completes.
// After execution, the program calculates and outputs each process’s completion time, waiting time, and turnaround time.

// Summary
// This code efficiently schedules processes using the Shortest Remaining Time First algorithm, minimizing average waiting time by continuously checking for the process with the shortest remaining burst time. The preemptive nature of SRTF allows it to switch to new, shorter processes as they arrive, making it well-suited for time-sensitive, real-time applications.