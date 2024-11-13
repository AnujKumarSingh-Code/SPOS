#include <bits/stdc++.h>
using namespace std;

int firstFit(vector<int>& blocks, int req) {
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] >= req) {
            blocks[i] -= req;
            return i;
        }
    }
    return -1;
}

int bestFit(vector<int>& blocks, int req) {
    int ind = -1, mn = INT_MAX;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] >= req && blocks[i] - req < mn) {
            mn = blocks[i] - req;
            ind = i;
        }
    }
    if (ind != -1) blocks[ind] -= req;
    return ind;
}

int nextFit(vector<int>& blocks, int req, int lind) {
    int n = blocks.size();
    int i = lind;
    while (true) {
        if (blocks[i] >= req) {
            blocks[i] -= req;
            int ind = i;
            i = (i + 1) % n;  // Update last index
            return ind;
        }
        i = (i + 1) % n;
        if (i == lind) break;  // We've checked all blocks
    }
    return -1;
}

int worstFit(vector<int>& blocks, int req) {
    int ind = -1, mx = INT_MIN;
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i] >= req && blocks[i] - req > mx) {
            mx = blocks[i] - req;
            ind = i;
        }
    }
    if (ind != -1) blocks[ind] -= req;
    return ind;
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> req = {212, 417, 112, 426};

    cout << "\n--- First Fit ---\n";
    vector<int> blocksCopy = blocks;
    for (int r : req) {
        int result = firstFit(blocksCopy, r);
        cout << "Process " << r << " -> Block " << (result != -1 ? to_string(result) : "Not Allocated") << endl;
    }

    cout << "\n--- Best Fit ---\n";
    blocksCopy = blocks;
    for (int r : req) {
        int result = bestFit(blocksCopy, r);
        cout << "Process " << r << " -> Block " << (result != -1 ? to_string(result) : "Not Allocated") << endl;
    }

    cout << "\n--- Next Fit ---\n";
    blocksCopy = blocks;
    int lastIndex = 0;
    for (int r : req) {
        int result = nextFit(blocksCopy, r, lastIndex);
        cout << "Process " << r << " -> Block " << (result != -1 ? to_string(result) : "Not Allocated") << endl;
    }

    cout << "\n--- Worst Fit ---\n";
    blocksCopy = blocks;
    for (int r : req) {
        int result = worstFit(blocksCopy, r);
        cout << "Process " << r << " -> Block " << (result != -1 ? to_string(result) : "Not Allocated") << endl;
    }

    return 0;
}



/*Memory management in an Operating System (OS) is the process of handling and optimizing the use of computer memory (RAM). It ensures that each application and process has the necessary memory space to operate, and that the overall memory usage is efficient and secure. Effective memory management is crucial for system performance, as it prevents issues like memory fragmentation and application crashes due to insufficient memory.

Here are the key concepts in memory management:

### 1. **Memory Partitioning**
   - **Fixed Partitioning**: The memory is divided into fixed-sized partitions. Each partition can hold one process, and any unused space in the partition remains wasted (called *internal fragmentation*).
   - **Dynamic Partitioning**: The OS dynamically allocates memory space as needed. Partitions are sized based on the requirements of the process, reducing internal fragmentation. However, it can lead to *external fragmentation* (small gaps of unused memory between allocated spaces).

### 2. **Paging**
   - Paging divides both physical memory and logical memory into fixed-size blocks called *pages* and *page frames*, respectively. A page table maps each process page to a specific frame in physical memory.
   - Paging enables the OS to manage memory more flexibly, allowing non-contiguous memory allocation for processes, which helps avoid external fragmentation.

### 3. **Segmentation**
   - In segmentation, a program’s memory is divided into segments based on logical units like functions, data structures, or arrays. Each segment has a base address and length, and the segment table maps logical addresses to physical addresses.
   - Segmentation aligns with the logical structure of programs and allows for easier handling of code and data separately, although it can result in external fragmentation.

### 4. **Virtual Memory**
   - Virtual memory allows the OS to extend the available memory by using a portion of the hard disk as additional memory, known as a *swap space*.
   - When a process requires more memory than physically available, parts of it are stored on the disk and swapped in and out of physical memory as needed (this is called *paging* or *swapping*).
   - Virtual memory enables multitasking and memory-intensive applications on systems with limited physical memory.

### 5. **Memory Allocation Techniques**
   - **Best-fit**: Allocates the smallest available memory block that fits the process requirements, minimizing waste but can lead to fragmentation.
   - **First-fit**: Allocates the first memory block that is large enough, leading to faster allocation but potentially higher fragmentation.
   - **Worst-fit**: Allocates the largest available block, which may help reduce fragmentation by leaving bigger gaps.

### 6. **Page Replacement Algorithms**
   - When the OS runs out of page frames, it must decide which page to remove to make space for a new one. Page replacement algorithms optimize which page to evict:
     - **FIFO (First-In, First-Out)**: Removes the oldest page in memory.
     - **LRU (Least Recently Used)**: Removes the page that hasn’t been used for the longest time.
     - **Optimal**: Removes the page that will not be used for the longest period (ideal but requires future knowledge).

### 7. **Memory Protection**
   - Memory protection prevents processes from accessing memory allocated to other processes, which is essential for data security and system stability.
   - Techniques like *bound registers* and *keys* help isolate memory and avoid accidental or malicious interference among processes.

### 8. **Swapping**
   - Swapping is the process of temporarily moving an inactive process from RAM to the swap space (disk) to free up memory for active processes.
   - It allows the OS to manage more processes simultaneously by dynamically adjusting active memory usage.

### 9. **Fragmentation**
   - **Internal Fragmentation**: Occurs when allocated memory is larger than the required memory, leaving unused space within the allocation.
   - **External Fragmentation**: Happens when free memory is split into small blocks, making it difficult to allocate large continuous blocks to new processes.
   - Memory compaction can help by reorganizing memory to consolidate free space.

### 10. **Cache Memory**
   - Cache memory sits between the CPU and main memory and stores frequently accessed data and instructions to improve performance.
   - The OS and hardware use algorithms to manage cache content, ensuring that frequently used information is readily available to reduce access time.

### Key Goals of Memory Management

1. **Efficient Memory Utilization**: Ensuring that all memory is optimally used.
2. **Fast Access**: Minimizing access time to memory for active processes.
3. **Security and Protection**: Isolating processes to prevent unauthorized access.
4. **Support for Multitasking**: Allowing multiple processes to run concurrently.

Through memory management, an OS can provide a stable, efficient environment for applications, balancing performance, memory availability, and process security.*/

/*This code demonstrates different memory allocation strategies: First Fit, Best Fit, Next Fit, and Worst Fit. Each strategy attempts to allocate a memory block for a given process's memory request based on a specific rule. Here’s a breakdown of each function and how it operates within the program.

### Key Variables
- `blocks`: A vector representing memory blocks with different sizes.
- `req`: A vector containing memory requests for different processes.
- `blocksCopy`: Used to reset the blocks' state for each allocation method.

### 1. **First Fit Allocation**
   - **Algorithm**: This function scans the list of blocks from the beginning, searching for the first block large enough to satisfy the process's memory request. 
   - **Code Explanation**:
     ```cpp
     int firstFit(vector<int>& blocks, int req) {
         for (int i = 0; i < blocks.size(); i++) {
             if (blocks[i] >= req) {
                 blocks[i] -= req;
                 return i;
             }
         }
         return -1;
     }
     ```
   - It iterates through each block. If a block is found with a size greater than or equal to `req`, it allocates the block by reducing its size by `req`, returning the block index. If no block is found, it returns `-1`, indicating that the allocation was unsuccessful.

### 2. **Best Fit Allocation**
   - **Algorithm**: This function searches for the smallest block that can fit the process's memory request. It minimizes wasted space by choosing the smallest possible block that can hold the request.
   - **Code Explanation**:
     ```cpp
     int bestFit(vector<int>& blocks, int req) {
         int ind = -1, mn = INT_MAX;
         for (int i = 0; i < blocks.size(); i++) {
             if (blocks[i] >= req && blocks[i] - req < mn) {
                 mn = blocks[i] - req;
                 ind = i;
             }
         }
         if (ind != -1) blocks[ind] -= req;
         return ind;
     }
     ```
   - It iterates through each block, finding the block with the smallest difference (`blocks[i] - req`) that can accommodate `req`. If it finds a block, it allocates memory and returns the block index. If not, it returns `-1`.

### 3. **Next Fit Allocation**
   - **Algorithm**: This function is a variant of First Fit. Instead of starting from the beginning for each new request, it starts from where the last allocation left off.
   - **Code Explanation**:
     ```cpp
     int nextFit(vector<int>& blocks, int req, int lind) {
         int n = blocks.size();
         int i = lind;
         while (true) {
             if (blocks[i] >= req) {
                 blocks[i] -= req;
                 int ind = i;
                 i = (i + 1) % n;  // Update last index
                 return ind;
             }
             i = (i + 1) % n;
             if (i == lind) break;  // We've checked all blocks
         }
         return -1;
     }
     ```
   - Starting from `lind`, it iterates over the blocks circularly. If it finds a block large enough, it allocates memory there, updates `lind` to the next index, and returns the block index. If no block is found after a complete cycle, it returns `-1`.

### 4. **Worst Fit Allocation**
   - **Algorithm**: This function looks for the largest block that can hold the memory request. It aims to minimize fragmentation by allocating to the largest available block.
   - **Code Explanation**:
     ```cpp
     int worstFit(vector<int>& blocks, int req) {
         int ind = -1, mx = INT_MIN;
         for (int i = 0; i < blocks.size(); i++) {
             if (blocks[i] >= req && blocks[i] - req > mx) {
                 mx = blocks[i] - req;
                 ind = i;
             }
         }
         if (ind != -1) blocks[ind] -= req;
         return ind;
     }
     ```
   - The function finds the largest block with a difference (`blocks[i] - req`) greater than the current maximum (`mx`). If a suitable block is found, it allocates memory and returns the index. Otherwise, it returns `-1`.

### Main Function Execution

In `main()`, each memory allocation strategy is tested independently:

```cpp
int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> req = {212, 417, 112, 426};

    cout << "\n--- First Fit ---\n";
    vector<int> blocksCopy = blocks;
    for (int r : req) {
        int result = firstFit(blocksCopy, r);
        cout << "Process " << r << " -> Block " << (result != -1 ? to_string(result) : "Not Allocated") << endl;
    }
    ...
}
```

For each strategy:
1. A copy of `blocks` is used to avoid affecting the original memory blocks across strategies.
2. The program iterates over each request in `req` and applies the selected allocation method.
3. Results display which block was allocated to each process, or if the process couldn’t be allocated due to insufficient space.

### Sample Output Explanation

Given `blocks = {100, 500, 200, 300, 600}` and `req = {212, 417, 112, 426}`, the output shows which block each process is allocated to for each strategy.

Each method demonstrates different allocation results:
- **First Fit** quickly finds the first available space.
- **Best Fit** seeks to minimize remaining space after allocation.
- **Next Fit** starts from the last allocated position.
- **Worst Fit** allocates to the largest block.

These strategies illustrate trade-offs in memory allocation efficiency and fragmentation reduction based on different scenarios.*/