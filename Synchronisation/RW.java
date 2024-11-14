
import java.util.Scanner;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class RW {
    private final Lock readLock = new ReentrantLock();
    private final Semaphore writeLock = new Semaphore(1);
    private static int rc = 0;

    private void Reader(int id) {
        try {
            readLock.lock();
            if (++rc == 1) {
                writeLock.acquire();
            }
            readLock.unlock();

            System.out.println("Reader " + id + " is reading.");
            Thread.sleep(2500);
            System.out.println("Reader " + id + " finished reading.");

            readLock.lock();
            if (--rc == 0) {
                writeLock.release();
            }
            readLock.unlock();
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }

    private void Writer(int id) {
        try {
            writeLock.acquire();

            System.out.println("Writer " + id + " is writing.");
            Thread.sleep(1000);
            System.out.println("Writer " + id + " finished writing.");

            writeLock.release();

        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void main(String[] args) {
        RW rw = new RW();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of processes: ");
        int n = sc.nextInt();

        int[] seq = new int[n];
        System.out.println("Enter the sequence of processes (1 for Reader, 2 for Writer):");
        for (int i = 0; i < n; i++) {
            seq[i] = sc.nextInt();
        }

        for (int i = 0; i < n; i++) {
            int id = i + 1;
            if (seq[i] == 1) {
                new Thread(() -> rw.Reader(id)).start();
            } else {
                new Thread(() -> rw.Writer(id)).start();
            }
        }

        sc.close();
    }
}

/*This Java code implements a **Readers-Writers** problem using threads, locks, and semaphores. In the Readers-Writers problem, there are multiple threads (readers and writers) accessing a shared resource. Readers can read the resource simultaneously, but a writer requires exclusive access. This code ensures mutual exclusion, preventing writers from writing while readers are reading, and vice versa.

Let's go through the code step-by-step.

### Imports and Class Setup

```java
import java.util.Scanner;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class RW {
    private final Lock readLock = new ReentrantLock();
    private final Semaphore writeLock = new Semaphore(1);
    private static int rc = 0;
```

- **Imports**: The code uses `Scanner` for input, `Semaphore` for managing access to the shared resource by the writers, and `Lock` and `ReentrantLock` for managing reader access.
- **Locks and Semaphores**: 
  - `readLock`: A `ReentrantLock` used to coordinate access to the `rc` (reader count).
  - `writeLock`: A `Semaphore` with a single permit, ensuring only one writer can write at a time.
- **Reader Count (`rc`)**: A static counter to track the number of active readers.

### Reader Method

```java
private void Reader(int id) {
    try {
        readLock.lock();
        if (++rc == 1) {
            writeLock.acquire();
        }
        readLock.unlock();

        System.out.println("Reader " + id + " is reading.");
        Thread.sleep(2500);
        System.out.println("Reader " + id + " finished reading.");

        readLock.lock();
        if (--rc == 0) {
            writeLock.release();
        }
        readLock.unlock();
    } catch (InterruptedException e) {
        System.out.println(e.getMessage());
    }
}
```

#### Explanation:
- **Acquiring Read Access**:
  1. `readLock.lock()`: Locks the `readLock` to safely modify `rc`.
  2. `++rc == 1`: Increments the reader count `rc`. If `rc` is 1, it indicates the first reader, so `writeLock.acquire()` blocks any writers until all readers have finished.
  3. `readLock.unlock()`: Releases `readLock`, allowing other readers to increment `rc`.
  
- **Reading Section**:
  - `System.out.println("Reader " + id + " is reading.")`: Simulates the reader’s reading operation.
  - `Thread.sleep(2500)`: Simulates the time taken for reading.

- **Releasing Read Access**:
  1. `readLock.lock()`: Locks the `readLock` to safely modify `rc`.
  2. `--rc == 0`: Decrements `rc`. If `rc` is 0 (no more readers), `writeLock.release()` allows writers to access the resource.
  3. `readLock.unlock()`: Releases `readLock`, allowing other readers to decrement `rc`.

This ensures that writers cannot access the shared resource if any reader is reading.

### Writer Method

```java
private void Writer(int id) {
    try {
        writeLock.acquire();

        System.out.println("Writer " + id + " is writing.");
        Thread.sleep(1000);
        System.out.println("Writer " + id + " finished writing.");

        writeLock.release();

    } catch (InterruptedException e) {
        System.out.println(e.getMessage());
    }
}
```

#### Explanation:
- **Acquiring Write Access**: `writeLock.acquire()` blocks the writer until it has exclusive access to the resource.
- **Writing Section**:
  - `System.out.println("Writer " + id + " is writing.")`: Indicates the start of the writing operation.
  - `Thread.sleep(1000)`: Simulates the time taken for writing.
- **Releasing Write Access**: `writeLock.release()` allows other readers or writers to access the shared resource.

### Main Method

```java
public static void main(String[] args) {
    RW rw = new RW();
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter the number of processes: ");
    int n = sc.nextInt();

    int[] seq = new int[n];
    System.out.println("Enter the sequence of processes (1 for Reader, 2 for Writer):");
    for (int i = 0; i < n; i++) {
        seq[i] = sc.nextInt();
    }

    for (int i = 0; i < n; i++) {
        int id = i + 1;
        if (seq[i] == 1) {
            new Thread(() -> rw.Reader(id)).start();
        } else {
            new Thread(() -> rw.Writer(id)).start();
        }
    }

    sc.close();
}
```

#### Explanation:
- **User Input**:
  - `n`: The number of processes.
  - `seq`: An array representing the process sequence (1 for Reader, 2 for Writer).
- **Creating and Starting Threads**:
  - A loop iterates through each process in `seq`. For each process:
    - If `seq[i]` is `1`, a new `Reader` thread is created and started.
    - If `seq[i]` is `2`, a new `Writer` thread is created and started.
- **Closing Scanner**: `sc.close()` closes the input scanner.

### Summary
- **Readers**: Multiple readers can read simultaneously without blocking each other, but if a writer is waiting, the first reader to start reading blocks writers until all readers finish.
- **Writers**: Writers gain exclusive access to the resource. Only one writer can write at a time, and no readers can read during this period.
  
The code demonstrates a classic solution to the Readers-Writers problem, ensuring that multiple readers can read simultaneously, while writers get exclusive access to the resource. */




/*The code you provided implements a **Readers-Writers synchronization problem** solution. Let’s break down the theoretical background and definitions of all relevant concepts, including **mutual exclusion**, **locks**, **semaphores**, **thread synchronization**, **concurrency control**, and **Readers-Writers Problem** itself.

---

### 1. **Concurrency Control**

Concurrency control is a fundamental concept in computer science, particularly in **operating systems** and **database management systems**. It manages access to a shared resource by multiple processes or threads to prevent conflicts. The primary goals of concurrency control are:
- To maintain **data consistency**.
- To **prevent race conditions**, where multiple threads try to access a resource simultaneously, potentially leading to conflicts.

Concurrency control ensures that data integrity is maintained and that processes or threads cooperate properly when accessing shared resources.

---

### 2. **Readers-Writers Problem**

The **Readers-Writers Problem** is a classical synchronization problem that illustrates the challenges of managing concurrent access to a shared resource. The problem is as follows:
- **Readers** are threads that only need to read the shared resource without modifying it.
- **Writers** are threads that need to write (modify) the shared resource.
  
The constraints are:
- Multiple readers can access the resource simultaneously.
- Only one writer can access the resource at a time.
- No readers can access the resource while a writer is writing to it.

The Readers-Writers problem has various solutions, with different fairness considerations:
- **Reader-preference solution**: Prioritizes readers, so they don't have to wait if other readers are active, but this may starve writers.
- **Writer-preference solution**: Gives priority to writers, reducing the chance of writer starvation but possibly delaying readers.
- **Fair solution**: Alternates between readers and writers to prevent starvation of either.

The code provided is a **Reader-preference solution**, which means readers can enter and read concurrently without being blocked by other readers. However, writers will be blocked if there are active readers.

---

### 3. **Mutual Exclusion**

**Mutual exclusion** is a concurrency control concept that prevents multiple threads from accessing the same resource at the same time. This principle ensures that critical sections of code, where shared resources are accessed or modified, are only accessible to one thread at a time. Mutual exclusion can be implemented using various synchronization tools, such as **locks** and **semaphores**.

In the Readers-Writers problem:
- Mutual exclusion is enforced for writers since only one writer can modify the shared resource at a time.
- Mutual exclusion for readers is more relaxed, allowing multiple readers to access the resource concurrently, as they are only reading (not modifying) the data.

---

### 4. **Locks and Reentrant Locks**

A **lock** is a synchronization tool that enforces mutual exclusion on a critical section. Only the thread that acquires the lock can execute the critical section, preventing other threads from accessing shared resources simultaneously.

- **Reentrant Lock**: A reentrant lock allows a thread to acquire the lock multiple times without causing a deadlock. When a thread acquires a reentrant lock, it maintains a hold count, which is incremented with each acquisition and decremented with each release. The lock is only fully released when the hold count reaches zero.

In the code:
- `readLock` is a `ReentrantLock` used to safely increment or decrement the reader count (`rc`) in the `Reader` method. It ensures that changes to the reader count are done without interference from other readers or writers.

---

### 5. **Semaphore**

A **semaphore** is a synchronization primitive that allows a specific number of threads to access a shared resource concurrently. Semaphores come in two types:
- **Binary Semaphore (Mutex)**: Allows only one thread to access the resource at a time (similar to a lock).
- **Counting Semaphore**: Allows a fixed number of threads to access the resource concurrently.

In the code:
- `writeLock` is a `Semaphore` with a single permit (`new Semaphore(1)`), allowing only one writer thread to acquire it at a time. When a writer acquires this lock, other writers and readers are blocked from accessing the shared resource until it releases the semaphore.

---

### 6. **Thread Synchronization**

**Thread synchronization** ensures that threads coordinate correctly when accessing shared resources, preventing race conditions and maintaining data consistency.

In the Readers-Writers solution:
- **Readers synchronize** using `readLock` to control access to the reader count (`rc`), ensuring that no readers increment or decrement `rc` simultaneously, which could lead to incorrect values.
- **Writers synchronize** by acquiring `writeLock`, ensuring they have exclusive access to the shared resource while writing.

---

### 7. **Race Condition**

A **race condition** occurs when two or more threads try to access and modify shared data simultaneously, leading to unpredictable or incorrect results. Synchronization mechanisms like locks and semaphores prevent race conditions by controlling access to critical sections.

In the Readers-Writers problem:
- A race condition could occur if multiple readers or a reader and writer accessed `rc` (reader count) without synchronization. This is avoided by using `readLock` to control access to `rc`.

---

### 8. **Code Explanation**

With these definitions in mind, let's review the code in context:

#### `Reader` Method

```java
private void Reader(int id) {
    try {
        readLock.lock();                     // 1. Lock readLock to safely modify rc.
        if (++rc == 1) {                     // 2. First reader acquires writeLock, blocking writers.
            writeLock.acquire();
        }
        readLock.unlock();                   // 3. Unlock readLock, allowing other readers.

        System.out.println("Reader " + id + " is reading."); 
        Thread.sleep(2500);                  // 4. Simulate reading operation.
        System.out.println("Reader " + id + " finished reading.");

        readLock.lock();                     // 5. Lock readLock to safely modify rc.
        if (--rc == 0) {                     // 6. Last reader releases writeLock, allowing writers.
            writeLock.release();
        }
        readLock.unlock();                   // 7. Unlock readLock.
    } catch (InterruptedException e) {
        System.out.println(e.getMessage());
    }
}
```

The `Reader` method ensures that:
- The first reader locks `writeLock` to block writers, allowing all readers to read concurrently.
- The last reader releases `writeLock`, unblocking any waiting writers.

#### `Writer` Method

```java
private void Writer(int id) {
    try {
        writeLock.acquire();                 // 1. Acquire writeLock for exclusive access.

        System.out.println("Writer " + id + " is writing.");
        Thread.sleep(1000);                  // 2. Simulate writing operation.
        System.out.println("Writer " + id + " finished writing.");

        writeLock.release();                 // 3. Release writeLock.
    } catch (InterruptedException e) {
        System.out.println(e.getMessage());
    }
}
```

The `Writer` method ensures:
- Only one writer can access the shared resource at a time.
- Writers wait if there are active readers.

#### `main` Method

The `main` method initiates the Readers and Writers based on user input, creating threads for each reader and writer according to the sequence provided.

---

### Summary of Key Points:
- **Readers-Writers Problem**: A synchronization problem that allows multiple readers or one writer access at any time.
- **Locks**: Used for mutual exclusion to protect access to shared resources.
- **Semaphore**: Limits access to a resource, used here to manage exclusive access for writers.
- **Thread Synchronization**: Ensures readers and writers coordinate access without conflict.
- **Race Conditions**: Avoided by using locks and semaphores to control access to shared data.

This setup allows for efficient and safe access to shared resources by coordinating readers and writers, preventing simultaneous write-read conflicts and achieving concurrency control. */


/*Enter the number of processes: 5
Enter the sequence of processes (1 for Reader, 2 for Writer):
1 1 2 1 2
 */


/*This Java code demonstrates a solution to the Readers-Writers problem, a classic synchronization challenge in operating systems. It ensures that multiple readers can access a shared resource concurrently, but a writer must have exclusive access.

### Code Explanation

1. **Imports**:
   - `java.util.Scanner`: Used for reading input from the user.
   - `java.util.concurrent.Semaphore`: Provides control over resource access, ensuring exclusive access for writers.
   - `java.util.concurrent.locks.Lock` and `java.util.concurrent.locks.ReentrantLock`: Provides mutual exclusion for readers.

2. **Class Definition and Variables**:
   - `class RW`: Main class containing synchronization logic for readers and writers.
   - `readLock` (of type `ReentrantLock`): Ensures mutual exclusion for modifying the reader count (`rc`) variable.
   - `writeLock` (of type `Semaphore`): Controls exclusive access for writers, allowing only one writer at a time.
   - `static int rc = 0`: A shared counter that tracks the number of readers currently reading.

3. **Reader Method**:
   - Method: `Reader(int id)`: Represents a reader’s actions.
   - **Acquiring Access for Readers**:
     - `readLock.lock()`: Acquires the lock to modify `rc`.
     - `if (++rc == 1)`: If this is the first reader, it blocks writers by acquiring `writeLock`.
     - `readLock.unlock()`: Releases `readLock`, allowing other readers to modify `rc`.
   - **Reading**:
     - `System.out.println("Reader " + id + " is reading.");`: Indicates reading in progress.
     - `Thread.sleep(2500);`: Simulates reading time by making the reader wait for 2500 milliseconds.
     - `System.out.println("Reader " + id + " finished reading.");`: Reading completed.
   - **Releasing Access for Readers**:
     - `readLock.lock()` and `if (--rc == 0)`: If this is the last reader, it releases `writeLock`, allowing writers to access the resource.
     - `readLock.unlock()`: Releases `readLock` after modifying `rc`.

4. **Writer Method**:
   - Method: `Writer(int id)`: Represents a writer’s actions.
   - **Acquiring Write Access**:
     - `writeLock.acquire()`: Acquires `writeLock`, ensuring exclusive access.
   - **Writing**:
     - `System.out.println("Writer " + id + " is writing.");`: Indicates writing in progress.
     - `Thread.sleep(1000);`: Simulates writing time by making the writer wait for 1000 milliseconds.
     - `System.out.println("Writer " + id + " finished writing.");`: Writing completed.
   - **Releasing Write Access**:
     - `writeLock.release()`: Releases `writeLock`, allowing other writers or readers to access the resource.

5. **Main Method**:
   - Instantiates the `RW` class and prompts the user to enter the number of processes.
   - Creates an array to store the sequence of processes (1 for Reader, 2 for Writer).
   - Iterates over `seq[]`:
     - For each element, if it’s `1`, a `Reader` thread is created; if `2`, a `Writer` thread is created.
   - Closes the `Scanner`.

### Sample Input and Execution

Given input:
```plaintext
Enter the number of processes: 3
Enter the sequence of processes (1 for Reader, 2 for Writer):
1
2
1
```

The code creates two reader threads and one writer thread. The sequence and timing of output will vary based on the order and timing of thread execution.

### Possible Viva Questions

1. **What is the Readers-Writers Problem?**
   - This is a synchronization problem where multiple readers can read a resource concurrently, but only one writer can access it at a time to prevent data inconsistency.

2. **What are `ReentrantLock` and `Semaphore`?**
   - `ReentrantLock` allows mutual exclusion for critical sections, particularly useful in ensuring that only one reader modifies the `rc` counter at a time.
   - `Semaphore` allows for resource control. In this code, it allows only one writer to access the shared resource.

3. **Why is `rc` incremented and decremented?**
   - `rc` (reader count) tracks the number of active readers. When `rc` becomes 1, the first reader acquires the writer lock to prevent writers from accessing the resource. When `rc` becomes 0, the last reader releases the writer lock.

4. **Why are `readLock.lock()` and `readLock.unlock()` used twice in the Reader method?**
   - The first `readLock.lock()`/`unlock()` pair increments the reader count (`rc`), and the second pair decrements it. This ensures that no other thread modifies `rc` while checking and updating it.

5. **What would happen if `writeLock` was not used?**
   - Without `writeLock`, multiple writers could potentially access the resource simultaneously, leading to inconsistent data.

6. **Explain the purpose of `Thread.sleep()` in both methods.**
   - `Thread.sleep()` simulates time taken to read or write. It also demonstrates concurrency and synchronization by allowing other threads to potentially access the resource.

7. **What would happen if a reader starts reading while a writer is writing?**
   - In this program, it’s prevented by the `writeLock` semaphore, which ensures exclusive access for writers and no readers can access the resource if a writer is writing.

8. **Why use multithreading in this code?**
   - Multithreading enables concurrent execution of readers and writers, simulating a real-world shared resource where readers and writers may attempt access simultaneously.

9. **What is the difference between `lock()` and `acquire()`?**
   - `lock()` is a method from `Lock` that provides mutual exclusion for the lock, while `acquire()` is from `Semaphore`, used to acquire a permit to access a limited resource.

10. **Can multiple readers read concurrently in this code?**
    - Yes, multiple readers can read concurrently, as long as no writer is currently writing. This is controlled by the `writeLock` semaphore.*/
