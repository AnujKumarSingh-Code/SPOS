#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Enum for module status
enum class ModuleStatus {
    LOADING,
    LOADED,
    UNLOADED
};

// Structure to represent a module/resource
struct Module {
    std::string name;
    ModuleStatus status;
    time_t load_time;  // Timestamp for when the module was loaded

    // Constructor to initialize the module
    Module(const std::string& moduleName)
        : name(moduleName), status(ModuleStatus::LOADING), load_time(time(0)) {}

    // Function to change module status
    void setStatus(ModuleStatus newStatus) {
        status = newStatus;
    }

    // Function to display module info
    void displayInfo() const {
        std::string status_str;
        switch (status) {
            case ModuleStatus::LOADING: status_str = "Loading"; break;
            case ModuleStatus::LOADED: status_str = "Loaded"; break;
            case ModuleStatus::UNLOADED: status_str = "Unloaded"; break;
        }
        std::cout << "Module: " << name << ", Status: " << status_str << ", Loaded at: " << load_time << std::endl;
    }
};

// Loader class that manages loaded modules
class Loader {
private:
    std::unordered_map<std::string, std::shared_ptr<Module>> modules;

public:
    // Load a module into the system
    void loadModule(const std::string& moduleName) {
        if (modules.find(moduleName) == modules.end()) {
            // Create a new module and load it
            auto module = std::make_shared<Module>(moduleName);
            modules[moduleName] = module;
            module->setStatus(ModuleStatus::LOADED);
            std::cout << "Module " << moduleName << " loaded successfully!" << std::endl;
        } else {
            std::cout << "Module " << moduleName << " is already loaded." << std::endl;
        }
    }

    // Unload a module
    void unloadModule(const std::string& moduleName) {
        auto it = modules.find(moduleName);
        if (it != modules.end()) {
            it->second->setStatus(ModuleStatus::UNLOADED);
            std::cout << "Module " << moduleName << " unloaded successfully!" << std::endl;
        } else {
            std::cout << "Module " << moduleName << " not found!" << std::endl;
        }
    }

    // Display all loaded modules
    void displayAllModules() const {
        if (modules.empty()) {
            std::cout << "No modules loaded." << std::endl;
            return;
        }

        for (const auto& module_pair : modules) {
            module_pair.second->displayInfo();
        }
    }
};

int main() {
    Loader loader;

    loader.loadModule("Module1");
    loader.loadModule("Module2");
    loader.loadModule("Module3");

    loader.displayAllModules();

    loader.unloadModule("Module2");

    loader.displayAllModules();

    return 0;
}


/*This C++ program demonstrates a module management system that uses object-oriented programming and smart pointers. The `Loader` class manages modules, which can be loaded, unloaded, and displayed with their statuses. The code uses an `enum class` for module status, a `struct` for module representation, and a class to manage module operations.

### Code Explanation

1. **Include Statements and Namespace**
   ```cpp
   #include <iostream>
   #include <string>
   #include <unordered_map>
   #include <memory>
   ```
   - `iostream`: Provides functionality for input/output.
   - `string`: Defines the `std::string` class for handling strings.
   - `unordered_map`: Provides the hash table-based associative container.
   - `memory`: Provides smart pointers (e.g., `std::shared_ptr`).

2. **Enum for Module Status**
   ```cpp
   enum class ModuleStatus {
       LOADING,
       LOADED,
       UNLOADED
   };
   ```
   - This `enum class` defines different statuses (`LOADING`, `LOADED`, `UNLOADED`) that a module can have.
   - Using `enum class` ensures type safety and avoids conflicts with other enumerations.

3. **Module Structure**
   ```cpp
   struct Module {
       std::string name;
       ModuleStatus status;
       time_t load_time;

       Module(const std::string& moduleName)
           : name(moduleName), status(ModuleStatus::LOADING), load_time(time(0)) {}
       
       void setStatus(ModuleStatus newStatus) {
           status = newStatus;
       }

       void displayInfo() const {
           std::string status_str;
           switch (status) {
               case ModuleStatus::LOADING: status_str = "Loading"; break;
               case ModuleStatus::LOADED: status_str = "Loaded"; break;
               case ModuleStatus::UNLOADED: status_str = "Unloaded"; break;
           }
           std::cout << "Module: " << name << ", Status: " << status_str << ", Loaded at: " << load_time << std::endl;
       }
   };
   ```
   - **Attributes**:
     - `name`: Holds the module's name.
     - `status`: Stores the module's current status.
     - `load_time`: Stores the time when the module was loaded (using `time(0)`).
   - **Constructor**:
     - Initializes `name`, sets the status to `LOADING`, and captures the load time.
   - **Member Functions**:
     - `setStatus`: Changes the module's status.
     - `displayInfo`: Prints module details, converting `ModuleStatus` to a string.

4. **Loader Class**
   ```cpp
   class Loader {
   private:
       std::unordered_map<std::string, std::shared_ptr<Module>> modules;

   public:
       void loadModule(const std::string& moduleName);
       void unloadModule(const std::string& moduleName);
       void displayAllModules() const;
   };
   ```
   - **Attributes**:
     - `modules`: A map holding modules, where the key is the module name, and the value is a `shared_ptr` to `Module`. Using `shared_ptr` allows efficient memory management.
   - **Member Functions**:
     - `loadModule`: Loads a module if it doesn't already exist in `modules`.
     - `unloadModule`: Unloads a module by updating its status to `UNLOADED`.
     - `displayAllModules`: Displays information for each module in `modules`.

5. **Function Implementations in Loader**
   ```cpp
   void Loader::loadModule(const std::string& moduleName) { ... }
   void Loader::unloadModule(const std::string& moduleName) { ... }
   void Loader::displayAllModules() const { ... }
   ```
   - `loadModule`: Checks if `moduleName` exists. If not, it creates a new `Module` object, sets its status to `LOADED`, and adds it to `modules`.
   - `unloadModule`: Finds `moduleName` in `modules`. If found, updates its status to `UNLOADED`.
   - `displayAllModules`: Iterates through `modules`, calling `displayInfo()` for each.

6. **Main Function**
   ```cpp
   int main() {
       Loader loader;

       loader.loadModule("Module1");
       loader.loadModule("Module2");
       loader.loadModule("Module3");

       loader.displayAllModules();

       loader.unloadModule("Module2");

       loader.displayAllModules();

       return 0;
   }
   ```
   - Creates a `Loader` object, then loads, displays, and unloads modules while showing changes to verify the functions.

### Possible Viva Questions and Answers

1. **Q: What is the purpose of `ModuleStatus`?**
   - A: `ModuleStatus` is an enumeration that defines possible states (`LOADING`, `LOADED`, `UNLOADED`) for a module.

2. **Q: Why do we use `shared_ptr` in the `modules` map?**
   - A: `shared_ptr` allows multiple parts of the program to share ownership of a `Module` object, handling automatic memory management to prevent leaks.

3. **Q: What does `time(0)` do in the constructor of `Module`?**
   - A: `time(0)` returns the current calendar time as `time_t`, used here to log when the module was loaded.

4. **Q: Explain the role of the `Loader` class.**
   - A: `Loader` manages modules by loading, unloading, and displaying their information. It uses an unordered map to store `Module` objects.

5. **Q: What would happen if we tried to unload a module not loaded in `modules`?**
   - A: The program will display a message indicating the module was not found.

6. **Q: Can `modules` hold duplicate module names?**
   - A: No, `modules` uses module names as unique keys, so only one instance per name is stored.

7. **Q: Why do we use an `unordered_map` instead of a `map`?**
   - A: `unordered_map` has average O(1) time complexity for insertions, deletions, and lookups, which is efficient for module management.

8. **Q: What is `const` used for in `displayInfo()` and `displayAllModules()`?**
   - A: `const` indicates these functions don’t modify member variables, allowing them to be called on `const` instances.

9. **Q: Why are `ModuleStatus` values converted to strings in `displayInfo()`?**
   - A: To make the module status human-readable when printed.

10. **Q: What if `ModuleStatus` had more statuses? How would it affect `displayInfo()`?**
   - A: We would add more cases in the `switch` statement to handle additional statuses.*/
