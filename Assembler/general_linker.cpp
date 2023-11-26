#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Struct to represent a relocation entry
struct RelocationEntry {
    string type;
    int offset;
};

// Struct to represent a symbol table entry
struct SymbolEntry {
    string name;
    int address;
};

// Function to read a binary object file and append machine code to the output vector
void readObjectFile(const string &filename, vector<char> &output, vector<SymbolEntry> &symbolTable, vector<RelocationEntry> &relocationTable) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        cerr << "Error: Unable to read file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // Read the symbol table from the object file
    istringstream symbolStream(buffer.data());
    string symbolName;
    int symbolAddress;

    while (symbolStream >> symbolName >> symbolAddress) {
        symbolTable.push_back({symbolName, symbolAddress});
    }

    // Read the relocation table from the object file
    istringstream relocationStream(buffer.data());
    string relocType;
    int relocOffset;

    while (relocationStream >> relocType >> relocOffset) {
        relocationTable.push_back({relocType, relocOffset});
    }

    // Append the machine code to the output vector
    output.insert(output.end(), buffer.begin(), buffer.end());

    file.close();
}

// Function to resolve symbols and perform relocation
void resolveSymbolsAndRelocate(vector<char> &machineCode, const vector<SymbolEntry> &symbolTable, const vector<RelocationEntry> &relocationTable) {
    // Resolve symbols and perform relocation based on the tables
    for (const auto &relocEntry : relocationTable) {
        // Find the symbol in the symbol table
        const auto it = find_if(symbolTable.begin(), symbolTable.end(), [&](const SymbolEntry &entry) {
            return entry.name == relocEntry.type;
        });

        if (it != symbolTable.end()) {
            // Update the machine code at the specified offset
            int symbolAddress = it->address;
            int relocOffset = relocEntry.offset;

            // Perform relocation (assuming a simple case, you may need to adapt this based on your actual requirements)
            int* codeToModify = reinterpret_cast<int*>(&machineCode[relocOffset]);
            *codeToModify += symbolAddress;
        } else {
            cerr << "Error: Symbol not found in the symbol table - " << relocEntry.type << endl;
            exit(EXIT_FAILURE);
        }
    }
}

// Function to perform linking and generate the final executable
void linkFiles(const string &asmFile, const string &libFile, const string &outputFile, uint32_t &entryPoint) {
    // Vector to store the merged machine code
    vector<char> mergedMachineCode;

    // Vector to store the symbol table
    vector<SymbolEntry> symbolTable;

    // Vector to store the relocation table
    vector<RelocationEntry> relocationTable;

    // Read the machine code, symbol table, and relocation table from the asm file
    readObjectFile(asmFile, mergedMachineCode, symbolTable, relocationTable);

    // Read the machine code, symbol table, and relocation table from the lib file
    readObjectFile(libFile, mergedMachineCode, symbolTable, relocationTable);

    // Resolve symbols and perform relocation
    resolveSymbolsAndRelocate(mergedMachineCode, symbolTable, relocationTable);

    // Write the final executable file
    ofstream outFile(outputFile, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to create output file " << outputFile << endl;
        exit(EXIT_FAILURE);
    }

    // Write the merged machine code to the output file
    outFile.write(mergedMachineCode.data(), mergedMachineCode.size());

    // Set the entry point to the address of the main function (change this based on your actual entry point)
    entryPoint = 0x00400000; // Example entry point for MIPS

    // Write the entry point to the output file
    outFile.write(reinterpret_cast<char*>(&entryPoint), sizeof(entryPoint));

    outFile.close();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " asmout.o lib.o output" << endl;
        return EXIT_FAILURE;
    }

    // Get input and output filenames from command line arguments
    string asmFile = argv[1];
    string libFile = argv[2];
    string outputFile = argv[3];

    // Entry point for the program
    uint32_t entryPoint;

    // Perform linking
    linkFiles(asmFile, libFile, outputFile, entryPoint);

    cout << "Linking successful. Output written to " << outputFile << endl;

    return EXIT_SUCCESS;
}
