// #include <iostream>
// #include <vector>
// #include <cstdint>
// #include <cstring>
// #include <fstream>
// using namespace std;

// // Function to load the executable into memory and simulate execution
// void loadAndRun(const string &executableFile) {
//     // Read the executable file into a vector
//     vector<char> machineCode;
//     uint32_t entryPoint = 0;

//     ifstream file(executableFile, ios::binary | ios::ate);
//     if (!file.is_open()) {
//         cerr << "Error: Unable to open file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     streamsize size = file.tellg();
//     file.seekg(0, ios::beg);

//     machineCode.resize(size);
//     if (!file.read(machineCode.data(), size)) {
//         cerr << "Error: Unable to read file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     // Read the entry point from the executable file
//     if (!file.read(reinterpret_cast<char*>(&entryPoint), sizeof(entryPoint))) {
//         cerr << "Error: Unable to read entry point from file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     file.close();

//     // Simulate execution starting from the entry point
//     cout << "Simulating execution starting from entry point: " << hex << entryPoint << endl;

//     // Assuming the machine code is an array of instructions (32-bit integers)
//     int* codeToExecute = reinterpret_cast<int*>(machineCode.data());
//     size_t codeSize = machineCode.size() / sizeof(int);

//     // Locate the entry point in the machine code
//     size_t entryIndex = entryPoint / sizeof(int);
//     if (entryIndex < codeSize) {
//         codeToExecute += entryIndex;

//         // Simulate execution (this will depend on your actual machine code)
//         for (size_t i = entryIndex; i < codeSize; ++i) {
//             cout << "Executing instruction: " << hex << codeToExecute[i] << endl;
//             // Simulate execution logic here
//         }

//         cout << "Execution completed." << endl;
//     } else {
//         cerr << "Error: Entry point not found in machine code." << endl;
//         exit(EXIT_FAILURE);
//     }
// }

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         cerr << "Usage: " << argv[0] << " executable" << endl;
//         return EXIT_FAILURE;
//     }

//     // Get the executable filename from the command line argument
//     string executableFile = argv[1];

//     // Load and run the executable
//     loadAndRun(executableFile);

//     return EXIT_SUCCESS;
// }


// 2nd modification
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <cstdint>

// using namespace std;

// // Function to load the executable into memory and simulate execution
// void loadAndRun(const string &executableFile) {
//     // Read the executable file into a vector
//     vector<char> machineCode;
//     uint32_t entryPoint = 0;

//     ifstream file(executableFile, ios::binary | ios::ate);
//     if (!file.is_open()) {
//         cerr << "Error: Unable to open file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     streamsize size = file.tellg();
//     file.seekg(0, ios::beg);

//     machineCode.resize(size);
//     if (!file.read(machineCode.data(), size)) {
//         cerr << "Error: Unable to read file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     // Read the entry point from the executable file
//     if (!file.read(reinterpret_cast<char*>(&entryPoint), sizeof(entryPoint))) {
//         cerr << "Error: Unable to read entry point from file " << executableFile << endl;
//         exit(EXIT_FAILURE);
//     }

//     file.close();

//     // Simulate execution starting from the entry point
//     cout << "Simulating execution starting from entry point: " << hex << entryPoint << endl;

//     // Assuming the machine code is an array of instructions (32-bit integers)
//     int* codeToExecute = reinterpret_cast<int*>(machineCode.data());
//     size_t codeSize = machineCode.size() / sizeof(int);

//     // Locate the entry point in the machine code
//     size_t entryIndex = entryPoint / sizeof(int);
//     if (entryIndex < codeSize) {
//         codeToExecute += entryIndex;

//         // Simulate execution (this will depend on your actual machine code)
//         for (size_t i = entryIndex; i < codeSize; ++i) {
//             cout << "Executing instruction: " << hex << codeToExecute[i] << endl;
//             // Simulate execution logic here
//         }

//         cout << "Execution completed." << endl;
//     } else {
//         cerr << "Error: Entry point not found in machine code." << endl;
//         exit(EXIT_FAILURE);
//     }
// }

// int main(int argc, char *argv[]) {
//     if (argc != 2) {
//         cerr << "Usage: " << argv[0] << " executable" << endl;
//         return EXIT_FAILURE;
//     }

//     // Get the executable filename from the command line argument
//     string executableFile = argv[1];

//     // Load and run the executable
//     loadAndRun(executableFile);

//     return EXIT_SUCCESS;
// }

// 3rd modification
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;

// Function to load the executable into memory and simulate execution
void loadAndRun(const string &executableFile) {
    // Read the executable file into a vector
    vector<char> machineCode;
    uint32_t entryPoint = 0;

    ifstream file(executableFile, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << executableFile << endl;
        exit(EXIT_FAILURE);
    }

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    machineCode.resize(size);
    if (!file.read(machineCode.data(), size)) {
        cerr << "Error: Unable to read file " << executableFile << endl;
        exit(EXIT_FAILURE);
    }

    // Read the entry point from the executable file
    size_t entryPointOffset = size - sizeof(entryPoint);
    file.seekg(entryPointOffset);
    if (!file.read(reinterpret_cast<char*>(&entryPoint), sizeof(entryPoint))) {
        cerr << "Error: Unable to read entry point from file " << executableFile << endl;
        exit(EXIT_FAILURE);
    }

    file.close();

    // Simulate execution starting from the entry point
    cout << "Simulating execution starting from entry point: " << hex << entryPoint << endl;

    // Assuming the machine code is an array of instructions (32-bit integers)
    int* codeToExecute = reinterpret_cast<int*>(machineCode.data());
    size_t codeSize = (entryPointOffset / sizeof(int));

    // Simulate execution (this will depend on your actual machine code)
    for (size_t i = 0; i < codeSize; ++i) {
        cout << "Executing instruction: " << hex << codeToExecute[i] << endl;
        // Simulate execution logic here
    }

    cout << "Execution completed." << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " executable" << endl;
        return EXIT_FAILURE;
    }

    // Get the executable filename from the command line argument
    string executableFile = argv[1];

    // Load and run the executable
    loadAndRun(executableFile);

    return EXIT_SUCCESS;
}
