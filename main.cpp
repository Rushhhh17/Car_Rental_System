#include <iostream>
#include <mysql.h> // Necessary to establish connection
#include <mysqld_error.h> // Handle MySQL errors

#ifdef _WIN32
#include <windows.h> // For Sleep on Windows
#else
#include <unistd.h> // For sleep on Unix/Linux
#endif

#include <sstream> // For stringstream
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "j@meS1122";
const char* DB = "projectcpp";

// Car class to store car details
class Car {
private:
    string Brand, Model;
    int Serial, Rent;
    bool Avail;

public:
    // Constructor to initialize car details
    Car(int serial, string brand, string model, int rent, bool avail) {
        Serial = serial;
        Brand = brand;
        Model = model;
        Rent = rent;
        Avail = avail;
    }

    // Getter functions to access car details
    int getSerial() { return Serial; }
    string getBrand() { return Brand; }
    string getModel() { return Model; }
    int getRent() { return Rent; }
    bool getAvail() { return Avail; }
};

// Function to check availability of a car from the database
bool isAvail(MYSQL* conn, string toS) {
    string comp = "SELECT Avail FROM car WHERE Serial='" + toS + "'";
    if (mysql_query(conn, comp.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            int availability = atoi(row[0]);
            mysql_free_result(result);
            return (availability == 1); // Return true if car is available
        }
        mysql_free_result(result);
    }

    return false;
}

int main() {
    MYSQL* conn; // Variable for MySQL connection
    conn = mysql_init(NULL); // Initialize MySQL connection

    // Attempt to connect to the database
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl; // Print error if connection fails
    } else {
        cout << "Logged in!!" << endl;
    }

    // Creating car objects with details
    Car car1(123, "Honda", "Civic", 60, true);
    Car car2(223, "Toyota", "Yaris", 50, true);
    Car car3(323, "Suzuki", "Alto", 30, true);
    Car car4(423, "Hyundai", "i20", 45, true);
    Car car5(523, "Tata", "Harris", 80, true);

    // SQL queries to save car data into the database
    string save1 = "INSERT INTO car (Serial, Brand, Model, Rent, Avail) VALUES (123, 'Honda', 'Civic', 60, 1)";
    string save2 = "INSERT INTO car (Serial, Brand, Model, Rent, Avail) VALUES (223, 'Toyota', 'Yaris', 50, 1)";
    string save3 = "INSERT INTO car (Serial, Brand, Model, Rent, Avail) VALUES (323, 'Suzuki', 'Alto', 30, 1)";
    string save4 = "INSERT INTO car (Serial, Brand, Model, Rent, Avail) VALUES (423, 'Hyundai', 'i20', 45, 1)";
    string save5 = "INSERT INTO car (Serial, Brand, Model, Rent, Avail) VALUES (523, 'Tata', 'Harris', 80, 1)";

    // Execute queries to save car data
    if (mysql_query(conn, save1.c_str()) || mysql_query(conn, save2.c_str()) || mysql_query(conn, save3.c_str()) || mysql_query(conn, save4.c_str()) || mysql_query(conn, save5.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl; // Print error if any query fails
    } else {
        cout << "Data saved for cars!" << endl;
    }

    Sleep(5000); // Wait for 5 seconds

    bool exit = false; // Flag to control the loop

    // Main loop
    while (!exit) {
        system("cls"); // Clear screen
        cout << "Welcome to Asmit's Car Gallery" << endl;
        cout << "****************************" << endl;

        // SQL query to retrieve all car data
        string get = "SELECT * FROM car";
        if (mysql_query(conn, get.c_str())) {
            cout << "Error: " << mysql_error(conn) << endl; // Print error if query fails
        } else {
            MYSQL_RES* result = mysql_store_result(conn);
            if (result) {
                int num = mysql_num_fields(result); // Get number of fields
                MYSQL_ROW row;
                // Loop through each row and print car details
                while ((row = mysql_fetch_row(result))) {
                    for (int i = 0; i < num; i++) {
                        cout << " " << row[i];
                    }
                    cout << endl;
                }
                mysql_free_result(result); // Free result set
            }
        }

        int val; // Variable to store user input
        cout << "1. Select Car." << endl;
        cout << "0. Exit." << endl;
        cin >> val;

        // If user selects to rent a car
        if (val == 1) {
            int ser;
            cout << "Enter Serial: " << endl;
            cin >> ser;
            stringstream ss;
            ss << ser;
            string toS = ss.str();

            // Check if car1 matches the serial and is available
            if (car1.getSerial() == ser) {
                if (isAvail(conn, toS)) {
                    string upd = "UPDATE car SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected the following car: " << endl;
                        cout << car1.getBrand() << " " << car1.getModel() << "  $" << car1.getRent() << endl;
                    }
                } else {
                    cout << "Sorry, this car is already booked" << endl;
                }
            }

            // Check if car2 matches the serial and is available
            if (car2.getSerial() == ser) {
                if (isAvail(conn, toS)) {
                    string upd = "UPDATE car SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected the following car: " << endl;
                        cout << car2.getBrand() << " " << car2.getModel() << "  $" << car2.getRent() << endl;
                    }
                } else {
                    cout << "Sorry, this car is already booked" << endl;
                }
            }

            // Check if car3 matches the serial and is available
            if (car3.getSerial() == ser) {
                if (isAvail(conn, toS)) {
                    string upd = "UPDATE car SET Avail ='0' WHERE Serial ='" + toS + "'";
                    if (mysql_query(conn, upd.c_str())) {
                        cout << "Error: " << mysql_error(conn);
                    } else {
                        cout << "You have selected the following car: " << endl;
                        cout << car3.getBrand() << " " << car3.getModel() << "  $" << car3.getRent() << endl;
                    }
                } else {
                    cout << "Sorry, this car is already booked" << endl;
                }
            }

            Sleep(8000); // Wait for 8 seconds
        }

        // If user selects to exit
        else if (val == 0) {
            exit = true;
            cout << "BYE!!" << endl;
            Sleep(2000); // Wait for 2 seconds before exiting
        }
    }

    mysql_close(conn); // Close MySQL connection
    return 0;
}
