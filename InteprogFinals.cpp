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
}
};

void displayMainMenu() {
    cout << "\nAirline Reservation System" << endl;
    cout << "1. Login as Passenger" << endl;
    cout << "2. Login as Admin" << endl;
    cout << "3. Login as Staff" << endl;
    cout << "4. Register as Passenger" << endl;
    cout << "5. View Flights (Guest)" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Passenger> passengers;
    vector<Admin> admins = {
        Admin("admin1", "Admin One", "admin@example.com", "adminpass"),
        Admin("admin2", "Admin", "admin@gmail.com", "password")
    };
    vector<Staff> staffMembers = {
        Staff("staff1", "Staff One", "staff@example.com", "staffpass"),
        Staff("staff2", "Staff", "staff@gmail.com", "password")
    };
    vector<string> flights = { "Flight A - New York to London", "Flight B - Paris to Tokyo" };

    User* currentUser = nullptr;
    string userRole;

    while (true) {
        while (currentUser == nullptr) {
            displayMainMenu();
            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    string email, password;
                    cout << "Enter email: ";
                    getline(cin, email);
                    cout << "Enter password: ";
                    getline(cin, password);

                    for (auto& passenger : passengers) {
                        if (passenger.login(email, password)) {
                            currentUser = &passenger;
                            userRole = "Passenger";
                            break;
                        }
                    }

                    if (currentUser) {
                        cout << "Login successful as Passenger!" << endl;
                    } else {
                        cout << "Invalid Passenger credentials!" << endl;
                    }
                    break;
                }
                case 2: {
                    string email, password;
                    cout << "Enter admin email: ";
                    getline(cin, email);
                    cout << "Enter password: ";
                    getline(cin, password);

                    for (auto& admin : admins) {
                        if (admin.login(email, password)) {
                            currentUser = &admin;
                            userRole = "Admin";
                            break;
                        }
                    }

                    if (currentUser) {
                        cout << "Login successful as Admin!" << endl;
                    } else {
                        cout << "Invalid Admin credentials!" << endl;
                    }
                    break;
                }
                case 3: {
                    string email, password;
                    cout << "Enter staff email: ";
                    getline(cin, email);
                    cout << "Enter password: ";
                    getline(cin, password);

                    for (auto& staff : staffMembers) {
                        if (staff.login(email, password)) {
                            currentUser = &staff;
                            userRole = "Staff";
                            break;
                        }
                    }

                    if (currentUser) {
                        cout << "Login successful as Staff!" << endl;
                    } else {
                        cout << "Invalid Staff credentials!" << endl;
                    }
