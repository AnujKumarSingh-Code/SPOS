
#include <iostream>
#include <unistd.h>  // For fork() and getpid()
#include <sys/types.h> 
using namespace std;

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // If fork() fails
        cout << "Fork failed!" << endl;
        return 1;
    }

    if (pid == 0) {
        // Child process
        cout << "Child Process: " << endl;
        cout << "Child PID: " << getpid() << endl;
        cout << "Parent PID (PPID) of Child: " << getppid() << endl;
    } else {
        // Parent process
        cout << "Parent Process: " << endl;
        cout << "Parent PID: " << getpid() << endl;
        cout << "Parent of Parent Process: " << getppid() << endl;
    }

    return 0;
}


/*The code provided creates a child process using `fork()`, then prints the process ID (PID) and parent process ID (PPID) of both the parent and child processes. Here's the complete breakdown of the code and some potential viva questions related to it.

### Code Explanation

```cpp
#include <iostream>
#include <unistd.h>   // for fork(), getpid(), and getppid()
using namespace std;

int main() {
    pid_t pid = fork();   // Create a child process

    if (pid < 0) {
        // Error handling for fork failure
        cerr << "Fork failed" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process block
        cout << "This is the child process." << endl;
        cout << "Child Process ID (PID): " << getpid() << endl;
        cout << "Child's Parent Process ID (PPID): " << getppid() << endl;
    } else {
        // Parent process block
        cout << "This is the parent process." << endl;
        cout << "Parent Process ID (PID): " << getpid() << endl;
        cout << "Parent's Parent Process ID (PPID): " << getppid() << endl;
    }

    return 0;
}
```

### Code Breakdown

1. **Header Files**:
   - `#include <iostream>`: Provides input/output stream functionality.
   - `#include <unistd.h>`: Necessary for process control functions like `fork()`, `getpid()`, and `getppid()`.

2. **fork() Function**:
   - `pid_t pid = fork();` creates a new process. If successful, `fork()` returns:
     - `0` to the child process.
     - A positive PID of the child to the parent process.
     - `-1` if the process creation fails (an error).

3. **if-else Conditions**:
   - `pid < 0`: Indicates an error occurred during `fork()`.
   - `pid == 0`: This block is executed in the child process.
   - `pid > 0`: This block is executed in the parent process.

4. **Output Information**:
   - **Child Process**:
     - Prints `"This is the child process."`
     - Displays its own PID with `getpid()` and its parent’s PID using `getppid()`.
   - **Parent Process**:
     - Prints `"This is the parent process."`
     - Displays its own PID with `getpid()` and its own parent’s PID using `getppid()`.

### Sample Output

The output will differ based on process IDs but generally follows this structure:

```plaintext
This is the parent process.
Parent Process ID (PID): 1234
Parent's Parent Process ID (PPID): 5678

This is the child process.
Child Process ID (PID): 5679
Child's Parent Process ID (PPID): 1234
```

### Possible Viva Questions and Answers

Here are some common viva questions that may be asked based on this code:

1. **Q: What is the purpose of `fork()`?**
   - **A:** `fork()` is used to create a new process, which is an exact copy of the calling (parent) process. This new process is called the child process.

2. **Q: What does `pid` represent after calling `fork()`?**
   - **A:** After calling `fork()`, `pid` contains:
     - `0` in the child process.
     - The child’s PID in the parent process.
     - `-1` if the fork failed.

3. **Q: How do `getpid()` and `getppid()` functions work?**
   - **A:** `getpid()` returns the PID of the calling process. `getppid()` returns the PID of the parent of the calling process.

4. **Q: Why do we need to check if `pid` is `0`, less than `0`, or greater than `0`?**
   - **A:** This check is necessary to differentiate between the parent and child processes after `fork()` is called. `pid == 0` indicates the child process, while `pid > 0` indicates the parent process. A negative `pid` means an error occurred.

5. **Q: What happens if `fork()` fails, and why might it fail?**
   - **A:** If `fork()` fails, it returns `-1`, and typically, an error message is printed. `fork()` might fail due to insufficient memory or if the maximum process limit for the user/system has been reached.

6. **Q: Is the child process a copy of the parent process?**
   - **A:** Yes, the child process is a duplicate of the parent process, inheriting variables and file descriptors. However, both processes execute independently from the point of `fork()`.

7. **Q: What will happen if we call `fork()` multiple times in a loop?**
   - **A:** Calling `fork()` multiple times creates multiple child processes, which may lead to exponential process creation if not handled correctly.

8. **Q: Can the parent process finish before the child process?**
   - **A:** Yes, the parent process can finish before the child process. This often results in the child process becoming a "zombie" until the `init` system process adopts it and releases resources.

9. **Q: What is a “zombie” process?**
   - **A:** A zombie process is a terminated process whose exit status has not been read by its parent, causing it to remain in the process table.

10. **Q: How can we avoid zombie processes?**
    - **A:** Using the `wait()` or `waitpid()` function in the parent process helps to retrieve the child’s exit status, preventing zombie processes.

11. **Q: Can you explain the significance of `#include <unistd.h>`?**
    - **A:** `unistd.h` provides access to POSIX API functions for process management, including `fork()`, `getpid()`, and `getppid()`, which are essential for creating and managing processes.

12. **Q: What is the return type of `fork()` and why?**
    - **A:** The return type of `fork()` is `pid_t`, which is typically an integer type specifically designed for holding process IDs.*/
