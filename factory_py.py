from abc import ABC, abstractmethod

# Step 1: Create an Animal interface or abstract class
class Animal(ABC):
    @abstractmethod
    def speak(self):
        pass

# Step 2: Create concrete classes that implement the Animal interface
class Dog(Animal):
    def speak(self):
        return "Woof!"

class Cat(Animal):
    def speak(self):
        return "Meow!"

# Step 3: Create a Factory class to generate objects of concrete classes based on the input
class AnimalFactory:
    @staticmethod
    def create_animal(animal_type: str) -> Animal:
        if animal_type == "dog":
            return Dog()
        elif animal_type == "cat":
            return Cat()
        else:
            raise ValueError(f"Unknown animal type: {animal_type}")

# Step 4: Client code that uses the factory
if __name__ == "__main__":
    # Create a dog using the factory
    dog = AnimalFactory.create_animal("dog")
    print(f"Dog says: {dog.speak()}")  # Output: Dog says: Woof!

    # Create a cat using the factory
    cat = AnimalFactory.create_animal("cat")
    print(f"Cat says: {cat.speak()}")  # Output: Cat says: Meow!
