# Criminal Management System

A comprehensive C program implementing a menu-driven criminal database management system with network analysis capabilities.

## Completed Features

### 1. Criminal Module (CRUD Operations)
- **Create**: Add new criminal records with ID, name, age, crime, and status
- **Read**: Display all criminals and search by ID
- **Update**: Modify existing criminal information
- **Delete**: Remove criminal records

### 2. Case Module
- **Add Case**: Create new cases with title, description, associated criminal ID, priority, and status
- **Display Cases**: View all cases in a formatted table
- **Urgent Cases**: Filter and display only high-priority cases

### 3. Criminal Network Graph
- **Initialize Graph**: Set up the criminal network structure
- **Add Connections**: Create bi-directional relationships between criminals
- **Network Visualization**: Display the complete network structure

### 4. Action History Logging
- **Stack-based History**: Track all major system actions
- **History Display**: View chronological log of all operations
- **Automatic Logging**: System automatically logs user actions

## How to Compile and Run

### Method 1: Using Makefile
```bash
make
./criminal_management_system
```

### Method 2: Direct compilation
```bash
gcc -Wall -Wextra -std=c99 -o criminal_management_system criminal_management_system.c
./criminal_management_system
```

### Method 3: Using Makefile with run target
```bash
make run
```

## Program Structure

The program features a hierarchical menu system:

### Main Menu
1. **Criminal Management** - Access CRUD operations for criminals
2. **Case Management** - Manage cases and view urgent cases
3. **Criminal Network** - View and manage criminal connections
4. **View Action History** - See all logged system actions
5. **Exit** - Close the program

### Criminal Management Submenu
1. Add Criminal
2. Display All Criminals
3. Search Criminal
4. Update Criminal
5. Delete Criminal
6. Back to Main Menu

### Case Management Submenu
1. Add Case
2. Display All Cases
3. Display Urgent Cases
4. Back to Main Menu

### Criminal Network Submenu
1. Display Network
2. Add Connection
3. Back to Main Menu

## Data Structures Used

- **Arrays**: For storing criminals, cases, and connections
- **Structures**: Criminal, Case, Connection, Graph, HistoryAction, HistoryStack
- **Stack**: For implementing action history logging
- **Graph**: For managing criminal network connections

## Features

- **Input Validation**: Checks for duplicate IDs and maximum limits
- **Formatted Output**: Clean, tabular display of data
- **Error Handling**: Graceful handling of invalid inputs
- **History Tracking**: Automatic logging of all user actions
- **Modular Design**: Separate functions for each operation

## Sample Usage

1. Run the program
2. Choose "Criminal Management" to add some criminals
3. Choose "Case Management" to add some cases
4. Choose "Criminal Network" to add connections between criminals
5. Use "View Action History" to see all logged actions

## Clean Up

To remove compiled files:
```bash
make clean
```


