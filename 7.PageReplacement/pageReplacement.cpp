#include<bits/stdc++.h>

using namespace std;

// FIFO Page Replacement Algorithm
int fifoPageReplacement(vector<int>& pages, int frames) {
    queue<int> q;
    unordered_set<int> s;
    int pageFaults = 0;

    for (int page : pages) {
        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                q.push(page);
                pageFaults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                int removedPage = q.front();
                q.pop();
                s.erase(removedPage);
                s.insert(page);
                q.push(page);
                pageFaults++;
            }
        }
    }
    return pageFaults;
}

// LRU Page Replacement Algorithm
int lruPageReplacement(vector<int>& pages, int frames) {
    unordered_map<int, int> pageMap;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (pageMap.size() < frames) {
            if (pageMap.find(page) == pageMap.end()) {
                pageFaults++;
            }
            pageMap[page] = i;
        } else {
            if (pageMap.find(page) == pageMap.end()) {
                int lruPage = -1, lruIndex = i;
                for (auto it : pageMap) {
                    if (it.second < lruIndex) {
                        lruIndex = it.second;
                        lruPage = it.first;
                    }
                }
                pageMap.erase(lruPage);
                pageMap[page] = i;
                pageFaults++;
            } else {
                pageMap[page] = i;
            }
        }
    }
    return pageFaults;
}

// Optimal Page Replacement Algorithm
int optimalPageReplacement(vector<int>& pages, int frames) {
    unordered_set<int> s;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (s.size() < frames) {
            if (s.find(page) == s.end()) {
                s.insert(page);
                pageFaults++;
            }
        } else {
            if (s.find(page) == s.end()) {
                int farthest = i, victimPage = -1;
                for (int pg : s) {
                    int nextUse = find(pages.begin() + i + 1, pages.end(), pg) - pages.begin();
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        victimPage = pg;
                    }
                }
                s.erase(victimPage);
                s.insert(page);
                pageFaults++;
            }
        }
    }
    return pageFaults;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 3;

    cout << "FIFO Page Faults: " << fifoPageReplacement(pages, frames) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(pages, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(pages, frames) << endl;

    return 0;
}



/*Page replacement algorithms are used in operating systems to manage the limited space in main memory when handling page faults. A page fault occurs when a process attempts to access a page not currently in memory, causing the system to load the required page from secondary storage (like a disk) into main memory. Since main memory has limited capacity, a page replacement algorithm determines which page should be replaced to free up space for the new page.

### Key Page Replacement Algorithms

1. **FIFO (First-In, First-Out)**
   - **Concept**: The oldest loaded page (the "first in") is the first to be replaced.
   - **Steps**:
     - Maintain a queue of pages in memory in the order they were loaded.
     - When a new page needs to be loaded, remove the page at the front of the queue.
   - **Advantages**: Simple to implement.
   - **Disadvantages**: It can lead to poor performance, as the oldest page may still be frequently used.

2. **Optimal Page Replacement (OPT)**
   - **Concept**: Replace the page that will not be used for the longest period in the future.
   - **Steps**:
     - For each page fault, look at the pages currently in memory and predict their future use.
     - Replace the page that won’t be needed for the longest time.
   - **Advantages**: Minimizes the number of page faults.
   - **Disadvantages**: It’s impractical in real systems since future page requests are not known, but it’s useful as a theoretical benchmark.

3. **LRU (Least Recently Used)**
   - **Concept**: Replace the page that has not been used for the longest time.
   - **Steps**:
     - Keep track of the pages based on their recent use (using a counter or stack).
     - Replace the page that was least recently accessed when a new page is needed.
   - **Advantages**: Effective in many cases because it leverages locality of reference (recently used pages are more likely to be used again).
   - **Disadvantages**: Can be complex to implement efficiently due to tracking the recency of usage.

4. **Clock (Second Chance) Algorithm**
   - **Concept**: A variation of FIFO, providing a “second chance” to pages.
   - **Steps**:
     - Maintain a circular list (or "clock") of pages.
     - Each page has a reference bit, initially set to 1 when loaded.
     - When a page fault occurs, check each page’s reference bit:
       - If it’s 0, replace the page.
       - If it’s 1, set it to 0 and move to the next page, giving the page a "second chance."
   - **Advantages**: Balances simplicity and efficiency, as frequently used pages are not immediately replaced.
   - **Disadvantages**: May lead to more page faults in certain scenarios due to repeated scanning.

5. **LFU (Least Frequently Used)**
   - **Concept**: Replace the page that has been accessed the least number of times.
   - **Steps**:
     - Each page has a counter, incremented each time the page is accessed.
     - When a replacement is needed, the page with the lowest count is removed.
   - **Advantages**: Suitable for cases where frequently used pages need to stay longer in memory.
   - **Disadvantages**: Can perform poorly when pages that were used heavily in the past aren’t needed in the future.

6. **MFU (Most Frequently Used)**
   - **Concept**: Replace the page with the highest frequency, under the assumption that pages accessed frequently are less likely to be needed soon.
   - **Steps**:
     - Each page has a counter for accesses, similar to LFU.
     - When a page fault occurs, replace the page with the highest count.
   - **Advantages**: Provides a counterintuitive but sometimes effective approach.
   - **Disadvantages**: Rarely used in practice, as it doesn’t suit many access patterns well.

### Example: Working of the LRU Algorithm

Consider a memory with 3 frames and a sequence of page requests: **1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5**.

1. **Initial state**: All frames are empty.
2. **Page request 1**: Page 1 is loaded (page fault).
3. **Page request 2**: Page 2 is loaded (page fault).
4. **Page request 3**: Page 3 is loaded (page fault).
5. **Page request 4**: Memory is full. Replace page 1 (least recently used), and load page 4 (page fault).
6. **Page request 1**: Replace page 2 (least recently used), and load page 1 (page fault).
7. **Page request 2**: Replace page 3 (least recently used), and load page 2 (page fault).
8. **Page request 5**: Replace page 4 (least recently used), and load page 5 (page fault).

**Outcome**: Using LRU, we experience several page faults as we load each new page and replace the least recently used page. This illustrates how LRU maintains recently accessed pages, though it may lead to frequent replacements if the access pattern changes quickly.

### Summary of Page Replacement Strategies
- **FIFO**: Simple but can suffer from poor performance.
- **Optimal**: Theoretical best but impractical.
- **LRU**: Effective, especially for access patterns with locality.
- **Clock**: A balanced approach, offering simplicity and performance.
- **LFU/MFU**: Frequency-based, though less commonly used due to performance issues in some patterns.

Each algorithm has trade-offs in terms of efficiency, ease of implementation, and suitability for specific memory access patterns. Operating systems select the best-fit algorithm based on the requirements and workload to optimize memory usage and reduce page faults.*/


/*This code demonstrates three page replacement algorithms: **FIFO (First-In-First-Out)**, **LRU (Least Recently Used)**, and **Optimal Page Replacement**. The goal of each algorithm is to manage a fixed number of page frames and minimize page faults by selecting the best page to replace when a new page needs to be loaded into memory.

Let's break down each section of the code.

### 1. FIFO Page Replacement Algorithm
The `fifoPageReplacement` function implements the FIFO page replacement strategy.

```cpp
int fifoPageReplacement(vector<int>& pages, int frames) {
    queue<int> q; // Keeps track of pages in FIFO order
    unordered_set<int> s; // Keeps track of pages currently in frames
    int pageFaults = 0; // Counts the number of page faults

    for (int page : pages) {
        // If frames are not yet filled
        if (s.size() < frames) {
            if (s.find(page) == s.end()) { // Page is not in frames
                s.insert(page); // Add page to set of frames
                q.push(page); // Add page to the queue
                pageFaults++; // Increase page fault count
            }
        } else { // Frames are full
            if (s.find(page) == s.end()) { // Page is not in frames
                int removedPage = q.front(); // Get the oldest page
                q.pop(); // Remove oldest page from queue
                s.erase(removedPage); // Remove oldest page from frames
                s.insert(page); // Insert new page
                q.push(page); // Add new page to queue
                pageFaults++; // Increase page fault count
            }
        }
    }
    return pageFaults;
}
```

#### Explanation:
- A queue (`q`) is used to keep track of the order of pages, and an unordered set (`s`) stores the pages currently in memory.
- If a page is not in memory and a page fault occurs, the algorithm checks if there is space in the frames.
- When the frames are full, the oldest page (front of the queue) is removed, and the new page is added.
- **Page Faults**: Every time a new page is loaded (not found in memory), `pageFaults` is incremented.

### 2. LRU Page Replacement Algorithm
The `lruPageReplacement` function implements the LRU page replacement strategy.

```cpp
int lruPageReplacement(vector<int>& pages, int frames) {
    unordered_map<int, int> pageMap; // Tracks pages and their recent usage indices
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (pageMap.size() < frames) {
            if (pageMap.find(page) == pageMap.end()) { // Page is not in frames
                pageFaults++;
            }
            pageMap[page] = i; // Update usage index for the page
        } else {
            if (pageMap.find(page) == pageMap.end()) { // Page is not in frames
                int lruPage = -1, lruIndex = i;
                // Find the least recently used page
                for (auto it : pageMap) {
                    if (it.second < lruIndex) {
                        lruIndex = it.second;
                        lruPage = it.first;
                    }
                }
                pageMap.erase(lruPage); // Remove the LRU page
                pageMap[page] = i; // Add new page and update usage index
                pageFaults++;
            } else {
                pageMap[page] = i; // Update usage index for the page
            }
        }
    }
    return pageFaults;
}
```

#### Explanation:
- This algorithm uses a map (`pageMap`) to keep track of pages in memory and their last used index.
- When a page needs to be replaced, the algorithm finds the page with the earliest last-used index and replaces it.
- **Page Faults**: When a new page is loaded, `pageFaults` is incremented.

### 3. Optimal Page Replacement Algorithm
The `optimalPageReplacement` function implements the Optimal page replacement strategy.

```cpp
int optimalPageReplacement(vector<int>& pages, int frames) {
    unordered_set<int> s; // Tracks pages currently in frames
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (s.size() < frames) {
            if (s.find(page) == s.end()) { // Page is not in frames
                s.insert(page);
                pageFaults++;
            }
        } else {
            if (s.find(page) == s.end()) { // Page is not in frames
                int farthest = i, victimPage = -1;
                // Find the page that will not be used for the longest time
                for (int pg : s) {
                    int nextUse = find(pages.begin() + i + 1, pages.end(), pg) - pages.begin();
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        victimPage = pg;
                    }
                }
                s.erase(victimPage); // Replace page with the farthest next use
                s.insert(page);
                pageFaults++;
            }
        }
    }
    return pageFaults;
}
```

#### Explanation:
- This algorithm uses an unordered set (`s`) to track pages currently in frames.
- When a page needs to be replaced, the algorithm searches for the page that will not be used for the longest time in the future and replaces it.
- **Page Faults**: Incremented each time a new page is loaded.

### Main Function
The `main` function initializes the page requests (`pages`) and the number of frames (`frames`). It then calls each page replacement function and outputs the number of page faults for each algorithm.

```cpp
int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 3;

    cout << "FIFO Page Faults: " << fifoPageReplacement(pages, frames) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(pages, frames) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(pages, frames) << endl;

    return 0;
}
```

#### Explanation:
- `pages` is a sequence of page references.
- `frames` is the total number of page frames available in memory.
- The function calls print the page fault counts for each replacement strategy.

### Summary
- **FIFO**: Replaces the oldest page in memory.
- **LRU**: Replaces the page that hasn’t been used for the longest time.
- **Optimal**: Replaces the page that will not be used for the longest time in the future.

Each algorithm has trade-offs in terms of page fault counts and applicability, depending on the access pattern of pages.*/