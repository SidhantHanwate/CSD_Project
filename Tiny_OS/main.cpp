#include "Keyboard.h"
#include "Memory.h"
#include <iostream>
using namespace std;

int main() {

    // MemoryManager manager;

    // manager.init();

    // manager.printFreeList();

    // int ptr1 = manager.allocate(1024);
    // int ptr2 = manager.allocate(2048);
    // int ptr3 = manager.allocate(4096);

    // if (ptr1 != NO_BLOCK) std::cout << "Memory block 1 allocated at: " << ptr1 << std::endl;
    // if (ptr2 != NO_BLOCK) std::cout << "Memory block 2 allocated at: " << ptr2 << std::endl;
    // if (ptr3 != NO_BLOCK) std::cout << "Memory block 3 allocated at: " << ptr3 << std::endl;

    // manager.printFreeList(); // Print the state of the free list
    // // Deallocate memory
    // if (ptr1 != NO_BLOCK) manager.deallocate(ptr1, 1024);
    // if (ptr2 != NO_BLOCK) manager.deallocate(ptr2, 2048);

    // cout<<"After deallocation of ptr1 and ptr2: \n";
    // manager.printFreeList(); // Print the state of the free list after deallocation

    // int p = manager.allocate(100);
    // manager.printFreeList();
    
    // manager.poke(100, 42);
    // std::cout << "Value at address 100: " << manager.peek(100) << std::endl;

    // Initialize the Keyboard
    Keyboard::init();

    // Sample usage for Keyboard
    string inputLine = Keyboard::readLine("\nEnter a line: ");
    cout << "\nYou entered: " << inputLine << endl;

    int inputInt = Keyboard::readInt("\nEnter an integer: ");
    cout << "\nYou entered: " << inputInt << endl;

    char readCharacter = Keyboard::readChar();
    cout << "\nYou entered character: " << readCharacter << endl;

    char pressedKey = Keyboard::keyPressed();
    cout << "\nCurrently pressed key: " << pressedKey << endl;

    return 0;
}

