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
