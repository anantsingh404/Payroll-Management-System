# Payroll Management System

A simple payroll management system written in modern C++. This project stores employee details, generates reports, and computes salary components like allowances and deductions. It also allows users to add new employees and search for specific employees to generate their pay slips.

## Features

- **Employee Report Generation**: Displays a list of employees with details like code, name, designation, salary, and net pay.
- **Pay Slip Generation**: Generates a detailed pay slip for a specific employee.
- **Add New Employee**: Allows adding new employee records to the system.
- **Salary Calculations**: Calculates various components such as gross pay, tax deductions, and net pay.

## Technologies Used

- **C++**: Core programming language used.
- **File Handling**: Employee data is stored and retrieved using file streams (`fstream`).
- **Console Application**: A simple console-based user interface using modern C++ standard libraries.

## Prerequisites

- A modern C++ compiler like `g++` (with C++11 or later).
- Console access (for command-line execution).
- Supported operating systems: Windows, Linux, macOS.

## Setup and Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/payroll-management-system.git
   cd payroll-management-system
   g++ -std=c++11 payroll.cpp -o payroll
   ./payroll

