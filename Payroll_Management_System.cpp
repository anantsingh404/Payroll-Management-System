#include <iostream>    // Modern equivalent of iostream.h
#include <fstream>     // Modern file stream handling
#include <string>      // For using std::string instead of char arrays
#include <iomanip>     // For setting the output format
#include <thread>      // For using modern sleep functions
#include <chrono>      // For using std::chrono for delays
#include <cstdlib>     // For system() function and exit()
using namespace std;

// Struct to store employee details
struct Employee {
    string name, designation;
    int code;
    float salary, tax, hra, gross, da, netPay;
};

fstream payFile;   // File stream to handle employee data
char choice;

void delay(int milliseconds) {
    // Modern C++ way to implement delay using sleep_for()
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Function to clear the console screen (Windows-specific)
void clearScreen() {
    // Use system() to clear the console based on OS
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/Unix
    #endif
}

// Function to display the developer information with delay effect
void dev() {
    clearScreen();
    
        cout << "P R O J E C T   " << endl;
        cout<<"D E V E L O P E D  B Y  :  " << endl;
        cout  << "ANANT VIKRAM SINGH" << endl;
    cout << "PRESS ANY KEY TO CONTINUE";
    cin.get();  
}

// Function to display the menu
void displayMenu() {
    clearScreen();
    cout << "\n* MENU *" << endl;
    cout << "1. REPORT" << endl;
    cout << "2. PAY SLIP" << endl;
    cout << "3. ADD" << endl;
    cout << "4. EXIT" << endl;
    cout << "ENTER YOUR CHOICE (1, 2, 3, 4): ";
    cin >> choice;
}

// Function to generate report for all employees
void generateReport() {
    clearScreen();
    cout << setw(10) << "CODE" << setw(20) << "NAME" << setw(20) << "POST" << setw(15) << "BASIC"
         << setw(15) << "GROSS PAY" << setw(15) << "DEDUCTION" << setw(15) << "NET PAY" << endl;
    cout << string(100, '-') << endl;

    payFile.open("employee.dat", ios::in);
    if (!payFile) {
        cout << "\nFile Not Found... Program Terminated!" << endl;
        exit(0);
    }

    Employee emp;
    while (payFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        cout << setw(10) << emp.code << setw(20) << emp.name << setw(20) << emp.designation
             << setw(15) << emp.salary << setw(15) << emp.gross << setw(15) << emp.tax
             << setw(15) << emp.netPay << endl;
    }

    payFile.close();
    cin.get();  // Pause for user input
}

// Function to generate pay slip for a specific employee
void generatePaySlip() {
    clearScreen();
    int searchCode, flag = 0;
    cout << "\nEnter employee number to search: ";
    cin >> searchCode;

    payFile.open("employee.dat", ios::in);
    if (!payFile) {
        cout << "\nFile Not Found... Program Terminated!" << endl;
        exit(0);
    }

    Employee emp;
    while (payFile.read(reinterpret_cast<char*>(&emp), sizeof(emp))) {
        if (emp.code == searchCode) {
            cout << "\n*********************************************" << endl;
            cout << "         PAYROLL SYSTEM        " << endl;
            cout << "*********************************************" << endl;
            cout << "EMPLOYEE CODE                : " << emp.code << endl;
            cout << "NAME OF EMPLOYEE             : " << emp.name << endl;
            cout << "EMPLOYEE DESIGNATION         : " << emp.designation << endl;
            cout << "BASIC SALARY                 : " << emp.salary << endl;
            cout << "DEARNESS ALLOWANCE           : " << emp.da << endl;
            cout << "HOUSE RENT ALLOWANCE         : " << emp.hra << endl;
            cout << "GROSS PAY                    : " << emp.gross << endl;
            cout << "TAX                          : " << emp.tax << endl;
            cout << "NET PAY                      : " << emp.netPay << endl;
            cout << "*********************************************" << endl;
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        cout << "\nNo such employee found." << endl;
    }

    payFile.close();
    cin.get();  // Pause for user input
}

// Function to add a new employee
void addEmployee() {
    Employee emp;
    char continueAdding;

    payFile.open("employee.dat", ios::out | ios::app);
    if (!payFile) {
        cout << "\nFile Not Found... Program Terminated!" << endl;
        exit(0);
    }

    do {
        clearScreen();
        cout << "\nEnter Employee Name: ";
        cin >> emp.name;
        cout << "Enter Employee Code: ";
        cin >> emp.code;

        int designationChoice;
        cout << "Enter Employee Designation:" << endl;
        cout << "1. SUBSTAFF" << endl;
        cout << "2. CLERK" << endl;
        cout << "3. MANAGER" << endl;
        cout << "Enter your choice (1/2/3): ";
        cin >> designationChoice;

        switch (designationChoice) {
            case 1:
                emp.salary = 1000;
                emp.hra = 100;
                emp.da = emp.salary * 0.10;
                emp.tax = emp.salary * 0.02;
                emp.designation = "SUBSTAFF";
                break;
            case 2:
                emp.salary = 2000;
                emp.hra = 200;
                emp.da = 200;
                emp.tax = emp.salary * 0.10;
                emp.designation = "CLERK";
                break;
            case 3:
                emp.salary = 14000;
                emp.hra = 400;
                emp.da = 400;
                emp.tax = emp.salary * 0.20;
                emp.designation = "MANAGER";
                break;
            default:
                cout << "Invalid input, setting default salary for SUBSTAFF." << endl;
                emp.salary = 1000;
                emp.hra = 100;
                emp.da = emp.salary * 0.10;
                emp.tax = emp.salary * 0.02;
                emp.designation = "SUBSTAFF";
                break;
        }

        emp.gross = emp.salary + emp.hra + emp.da;
        emp.netPay = emp.gross - emp.tax;
        payFile.write(reinterpret_cast<char*>(&emp), sizeof(emp));

        cout << "\nContinue adding employees? (Y/N): ";
        cin >> continueAdding;

    } while (continueAdding == 'Y' || continueAdding == 'y');

    payFile.close();
}

int main() {
    dev();

    do {
        displayMenu();

        switch (choice) {
            case '1':
                generateReport();
                break;
            case '2':
                generatePaySlip();
                break;
            case '3':
                addEmployee();
                break;
            case '4':
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice, please try again!" << endl;
                break;
        }
    } while (choice != '4');

    return 0;
}
