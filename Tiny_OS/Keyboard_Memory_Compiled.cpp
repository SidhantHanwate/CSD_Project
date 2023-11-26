
void global(){
    int MEMORY_SIZE = 16384;
    int FREE_LIST_START = 2048;

    int NO_BLOCK = -1;

    int freeBlockStarts[14336];
    int freeBlockSizes[14336];
    int memory[16384];
    int FL_LENGTH = 1;
    int FL_NEXT ;
    FL_NEXT=FREE_LIST_START;
    char keyboard[8];
}



void init() {
    FL_LENGTH = 1;
    FL_NEXT = FREE_LIST_START;
    freeBlockStarts[0] = FREE_LIST_START;
    freeBlockSizes[0] = MEMORY_SIZE - FREE_LIST_START;
    int i;
    for (i = 0; i < 8; i++) {
        keyboard[i] = 0;
    }
}

int peek(int address) {
    if (address >= 0 && address < MEMORY_SIZE) {
        return memory[address];
    }
    return -1; 
}

void poke(int address, int value) {
    if (address >= 0 && address < MEMORY_SIZE) {
        memory[address] = value;
    }
}

int best_fit(int size) {
    int bestFitIndex = NO_BLOCK;
    int bestFitSize = MEMORY_SIZE;
    int i;
    for (i = 0; i < FL_LENGTH; i=i+1) {
        if (freeBlockSizes[i] >= size && freeBlockSizes[i] < bestFitSize) {
            bestFitSize = freeBlockSizes[i];
            bestFitIndex = i;
        }
    }

    return bestFitIndex;
}

void custom_sort() {
    int i;
    for (i = 0; i < FL_LENGTH - 1; i=i+1) {
        int j;
        for (j = i + 1; j < FL_LENGTH; j=j+1) {
            if (freeBlockStarts[i] > freeBlockStarts[j]) {
                int tempStart = freeBlockStarts[i];
                int tempSize = freeBlockSizes[i];
                freeBlockStarts[i] = freeBlockStarts[j];
                freeBlockSizes[i] = freeBlockSizes[j];
                freeBlockStarts[j] = tempStart;
                freeBlockSizes[j] = tempSize;
            }
        }
    }
}

int allocate(int size) {
    //typeof size;
    int bestFitIndex = best_fit(size);

    if (bestFitIndex != NO_BLOCK) {
        int allocatedStart = freeBlockStarts[bestFitIndex];

        if (freeBlockSizes[bestFitIndex] > size) {
            freeBlockStarts[FL_LENGTH] = allocatedStart + size;
            freeBlockSizes[FL_LENGTH] = freeBlockSizes[bestFitIndex] - size;
            FL_LENGTH = FL_LENGTH + 1;
        }

        if (bestFitIndex < FL_LENGTH - 1) {
            int i;
            for (i = bestFitIndex; i < FL_LENGTH - 1; i=i+1) {
                freeBlockStarts[i] = freeBlockStarts[i+1];
                freeBlockSizes[i] = freeBlockSizes[i+1];
            }
        }

        FL_LENGTH = FL_LENGTH - 1;

        return allocatedStart;
    }

    return NO_BLOCK; // Allocation failed
}

void deallocate(int start, int size) {
    freeBlockStarts[FL_LENGTH] = start;
    freeBlockSizes[FL_LENGTH] = size;
    FL_LENGTH = FL_LENGTH + 1;

    custom_sort();

    // Merge adjacent free blocks
    int i;
    for (i = 0; i < FL_LENGTH - 1; i=i+1) {
        if (freeBlockStarts[i] + freeBlockSizes[i] == freeBlockStarts[i + 1]) {
            freeBlockSizes[i] = freeBlockSizes[i] + freeBlockSizes[i + 1];
            int j;
            for(j = i+1; j < FL_LENGTH - 1; j=j+1) {
                freeBlockStarts[j] = freeBlockStarts[j+1];
                freeBlockSizes[j] = freeBlockSizes[j+1];
            }
            FL_LENGTH = FL_LENGTH - 1;
            i = i - 1;
        }
    }
}


char keyPressed() {
    return keyboard[0];
}

char readChar() {
    char key;
    while (keyPressed() == 0) {}
    key = keyPressed();
    while (keyPressed() != 0) {}
    //cout << key;   //print to screen
    return key;
}

string removeLastCharacter(string input,int length) {
    // if (input.length() == 0) {
    //     return input; // Return empty string if input is already empty
    // }   This base case is redundant. Already handled in readLine itself.
    
    string result;
    int i;
    for (i = 0; i < length-1; i=i+1) {
        result = result + input[i];
    }
    return result;
}

string readLine(string message) {
    string line;
    int length=0;
    char c;

    //cout << message;
    c = readChar();
    // char a = '\n';
    // char b = '\b';
    while (c != '\n') {
        if (c == '\b') {
            if (length != 0) {
                removeLastCharacter(line,length);
            }
        }
        else {
            line = line + c;
            length=length+1;
        }
        c = readChar();
    }

    return line;
}

int stoi(string str) {
    int result = 0;
    bool isNegative = 0;
    int i = 0;

    if (str[0] == '-') {
        isNegative = 1;
        // i = 1;
    }

    for (i=1; i < 10; i=i+1) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            // Handle invalid characters here if needed
            // For simplicity, we'll just return 0 for invalid inputs
            return 0;
        }
    }

    if (isNegative) {
        result = -result;
    }

    return result;
}

int readInt(string message) {
    string line;
    line = readLine(message);
    return stoi(line);
}


int main() {
    global();
    init();
    return 0;
}