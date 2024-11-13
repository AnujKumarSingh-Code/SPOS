#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;      // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int ct;      // Completion Time
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int priority; // Priority (lower number means higher priority)
    bool comp;   // Completion status
};

bool arrivalSort(Process a, Process b) {
    if (a.at == b.at)
        return a.priority < b.priority; // Sort by priority if arrival times are the same
    return a.at < b.at; // Otherwise, sort by arrival time
}

void priorityScheduling(vector<Process>& p) {
    int n = p.size();
    int ctm = 0; // Current time
    int cnt = 0; // Count of completed processes

    while (cnt != n) {
        int ind = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].comp && p[i].at <= ctm && p[i].priority < highestPriority) {
                ind = i;
                highestPriority = p[i].priority;
            }
        }

        if (ind == -1) {
            ctm++; // Increment time if no process is available to execute
        } else {
            // Execute the process
            p[ind].ct = ctm + p[ind].bt; // Completion time
            p[ind].tat = p[ind].ct - p[ind].at; // Turnaround time
            p[ind].wt = p[ind].tat - p[ind].bt; // Waiting time
            p[ind].comp = true; // Mark process as completed

            ctm = p[ind].ct; // Move current time to the completion time of this process
            cnt++; // Increase count of completed processes
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> p(n);

    cout << "Enter process ID, Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].at >> p[i].bt >> p[i].priority;
        p[i].comp = false; // Initially, no process is completed
    }

    // Sort processes by arrival time, and by priority if arrival times are equal
    sort(p.begin(), p.end(), arrivalSort);

    // Apply Priority Scheduling
    priorityScheduling(p);

    // Display the results
    for(int i=0;i<n;i++){
        cout<<p[i].ct<<" "<<p[i].wt<<" "<<p[i].tat<<endl;
    }

    return 0;
}


/***Priority Scheduling** is a CPU scheduling algorithm where each process is assigned a priority, and the CPU is allocated to the process with the highest priority (or lowest number if priorities are ranked numerically). 

### Key Concepts of Priority Scheduling

1. **Priority Assignment**: Each process has a priority level associated with it. This priority can be set by the user or system, based on factors like memory requirements, process type, or importance. Priorities can either be:
   - **Static**: Assigned when the process is created and doesn’t change.
   - **Dynamic**: Adjusted over time, possibly depending on factors like the amount of CPU used or waiting time.

2. **Types of Priority Scheduling**:
   - **Preemptive Priority Scheduling**: If a new process arrives with a higher priority than the current running process, it immediately preempts the CPU.
   - **Non-Preemptive Priority Scheduling**: The CPU isn’t released until the current process finishes. Even if a new process with a higher priority arrives, it will wait until the current process completes.

3. **Priority Levels**:
   - Priority can be represented numerically (e.g., 1 to 10), with either:
     - Lower numbers representing higher priority (commonly used in practice).
     - Higher numbers representing higher priority (depends on system implementation).

### Calculations in Priority Scheduling

For each process, the following metrics are typically calculated to evaluate scheduling performance:

- **Waiting Time (WT)**: The total time a process spends in the ready queue waiting for its turn.
- **Turnaround Time (TAT)**: The total time from when a process arrives until it finishes execution, calculated as:
  \[
  \text{Turnaround Time} = \text{Completion Time} - \text{Arrival Time}
  \]

### Example of Priority Scheduling (Non-Preemptive)

Let’s go through a simple example with non-preemptive priority scheduling:

Suppose we have the following processes:

| Process | Arrival Time | Burst Time | Priority |
|---------|--------------|------------|----------|
| P1      | 0            | 10         | 2        |
| P2      | 2            | 4          | 1        |
| P3      | 3            | 6          | 3        |

**Steps to Execute Non-Preemptive Priority Scheduling**:

1. **At Time 0**: Process P1 is the only available process, so it starts executing.
2. **At Time 2**: Process P2 arrives. Since it has a higher priority (lower priority number) than P1, in a non-preemptive system, it must wait until P1 finishes.
3. **At Time 10**: P1 finishes. P2, having the highest priority among available processes, starts executing.
4. **At Time 14**: P2 finishes, and P3 begins executing as it is the only remaining process.
5. **At Time 20**: P3 finishes.

**Final Metrics**:

| Process | Completion Time | Turnaround Time | Waiting Time |
|---------|-----------------|-----------------|--------------|
| P1      | 10              | 10              | 0            |
| P2      | 14              | 12              | 8            |
| P3      | 20              | 17              | 11           |

- **Average Waiting Time**: \((0 + 8 + 11) / 3 = 6.33\)
- **Average Turnaround Time**: \((10 + 12 + 17) / 3 = 13\)

### Advantages and Disadvantages of Priority Scheduling

#### Advantages:
- Suitable for time-sensitive tasks, as high-priority tasks are handled first.
- Can ensure certain critical processes get CPU time as needed.

#### Disadvantages:
- **Starvation**: Low-priority processes may get indefinitely delayed if higher-priority processes keep arriving.
- **Aging Solution**: To address starvation, priorities can increase with waiting time, ensuring that longer-waiting processes eventually get CPU time.

### Summary

Priority scheduling is a flexible algorithm used in systems where certain processes or tasks are more critical than others. In systems requiring timely responses (like real-time systems), preemptive priority scheduling is often used, ensuring that high-priority tasks interrupt lower-priority ones when necessary. Non-preemptive scheduling is simpler but may lead to higher wait times for lower-priority processes.*/


/*This code demonstrates **Non-Preemptive Priority Scheduling** in C++. Let's go through it step-by-step to understand how each part functions and implements the algorithm.

### Code Explanation

1. **Structure Definition**:
   ```cpp
   struct Process {
       int id;       // Process ID
       int at;       // Arrival Time
       int bt;       // Burst Time
       int ct;       // Completion Time
       int wt;       // Waiting Time
       int tat;      // Turnaround Time
       int priority; // Priority (lower number means higher priority)
       bool comp;    // Completion status
   };
   ```
   This structure `Process` is defined to hold information for each process:
   - `id`: Unique identifier for the process.
   - `at`: Arrival time.
   - `bt`: Burst time, the time required for execution.
   - `ct`: Completion time, indicating when a process finishes.
   - `wt`: Waiting time, the time spent waiting in the queue before execution.
   - `tat`: Turnaround time, the total time from arrival to completion.
   - `priority`: Priority level (lower number = higher priority).
   - `comp`: Boolean flag indicating if the process is completed.

2. **Sorting by Arrival Time (and Priority)**:
   ```cpp
   bool arrivalSort(Process a, Process b) {
       if (a.at == b.at)
           return a.priority < b.priority; // Sort by priority if arrival times are the same
       return a.at < b.at; // Otherwise, sort by arrival time
   }
   ```
   This function `arrivalSort` is used to sort the processes:
   - Primarily by `arrival time` (`at`).
   - If two processes have the same arrival time, it sorts them by priority (`priority`), with a lower priority value indicating a higher priority.

3. **Priority Scheduling Logic**:
   ```cpp
   void priorityScheduling(vector<Process>& p) {
       int n = p.size();
       int ctm = 0; // Current time
       int cnt = 0; // Count of completed processes

       while (cnt != n) {
           int ind = -1;
           int highestPriority = INT_MAX;

           for (int i = 0; i < n; i++) {
               if (!p[i].comp && p[i].at <= ctm && p[i].priority < highestPriority) {
                   ind = i;
                   highestPriority = p[i].priority;
               }
           }

           if (ind == -1) {
               ctm++; // Increment time if no process is available to execute
           } else {
               p[ind].ct = ctm + p[ind].bt; // Completion time
               p[ind].tat = p[ind].ct - p[ind].at; // Turnaround time
               p[ind].wt = p[ind].tat - p[ind].bt; // Waiting time
               p[ind].comp = true; // Mark process as completed

               ctm = p[ind].ct; // Move current time to the completion time of this process
               cnt++; // Increase count of completed processes
           }
       }
   }
   ```
   This function `priorityScheduling` implements the **non-preemptive priority scheduling**:

   - **Variables**:
     - `ctm` (Current Time): Tracks the current time of the CPU.
     - `cnt` (Count): Counts completed processes.
   - **Loop**:
     - Continues until all processes (`cnt != n`) are completed.
     - In each iteration, it searches for the process with the highest priority that has arrived (`at <= ctm`) and is not yet completed (`comp == false`).
     - If no process is available, it increments `ctm` to simulate the passing of time.
   - **Execution**:
     - Once the highest-priority process is found, it "executes" this process by:
       - Calculating `ct` (completion time) as `ctm + bt`.
       - Calculating `tat` (turnaround time) as `ct - at`.
       - Calculating `wt` (waiting time) as `tat - bt`.
       - Setting `comp = true` to mark it completed.
       - Updating `ctm` to the completion time of this process.

4. **Main Function**:
   ```cpp
   int main() {
       int n;
       cout << "Enter the number of processes: ";
       cin >> n;
       vector<Process> p(n);

       cout << "Enter process ID, Arrival Time, Burst Time, and Priority for each process:\n";
       for (int i = 0; i < n; i++) {
           cin >> p[i].id >> p[i].at >> p[i].bt >> p[i].priority;
           p[i].comp = false; // Initially, no process is completed
       }

       sort(p.begin(), p.end(), arrivalSort); // Sort processes by arrival time, and by priority if arrival times are equal
       priorityScheduling(p); // Apply Priority Scheduling

       // Display the results
       for(int i = 0; i < n; i++) {
           cout << "Process ID: " << p[i].id
                << " Completion Time: " << p[i].ct
                << " Waiting Time: " << p[i].wt
                << " Turnaround Time: " << p[i].tat << endl;
       }

       return 0;
   }
   ```
   - **Input**:
     - Prompts the user for the number of processes and for each process's `id`, `arrival time`, `burst time`, and `priority`.
     - Initializes `comp = false` for all processes.
   - **Sorting**:
     - Sorts the processes by arrival time and priority.
   - **Scheduling**:
     - Calls `priorityScheduling` to execute processes according to priority.
   - **Output**:
     - Displays each process’s `id`, `completion time`, `waiting time`, and `turnaround time`.

### Example Walkthrough

Suppose we have three processes with the following attributes:

| Process ID | Arrival Time | Burst Time | Priority |
|------------|--------------|------------|----------|
| 1          | 0            | 4          | 2        |
| 2          | 1            | 3          | 1        |
| 3          | 2            | 1          | 3        |

3
1 0 4 2
2 1 3 1
3 2 1 3


**Execution**:

1. **Time 0**: Process 1 arrives and begins execution.
2. **Time 1**: Process 2 arrives and has a higher priority than Process 1 but cannot preempt (non-preemptive scheduling).
3. **Time 4**: Process 1 completes, and Process 2 starts executing.
4. **Time 7**: Process 2 completes, and Process 3 starts.
5. **Time 8**: Process 3 completes.

*/