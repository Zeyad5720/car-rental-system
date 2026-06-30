#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Class representing a Car
class Car {
private:
    string carId;
    string brand;
    string model;
    double pricePerDay;
    bool isAvailable;

public:
    Car(string id, string b, string m, double price) {
        carId = id;
        brand = b;
        model = m;
        pricePerDay = price;
        isAvailable = true;
    }

    string getCarId() const { return carId; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getPricePerDay() const { return pricePerDay; }
    bool getAvailability() const { return isAvailable; }

    void rentCar() { isAvailable = false; }
    void returnCar() { isAvailable = true; }
};

// Class representing a Customer
class Customer {
private:
    string customerId;
    string name;

public:
    Customer(string id, string n) {
        customerId = id;
        name = n;
    }

    string getCustomerId() const { return customerId; }
    string getName() const { return name; }
};

// Class managing the Rental Operations
class RentalSystem {
private:
    vector<Car> cars;
    vector<Customer> customers;

public:
    // Add cars to the system fleet
    void addCar(const Car& car) {
        cars.push_back(car);
    }

    // Display all available cars
    void displayAvailableCars() const {
        cout << "\n===== AVAILABLE CARS =====" << endl;
        cout << left << setw(10) << "Car ID" << setw(15) << "Brand" << setw(15) << "Model" << "Price/Day" << endl;
        cout << "---------------------------------------------------" << endl;

        bool found = false;
        for (const auto& car : cars) {
            if (car.getAvailability()) {
                cout << left << setw(10) << car.getCarId()
                     << setw(15) << car.getBrand()
                     << setw(15) << car.getModel()
                     << "$" << car.getPricePerDay() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No cars available at the moment." << endl;
        }
    }

    // Process a car rental
    void rentCarMenu() {
        string customerName, carIdToRent;
        int rentalDays;

        cout << "\n--- Rent a Car ---" << endl;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, customerName);

        displayAvailableCars();

        cout << "\nEnter the Car ID you want to rent: ";
        cin >> carIdToRent;
        cout << "Enter the number of days for rental: ";
        cin >> rentalDays;

        // Find the car
        Car* selectedCar = nullptr;
        for (auto& car : cars) {
            if (car.getCarId() == carIdToRent && car.getAvailability()) {
                selectedCar = &car;
                break;
            }
        }

        if (selectedCar != nullptr) {
            // Create a unique customer ID based on vector size
            string custId = "CUST" + to_string(customers.size() + 1);
            Customer newCustomer(custId, customerName);
            customers.push_back(newCustomer);

            selectedCar->rentCar();
            double totalBill = selectedCar->getPricePerDay() * rentalDays;

            cout << "\n===== RENTAL RECEIPT =====" << endl;
            cout << "Customer ID: " << newCustomer.getCustomerId() << endl;
            cout << "Customer Name: " << newCustomer.getName() << endl;
            cout << "Car: " << selectedCar->getBrand() << " " << selectedCar->getModel() << endl;
            cout << "Rental Duration: " << rentalDays << " days" << endl;
            cout << fixed << setprecision(2);
            cout << "Total Bill: $" << totalBill << endl;
            cout << "Rental successful! Drive safely." << endl;
        } else {
            cout << "\nError: Invalid Car ID or the car is currently unavailable." << endl;
        }
    }

    // Process a car return
    void returnCarMenu() {
        string carIdToReturn;
        cout << "\n--- Return a Car ---" << endl;
        cout << "Enter the Car ID you are returning: ";
        cin >> carIdToReturn;

        bool found = false;
        for (auto& car : cars) {
            if (car.getCarId() == carIdToReturn && !car.getAvailability()) {
                car.returnCar();
                cout << "\nCar ID " << carIdToReturn << " (" << car.getBrand() << " " << car.getModel() << ") returned successfully!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nError: Invalid Car ID or the car was not rented out." << endl;
        }
    }
};

// Main execution function
int main() {
    RentalSystem system;

    // Seeding the system with initial sample cars
    system.addCar(Car("CAR001", "Toyota", "Camry", 50.0));
    system.addCar(Car("CAR002", "Honda", "Civic", 45.0));
    system.addCar(Car("CAR003", "Ford", "Mustang", 90.0));
    system.addCar(Car("CAR004", "BMW", "3 Series", 120.0));

    int choice;
    do {
        cout << "\n=================================" << endl;
        cout << "    CAR RENTAL MANAGEMENT SYSTEM " << endl;
        cout << "=================================" << endl;
        cout << "1. View Available Cars" << endl;
        cout << "2. Rent a Car" << endl;
        cout << "3. Return a Car" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.displayAvailableCars();
                break;
            case 2:
                system.rentCarMenu();
                break;
            case 3:
                system.returnCarMenu();
                break;
            case 4:
                cout << "\nThank you for using the Car Rental System. Goodbye!" << endl;
                break;
            default:
                cout << "\nInvalid selection. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
