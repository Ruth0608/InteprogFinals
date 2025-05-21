#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class for all users
class User {
protected:
    string id, name, email, password;

public:
    User(string id, string name, string email, string password)
        : id(id), name(name), email(email), password(password) {}

    virtual bool login(const string& inputEmail, const string& inputPassword) {
        return email == inputEmail && password == inputPassword;
    }

    virtual void registerUser() {
        cout << "User " << name << " registered successfully." << endl;
    }

    virtual void viewProfile() {
        cout << "ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }

    virtual void searchFlight(const vector<string>& flights) {
        cout << "Available flights:\n";
        for (const auto& flight : flights) {
            cout << " - " << flight << endl;
        }
    }

    virtual ~User() {}
};

class Passenger : public User {
public:
    Passenger(string id, string name, string email, string password)
        : User(id, name, email, password) {}

    void bookTicket() {
        cout << name << " booked a ticket." << endl;
    }

    void cancelTicket() {
        cout << name << " canceled a ticket." << endl;
    }

    void viewBookingHistory() {
        cout << name << " is viewing booking history." << endl;
    }
};

class Admin : public User {
public:
    Admin(string id, string name, string email, string password)
        : User(id, name, email, password) {}

    void manageUsers() {
        cout << name << " is managing users." << endl;
    }

    void addFlight() {
        cout << name << " added a new flight." << endl;
    }

    void editFlight() {
        cout << name << " edited a flight." << endl;
    }

    void deleteFlight() {
        cout << name << " deleted a flight." << endl;
    }

    void viewAllBookings() {
        cout << name << " is viewing all bookings." << endl;
    }
};

class Staff : public User {
public:
    Staff(string id, string name, string email, string password)
        : User(id, name, email, password) {}

    void assistPassengers() {
        cout << name << " is assisting passengers." << endl;
    }

    void updateFlightStatus() {
        cout << name << " updated flight status." << endl;
    }

    void confirmCheckIn() {
        cout << name << " confirmed check-in for a passenger." << endl;
    }

    void viewPassengerList() {
        cout << name << " is viewing the passenger list." << endl;
    }
