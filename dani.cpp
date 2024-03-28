#include <iostream>
#include <vector>
#include <string>

class FitnessClass {
private:
    std::string className;
    int maxSlots;
    int availableSlots;

public:
    FitnessClass(const std::string& name, int maxSlots)
        : className(name), maxSlots(maxSlots), availableSlots(maxSlots) {}

    std::string getClassName() const {
        return className;
    }

    int getAvailableSlots() const {
        return availableSlots;
    }

    bool bookSlot() {
        if (availableSlots > 0) {
            availableSlots--;
            return true;
        }
        return false;
    }
};

class Booking {
private:
    std::string memberName;
    FitnessClass* fitnessClass;

public:
    Booking(const std::string& name, FitnessClass* fitnessClass)
        : memberName(name), fitnessClass(fitnessClass) {}

    std::string getMemberName() const {
        return memberName;
    }

    FitnessClass* getFitnessClass() const {
        return fitnessClass;
    }
};

int main() {
    // Create fitness classes
    FitnessClass yoga("Yoga", 10);
    FitnessClass zumba("Zumba", 15);
    FitnessClass pilates("Pilates", 8);

    // Create a vector to store bookings
    std::vector<Booking> bookings;

    // Display available fitness classes
    std::cout << "Available Fitness Classes:" << std::endl;
    std::cout << "1. " << yoga.getClassName() << " (" << yoga.getAvailableSlots() << " slots available)" << std::endl;
    std::cout << "2. " << zumba.getClassName() << " (" << zumba.getAvailableSlots() << " slots available)" << std::endl;
    std::cout << "3. " << pilates.getClassName() << " (" << pilates.getAvailableSlots() << " slots available)" << std::endl;

    // Get member's choice
    int choice;
    std::cout << "Enter the number of the fitness class you want to book: ";
    std::cin >> choice;

    // Book a slot for the chosen fitness class
    FitnessClass* chosenClass = nullptr;
    switch (choice) {
        case 1:
            chosenClass = &yoga;
            break;
        case 2:
            chosenClass = &zumba;
            break;
        case 3:
            chosenClass = &pilates;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            return 0;
    }

    if (chosenClass->bookSlot()) {
        std::string memberName;
        std::cout << "Enter your name: ";
        std::cin >> memberName;

        Booking newBooking(memberName, chosenClass);
        bookings.push_back(newBooking);

        std::cout << "Booking confirmed! You have successfully booked a slot for " << chosenClass->getClassName() << "." << std::endl;
    } else {
        std::cout << "Sorry, no slots available for " << chosenClass->getClassName() << "." << std::endl;
    }

    return 0;
}