#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;     // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int ct;     // Completion Time
    int wt;     // Waiting Time
    int tat;    // Turnaround Time
};

void roundRobin(vector<Process>& p, int quantum) {
    int n = p.size();
    int ctm = 0; // Current time
    int cnt = 0; // Count of completed processes
    queue<int> q; // Queue to hold the indexes of processes
    vector<bool> inQueue(n, false); // Track if a process is in the queue

    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    // Push the first process into the queue
    q.push(0);
    inQueue[0] = true;

    while (cnt != n) {
        if (q.empty()) {
            // If no processes are in the queue, increment time until a process arrives
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && p[i].at <= ctm) {
                    q.push(i);
                    inQueue[i] = true;
                    break;
                }
            }
            ctm++;
            continue;
        }

        int i = q.front();
        q.pop();
        inQueue[i] = false;

        // Execute the process for a time slice (quantum)
        if (p[i].rt > quantum) {
            ctm += quantum;
            p[i].rt -= quantum;
        } else {
            ctm += p[i].rt;
            p[i].rt = 0;

            // Process is completed
            p[i].ct = ctm;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            cnt++;
        }

        // Add newly arrived processes to the queue
        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && p[j].at <= ctm && p[j].rt > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If the process is not finished, put it back into the queue
        if (p[i].rt > 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<Process> p(n);
    cout << "Enter process ID, Arrival Time, and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt; // Initialize remaining time with burst time
    }

    // Apply Round Robin Scheduling
    roundRobin(p, quantum);

    // Display the results
    cout << "\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t\t" << p[i].at << "\t\t" << p[i].bt << "\t\t" << p[i].ct
             << "\t\t" << p[i].wt << "\t\t" << p[i].tat << endl;
    }

    return 0;
}
/***Round Robin Scheduling** is a preemptive CPU scheduling algorithm used in operating systems to manage processes. It’s particularly effective for time-sharing systems and aims to ensure that each process receives a fair share of CPU time. Here’s a detailed breakdown of the theory and operation of Round Robin (RR) scheduling:

### Key Characteristics of Round Robin Scheduling

1. **Time Quantum**:
   - Round Robin scheduling divides CPU time into small, equal intervals called "time quantum" or "time slice."
   - Each process gets a time slice to execute, after which it is moved to the back of the queue if it hasn’t completed.
   - The time quantum should ideally be balanced. If it's too short, there’s a lot of context switching (overhead). If it’s too long, Round Robin behaves more like a First-Come, First-Served (FCFS) scheduler.

2. **Preemptive Nature**:
   - Unlike non-preemptive scheduling algorithms, Round Robin is preemptive, meaning the CPU can be taken away from a process if its time quantum expires.
   - This feature makes it suitable for interactive systems where multiple tasks need to be handled in small intervals.

3. **Process Queue**:
   - Processes are maintained in a circular queue, which helps rotate through processes in a cyclic order.
   - The first process in the queue is given CPU time until its time quantum expires or it completes.
   - If a process finishes before its time slice ends, it leaves the queue. If it doesn’t, it moves to the back of the queue to wait for another turn.

4. **Fairness**:
   - Round Robin ensures that every process gets a chance to run, which prevents the issue of starvation that can occur in priority-based or Shortest Job First (SJF) scheduling.

### Steps in Round Robin Scheduling

1. **Initialize the Queue**:
   - Load all processes into a queue in the order of their arrival times.
2. **Allocate CPU Time**:
   - Start with the first process in the queue, assign CPU time for a duration equal to the time quantum.
3. **Check Process Completion**:
   - If the process completes before the quantum expires, it leaves the queue.
   - If it hasn’t completed, the remaining burst time is updated, and the process is moved to the back of the queue.
4. **Move to the Next Process**:
   - The CPU then shifts to the next process in the queue.
5. **Repeat**:
   - This continues until all processes have finished execution.

### Calculating Metrics

To evaluate the efficiency of Round Robin, we calculate the following for each process:

1. **Completion Time (CT)**:
   - The time at which a process completes its execution.

2. **Turnaround Time (TAT)**:
   - \( TAT = CT - AT \)
   - The total time taken from arrival to completion of the process.

3. **Waiting Time (WT)**:
   - \( WT = TAT - BT \)
   - The time a process spends waiting in the queue.

### Example of Round Robin Scheduling

Let's take an example to see how Round Robin works with a time quantum of 4 units.

| Process | Arrival Time (AT) | Burst Time (BT) |
|---------|--------------------|-----------------|
| P1      | 0                 | 6               |
| P2      | 1                 | 8               |
| P3      | 2                 | 7               |
| P4      | 3                 | 3               |

#### Execution:

1. **Time 0**:
   - Process P1 starts, with a time quantum of 4.
   - P1 executes for 4 units, so it has 2 units remaining.
   - **CTM = 4**.

2. **Time 4**:
   - Process P2 starts with a time quantum of 4.
   - P2 executes for 4 units, so it has 4 units remaining.
   - **CTM = 8**.

3. **Time 8**:
   - Process P3 starts with a time quantum of 4.
   - P3 executes for 4 units, so it has 3 units remaining.
   - **CTM = 12**.

4. **Time 12**:
   - Process P4 starts with a time quantum of 4.
   - P4 requires only 3 units, so it completes.
   - **CTM = 15**.

5. **Time 15**:
   - Back to P1, which has 2 units left.
   - P1 completes after 2 units.
   - **CTM = 17**.

6. **Time 17**:
   - Back to P2, which has 4 units left.
   - P2 executes for 4 units and completes.
   - **CTM = 21**.

7. **Time 21**:
   - Back to P3, which has 3 units left.
   - P3 completes after 3 units.
   - **CTM = 24**.

#### Final Calculation:

| Process | Completion Time (CT) | Turnaround Time (TAT) | Waiting Time (WT) |
|---------|-----------------------|-----------------------|--------------------|
| P1      | 17                    | 17 - 0 = 17          | 17 - 6 = 11       |
| P2      | 21                    | 21 - 1 = 20          | 20 - 8 = 12       |
| P3      | 24                    | 24 - 2 = 22          | 22 - 7 = 15       |
| P4      | 15                    | 15 - 3 = 12          | 12 - 3 = 9        |

### Advantages of Round Robin

- **Fairness**: Every process gets equal opportunity.
- **Reduced Starvation**: By design, it prevents starvation since each process is given time repeatedly.
- **Responsive to Interactive Systems**: Suitable for systems requiring quick response times, like time-sharing systems.

### Disadvantages of Round Robin

- **High Context-Switching Overhead**: With many processes, the system may spend a lot of time switching between them.
- **Dependent on Quantum Size**: An inappropriate quantum size can lead to inefficiency (too small causes more switching, too large reduces interactivity).
  
*/


/*The provided code implements **Round Robin Scheduling** to manage CPU scheduling for multiple processes. Here’s a breakdown of how this program works.

### Code Explanation

#### Structures and Variables

1. **Process Structure**:
   - `id`: Process ID for identification.
   - `at`: Arrival Time, when the process arrives in the ready queue.
   - `bt`: Burst Time, the total CPU time the process requires.
   - `rt`: Remaining Time, which starts equal to `bt` and decreases as the process executes.
   - `ct`: Completion Time, when the process finishes execution.
   - `wt`: Waiting Time, total time the process waits in the queue.
   - `tat`: Turnaround Time, total time from arrival to completion.

2. **roundRobin Function**:
   - Takes `vector<Process>& p` (a list of processes) and `quantum` (time slice).
   - Manages the execution of processes based on the Round Robin algorithm.
   
#### Steps in the Round Robin Scheduling Function

1. **Initial Sorting**:
   - The processes are sorted by their `arrival time` to determine the order they appear in the queue.

2. **Queue and Time Management**:
   - A queue (`q`) holds the indices of processes currently ready to execute.
   - `inQueue` is a boolean vector to track whether a process is in the queue to avoid duplicates.
   - `ctm` (current time) keeps track of the time in the system, and `cnt` counts completed processes.

3. **Main Loop**:
   - The main loop continues until all processes are completed (`cnt == n`).
   - If `q` is empty, it increments `ctm` to move to the next available process by arrival time.

4. **Executing Processes**:
   - The process at the front of the queue is removed, and `inQueue` is updated to reflect this.
   - If the process's `remaining time (rt)` is greater than the time quantum, it executes for `quantum`, reduces `rt` by `quantum`, and updates `ctm` by `quantum`.
   - If the process completes within the quantum (i.e., `rt <= quantum`), `ctm` is updated by the remaining time, `rt` is set to 0, and the process's completion details (`ct`, `tat`, `wt`) are calculated. `cnt` increments as the process is marked complete.

5. **Queueing New Arrivals**:
   - For each process, if it hasn’t been queued (`inQueue[j] == false`), has arrived (`p[j].at <= ctm`), and still requires CPU time (`p[j].rt > 0`), it is added to `q`.

6. **Requeueing Incomplete Processes**:
   - If a process is not completed after its time quantum, it is placed back in the queue.

### Example Walkthrough

Suppose we have 3 processes with a time quantum of 4 units.

| Process | Arrival Time | Burst Time |
|---------|--------------|------------|
| P1      | 0            | 5          |
| P2      | 2            | 3          |
| P3      | 4            | 8          |

#### Execution Flow

1. **Initial State**:
   - Sort processes by arrival time.
   - At time `ctm = 0`, only P1 is available. P1 is added to `q`.

2. **Round 1**:
   - **P1** starts at `ctm = 0`. Since `bt (5) > quantum (4)`, it executes for 4 units, remaining time `rt` reduces to 1. `ctm` now becomes 4.
   - **P2** arrives at `ctm = 2`, so it’s also added to `q`.

3. **Round 2**:
   - **P2** executes at `ctm = 4` for 3 units (its `bt`). It completes execution (`rt` becomes 0), `ctm` updates to 7. Completion, turnaround, and waiting times are calculated for P2.
   - **P3** arrives at `ctm = 4`, so it’s added to `q`.

4. **Round 3**:
   - **P1** resumes at `ctm = 7`, completing its remaining 1 unit of `bt`. `ctm` becomes 8. P1 finishes with calculated completion, turnaround, and waiting times.

5. **Round 4**:
   - **P3** executes from `ctm = 8` for 4 units (time quantum). Its `rt` reduces to 4, and it’s requeued. `ctm` becomes 12.

6. **Round 5**:
   - **P3** executes again, completing its remaining 4 units. `ctm` becomes 16, and it exits the queue.

### Display Output

The output prints each process’s ID, arrival, burst, completion, waiting, and turnaround times.

*/