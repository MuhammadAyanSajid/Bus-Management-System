# Build and Run Script for Bus Management System
# PowerShell Script

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "   Building Bus Management System      " -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

# Create directories if they don't exist
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
    Write-Host "Created build directory" -ForegroundColor Green
}

if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
    Write-Host "Created bin directory" -ForegroundColor Green
}

# Compile all source files
Write-Host "`nCompiling source files..." -ForegroundColor Yellow

$sourceFiles = @(
    "src/Bus.cpp",
    "src/Driver.cpp",
    "src/Route.cpp",
    "src/Schedule.cpp",
    "src/User.cpp",
    "src/DataLoader.cpp",
    "src/DataSaver.cpp",
    "src/DisplayManager.cpp",
    "src/LoginManager.cpp",
    "src/RouteManager.cpp",
    "src/BusManager.cpp",
    "src/DriverManager.cpp",
    "src/ScheduleManager.cpp",
    "src/AdminDashboard.cpp",
    "src/DriverDashboard.cpp",
    "src/PassengerMenu.cpp",
    "src/main.cpp"
)

$objectFiles = @()

foreach ($sourceFile in $sourceFiles) {
    $objectFile = "build/" + [System.IO.Path]::GetFileNameWithoutExtension($sourceFile) + ".o"
    $objectFiles += $objectFile
    
    Write-Host "  Compiling $sourceFile..." -ForegroundColor Gray
    g++ -std=c++17 -Wall -Iinclude -c $sourceFile -o $objectFile
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "`nCompilation failed for $sourceFile" -ForegroundColor Red
        exit 1
    }
}

# Link object files
Write-Host "`nLinking object files..." -ForegroundColor Yellow
g++ -std=c++17 -Wall $objectFiles -o "bin/BusManagementSystem.exe"

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nLinking failed" -ForegroundColor Red
    exit 1
}

Write-Host "`nBuild completed successfully!" -ForegroundColor Green
Write-Host "Executable: bin/BusManagementSystem.exe`n" -ForegroundColor Green

# Ask if user wants to run the program
$response = Read-Host "Do you want to run the program now? (Y/N)"
if ($response -eq 'Y' -or $response -eq 'y') {
    Write-Host "`n========================================" -ForegroundColor Cyan
    Write-Host "   Running Bus Management System       " -ForegroundColor Cyan
    Write-Host "========================================`n" -ForegroundColor Cyan
    & "bin/BusManagementSystem.exe"
}
