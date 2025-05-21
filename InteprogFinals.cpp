#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;
class Flight {
private:
string flightNumber;
string origin;
string destination;
string departureTime;
string date;
double price;
int availableSeats;
string status;
public:
Flight(string num, string orig, string dest, string time, string dt, double p, int seats)
: flightNumber(num), origin(orig), destination(dest),
departureTime(time), date(dt), price(p), availableSeats(seats), status("On Time") {}
// Getters
string getFlightNumber() const { return flightNumber; }
string getOrigin() const { return origin; }
string getDestination() const { return destination; }
string getDepartureTime() const { return departureTime; }
string getDate() const { return date; }
double getPrice() const { return price; }
int getAvailableSeats() const { return availableSeats; }
string getStatus() const { return status; }
// Setters
void setStatus(string newStatus) { status = newStatus; }
void setAvailableSeats(int seats) { availableSeats = seats; }
void displayDetails() const {
cout << "\nFlight " << flightNumber << ":\n";
cout << "Route: " << origin << " to " << destination << endl;
cout << "Date: " << date << " at " << departureTime << endl;
cout << "Price: $" << price << endl;
cout << "Available Seats: " << availableSeats << endl;
cout << "Status: " << status << endl;
}
};
class User {
protected:
string id;
string name;
string email;
string password;
public:
User(string id, string name, string email, string password)
: id(id), name(name), email(email), password(password) {}
virtual bool login(string email, string password) {
return (this->email == email && this->password == password);
}
virtual void registerUser() {
cout << "User registered successfully!\n";
}
string getName() const { return name; }
string getEmail() const { return email; }
string getId() const { return id; }
string getPassword() const { return password; }
void setName(string newName) { name = newName; }
void setEmail(string newEmail) { email = newEmail; }
void setPassword(string newPassword) { password = newPassword; }
virtual void searchFlights(const vector<Flight>& flights, string destination = "", string date = "")
{
cout << "\nAvailable Flights:\n";
for (const auto& flight : flights) {
if ((destination.empty() || flight.getDestination() == destination) &&
(date.empty() || flight.getDate() == date)) {
flight.displayDetails();
}
}
}
virtual ~User() {}
};
class Passenger : public User {
private:
vector<string> bookedFlights;
public:
Passenger(string id, string name, string email, string password)
: User(id, name, email, password) {}
void bookFlight(Flight& flight) {
if (flight.getAvailableSeats() > 0) {
flight.setAvailableSeats(flight.getAvailableSeats() - 1);
bookedFlights.push_back(flight.getFlightNumber());
cout << "\nSuccessfully booked Flight " << flight.getFlightNumber() << endl;
cout << "From: " << flight.getOrigin() << " to " << flight.getDestination() << endl;
cout << "Departure: " << flight.getDate() << " at " << flight.getDepartureTime() << endl;
cout << "Price: $" << flight.getPrice() << endl;
} else {
cout << "\nNo available seats for this flight!\n";
}
}
void cancelBooking(Flight& flight) {
auto it = find(bookedFlights.begin(), bookedFlights.end(), flight.getFlightNumber());
if (it != bookedFlights.end()) {
bookedFlights.erase(it);
flight.setAvailableSeats(flight.getAvailableSeats() + 1);
cout << "\nBooking for Flight " << flight.getFlightNumber() << " canceled successfully!\n";
} else {
cout << "\nNo booking found for this flight!\n";
}
}
void viewBookings(const vector<Flight>& flights) {
cout << "\n=== YOUR BOOKING HISTORY ===\n";
if (bookedFlights.empty()) {
cout << "You have no bookings yet.\n";
return;
}
for (const auto& flightNum : bookedFlights) {
bool found = false;
for (const auto& flight : flights) {
if (flight.getFlightNumber() == flightNum) {
flight.displayDetails();
found = true;
break;
}
}
if (!found) {
cout << "Flight " << flightNum << " (details not available)\n";
}
}
}
void updateProfile() {
cout << "\n=== UPDATE PROFILE ===\n";
cout << "Current Name: " << name << endl;
cout << "New Name (leave blank to keep current): ";
string newName;
getline(cin, newName);
if (!newName.empty()) name = newName;
cout << "Current Email: " << email << endl;
cout << "New Email (leave blank to keep current): ";
string newEmail;
getline(cin, newEmail);
if (!newEmail.empty()) email = newEmail;
cout << "New Password (leave blank to keep current): ";
string newPassword;
getline(cin, newPassword);
if (!newPassword.empty()) password = newPassword;
cout << "Profile updated successfully!\n";
}
void passengerMenu(vector<Flight>& flights) {
while (true) {
cout << "\n===== PASSENGER MENU =====\n";
cout << "1. Search Flights\n";
cout << "2. Book Flight\n";
cout << "3. Cancel Booking\n";
cout << "4. View Booking History\n";
cout << "5. Update Profile\n";
cout << "6. Logout\n";
cout << "Enter your choice: ";
int choice;
cin >> choice;
cin.ignore();
switch (choice) {
case 1: {
string destination, date;
cout << "\n=== SEARCH FLIGHTS ===\n";
cout << "Enter destination (leave empty for all): ";
getline(cin, destination);
cout << "Enter date (YYYY-MM-DD, leave empty for all): ";
getline(cin, date);
searchFlights(flights, destination, date);
break;
}
case 2: {
string flightNum;
cout << "\n=== BOOK FLIGHT ===\n";
cout << "Enter flight number to book: ";
getline(cin, flightNum);
bool found = false;
for (auto& flight : flights) {
if (flight.getFlightNumber() == flightNum) {
bookFlight(flight);
found = true;
break;
}
}
if (!found) {
cout << "Flight not found!\n";
}
break;
}
case 3: {
string flightNum;
cout << "\n=== CANCEL BOOKING ===\n";
cout << "Enter flight number to cancel: ";
getline(cin, flightNum);
bool found = false;
for (auto& flight : flights) {
if (flight.getFlightNumber() == flightNum) {
cancelBooking(flight);
found = true;
break;
}
}
if (!found) {
cout << "Flight not found!\n";
}
break;
}
case 4:
viewBookings(flights);
break;
case 5:
updateProfile();
break;
case 6:
cout << "Logging out...\n";
return;
default:
cout << "Invalid choice! Please try again.\n";
}
}
}
};
class Admin : public User {
public:
Admin(string id, string name, string email, string password)
: User(id, name, email, password) {}
void addFlight(vector<Flight>& flights) {
string num, orig, dest, time, date;
double price;
int seats;
cout << "\nEnter flight number: ";
getline(cin, num);
cout << "Enter origin: ";
getline(cin, orig);
cout << "Enter destination: ";
getline(cin, dest);
cout << "Enter departure time: ";
getline(cin, time);
cout << "Enter date (YYYY-MM-DD): ";
getline(cin, date);
cout << "Enter price: ";
cin >> price;
cout << "Enter available seats: ";
cin >> seats;
cin.ignore();
flights.emplace_back(num, orig, dest, time, date, price, seats);
cout << "Flight added successfully!\n";
}
void editFlight(vector<Flight>& flights) {
string num;
cout << "Enter flight number to edit: ";
getline(cin, num);
for (auto& flight : flights) {
if (flight.getFlightNumber() == num) {
cout << "\nCurrent flight details:\n";
flight.displayDetails();
cout << "\nEnter new details (leave blank to keep current):\n";
string orig, dest, time, date, status;
double price;
int seats;
cout << "Enter new origin: ";
getline(cin, orig);
if (!orig.empty()) flight = Flight(num, orig, flight.getDestination(),
flight.getDepartureTime(), flight.getDate(),
flight.getPrice(), flight.getAvailableSeats());
cout << "Enter new destination: ";
getline(cin, dest);
if (!dest.empty()) flight = Flight(num, flight.getOrigin(), dest,
flight.getDepartureTime(), flight.getDate(),
flight.getPrice(), flight.getAvailableSeats());
cout << "Enter new departure time: ";
getline(cin, time);
if (!time.empty()) flight = Flight(num, flight.getOrigin(), flight.getDestination(),
time, flight.getDate(),
flight.getPrice(), flight.getAvailableSeats());
cout << "Enter new date (YYYY-MM-DD): ";
getline(cin, date);
if (!date.empty()) flight = Flight(num, flight.getOrigin(), flight.getDestination(),
flight.getDepartureTime(), date,
flight.getPrice(), flight.getAvailableSeats());
cout << "Enter new price: ";
string priceStr;
getline(cin, priceStr);
if (!priceStr.empty()) {
price = stod(priceStr);
flight = Flight(num, flight.getOrigin(), flight.getDestination(),
flight.getDepartureTime(), flight.getDate(),
price, flight.getAvailableSeats());
}
cout << "Enter new available seats: ";
string seatsStr;
getline(cin, seatsStr);
if (!seatsStr.empty()) {
seats = stoi(seatsStr);
flight = Flight(num, flight.getOrigin(), flight.getDestination(),
flight.getDepartureTime(), flight.getDate(),
flight.getPrice(), seats);
}
cout << "Enter new status: ";
getline(cin, status);
if (!status.empty()) flight.setStatus(status);
cout << "Flight updated successfully!\n";
return;
}
}
cout << "Flight not found!\n";
}
void deleteFlight(vector<Flight>& flights) {
string num;
cout << "Enter flight number to delete: ";
getline(cin, num);
auto it = remove_if(flights.begin(), flights.end(),
[&num](const Flight& flight) {
return flight.getFlightNumber() == num;
});
if (it != flights.end()) {
flights.erase(it, flights.end());
cout << "Flight deleted successfully!\n";
} else {
cout << "Flight not found!\n";
}
}
void viewAllBookings(const vector<Passenger>& passengers, const vector<Flight>& flights) {
cout << "\nAll Bookings:\n";
if (passengers.empty()) {
cout << "No passengers have made bookings yet.\n";
return;
}
for (const auto& passenger : passengers) {
cout << "\nPassenger: " << passenger.getName() << " (" << passenger.getEmail() <<
")\n";
// In a real system, we'd have proper access to bookings
// For this example, we'll simulate it
cout << "Bookings: [Simulated booking data]\n";
}
}
void adminMenu(vector<Flight>& flights, const vector<Passenger>& passengers) {
while (true) {
cout << "\n===== ADMIN MENU =====\n";
cout << "1. Add Flight\n";
cout << "2. Edit Flight\n";
cout << "3. Delete Flight\n";
cout << "4. View All Bookings\n";
cout << "5. Search Flights\n";
cout << "6. Logout\n";
cout << "Enter your choice: ";
int choice;
cin >> choice;
cin.ignore();
switch (choice) {
case 1: addFlight(flights); break;
case 2: editFlight(flights); break;
case 3: deleteFlight(flights); break;
case 4: viewAllBookings(passengers, flights); break;
case 5: {
string destination, date;
cout << "Enter destination (leave empty for all): ";
getline(cin, destination);
cout << "Enter date (YYYY-MM-DD, leave empty for all): ";
getline(cin, date);
searchFlights(flights, destination, date);
break;
}
case 6:
cout << "Logging out...\n";
return;
default:
cout << "Invalid choice! Please try again.\n";
}
}
}
};
class Staff : public User {
public:
Staff(string id, string name, string email, string password)
: User(id, name, email, password) {}
void viewPassengerList(const vector<Passenger>& passengers) {
cout << "\nPassenger List:\n";
if (passengers.empty()) {
cout << "No passengers registered.\n";
return;
}
for (const auto& passenger : passengers) {
cout << "- " << passenger.getName() << " (" << passenger.getEmail() << ")\n";
}
}
void confirmCheckIn(Passenger& passenger, Flight& flight) {
cout << "Check-in confirmed for " << passenger.getName()
<< " on Flight " << flight.getFlightNumber() << endl;
flight.setStatus("Boarding");
}
void updateFlightStatus(Flight& flight) {
cout << "\nCurrent status: " << flight.getStatus() << endl;
cout << "Enter new status (e.g., On Time, Delayed, Boarding, Cancelled): ";
string status;
getline(cin, status);
flight.setStatus(status);
cout << "Flight status updated to: " << status << endl;
}
void staffMenu(vector<Flight>& flights, vector<Passenger>& passengers) {
while (true) {
cout << "\n===== STAFF MENU =====\n";
cout << "1. View Passenger List\n";
cout << "2. Confirm Check-In\n";
cout << "3. Update Flight Status\n";
cout << "4. Search Flights\n";
cout << "5. Logout\n";
cout << "Enter your choice: ";
int choice;
cin >> choice;
cin.ignore();
switch (choice) {
case 1: viewPassengerList(passengers); break;
case 2: {
string email, flightNum;
cout << "Enter passenger email: ";
getline(cin, email);
cout << "Enter flight number: ";
getline(cin, flightNum);
Passenger* passengerPtr = nullptr;
Flight* flightPtr = nullptr;
for (auto& passenger : passengers) {
if (passenger.getEmail() == email) {
passengerPtr = &passenger;
break;
}
}
for (auto& flight : flights) {
if (flight.getFlightNumber() == flightNum) {
flightPtr = &flight;
break;
}
}
if (passengerPtr && flightPtr) {
confirmCheckIn(*passengerPtr, *flightPtr);
} else {
cout << "Passenger or flight not found!\n";
}
break;
}
case 3: {
string flightNum;
cout << "Enter flight number: ";
getline(cin, flightNum);
bool found = false;
for (auto& flight : flights) {
if (flight.getFlightNumber() == flightNum) {
updateFlightStatus(flight);
found = true;
break;
}
}
if (!found) {
cout << "Flight not found!\n";
}
break;
}
case 4: {
string destination, date;
cout << "Enter destination (leave empty for all): ";
getline(cin, destination);
cout << "Enter date (YYYY-MM-DD, leave empty for all): ";
getline(cin, date);
searchFlights(flights, destination, date);
break;
}
case 5:
cout << "Logging out...\n";
return;
default:
cout << "Invalid choice! Please try again.\n";
}
}
}
};
void displayMainMenu() {
cout << "\n===== AIRLINE RESERVATION SYSTEM =====\n";
cout << "1. Login as Admin\n";
cout << "2. Login as Staff\n";
cout << "3. Login as Passenger\n";
cout << "4. Register as Passenger\n";
cout << "5. View Flights (Guest)\n";
cout << "6. Exit\n";
cout << "Enter your choice: ";
}
int main() {
vector<Flight> flights = {
Flight("AA111", "New York", "London", "10:00", "2023-12-01", 499.99, 150),
Flight("BB111", "London", "Paris", "14:30", "2023-12-02", 199.99, 200),
Flight("CC111", "Berlin", "Rome", "08:15", "2023-12-03", 249.99, 100)
};
vector<Passenger> passengers;
vector<Admin> admins = {Admin("admin1", "Admin", "admin@gmail.com", "password")};
vector<Staff> staffMembers = {Staff("staff1", "Staff", "staff@gmail.com", "password")};
User* currentUser = nullptr;
string userRole;
while (true) {
displayMainMenu();
int choice;
cin >> choice;
cin.ignore();
switch (choice) {
case 1: { // Admin login
string email, password;
cout << "\nAdmin Login\n";
cout << "Email: ";
getline(cin, email);
cout << "Password: ";
getline(cin, password);
bool loggedIn = false;
for (auto& admin : admins) {
if (admin.login(email, password)) {
currentUser = &admin;
userRole = "Admin";
loggedIn = true;
cout << "\nLogin successful! Welcome, " << admin.getName() << "!\n";
dynamic_cast<Admin*>(currentUser)->adminMenu(flights, passengers);
break;
}
}
if (!loggedIn) {
cout << "\nInvalid admin credentials!\n";
}
break;
}
case 2: { // Staff login
string email, password;
cout << "\nStaff Login\n";
cout << "Email: ";
getline(cin, email);
cout << "Password: ";
getline(cin, password);
bool loggedIn = false;
for (auto& staff : staffMembers) {
if (staff.login(email, password)) {
currentUser = &staff;
userRole = "Staff";
loggedIn = true;
cout << "\nLogin successful! Welcome, " << staff.getName() << "!\n";
dynamic_cast<Staff*>(currentUser)->staffMenu(flights, passengers);
break;
}
}
if (!loggedIn) {
cout << "\nInvalid staff credentials!\n";
}
break;
}
case 3: { // Passenger login
string email, password;
cout << "\nPassenger Login\n";
cout << "Email: ";
getline(cin, email);
cout << "Password: ";
getline(cin, password);
bool loggedIn = false;
for (auto& passenger : passengers) {
if (passenger.login(email, password)) {
currentUser = &passenger;
userRole = "Passenger";
loggedIn = true;
