/*
Explanation:
C Implementation (animal_factory.c):

Standard C functions for creating Dog and Cat objects using a factory function.
Memory management is done manually using malloc and free.
C++ Implementation (animal_factory_cpp.hpp):

The C++ version uses std::unique_ptr for memory management and a factory function that throws exceptions for invalid inputs.
Test Code (test_main.cpp):

The test file uses extern "C" to include the C code, ensuring proper linkage between the C and C++ implementations.
The test_c_implementation() function tests the C version by calling the C factory functions, invoking speak(), and manually managing memory.
The test_cpp_implementation() function tests the C++ version, using std::unique_ptr for memory management and handling exceptions for unknown animal types.
Both implementations are tested to verify correctness.
Compilation:
To compile the test code and link both C and C++ files, you can use a command like this (assuming GCC is used):

g++ -std=c++11 test_main.cpp animal_factory.c -o test_program
*/

// test_main.cpp (C++ test code to test both C and C++ implementations)

#include <iostream>
#include <memory>
#include <string>

// Include the C implementation
extern "C" {
    #include "animal_factory.c"
}

// Include the C++ implementation
#include "animal_factory_cpp.hpp"

void test_c_implementation() {
    std::cout << "Testing C implementation:" << std::endl;

    Animal *dog = animal_factory("dog");
    if (dog) {
        dog->speak(dog);  // Should print "Woof!"
        free_animal(dog);
    } else {
        std::cout << "Dog creation failed!" << std::endl;
    }

    Animal *cat = animal_factory("cat");
    if (cat) {
        cat->speak(cat);  // Should print "Meow!"
        free_animal(cat);
    } else {
        std::cout << "Cat creation failed!" << std::endl;
    }

    Animal *unknown = animal_factory("lion");
    if (unknown) {
        std::cout << "Unknown animal creation succeeded (this should not happen)!" << std::endl;
        free_animal(unknown);
    } else {
        std::cout << "Unknown animal creation failed (expected)!" << std::endl;
    }
}

void test_cpp_implementation() {
    std::cout << "Testing C++ implementation:" << std::endl;

    try {
        auto dog = AnimalFactory::createAnimal("dog");
        dog->speak();  // Should print "Woof!"
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    try {
        auto cat = AnimalFactory::createAnimal("cat");
        cat->speak();  // Should print "Meow!"
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    try {
        auto unknown = AnimalFactory::createAnimal("lion");
        unknown->speak();  // Should never be reached
    } catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;  // Expected: "Unknown animal type: lion"
    }
}

int main() {
    // Test C implementation
    test_c_implementation();

    // Test C++ implementation
    test_cpp_implementation();

    return 0;
}
