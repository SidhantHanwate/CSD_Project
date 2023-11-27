#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> 
using namespace std;
int main() {
    cout<<"Enter the hll code here : ";
    string s1;
    cin>>s1;
    ifstream inputFile(s1);
    if (!inputFile) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    vector<string> headerFiles;
    string line;
    while (getline(inputFile, line)) {
        if (line.find("#include") != string::npos) {
            size_t startPos = line.find("<") + 1;
            size_t endPos = line.find(">");
            if (startPos != string::npos && endPos != string::npos) {
                string headerFileName = line.substr(startPos, endPos - startPos);
                headerFiles.push_back(headerFileName);
            }
        }
    }
    string makefileCommand = "make clean";
int result1 = system(makefileCommand.c_str());
    for (const string& headerFile : headerFiles) {
        string makefileCommand = "make rundoto fname=" + headerFile;
        int result = system(makefileCommand.c_str());
        if (result == 0) {
            cout << "Successfully processed header file: " << headerFile << endl;
        } else {
            cerr << "Header file not there or Failed to process header file: " << headerFile << endl;
        }
    }
    string runParserCommand = "make fname="+s1;
    int result = system(runParserCommand.c_str());

    if (result == 0) {
        cout << "Successfully ran the parser." << endl;
    } else {
        cerr << "Failed to run the parser." << endl;
    }
    return 0;
}




