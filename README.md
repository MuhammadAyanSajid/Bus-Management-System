# Bus Management System

## Project Overview
A comprehensive Bus Management System implemented in C++ for managing bus operations, including routes, schedules, drivers, and user authentication.

## Project Structure
```
Bus-Management-System/
├── data/                  # Data files (CSV format)
│   ├── buses.txt
│   ├── drivers.txt
│   ├── routes.txt
│   ├── schedules.txt
│   └── credentials.txt
├── include/              # Header files
│   ├── Bus.h
│   ├── Driver.h
│   ├── Route.h
│   ├── Schedule.h
│   ├── User.h
│   ├── DataLoader.h
│   └── DisplayManager.h
├── src/                  # Source files
│   ├── Bus.cpp
│   ├── Driver.cpp
│   ├── Route.cpp
│   ├── Schedule.cpp
│   ├── User.cpp
│   ├── DataLoader.cpp
│   ├── DisplayManager.cpp
│   └── main.cpp
├── build/                # Compiled object files (generated)
├── bin/                  # Executable files (generated)
├── Makefile             # Build configuration
├── build.ps1            # PowerShell build script
└── README.md            # This file
```

## Sprint 1: Core Data Read (COMPLETED) ✓

### Implemented Features

#### 1. Data Structures (Classes)
- **Bus**: Manages bus information (ID, capacity, model, status)
- **Driver**: Stores driver details (ID, name, contact, license)
- **Route**: Defines routes (ID, origin, destination, stops, travel time)
- **Schedule**: Manages trip schedules (ID, route, bus, driver, date/time)
- **User**: Handles user credentials (username, password, role)

#### 2. Sample Data Files
All data files use CSV format for easy parsing:
- `buses.txt`: Bus fleet information
- `drivers.txt`: Driver registry
- `routes.txt`: Available routes with key stops
- `schedules.txt`: Trip schedules
- `credentials.txt`: User login credentials

#### 3. Data Loading (DataLoader)
Robust file I/O with error handling:
- `loadBuses()`: Loads bus data
- `loadDrivers()`: Loads driver data
- `loadRoutes()`: Loads route data with pipe-separated stops
- `loadSchedules()`: Loads schedule data
- `loadCredentials()`: Loads user credentials
- Error logging for file issues and parsing errors

#### 4. Display System (DisplayManager)
Formatted table display for all entities:
- Organized information display with headers
- Consistent formatting across all data types
- Summary statistics (total counts)

## How to Build and Run

### Prerequisites
- C++ compiler (g++) with C++17 support
- Windows OS with PowerShell

### Building the Project

#### Option 1: Using PowerShell Script (Recommended)
```powershell
.\build.ps1
```
This will:
- Create necessary directories
- Compile all source files
- Link the executable
- Offer to run the program

#### Option 2: Using Makefile (if you have Make installed)
```bash
make all
make run
```

#### Option 3: Manual Compilation
```powershell
# Create directories
New-Item -ItemType Directory -Path build, bin -Force

# Compile
g++ -std=c++17 -Wall -Iinclude -c src/*.cpp
move *.o build/

# Link
g++ -std=c++17 -Wall build/*.o -o bin/BusManagementSystem.exe

# Run
.\bin\BusManagementSystem.exe
```

### Running the Program
After building:
```powershell
.\bin\BusManagementSystem.exe
```

## Data File Format

### buses.txt
```
BusID,Capacity,Model,Status
B001,50,Volvo 9700,Active
```

### drivers.txt
```
DriverID,Name,ContactInfo,LicenseDetails
D101,John Doe,123-456-7890,Class B
```

### routes.txt
```
RouteID,Origin,Destination,KeyStops(pipe-separated),EstimatedTime
R001,Downtown,Airport,Central Station|Mall Plaza|Airport Terminal,90
```

### schedules.txt
```
ScheduleID,RouteID,BusID,DriverID,Date,DepartureTime,ArrivalTime
S001,R001,B001,D101,2025-11-15,08:00,09:30
```

### credentials.txt
```
Username,Password,Role
admin,admin123,Admin
```

## Testing Sprint 1
The current main.cpp tests all Sprint 1 functionality:
1. Loads all data from CSV files
2. Displays comprehensive information for each entity type
3. Shows error handling for file issues
4. Verifies data parsing accuracy

## Upcoming Sprints

### Sprint 2: Admin CRUD & Login (Next)
- Login system with authentication
- Admin dashboard
- CRUD operations for Routes, Buses, Drivers
- Input validation

### Sprint 3: Scheduling & Driver Logic
- CRUD for Trip Schedules
- Overlap detection (bus and driver)
- Driver-specific functionalities
- Driver dashboard

### Sprint 4: Passenger & Reporting
- Passenger menu (no login required)
- Route search functionality
- Operational reports

### Sprint 5: Integration & Testing
- End-to-end testing
- Bug fixes
- Performance optimization

### Sprint 6: Deployment & Finalization
- Final polish
- Documentation
- Deployment preparation

## Development Team
- Team Members: 2024-CS-661, 2024-CS-667, 2024-CS-677

## License
Academic Project - 3rd Semester SE Project

## Notes
- All data is stored in plain text CSV files
- User passwords are stored in plain text (for academic purposes only)
- The system uses string-based time comparison (works for HH:MM format)
- Object-oriented design with clear separation of concerns
