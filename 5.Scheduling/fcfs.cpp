#include<bits/stdc++.h>
using namespace std;
struct Process{
    int id;
    int at;
    int bt;
    int wt;
    int tat;
};
bool comp(Process a,Process b){
    return a.id<b.id;
}
float avgWT(vector<Process>&p){
    int n=p.size();
    p[0].wt=0;
    float val=0;
    for(int i=1;i<n;i++){
        p[i].wt=p[i-1].at+p[i-1].bt+p[i-1].wt-p[i].at;
        if(p[i].wt<0) p[i].wt=0;
        val+=p[i].wt;
    }
    return val/float(n);
}
float avgTAT(vector<Process>&p){
    int n=p.size();
    p[0].tat=p[0].bt;
    float val=0;
    for(int i=1;i<n;i++){
        p[i].tat=p[i].wt+p[i].bt;
        val+=p[i].tat;
    }
    return val/float(n);
}
int main(){
    int n;cin>>n;
    vector<Process>p(n);
    for(int i=0;i<n;i++){
        cin>>p[i].id>>p[i].at>>p[i].bt;
        p[i].wt=0;
        p[i].tat=0;
    }
    sort(p.begin(),p.end(),comp);
    cout<<"Average Waiting Time: "<<avgWT(p)<<endl;
    cout<<"Average TAT: "<<avgTAT(p)<<endl;
    // for(int i=0;i<n;i++){
    //     cout<<p[i].wt<<" "<<p[i].tat<<endl;
    // }

}


/*This code demonstrates the First Come First Serve (FCFS) scheduling algorithm, which schedules processes based on their arrival times. In FCFS, the process that arrives first is executed first, making it a straightforward, non-preemptive scheduling technique. Here’s a breakdown of the code, including the theory and functionality of each part:

### Key Structure and Variables

1. **Struct `Process`**: Defines a process with the following attributes:
   - `id`: Process identifier.
   - `at`: Arrival time of the process.
   - `bt`: Burst time (CPU execution time required).
   - `wt`: Waiting time, calculated based on arrival and execution order.
   - `tat`: Turnaround time, which is the total time from arrival to completion.

2. **Function `comp`**: Used to sort processes by their ID in ascending order, ensuring the process order remains stable after initial input.

3. **Function `avgWT`**: Calculates the average waiting time across all processes.
   - **Waiting Time Calculation**: For each process `i`, the waiting time (`wt`) is calculated as:
     \[
     \text{wt[i]} = \text{at[i-1]} + \text{bt[i-1]} + \text{wt[i-1]} - \text{at[i]}
     \]
     This formula calculates the time the process has waited since its arrival. If the calculated waiting time is negative (meaning the CPU was idle until that process arrived), it is set to 0.
   - **Average Waiting Time**: The total waiting time for all processes is summed, then divided by the number of processes to obtain the average.

4. **Function `avgTAT`**: Calculates the average Turnaround Time (TAT) across all processes.
   - **Turnaround Time Calculation**: For each process `i`, the TAT is computed as:
     \[
     \text{tat[i]} = \text{wt[i]} + \text{bt[i]}
     \]
     TAT represents the time taken from a process’s arrival to its completion.
   - **Average TAT**: The total TAT for all processes is divided by the number of processes to get the average TAT.

### Code Explanation in Detail

1. **Input Section (`main` function)**:
   - Reads the number of processes (`n`) and their details (ID, arrival time, burst time).
   - Initializes `wt` and `tat` to zero for each process.
   
2. **Sorting**:
   - The `sort` function sorts the processes based on their ID to maintain order consistency (if it matters). The sorting could also be done based on arrival time for correct FCFS processing, but it is not strictly necessary if the input is already ordered by arrival.

3. **Calculation of Average Waiting Time and TAT**:
   - Calls `avgWT` and `avgTAT` functions to compute the respective averages. These functions go through the process list and compute waiting and turnaround times based on the arrival and burst times of each process.
   - Prints the average waiting time and TAT.

4. **Commented Loop**:
   - This loop (commented out) can be used to print individual waiting and turnaround times of each process if needed for detailed output.

### Example Walkthrough

Consider three processes with the following attributes:
- Process 1: `ID = 1`, `Arrival Time = 0`, `Burst Time = 4`
- Process 2: `ID = 2`, `Arrival Time = 1`, `Burst Time = 3`
- Process 3: `ID = 3`, `Arrival Time = 2`, `Burst Time = 2`

### Expected Output and Results
- The program outputs the average waiting time and average turnaround time.
- Waiting times and turnaround times are computed iteratively based on each process’s position in the list and previous calculations, aligning with the FCFS scheduling policy.

### Theory of FCFS Scheduling

- **Non-Preemptive**: Once a process starts execution, it runs to completion without interruption.
- **Convoy Effect**: Shorter processes may have to wait for longer ones to finish, leading to potentially higher waiting times.
- **Fairness**: Every process is scheduled based on arrival, ensuring that no process is skipped or starved.

This FCFS scheduling code is a simple yet effective example of basic CPU scheduling, handling the fundamental aspects of process management in a system.*/

/*CPU scheduling is a crucial function of the operating system (OS), responsible for managing the order and time for which processes access the CPU. In a multitasking environment, multiple processes are competing for CPU time, and efficient scheduling ensures that these processes are executed in a way that optimizes performance, improves responsiveness, and maximizes CPU utilization.

### Objectives of CPU Scheduling

1. **Maximize CPU Utilization**: Keep the CPU as busy as possible.
2. **Maximize Throughput**: Increase the number of processes completed per unit time.
3. **Minimize Turnaround Time**: Reduce the total time taken for a process to complete from arrival to exit.
4. **Minimize Waiting Time**: Reduce the time a process spends in the waiting queue.
5. **Minimize Response Time**: In interactive systems, reduce the time from submitting a request until the first response.

To achieve these objectives, various CPU scheduling algorithms are implemented. They are broadly categorized into non-preemptive and preemptive algorithms.

---

### Types of CPU Scheduling Algorithms

#### 1. First-Come, First-Served (FCFS)

- **Mechanism**: Processes are scheduled in the order of their arrival.
- **Characteristics**: Non-preemptive, simple to implement.
- **Advantages**: Easy to understand and manage; no starvation.
- **Disadvantages**: High waiting time for shorter processes if longer processes arrive first (convoy effect).
- **Example**: If three processes arrive with burst times 4, 2, and 1, FCFS executes them in the same order of arrival.

#### 2. Shortest Job First (SJF)

- **Mechanism**: The process with the shortest burst time is scheduled next.
- **Characteristics**: Can be non-preemptive or preemptive (Shortest Remaining Time First).
- **Advantages**: Minimizes average waiting time.
- **Disadvantages**: Can lead to starvation of longer processes.
- **Example**: Given processes with burst times 5, 9, and 3, SJF schedules them in the order of 3 → 5 → 9.

#### 3. Priority Scheduling

- **Mechanism**: Each process is assigned a priority, and processes with higher priority are executed first.
- **Characteristics**: Can be preemptive or non-preemptive.
- **Advantages**: Useful for ensuring important tasks get CPU time quickly.
- **Disadvantages**: May cause starvation of low-priority processes. Aging can be used to prevent starvation.
- **Example**: If processes have priorities 2, 1, and 3 (lower number = higher priority), they’ll be scheduled in the order of priority: 1 → 2 → 3.

#### 4. Round Robin (RR)

- **Mechanism**: Processes are assigned a fixed time quantum and are cycled through in a round-robin manner.
- **Characteristics**: Preemptive, ensuring fairness and equal distribution of CPU time.
- **Advantages**: Suitable for time-sharing systems; reduces response time.
- **Disadvantages**: Higher average waiting time if time quantum is not well-tuned.
- **Example**: With a time quantum of 4, if three processes have burst times 10, 4, and 7, RR cycles through each process until completion.

#### 5. Multilevel Queue Scheduling

- **Mechanism**: The ready queue is divided into multiple queues, each with its own scheduling policy (e.g., interactive, batch).
- **Characteristics**: Non-preemptive or preemptive, depending on queue configuration.
- **Advantages**: Provides flexibility for handling different process types.
- **Disadvantages**: Complex to manage and configure.
- **Example**: Interactive processes in a high-priority queue, while batch jobs are placed in a lower-priority queue.

#### 6. Multilevel Feedback Queue Scheduling

- **Mechanism**: Similar to multilevel queue but allows processes to move between queues based on execution characteristics.
- **Characteristics**: Preemptive, adapting to process behavior dynamically.
- **Advantages**: Reduces response time for interactive processes while adapting to long-running tasks.
- **Disadvantages**: Complexity in managing queues and transitions.
- **Example**: Shorter jobs that don’t complete in the top-priority queue move to lower-priority queues.

---

### Key CPU Scheduling Metrics

1. **CPU Utilization**: Percentage of time the CPU is actively working on processes.
2. **Throughput**: Number of processes completed in a given time frame.
3. **Turnaround Time**: Total time taken from process arrival to completion.
4. **Waiting Time**: Total time a process spends waiting in the ready queue.
5. **Response Time**: Time from process submission to the start of its execution.

---

### Preemptive vs. Non-Preemptive Scheduling

- **Preemptive Scheduling**: Allows interruption of processes. If a higher-priority or shorter job arrives, the current process may be paused. Examples include SJF (preemptive), Priority (preemptive), and Round Robin.
  
- **Non-Preemptive Scheduling**: Once a process starts, it runs until completion without interruption. Examples include FCFS and SJF (non-preemptive).

---

### Factors in Choosing a Scheduling Algorithm

- **System Type**: Interactive (like RR for equal time sharing) vs. Batch Processing (like FCFS for simplicity).
- **Process Behavior**: Short or long CPU bursts (e.g., SJF for short bursts).
- **Efficiency Needs**: Throughput vs. Response Time optimization.

CPU scheduling is a balancing act, where the algorithm choice impacts system performance, user satisfaction, and process prioritization. The ideal scheduling algorithm is determined by the specific needs of the OS and the types of processes it manages.*/
