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