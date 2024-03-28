#include <iostream>
#include <vector>
#include <string>

using namespace std;


class FitnessClass {
private:
    string className;
    int maxSlots;
    int availableSlots;

public:
    FitnessClass(const string& name, int maxSlots)
        : className(name), maxSlots(maxSlots), availableSlots(maxSlots) {}

    string getClassName() const {
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
    string memberName;
    FitnessClass* fitnessClass;

public:
    Booking(const string& name, FitnessClass* fitnessClass)
        : memberName(name), fitnessClass(fitnessClass) {}

    string getMemberName() const {
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
    vector<Booking> bookings;

    // Display available fitness classes
    cout << "Available Fitness Classes:" << endl;
    cout << "1. " << yoga.getClassName() << " (" << yoga.getAvailableSlots() << " slots available)" << endl;
    cout << "2. " << zumba.getClassName() << " (" << zumba.getAvailableSlots() << " slots available)" << endl;
    cout << "3. " << pilates.getClassName() << " (" << pilates.getAvailableSlots() << " slots available)" << endl;

    // Get member's choice
    int choice;
    cout << "Enter the number of the fitness class you want to book: ";
    cin >> choice;

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
        cout << "Invalid choice!" << endl;
        return 0;
    }

    if (chosenClass->bookSlot()) {
        string memberName;
        cout << "Enter your name: ";
        cin >> memberName;

        Booking newBooking(memberName, chosenClass);
        bookings.push_back(newBooking);

        cout << "Booking confirmed! You have successfully booked a slot for " << chosenClass->getClassName() << "." << endl;
    }
    else {
        cout << "Sorry, no slots available for " << chosenClass->getClassName() << "." << endl;
    }

    return 0;
}