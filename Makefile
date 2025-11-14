# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Source files
SOURCES = $(SRC_DIR)/Bus.cpp \
          $(SRC_DIR)/Driver.cpp \
          $(SRC_DIR)/Route.cpp \
          $(SRC_DIR)/Schedule.cpp \
          $(SRC_DIR)/User.cpp \
          $(SRC_DIR)/DataLoader.cpp \
          $(SRC_DIR)/DisplayManager.cpp \
          $(SRC_DIR)/main.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Executable name
TARGET = $(BIN_DIR)/BusManagementSystem.exe

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)
	@if not exist "$(BIN_DIR)" mkdir $(BIN_DIR)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo Build complete: $(TARGET)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q $(BUILD_DIR)
	@if exist "$(BIN_DIR)" rmdir /s /q $(BIN_DIR)
	@echo Clean complete

# Run the program
run: all
	@$(TARGET)

.PHONY: all directories clean run
