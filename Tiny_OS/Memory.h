#include <iostream>
#include <vector>
#include <bits/stdc++.h>

const int MEMORY_SIZE = 16384;
const int FREE_LIST_START = 2048;

const int NO_BLOCK = -1;

class MemoryManager {
private:
    std::vector<int> freeBlockStarts;
    std::vector<int> freeBlockSizes;
    std::vector<int> memory;
    int FL_LENGTH;
    int FL_NEXT;

public:
    void init() {
        FL_LENGTH = 0;
        FL_NEXT = FREE_LIST_START;
        freeBlockStarts.push_back(FREE_LIST_START);
        freeBlockSizes.push_back(MEMORY_SIZE - FREE_LIST_START);
        memory.resize(MEMORY_SIZE, 0);
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

    int allocate(int size) {
        int bestFitIndex = best_fit(size);

        if (bestFitIndex != NO_BLOCK) {
            int allocatedStart = freeBlockStarts[bestFitIndex];

            if (freeBlockSizes[bestFitIndex] > size) {
                freeBlockStarts[bestFitIndex] += size;
                freeBlockSizes[bestFitIndex] -= size;
            } else {
                freeBlockStarts.erase(freeBlockStarts.begin() + bestFitIndex);
                freeBlockSizes.erase(freeBlockSizes.begin() + bestFitIndex);
            }

            return allocatedStart;
        }

        return NO_BLOCK; // Allocation failed
    }

    void deallocate(int start, int size) {
        freeBlockStarts.push_back(start);
        freeBlockSizes.push_back(size);

        // Sort by start addresses
        for (int i = 0; i < freeBlockStarts.size() - 1; i++) {
            for (int j = i + 1; j < freeBlockStarts.size(); j++) {
                if (freeBlockStarts[i] > freeBlockStarts[j]) {
                    std::swap(freeBlockStarts[i], freeBlockStarts[j]);
                    std::swap(freeBlockSizes[i], freeBlockSizes[j]);
                }
            }
        }

        // Merge adjacent free blocks
        for (int i = 0; i < freeBlockStarts.size() - 1; i++) {
            if (freeBlockStarts[i] + freeBlockSizes[i] == freeBlockStarts[i + 1]) {
                freeBlockSizes[i] += freeBlockSizes[i + 1];
                freeBlockStarts.erase(freeBlockStarts.begin() + i + 1);
                freeBlockSizes.erase(freeBlockSizes.begin() + i + 1);
                i--;
            }
        }
    }

    void printFreeList() {
        std::cout << "Free List: ";
        for(int i = 0; i < freeBlockStarts.size(); i++) {
            std::cout << "(" << freeBlockStarts[i] << ", " << freeBlockSizes[i] << ") ";
        }
        std::cout << std::endl;
    }

private:
    int best_fit(int size) {
        int bestFitIndex = NO_BLOCK;
        int bestFitSize = INT_MAX;

        for (int i = 0; i < freeBlockStarts.size(); i++) {
            if (freeBlockSizes[i] >= size && freeBlockSizes[i] < bestFitSize) {
                bestFitSize = freeBlockSizes[i];
                bestFitIndex = i;
            }
        }

        return bestFitIndex;
    }
};
