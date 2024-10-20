/*
Explanation:
Animal Interface:

The base class Animal is an abstract class with a pure virtual method speak(). This ensures that any class inheriting from Animal must implement the speak() method.
Destructor: The virtual ~Animal() destructor ensures that when we delete a derived object through a pointer to the base class (Animal), the correct destructor (for Dog or Cat) will be called.
Dog and Cat Concrete Classes:

Both Dog and Cat inherit from Animal and override the speak() method to provide their unique implementations.
The override keyword is used to explicitly declare that the function is overriding a base class method.
Factory Class (AnimalFactory):

The AnimalFactory class contains a static method createAnimal() that returns a unique_ptr<Animal>.
std::unique_ptr: This is a smart pointer that automatically manages memory. We use it to avoid manual memory management (i.e., calling delete) in the client code. It ensures that the objects are properly destroyed when they go out of scope.
Exception Handling: If an unknown animal type is passed to the factory, the method throws an invalid_argument exception.
Client Code:

The client code uses the factory to create a Dog and a Cat. It doesn't need to know about the concrete class constructors or memory management.
We use the speak() method on both animals to demonstrate polymorphism: the method call resolves to the correct implementation (Dog::speak() or Cat::speak()).
Benefits in C++:
Encapsulation: The client is not aware of the object creation process.
Polymorphism: The client interacts with objects via the base class (Animal) interface, and the correct method (speak()) is called based on the actual type of the object at runtime.
Memory Management: std::unique_ptr ensures that objects are deleted automatically, preventing memory leaks.
This approach follows the Factory Pattern principles while leveraging C++ features like polymorphism, exception handling, and smart pointers for safe memory management.

The C++ code provided uses features from C++11 and later. Specifically, it relies on the following key features introduced in C++11:

std::unique_ptr:

This is a smart pointer introduced in C++11, which automatically manages the lifetime of dynamically allocated objects and ensures that the memory is properly released when the pointer goes out of scope.
std::make_unique:

This function was added in C++14. It simplifies the creation of std::unique_ptr objects, ensuring exception safety and avoiding manual use of new.
override keyword:

This keyword was introduced in C++11 to explicitly indicate that a method is overriding a virtual method from the base class. It helps the compiler catch errors where a method might not correctly override a base class method due to a mismatch in the function signature.
Lambdas and range-based for loops (not used but available):

These features, though not directly used in the example, are also part of C++11 and would be accessible if needed.
*/

#include <iostream>
#include <string>
#include <memory>

// Step 1: Create an abstract base class "Animal"
// In C++, we use a class with a pure virtual function to act as the interface.
class Animal {
public:
    virtual void speak() const = 0;  // Pure virtual function (interface)
    virtual ~Animal() {}  // Virtual destructor to ensure proper cleanup of derived objects
};

// Step 2: Implement concrete classes "Dog" and "Cat" that inherit from "Animal"

// Dog class that inherits from Animal
class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!" << std::endl;  // Dog's implementation of speak
    }
};

// Cat class that inherits from Animal
class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Meow!" << std::endl;  // Cat's implementation of speak
    }
};

// Step 3: Create the Factory class that returns an Animal based on the input type
class AnimalFactory {
public:
    // The factory method that creates and returns Animal objects
    static std::unique_ptr<Animal> createAnimal(const std::string &animal_type) {
        if (animal_type == "dog") {
			return std::unique_ptr<Dog>(new Dog());   // Return a unique_ptr to a Dog object
        } else if (animal_type == "cat") {
            return std::unique_ptr<Cat>(new Cat());  // Return a unique_ptr to a Cat object
        } else {
            throw std::invalid_argument("Unknown animal type: " + animal_type);  // Throw an exception for unknown types
        }
    }
};

// Step 4: Client code to test the Factory Pattern
int main() {
    try {
        // Create a Dog using the factory
        std::unique_ptr<Animal> dog = AnimalFactory::createAnimal("dog");
        dog->speak();  // Output: Woof!

        // Create a Cat using the factory
        std::unique_ptr<Animal> cat = AnimalFactory::createAnimal("cat");
        cat->speak();  // Output: Meow!

    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;  // Handle exceptions if an unknown animal type is requested
    }

    return 0;  // Exit the program
}
