#include <iostream>
#include <string>
using namespace std;

class Keyboard {
public:
    static char keyboard[];

    static void init() {
        char keyboard[8];
    }

    static char keyPressed() {
        return keyboard[0];
    }

    static char readChar() {
        // char key;
        // while (Keyboard::keyPressed() == 0) {}
        // key = Keyboard::keyPressed();
        // while (Keyboard::keyPressed() != 0) {}
        // cout << key; print to screen
        // return key;
        char key;
        key = cin.get(); // Read a character from standard input
        keyboard[0] = key; 
        //cout << key; 
        return key;
    }

    static string readLine(string message) {
        string line;
        char c;

        cout << message;

        do {
            c = Keyboard::readChar();
            if (c == '\n') break;
            if (c == '\b') {
                if (!line.empty()) {
                    cout << "\b \b"; // Erase last character from console
                    line.pop_back();
                }
            }
            else {
                cout << c;
                line += c;
            }
        } while (true);

        return line;
    }

    static int readInt(string message) {
        string line;
        line = Keyboard::readLine(message);
        return stoi(line);
    }
};

char Keyboard::keyboard[8];
