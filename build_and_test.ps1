# Build and Run Test Suite for Bus Management System

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "   Building Test Suite" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

# Create directories if they don't exist
if (-not (Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

if (-not (Test-Path "bin")) {
    New-Item -ItemType Directory -Path "bin" | Out-Null
}

# Compile all source files needed for testing
Write-Host "Compiling source files..." -ForegroundColor Yellow

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
    "src/SystemTester.cpp",
    "src/test_runner.cpp"
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
g++ -std=c++17 -Wall $objectFiles -o "bin/TestRunner.exe"

if ($LASTEXITCODE -ne 0) {
    Write-Host "`nLinking failed" -ForegroundColor Red
    exit 1
}

Write-Host "`nBuild completed successfully!" -ForegroundColor Green
Write-Host "Test executable: bin/TestRunner.exe`n" -ForegroundColor Green

# Run the tests
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "   Running Test Suite" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

& "bin/TestRunner.exe"

Write-Host "`nPress any key to continue..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")
