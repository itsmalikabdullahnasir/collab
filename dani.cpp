#include <iostream>
#include <vector>
#include <string>
#include <memory> // For smart pointers
#include <limits> // For std::numeric_limits

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

    void cancelSlot() {
        if (availableSlots < maxSlots) {
            availableSlots++;
        }
    }
};

class Booking {
private:
    string memberName;
    shared_ptr<FitnessClass> fitnessClass;

public:
    Booking(const string& name, shared_ptr<FitnessClass> fitnessClass)
        : memberName(name), fitnessClass(fitnessClass) {}

    string getMemberName() const {
        return memberName;
    }

    shared_ptr<FitnessClass> getFitnessClass() const {
        return fitnessClass;
    }
};

// Function prototypes
void displayFitnessClasses(const vector<shared_ptr<FitnessClass>>& classes);
void displayMenu();
int getUserChoice(int maxOption);
void handleBooking(vector<shared_ptr<FitnessClass>>& classes, vector<Booking>& bookings);
void viewBookings(const vector<Booking>& bookings);
void cancelBooking(vector<Booking>& bookings);

int main() {
    vector<shared_ptr<FitnessClass>> classes = {
        make_shared<FitnessClass>("Yoga", 10),
        make_shared<FitnessClass>("Zumba", 15),
        make_shared<FitnessClass>("Pilates", 8)
    };

    vector<Booking> bookings;

    int choice;
    do {
        displayMenu();
        choice = getUserChoice(4);

        switch (choice) {
        case 1:
            displayFitnessClasses(classes);
            break;
        case 2:
            handleBooking(classes, bookings);
            break;
        case 3:
            viewBookings(bookings);
            break;
        case 4:
            cancelBooking(bookings);
            // Update class slots inside cancelBooking function as needed
            break;
        default:
            cout << "Exiting program." << endl;
        }
    } while (choice != 5);

    return 0;
}

void displayFitnessClasses(const vector<shared_ptr<FitnessClass>>& classes) {
    cout << "Available Fitness Classes:" << endl;
    for (size_t i = 0; i < classes.size(); i++) {
        cout << i + 1 << ". " << classes[i]->getClassName() << " (" << classes[i]->getAvailableSlots() << " slots available)" << endl;
    }
}

void displayMenu() {
    cout << "\nMenu:\n"
        << "1. View available fitness classes\n"
        << "2. Book a class\n"
        << "3. View bookings\n"
        << "4. Cancel booking\n"
        << "5. Exit\n"
        << "Enter your choice: ";
}

int getUserChoice(int maxOption) {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > maxOption) {
        cout << "Invalid choice, please enter a number between 1 and " << maxOption << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

void handleBooking(vector<shared_ptr<FitnessClass>>& classes, vector<Booking>& bookings) {
    displayFitnessClasses(classes);
    cout << "Enter the number of the fitness class you want to book: ";
    int choice = getUserChoice(classes.size());

    shared_ptr<FitnessClass> chosenClass = classes[choice - 1];
    if (chosenClass->bookSlot()) {
        cout << "Enter your name: ";
        string memberName;
        cin >> memberName;
        bookings.push_back(Booking(memberName, chosenClass));
        cout << "Booking confirmed for " << chosenClass->getClassName() << "." << endl;
    }
    else {
        cout << "Sorry, no slots available for " << chosenClass->getClassName() << "." << endl;
    }
}

void viewBookings(const vector<Booking>& bookings) {
    if (bookings.empty()) {
        cout << "No bookings have been made." << endl;
        return;
    }

    cout << "Current Bookings:" << endl;
    for (const auto& booking : bookings) {
        cout << booking.getMemberName() << " has booked " << booking.getFitnessClass()->getClassName() << "." << endl;
    }
}

void cancelBooking(vector<Booking>& bookings) {
    if (bookings.empty()) {
        cout << "No bookings to cancel." << endl;
        return;
    }

    cout << "Which booking would you like to cancel?" << endl;
    for (size_t i = 0; i < bookings.size(); ++i) {
        cout << i + 1 << ". " << bookings[i].getMemberName() << " - " << bookings[i].getFitnessClass()->getClassName() << endl;
    }

    int choice = getUserChoice(bookings.size());
    // Adjust available slots for the class
    bookings[choice - 1].getFitnessClass()->cancelSlot();
    // Remove the booking
    bookings.erase(bookings.begin() + (choice - 1));
    cout << "Booking cancelled." << endl;
}