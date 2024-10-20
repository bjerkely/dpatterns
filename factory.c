#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Step 1: Create an Animal interface using a struct
// The Animal struct acts as a base "interface" with a function pointer for `speak`.
typedef struct Animal {
    void (*speak)(struct Animal *self);  // Function pointer for polymorphic behavior
} Animal;

// Step 2: Implement the Dog class (a struct that implements Animal)
// Dog struct "inherits" from Animal by including an Animal base struct.
typedef struct Dog {
    Animal base;  // Base struct to simulate inheritance
} Dog;

// Implementation of the `speak` function for Dog
void dog_speak(Animal *self) {
    printf("Woof!\n");  // Dog's unique implementation of `speak`
}

// Factory method to create a Dog
Dog* create_dog() {
    Dog *dog = (Dog *)malloc(sizeof(Dog));  // Allocate memory for Dog
    dog->base.speak = dog_speak;  // Set Dog's `speak` function
    return dog;  // Return the Dog object as a pointer
}

// Step 3: Implement the Cat class (another struct that implements Animal)
// Similar to Dog, Cat struct "inherits" from Animal.
typedef struct Cat {
    Animal base;  // Base struct to simulate inheritance
} Cat;

// Implementation of the `speak` function for Cat
void cat_speak(Animal *self) {
    printf("Meow!\n");  // Cat's unique implementation of `speak`
}

// Factory method to create a Cat
Cat* create_cat() {
    Cat *cat = (Cat *)malloc(sizeof(Cat));  // Allocate memory for Cat
    cat->base.speak = cat_speak;  // Set Cat's `speak` function
    return cat;  // Return the Cat object as a pointer
}

// Step 4: Create the Animal Factory
// This function acts as a factory that returns the appropriate type of Animal based on input
Animal* animal_factory(const char *animal_type) {
    if (strcmp(animal_type, "dog") == 0) {  // Check if the requested animal is a dog
        return (Animal *)create_dog();  // Return a Dog cast as an Animal
    } else if (strcmp(animal_type, "cat") == 0) {  // Check if the requested animal is a cat
        return (Animal *)create_cat();  // Return a Cat cast as an Animal
    } else {
        printf("Unknown animal type: %s\n", animal_type);  // Handle unknown animal types
        return NULL;  // Return NULL if the type is not recognized
    }
}

// Step 5: Client code to test the Factory Pattern
int main() {
    // Create a Dog using the factory
    Animal *dog = animal_factory("dog");
    if (dog != NULL) {  // Check if the dog was successfully created
        dog->speak(dog);  // Call the `speak` method, which will output "Woof!"
        free(dog);  // Free the allocated memory for Dog
    }

    // Create a Cat using the factory
    Animal *cat = animal_factory("cat");
    if (cat != NULL) {  // Check if the cat was successfully created
        cat->speak(cat);  // Call the `speak` method, which will output "Meow!"
        free(cat);  // Free the allocated memory for Cat
    }

    return 0;  // Exit the program
}
