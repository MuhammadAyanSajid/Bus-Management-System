# Input Validation Guide

## Overview
The Bus Management System now includes comprehensive input validation across all user input points to ensure data integrity, prevent errors, and improve user experience.

## Validation Rules

### 1. ID Validation
**Applied to**: Bus ID, Driver ID, Route ID, Schedule ID

**Rules**:
- Must be 1-20 characters long
- Cannot be empty
- Cannot contain spaces
- Alphanumeric characters allowed

**Examples**:
- ✅ Valid: `B001`, `DRIVER_123`, `R-45`, `SCH2025`
- ❌ Invalid: ` ` (empty), `BUS 001` (contains space), `VeryLongIdentifierThatExceedsTwentyCharacters`

### 2. Name/Text Field Validation
**Applied to**: Names, Origins, Destinations, Models, License Details, Key Stops

**Rules**:
- Cannot be empty after trimming whitespace
- Must contain at least one non-whitespace character

**Examples**:
- ✅ Valid: `John Doe`, `Downtown`, `Mercedes-Benz`
- ❌ Invalid: ` ` (empty), `   ` (only whitespace)

### 3. Date Validation
**Applied to**: Schedule dates, Day-off requests

**Format**: `YYYY-MM-DD`

**Rules**:
- Must match format exactly (e.g., `2025-11-16`)
- Year must be between 2000 and 2100
- Month must be between 01 and 12
- Day must be between 01 and 31
- Leading zeros required for single-digit months/days

**Examples**:
- ✅ Valid: `2025-11-16`, `2024-01-05`, `2030-12-31`
- ❌ Invalid: `25-11-16` (wrong format), `2025/11/16` (wrong separator), `2025-13-01` (invalid month), `2025-11-32` (invalid day)

### 4. Time Validation
**Applied to**: Departure time, Arrival time

**Format**: `HH:MM` (24-hour format)

**Rules**:
- Must match format exactly (e.g., `14:30`)
- Hours must be between 00 and 23
- Minutes must be between 00 and 59
- Leading zeros required

**Examples**:
- ✅ Valid: `09:00`, `14:30`, `23:59`, `00:00`
- ❌ Invalid: `9:00` (missing leading zero), `24:00` (invalid hour), `14:60` (invalid minute), `2:30 PM` (12-hour format)

### 5. Time Logic Validation
**Applied to**: Schedule creation

**Rules**:
- Departure time must be before arrival time
- Cannot have same departure and arrival time

**Examples**:
- ✅ Valid: Departure `09:00`, Arrival `12:00`
- ❌ Invalid: Departure `12:00`, Arrival `09:00` (backwards), Departure `10:00`, Arrival `10:00` (same)

### 6. Status Validation
**Applied to**: Bus status

**Valid Values**: `Active`, `Maintenance`, `Inactive` (case-insensitive)

**Examples**:
- ✅ Valid: `Active`, `active`, `ACTIVE`, `Maintenance`, `Inactive`
- ❌ Invalid: `Running`, `Broken`, `Out of Service`, ` ` (empty)

### 7. Contact Information Validation
**Applied to**: Driver contact info updates

**Rules**:
- Cannot be empty
- Must be at least 7 characters long
- Can be phone number or email format

**Examples**:
- ✅ Valid: `+1-555-0123`, `555-123-4567`, `driver@example.com`, `03001234567`
- ❌ Invalid: ` ` (empty), `123` (too short)

### 8. Numeric Validation
**Applied to**: Bus capacity, Route travel time

**Rules**:
- Must be a positive integer (> 0)
- Cannot be zero or negative

**Examples**:
- ✅ Valid: `50`, `120`, `1`, `999`
- ❌ Invalid: `0`, `-10`, `abc` (not a number)

### 9. Location Logic Validation
**Applied to**: Route creation

**Rules**:
- Origin and destination cannot be the same
- Both must be non-empty

**Examples**:
- ✅ Valid: Origin `Downtown`, Destination `Airport`
- ❌ Invalid: Origin `Downtown`, Destination `Downtown` (same location)

### 10. Key Stops Validation
**Applied to**: Route creation

**Rules**:
- Must provide at least one key stop
- Stops are separated by pipe character `|`
- Empty stops are automatically filtered out
- Leading/trailing whitespace is trimmed

**Examples**:
- ✅ Valid: `Central Station|Mall Plaza|Airport Terminal`
- ✅ Valid: `Stop 1 | Stop 2 | Stop 3` (spaces are trimmed)
- ❌ Invalid: ` ` (empty), `  |  |  ` (all empty stops)

## Validation Error Messages

The system provides clear, specific error messages for validation failures:

### ID Errors
```
Error: ID must be 1-20 characters long and cannot be empty.
Error: ID cannot contain spaces.
```

### Empty Field Errors
```
Error: [Field Name] cannot be empty.
```

### Date Errors
```
Error: Date must be in YYYY-MM-DD format (e.g., 2025-11-16).
Error: Month must be between 01 and 12.
Error: Day must be between 01 and 31.
Error: Year must be between 2000 and 2100.
```

### Time Errors
```
Error: Time must be in HH:MM format (e.g., 14:30, 09:00).
Error: Departure time must be before arrival time.
```

### Status Errors
```
Error: Status must be Active, Maintenance, or Inactive.
```

### Contact Errors
```
Error: Contact information cannot be empty.
Error: Contact information seems too short. Please provide valid phone or email.
```

### Numeric Errors
```
Error: [Field Name] must be a positive number.
Error: Capacity cannot be negative.
Error: Travel time cannot be negative.
```

### Logic Errors
```
Error: Origin and Destination cannot be the same.
Error: At least one key stop is required.
```

## Validation Points by Module

### Admin Dashboard
1. **Route Management**
   - Add Route: ID, origin, destination, stops, travel time validation
   - Update Route: Optional field validation, logic checks
   - Remove Route: Confirmation prompt

2. **Bus Management**
   - Add Bus: ID, capacity, model, status validation
   - Update Bus: Optional field validation, status validation
   - Remove Bus: Confirmation prompt

3. **Driver Management**
   - Add Driver: ID, name, contact, license validation
   - Update Driver: Optional field validation, contact validation
   - Remove Driver: Confirmation prompt

4. **Schedule Management**
   - Add Schedule: All ID references, date, time validation, time logic
   - Update Schedule: Optional field validation with format checks
   - Remove Schedule: Confirmation prompt

### Driver Dashboard
1. **Update Contact Info**: Contact validation, non-empty check
2. **Request Day Off**: Date format validation
3. **View Assigned Schedule**: Optional date validation

### Passenger Menu
1. **Search by Origin**: Non-empty validation
2. **Search by Destination**: Non-empty validation
3. **Search by Stop**: Non-empty validation
4. **View Travel Time**: Route ID validation

### Login System
1. **Admin Login**: Username and password cannot be empty
2. **Driver Login**: Username and password cannot be empty

## User Input Loop Patterns

### Pattern 1: Required Field with Validation
```cpp
std::string id;
do {
    id = trim(getInput("Enter ID: "));
} while (!validateId(id));
```

### Pattern 2: Optional Field Update
```cpp
std::string newValue = trim(getInput("Enter new value (or press Enter to keep current): "));
if (!newValue.empty() && !validateField(newValue))
    return; // Exit if invalid
if (!newValue.empty())
    entity->setValue(newValue);
```

### Pattern 3: Numeric Input
```cpp
int value;
do {
    value = getIntInput("Enter value: ");
} while (!validatePositiveInt(value, "Field Name"));
```

## Benefits

### 1. Data Integrity
- Prevents invalid data from entering the system
- Ensures consistent formatting (dates, times)
- Maintains referential integrity

### 2. User Experience
- Clear, specific error messages
- Immediate feedback on invalid input
- Prevents system crashes from bad data

### 3. Security
- Prevents empty credentials
- Validates ID formats to prevent injection
- Trims whitespace to prevent bypass attempts

### 4. Business Logic
- Enforces logical constraints (departure before arrival)
- Prevents duplicate IDs
- Validates references exist before creating relationships

## Testing Validation

To test validation, try these edge cases:

1. **Empty Inputs**: Press Enter without typing anything
2. **Whitespace Only**: Type several spaces and press Enter
3. **Invalid Formats**: 
   - Dates: `2025/11/16`, `16-11-2025`, `25-11-16`
   - Times: `9:00`, `14:60`, `25:00`, `2:30 PM`
4. **Out of Range**: 
   - Negative numbers: `-10`, `0`
   - Invalid dates: `2025-13-01`, `2025-02-31`
5. **Wrong Types**: 
   - Text where numbers expected: `abc` for capacity
   - Numbers where text expected: `123` for name
6. **Logic Violations**:
   - Same origin and destination
   - Departure after arrival
   - Empty key stops list
7. **Boundary Values**:
   - Very long IDs (>20 chars)
   - Very short contact info (<7 chars)
   - Edge times: `00:00`, `23:59`

## Implementation Details

### Helper Functions
All validation functions are implemented as static helpers at the top of each relevant file:

- `trim()`: Removes leading/trailing whitespace
- `validateId()`: Checks ID format and length
- `validateNotEmpty()`: Ensures non-empty after trim
- `validateDate()`: Validates date format and ranges
- `validateTime()`: Validates time format and ranges
- `validateStatus()`: Checks against allowed status values
- `validateContact()`: Ensures contact info is adequate
- `validatePositiveInt()`: Ensures positive numbers

### Regular Expressions Used
- **Date Pattern**: `^\d{4}-\d{2}-\d{2}$`
- **Time Pattern**: `^([0-1]\d|2[0-3]):([0-5]\d)$`

## Future Enhancements

Potential validation improvements:
1. Email format validation (regex for @, domain)
2. Phone number format validation (country-specific)
3. Calendar-aware date validation (check actual days in month)
4. License number format validation
5. Bus model validation against known manufacturers
6. Stop name validation against master list
7. Real-time duplicate checking during input
8. Password strength validation
9. Cross-field validation (e.g., arrival time based on route distance)
10. Input history and auto-completion

---

**Note**: All validation is performed on the client side (in the application). For production systems, server-side or database-level validation should also be implemented as a security measure.
