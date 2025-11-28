# Criminal Management System - Modular Structure

A modular C program implementing a menu-driven criminal database management system with network analysis capabilities, organized into separate header and source files for better maintainability.

## 📁 Project Structure

```
DSAPROJECT/
├── main.c                    # Main driver program
├── criminal.h               # Criminal module header
├── criminal.c               # Criminal module implementation
├── case.h                   # Case module header
├── case.c                   # Case module implementation
├── graph.h                  # Graph module header
├── graph.c                  # Graph module implementation
├── history.h                # History module header
├── history.c                # History module implementation
├── Makefile                 # Build configuration
├── README_MODULAR.md        # This file
└── criminal_management_system.c  # Original monolithic file
```

## 🧩 Module Breakdown

### 1. **Criminal Module** (`criminal.h` & `criminal.c`)
- **Purpose**: Manages criminal records with full CRUD operations
- **Key Functions**:
  - `addCriminal()` - Add new criminal records
  - `displayCriminals()` - Show all criminals
  - `searchCriminal()` - Find criminals by ID
  - `updateCriminal()` - Modify criminal information
  - `deleteCriminal()` - Remove criminal records
  - `criminalMenu()` - Criminal management interface

### 2. **Case Module** (`case.h` & `case.c`)
- **Purpose**: Manages case records and priority filtering
- **Key Functions**:
  - `addCase()` - Create new cases
  - `displayCases()` - Show all cases
  - `displayUrgentCases()` - Filter urgent cases
  - `caseMenu()` - Case management interface

### 3. **Graph Module** (`graph.h` & `graph.c`)
- **Purpose**: Manages criminal network connections
- **Key Functions**:
  - `initGraph()` - Initialize network structure
  - `addConnection()` - Create criminal connections
  - `displayNetwork()` - Visualize network
  - `networkMenu()` - Network management interface

### 4. **History Module** (`history.h` & `history.c`)
- **Purpose**: Tracks all system actions using stack
- **Key Functions**:
  - `initHistory()` - Initialize history stack
  - `addHistoryAction()` - Log user actions
  - `displayHistory()` - Show action log

### 5. **Main Driver** (`main.c`)
- **Purpose**: Program entry point and main menu
- **Key Functions**:
  - `main()` - Initialize systems and start program
  - `mainMenu()` - Main navigation interface

## 🔧 Compilation and Usage

### Build the Program
```bash
# Clean previous builds
make clean

# Compile all modules
make

# Compile and run
make run
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -o criminal_management_system main.c criminal.c case.c graph.c history.c
```

## 📊 Data Structures

### Criminal Structure
```c
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char crime[MAX_CRIME_LEN];
    char status[20];
} Criminal;
```

### Case Structure
```c
typedef struct {
    int case_id;
    char title[MAX_CASE_TITLE_LEN];
    char description[200];
    int criminal_id;
    int priority;
    char status[20];
} Case;
```

### Graph Structure
```c
typedef struct {
    Connection connections[MAX_CONNECTIONS];
    int num_connections;
} Graph;
```

### History Stack Structure
```c
typedef struct {
    HistoryAction actions[MAX_HISTORY];
    int top;
} HistoryStack;
```

## 🎯 Module Dependencies

```
main.c
├── criminal.h (→ history.h)
├── case.h (→ history.h)
├── graph.h (→ history.h)
└── history.h
```

## ✨ Features by Module

### Criminal Module Features
- ✅ Add/Delete/Update/Search criminals
- ✅ Input validation and duplicate checking
- ✅ Formatted display of criminal records
- ✅ Automatic history logging

### Case Module Features
- ✅ Create and manage cases
- ✅ Priority-based filtering (urgent cases)
- ✅ Case-criminal association
- ✅ Comprehensive case display

### Graph Module Features
- ✅ Bi-directional criminal connections
- ✅ Network visualization
- ✅ Connection management
- ✅ Maximum connection limits

### History Module Features
- ✅ Stack-based action logging
- ✅ Chronological history display
- ✅ Automatic action tracking
- ✅ Memory-efficient storage

## 🚀 Advantages of Modular Design

1. **Maintainability**: Each module can be modified independently
2. **Readability**: Clear separation of concerns
3. **Reusability**: Modules can be reused in other projects
4. **Testing**: Individual modules can be tested separately
5. **Collaboration**: Multiple developers can work on different modules
6. **Scalability**: Easy to add new features or modules

## 🔄 Development Workflow

1. **Add New Feature**: Create new module files or extend existing ones
2. **Update Headers**: Modify `.h` files to expose new functions
3. **Implement Logic**: Write implementation in `.c` files
4. **Update Dependencies**: Modify Makefile if needed
5. **Test**: Compile and test the complete system

## 📝 Adding New Modules

To add a new module (e.g., `report.h` and `report.c`):

1. Create `report.h` with function prototypes and structures
2. Create `report.c` with implementations
3. Include `report.h` in `main.c`
4. Add `report.c` to Makefile SOURCES
5. Update dependencies in Makefile

## 🎮 Usage Example

```bash
$ ./criminal_management_system

=== CRIMINAL MANAGEMENT SYSTEM ===
Welcome to the Criminal Database Management System

=== MAIN MENU ===
1. Criminal Management
2. Case Management
3. Criminal Network
4. View Action History
5. Exit
Enter your choice: 1

=== CRIMINAL MANAGEMENT ===
1. Add Criminal
2. Display All Criminals
3. Search Criminal
4. Update Criminal
5. Delete Criminal
6. Back to Main Menu
Enter your choice: 1
```

This modular structure provides a clean, maintainable, and scalable foundation for the criminal management system.
